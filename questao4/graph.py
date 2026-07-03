import random

class Graph:
    def __init__(self, vertices=0):
        self.V = vertices
        # Lista de adjacência
        self.adj = [[] for _ in range(self.V)]
    
    def add_edge(self, u, v):
        if 0 <= u < self.V and 0 <= v < self.V and u != v:
            if v not in self.adj[u]:
                self.adj[u].append(v)

    def remove_edge(self, u, v):
         if 0 <= u < self.V and 0 <= v < self.V:
            if v in self.adj[u]:
                self.adj[u].remove(v)

    def add_vertex(self):
        self.V += 1
        self.adj.append([])

    @classmethod
    def generate_random(cls, mode="random"):
        """Gera um dígrafo baseado no modo selecionado."""
        V = random.randint(5, 10)
        g = cls(V)
        nodes = list(range(V))
        random.shuffle(nodes)

        if mode == "dag":
            # Para DAG: ordem topológica garantida, arestas apenas de i para j onde i < j
            for i in range(1, V):
                # Garante que é não-desconexo ligando ao menos a um nó anterior
                u = random.choice(nodes[:i])
                v = nodes[i]
                g.add_edge(u, v)
            extra_edges = random.randint(0, V)
            for _ in range(extra_edges):
                i = random.randint(0, V-2)
                j = random.randint(i+1, V-1)
                g.add_edge(nodes[i], nodes[j])

        elif mode == "scc":
            # Para Fortemente Conexo: cria um ciclo hamiltoniano passando por todos
            for i in range(V):
                g.add_edge(nodes[i], nodes[(i+1)%V])
            extra_edges = random.randint(0, V)
            for _ in range(extra_edges):
                u = random.randint(0, V - 1)
                v = random.randint(0, V - 1)
                if u != v: g.add_edge(u, v)

        elif mode == "cyclic_not_scc":
            # Para Cíclico NÃO FC: cria duas partições A e B. A é cíclico. A->B existe, B->A não.
            size_A = random.randint(2, V-1)
            A = nodes[:size_A]
            B = nodes[size_A:]
            # Ciclo em A
            for i in range(size_A):
                g.add_edge(A[i], A[(i+1)%size_A])
            # Conecta A em B
            g.add_edge(random.choice(A), random.choice(B))
            # Conecta itens em B para não ficarem desconexos
            if len(B) > 1:
                for i in range(len(B)-1):
                    g.add_edge(B[i], B[i+1])
            # Arestas extras que não podem voltar de B para A
            for _ in range(V):
                u = random.choice(nodes)
                v = random.choice(nodes)
                if u in B and v in A: continue
                if u != v: g.add_edge(u, v)

        else: # "random"
            # Garante conectividade fraca com árvore geradora e adiciona extras
            connected = [nodes[0]]
            unconnected = nodes[1:]
            while unconnected:
                u = random.choice(connected)
                v = unconnected.pop()
                if random.random() > 0.5:
                    g.add_edge(u, v)
                else:
                    g.add_edge(v, u)
                connected.append(v)
            extra_edges = random.randint(0, int(V * 1.5))
            for _ in range(extra_edges):
                u = random.randint(0, V - 1)
                v = random.randint(0, V - 1)
                if u != v: g.add_edge(u, v)
                 
        return g

    def dfs(self):
        """
        Executa DFS com cores (0=Branco, 1=Cinza, 2=Preto).
        Retorna (tem_ciclo, ordem_topologica, classificacao_arestas, ordem_descoberta).
        """
        colors = [0] * self.V
        has_cycle = False
        topo_order = []
        discovery_order = []
        
        edges_classification = {
            'tree': [],
            'back': [],
            'cross_forward': []
        }

        def dfs_visit(u):
            nonlocal has_cycle
            colors[u] = 1 # Cinza (visitando)
            discovery_order.append(u)
            
            for v in self.adj[u]:
                if colors[v] == 0:
                    edges_classification['tree'].append((u, v))
                    dfs_visit(v)
                elif colors[v] == 1:
                    edges_classification['back'].append((u, v))
                    has_cycle = True
                elif colors[v] == 2:
                    edges_classification['cross_forward'].append((u, v))
                        
            colors[u] = 2 # Preto (visitado)
            topo_order.append(u)

        for i in range(self.V):
            if colors[i] == 0:
                dfs_visit(i)
                
        # Para ordenação topológica via DFS, invertemos a ordem de finalização
        topo_order.reverse()
        
        return has_cycle, topo_order, edges_classification, discovery_order

    def dfs_generator(self, start_node=0):
        """
        Retorna um gerador para animar a DFS passo a passo.
        Yields eventos: dict com a ação tomada.
        """
        colors = [0] * self.V

        def dfs_visit(u):
            colors[u] = 1 # Cinza (visitando)
            yield {"action": "color_node", "node": u, "color": "gray"}
            
            for v in self.adj[u]:
                if colors[v] == 0:
                    yield {"action": "color_edge", "u": u, "v": v, "type": "tree"}
                    yield from dfs_visit(v)
                elif colors[v] == 1:
                    yield {"action": "color_edge", "u": u, "v": v, "type": "back"}
                elif colors[v] == 2:
                    yield {"action": "color_edge", "u": u, "v": v, "type": "cross_forward"}
                        
            colors[u] = 2 # Preto (visitado)
            yield {"action": "color_node", "node": u, "color": "black"}

        if start_node < self.V:
            yield from dfs_visit(start_node)
        
        for i in range(self.V):
            if colors[i] == 0:
                yield from dfs_visit(i)

    def is_cyclic(self):
        has_cycle, _, _, _ = self.dfs()
        return has_cycle
        
    def topological_sort(self):
        has_cycle, topo_order, _, _ = self.dfs()
        if has_cycle:
            return None # Não há ordem topológica para grafos com ciclos
        return topo_order

    def get_transpose(self):
        g_t = Graph(self.V)
        for i in range(self.V):
            for j in self.adj[i]:
                g_t.add_edge(j, i)
        return g_t

    def kosaraju_scc(self):
        """
        Algoritmo de Kosaraju para Componentes Fortemente Conexos.
        Retorna uma lista de listas, onde cada sublista é um CFC.
        """
        # Passo 1: DFS no grafo original para obter ordem de finalização
        colors = [0] * self.V
        stack = []
        
        def dfs_visit1(u):
            colors[u] = 1
            for v in self.adj[u]:
                if colors[v] == 0:
                    dfs_visit1(v)
            colors[u] = 2
            stack.append(u)
            
        for i in range(self.V):
            if colors[i] == 0:
                dfs_visit1(i)
                
        # Passo 2: Transpor o grafo
        g_t = self.get_transpose()
        
        # Passo 3: DFS no grafo transposto processando na ordem inversa (do stack)
        colors2 = [0] * self.V
        sccs = []
        
        def dfs_visit2(u, current_scc):
            colors2[u] = 1
            current_scc.append(u)
            for v in g_t.adj[u]:
                if colors2[v] == 0:
                    dfs_visit2(v, current_scc)
            colors2[u] = 2

        while stack:
            u = stack.pop()
            if colors2[u] == 0:
                current_scc = []
                dfs_visit2(u, current_scc)
                sccs.append(current_scc)
                
        return sccs
