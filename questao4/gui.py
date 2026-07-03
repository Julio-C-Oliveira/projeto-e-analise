import sys
import math
from PyQt6.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, 
                             QHBoxLayout, QPushButton, QLabel, QGraphicsView, 
                             QGraphicsScene, QGraphicsEllipseItem, QGraphicsLineItem, QGraphicsItem,
                             QComboBox)
from PyQt6.QtCore import Qt, QPointF, QRectF
from PyQt6.QtGui import QPen, QBrush, QColor, QPolygonF, QFont
from graph import Graph

class NodeItem(QGraphicsEllipseItem):
    def __init__(self, node_id, x, y, radius=15):
        super().__init__(-radius, -radius, 2*radius, 2*radius)
        self.node_id = node_id
        self.radius = radius
        self.setPos(x, y)
        self.setBrush(QBrush(QColor("lightblue")))
        self.setPen(QPen(Qt.GlobalColor.black))
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemIsMovable)
        self.setFlag(QGraphicsItem.GraphicsItemFlag.ItemSendsGeometryChanges)
        self.setZValue(1) # Ensure nodes are drawn above edges
        self.edges = [] # List of EdgeItems connected to this node

    def add_edge(self, edge):
        self.edges.append(edge)

    def itemChange(self, change, value):
        if change == QGraphicsItem.GraphicsItemChange.ItemPositionHasChanged:
            for edge in self.edges:
                edge.update_position()
        return super().itemChange(change, value)

    def set_dfs_color(self, color_name):
        if color_name == "white":
            self.setBrush(QBrush(QColor("lightblue")))
            self.text_color = Qt.GlobalColor.black
        elif color_name == "gray":
            self.setBrush(QBrush(QColor("gray")))
            self.text_color = Qt.GlobalColor.white
        elif color_name == "black":
            self.setBrush(QBrush(QColor("black")))
            self.text_color = Qt.GlobalColor.white
        self.update()

    def paint(self, painter, option, widget=None):
        super().paint(painter, option, widget)
        painter.setFont(QFont("Arial", 10, QFont.Weight.Bold))
        painter.setPen(QPen(getattr(self, "text_color", Qt.GlobalColor.black)))
        painter.drawText(self.boundingRect(), Qt.AlignmentFlag.AlignCenter, str(self.node_id))


class EdgeItem(QGraphicsLineItem):
    def __init__(self, source_node, dest_node):
        super().__init__()
        self.source_node = source_node
        self.dest_node = dest_node
        self.source_node.add_edge(self)
        self.dest_node.add_edge(self)
        self.current_pen = QPen(Qt.GlobalColor.black, 2)
        self.setPen(self.current_pen)
        self.setZValue(0)
        self.update_position()

    def set_dfs_color(self, type_name):
        if type_name == "tree":
            self.current_pen = QPen(Qt.GlobalColor.green, 3)
        elif type_name == "back":
            self.current_pen = QPen(Qt.GlobalColor.red, 3)
        elif type_name == "cross_forward":
            self.current_pen = QPen(Qt.GlobalColor.blue, 3)
        else:
            self.current_pen = QPen(Qt.GlobalColor.black, 2)
        self.setPen(self.current_pen)
        self.update()

    def update_position(self):
        line = self.line()
        line.setP1(self.source_node.scenePos())
        line.setP2(self.dest_node.scenePos())
        self.setLine(line)

    def paint(self, painter, option, widget=None):
        # Draw the line
        super().paint(painter, option, widget)
        
        # Draw the arrowhead
        p1 = self.source_node.scenePos()
        p2 = self.dest_node.scenePos()
        
        # Calculate angle and point at the edge of the destination node
        dx = p2.x() - p1.x()
        dy = p2.y() - p1.y()
        length = math.hypot(dx, dy)
        
        if length == 0:
            return
            
        angle = math.atan2(dy, dx)
        
        # The tip of the arrow should be at the boundary of the destination node
        radius = self.dest_node.radius
        arrow_tip = QPointF(p2.x() - radius * math.cos(angle), 
                            p2.y() - radius * math.sin(angle))
        
        arrow_size = 10
        arrow_p1 = QPointF(arrow_tip.x() - arrow_size * math.cos(angle - math.pi / 6),
                           arrow_tip.y() - arrow_size * math.sin(angle - math.pi / 6))
        arrow_p2 = QPointF(arrow_tip.x() - arrow_size * math.cos(angle + math.pi / 6),
                           arrow_tip.y() - arrow_size * math.sin(angle + math.pi / 6))
        
        arrow_head = QPolygonF([arrow_tip, arrow_p1, arrow_p2])
        painter.setBrush(QBrush(self.current_pen.color()))
        painter.setPen(QPen(self.current_pen.color()))
        painter.drawPolygon(arrow_head)


class GraphScene(QGraphicsScene):
    def __init__(self, parent_panel):
        super().__init__()
        self.parent_panel = parent_panel
        self.graph = Graph()
        self.nodes = []
        self.edges_items = {} # (u, v) -> EdgeItem
        
        self.drawing_edge = False
        self.temp_line = None
        self.source_node_for_edge = None
        self.waiting_for_dfs_start = False

    def reset_colors(self):
        for node in self.nodes:
            node.set_dfs_color("white")
        for edge in self.edges_items.values():
            edge.set_dfs_color("default")

    def load_graph(self, g):
        self.clear()
        self.graph = g
        self.nodes = []
        self.edges_items = {}
        
        V = g.V
        center_x, center_y = 150, 150
        radius = 100
        
        # Draw nodes in a circle
        for i in range(V):
            angle = 2 * math.pi * i / V
            x = center_x + radius * math.cos(angle)
            y = center_y + radius * math.sin(angle)
            node_item = NodeItem(i, x, y)
            self.addItem(node_item)
            self.nodes.append(node_item)
            
        # Draw edges
        for i in range(V):
            for j in g.adj[i]:
                edge_item = EdgeItem(self.nodes[i], self.nodes[j])
                self.addItem(edge_item)
                self.edges_items[(i, j)] = edge_item
                    
        self.parent_panel.cancel_dfs_animation()
        self.parent_panel.update_results()

    def mouseDoubleClickEvent(self, event):
        """Add a new node on double click."""
        self.parent_panel.cancel_dfs_animation()
        new_id = self.graph.V
        self.graph.add_vertex()
        
        x, y = event.scenePos().x(), event.scenePos().y()
        node_item = NodeItem(new_id, x, y)
        self.addItem(node_item)
        self.nodes.append(node_item)
        self.parent_panel.update_results()
        
        super().mouseDoubleClickEvent(event)

    def mousePressEvent(self, event):
        if event.button() == Qt.MouseButton.LeftButton:
            item = self.itemAt(event.scenePos(), self.views()[0].transform())
            if isinstance(item, NodeItem):
                if self.waiting_for_dfs_start:
                    self.waiting_for_dfs_start = False
                    self.parent_panel.start_dfs_animation(item.node_id)
                    return
                # Start drawing edge
                self.drawing_edge = True
                self.source_node_for_edge = item
                self.temp_line = QGraphicsLineItem(QLineF(item.scenePos(), event.scenePos()))
                self.temp_line.setPen(QPen(Qt.GlobalColor.gray, 1, Qt.PenStyle.DashLine))
                self.addItem(self.temp_line)
                
        super().mousePressEvent(event)

    def mouseMoveEvent(self, event):
        if self.drawing_edge and self.temp_line:
            line = self.temp_line.line()
            line.setP2(event.scenePos())
            self.temp_line.setLine(line)
        super().mouseMoveEvent(event)

    def mouseReleaseEvent(self, event):
        if self.drawing_edge:
            self.drawing_edge = False
            if self.temp_line:
                self.removeItem(self.temp_line)
                self.temp_line = None
                
            item = self.itemAt(event.scenePos(), self.views()[0].transform())
            if isinstance(item, NodeItem) and item != self.source_node_for_edge:
                u = self.source_node_for_edge.node_id
                v = item.node_id
                # Check if edge already exists
                if v not in self.graph.adj[u]:
                    self.parent_panel.cancel_dfs_animation()
                    self.graph.add_edge(u, v)
                    edge_item = EdgeItem(self.source_node_for_edge, item)
                    self.addItem(edge_item)
                    self.edges_items[(u, v)] = edge_item
                    self.parent_panel.update_results()
                    
            self.source_node_for_edge = None
            
        super().mouseReleaseEvent(event)


class GraphPanel(QWidget):
    def __init__(self, title):
        super().__init__()
        layout = QVBoxLayout(self)
        
        header_layout = QHBoxLayout()
        self.title_label = QLabel(f"<b>{title}</b>")
        header_layout.addWidget(self.title_label)
        
        self.mode_combo = QComboBox()
        self.mode_combo.addItems([
            "Misto (Aleatório)",
            "Acíclico / Topológico",
            "Fortemente Conexo",
            "Cíclico (Não FC)"
        ])
        header_layout.addWidget(self.mode_combo)
        self.btn_anim_dfs = QPushButton("Animar DFS")
        self.btn_anim_dfs.clicked.connect(self.prepare_dfs_animation)
        header_layout.addWidget(self.btn_anim_dfs)
        
        self.btn_next_step = QPushButton("Próximo Passo")
        self.btn_next_step.clicked.connect(self.next_dfs_step)
        self.btn_next_step.hide()
        header_layout.addWidget(self.btn_next_step)
        
        layout.addLayout(header_layout)
        
        self.scene = GraphScene(self)
        self.scene.setSceneRect(0, 0, 300, 300)
        self.view = QGraphicsView(self.scene)
        self.view.setRenderHint(QPainter.RenderHint.Antialiasing)
        layout.addWidget(self.view)
        
        self.results_label = QLabel("Resultados aparecerão aqui.")
        self.results_label.setWordWrap(True)
        self.results_label.setAlignment(Qt.AlignmentFlag.AlignTop)
        layout.addWidget(self.results_label)
        
        self.dfs_generator = None

    def prepare_dfs_animation(self):
        self.scene.waiting_for_dfs_start = True
        self.btn_anim_dfs.setText("Clique num Nó...")

    def start_dfs_animation(self, start_node):
        self.btn_anim_dfs.setText("Animar DFS")
        self.btn_anim_dfs.hide()
        self.btn_next_step.show()
        self.scene.reset_colors()
        self.dfs_generator = self.scene.graph.dfs_generator(start_node)

    def next_dfs_step(self):
        if not self.dfs_generator: return
        try:
            event = next(self.dfs_generator)
            if event["action"] == "color_node":
                self.scene.nodes[event["node"]].set_dfs_color(event["color"])
            elif event["action"] == "color_edge":
                edge = self.scene.edges_items.get((event["u"], event["v"]))
                if edge: edge.set_dfs_color(event["type"])
        except StopIteration:
            self.cancel_dfs_animation()

    def cancel_dfs_animation(self):
        self.dfs_generator = None
        self.btn_next_step.hide()
        self.btn_anim_dfs.show()
        self.btn_anim_dfs.setText("Animar DFS")
        self.scene.reset_colors()

    def load_random_graph(self):
        mode_idx = self.mode_combo.currentIndex()
        mode = "random"
        if mode_idx == 1: mode = "dag"
        elif mode_idx == 2: mode = "scc"
        elif mode_idx == 3: mode = "cyclic_not_scc"
        
        g = Graph.generate_random(mode)
        self.scene.load_graph(g)

    def update_results(self):
        g = self.scene.graph
        if g.V == 0:
            self.results_label.setText("Grafo Vazio.")
            return

        has_cycle, topo_order, edges_class, discovery_order = g.dfs()
        is_cyclic = has_cycle
        sccs = g.kosaraju_scc()
        
        is_strongly_connected = (len(sccs) == 1 and g.V > 0)
        
        res_text = f"<b>É cíclico?</b> {'Sim' if is_cyclic else 'Não'}<br>"
        
        if not is_cyclic:
            res_text += f"<b>Ordem Topológica:</b> {topo_order}<br>"
        else:
            res_text += f"<b>Ordem Topológica:</b> Não aplicável (tem ciclo)<br>"
            
        res_text += f"<b>Fortemente Conexo?</b> {'Sim' if is_strongly_connected else 'Não'}<br>"
        
        if not is_strongly_connected:
            res_text += f"<b>Nº de CFCs:</b> {len(sccs)}<br>"
            res_text += f"<b>CFCs:</b><br>"
            for i, comp in enumerate(sccs):
                res_text += f"  - CFC {i+1}: {comp}<br>"
                
        res_text += f"<br><b>--- Execução da DFS ---</b><br>"
        res_text += f"<b>Ordem de Descoberta:</b> {discovery_order}<br>"
        res_text += f"<b>Arestas de Árvore:</b> {edges_class['tree']}<br>"
        res_text += f"<b>Arestas de Retorno:</b> {edges_class['back']}<br>"
        res_text += f"<b>Arestas Cruz/Avanço:</b> {edges_class['cross_forward']}<br>"
                
        self.results_label.setText(res_text)

from PyQt6.QtGui import QPainter
from PyQt6.QtCore import QLineF

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Analisador de Grafos (Questão 4)")
        self.resize(1200, 600)
        
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        main_layout = QVBoxLayout(central_widget)
        
        # Instruction Label
        inst_label = QLabel("<b>Instruções:</b> Duplo-clique para adicionar vértice. "
                            "Clique e arraste de um vértice a outro para adicionar aresta (direcionada).")
        main_layout.addWidget(inst_label)

        # Control Panel
        control_layout = QHBoxLayout()
        self.btn_generate = QPushButton("Gerar Novos Grafos Aleatórios")
        self.btn_generate.clicked.connect(self.generate_graphs)
        control_layout.addWidget(self.btn_generate)
        main_layout.addLayout(control_layout)
        
        # Graphs Panel (3 graphs side by side)
        graphs_layout = QHBoxLayout()
        self.panels = []
        for i in range(1, 4):
            panel = GraphPanel(f"Grafo {i}")
            self.panels.append(panel)
            graphs_layout.addWidget(panel)
            
        main_layout.addLayout(graphs_layout)
        
        # Generate initial
        self.generate_graphs()

    def generate_graphs(self):
        for panel in self.panels:
            panel.load_random_graph()

def main():
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
