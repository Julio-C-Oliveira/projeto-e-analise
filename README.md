# Trabalho de Projeto e Análise de Algoritmos (PAA)

Este repositório contém as soluções, implementações e relatórios técnicos desenvolvidos para o trabalho prático da disciplina de Projeto e Análise de Algoritmos (PAA). O projeto aborda problemas clássicos em teoria dos grafos, explorando desde a modelagem matemática até a implementação e análise empírica de complexidade.

## 🗂️ Estrutura do Projeto

O trabalho está dividido em quatro questões principais, cada uma focada em uma aplicação específica de grafos e algoritmos de otimização e busca.

### [Questão 1: Planejamento e Gerenciamento de Projeto](questao1/)
Modelagem de um problema de planejamento de tarefas para a construção de uma casa utilizando **Grafos Direcionados Acíclicos (DAGs)**.
- **Tópicos Abordados:** Problema de Caminho Máximo, Método do Caminho Crítico (CPM / PERT), cálculo de folgas e identificação de tarefas críticas.
- **Arquivos Principais:** Resolução e modelagem detalhada no notebook `questao1.ipynb`.

### [Questão 2: Logística Militar (Segunda Guerra Mundial)](questao2/)
Resolução de um problema de alocação e deslocamento de tropas, considerando distâncias entre aquartelamentos e frentes de combate.
- **Tópicos Abordados:** Algoritmo de **Floyd-Warshall** para obter as distâncias mínimas (todos-para-todos) e modelagem de otimização utilizando **Programação Linear**.
- **Arquivos Principais:** Resolução passo a passo no notebook `questao2.ipynb`.

### [Questão 3: Árvores Geradoras Mínimas (MST) - Kruskal vs Prim](questao3/)
Estudo empírico comparativo do desempenho dos algoritmos de Kruskal e Prim para a construção de Árvores Geradoras Mínimas (MST).
- **Tópicos Abordados:** Implementação em hardware real, uso de estruturas Disjoint-Set (Union-Find) com otimizações, matriz de adjacência e análise teórica vs. prática em cenários de grafos densos e esparsos.
- **Arquivos Principais:** 
  - Códigos-fonte estruturais em `C++`.
  - Resultados e gráficos no notebook `questao3.ipynb`.
  - Discussão aprofundada de complexidade no [relatorio_tecnico_q3.md](questao3/relatorio_tecnico_q3.md).

### [Questão 4: Dígrafos e Componentes Fortemente Conexos](questao4/)
Implementação e análise de grafos direcionados aleatórios para verificação de propriedades topológicas.
- **Tópicos Abordados:** Busca em Profundidade (DFS), verificação de ciclos, **Ordenação Topológica** e extração de Componentes Fortemente Conexos utilizando o Algoritmo de **Kosaraju**.
- **Arquivos Principais:** 
  - Scripts de grafos e interface em `Python` (`graph.py`, `gui.py`).
  - Análise assintótica e teórica no [relatorio_tecnico_q4.md](questao4/relatorio_tecnico_q4.md).

## 🚀 Tecnologias e Ferramentas

- **Python:** Utilizado nos Jupyter Notebooks para análise de dados, modelagem, programação linear e visualização, além da implementação orientada a objetos da Questão 4.
- **C++:** Utilizado na Questão 3 para garantir a máxima performance e controle de memória na análise empírica dos algoritmos Kruskal e Prim.
- **Markdown / Jupyter:** Utilizados para a documentação e entrega dos relatórios técnicos.

## 📖 Como Navegar e Executar

Cada questão é auto-contida em sua respectiva pasta.
- Para as **Questões 1, 2 e 3**, você pode abrir os arquivos `.ipynb` em um ambiente que suporte Jupyter Notebook (como VS Code, JupyterLab ou Google Colab) para visualizar a execução teórica e os gráficos gerados.
- Para a **Questão 3**, os relatórios fornecem o detalhamento do experimento.
- Para a **Questão 4**, os requisitos estão no arquivo `pyproject.toml`. É possível ler as conclusões no `relatorio_tecnico_q4.md`.
