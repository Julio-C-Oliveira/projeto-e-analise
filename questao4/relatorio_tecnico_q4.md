# Relatório Técnico: Análise de Dígrafos, Ordenação Topológica e Componentes Fortemente Conexos

## 1. Listagem e Caracterização dos Testes

O escopo do problema exige a geração aleatória de três dígrafos (grafos direcionados) simples e não-desconexos (fracamente conexos), contendo entre 5 e 10 vértices. O objetivo principal é responder a três questões centrais sobre cada um desses grafos, o que nos permite analisar as suas propriedades topológicas:
1.  **O dígrafo possui ciclos?**
2.  **Existe uma ordenação topológica possível?** Caso sim, qual é?
3.  **O dígrafo é Fortemente Conexo?** Caso não, quantos e quais são os seus Componentes Fortemente Conexos (CFC)?

Para validar a implementação, as rotinas de geração foram preparadas para construir instâncias distintas que testam diferentes respostas, garantindo a avaliação do comportamento algorítmico em cenários como Grafos Acíclicos Direcionados (DAGs) e grafos contendo ciclos (fortemente conexos ou não). O tamanho reduzido ($5 \le V \le 10$) facilita a verificação visual dos algoritmos, mas o código e a estrutura foram desenvolvidos com generalidade para suportar instâncias maiores assintoticamente.

## 2. Aspectos de Implementação

A escolha da estrutura de dados para representar os grafos influencia de maneira substancial a complexidade temporal das abordagens adotadas.

*   **Representação do Grafo:** Ao contrário de matrizes, a implementação adotou a **Lista de Adjacência**. Essa estrutura foi escolhida pois os algoritmos de busca dependem fundamentalmente de iterar apenas sobre os vizinhos diretos (arestas existentes) e não sobre a totalidade de vértices $V$. A lista de adjacência garante espaço proporcional ao número efetivo de arestas e vértices $\Theta(V + E)$, otimizando drasticamente a exploração e o uso de memória.
*   **Busca em Profundidade (DFS):** A DFS principal foi implementada utilizando a técnica de coloração de vértices (0 = Branco/Não descoberto, 1 = Cinza/Visitando, 2 = Preto/Visitado). Essa mecânica é essencial para:
    *   **Detecção de Ciclos:** Durante a exploração, caso uma aresta aponte para um vértice Cinza, ela é classificada como *Aresta de Retorno* (Back Edge). A existência de pelo menos uma aresta de retorno é condição necessária e suficiente para atestar a presença de um **ciclo** no dígrafo.
    *   **Ordenação Topológica:** Se nenhuma aresta de retorno for encontrada (indicando um DAG), a ordenação topológica é deduzida registrando os vértices no momento em que finalizam sua visita (cor Preto) e, posteriormente, invertendo essa lista de ordem de finalização.
*   **Algoritmo de Kosaraju (CFC):** Para extrair os Componentes Fortemente Conexos, optou-se pela utilização do clássico algoritmo de Kosaraju, que aplica duas etapas de exploração em profundidade:
    1.  A primeira DFS é executada no grafo original para empilhar os vértices por ordem inversa de seu tempo de término.
    2.  Constrói-se então o **Grafo Transposto** $G^T$, onde a direção de todas as arestas do grafo original é invertida.
    3.  Realiza-se uma segunda DFS em $G^T$, processando os vértices na ordem prioritária definida pela pilha obtida no Passo 1. Cada árvore de busca gerada nesta fase isola e corresponde exatamente a um componente fortemente conexo. Se o algoritmo produzir exatamente 1 árvore contendo todos os vértices, o grafo é classificado em sua totalidade como Fortemente Conexo.

## 3. Análise de Complexidade

Os três questionamentos do problema são respondidos por derivações e extensões da Busca em Profundidade (DFS), o que homogeneíza os limites assintóticos do modelo geral:

*   **Detecção de Ciclo (DFS base):** 
    Visita cada vértice $V$ e percorre cada lista de adjacência (explorando cada aresta $E$) exatamente uma vez no pior caso. A complexidade de tempo é garantida em $O(V + E)$.
*   **Ordenação Topológica:**
    Ocorre de maneira simultânea e acoplada à DFS padrão, com operações de tempo constante ($O(1)$) em cada passo da recursão. A inversão estrutural do array de finalização adiciona $O(V)$ de tempo, mantendo a complexidade global da operação dominada pelo limite da DFS, totalizando $O(V + E)$.
*   **Componentes Fortemente Conexos (Kosaraju):**
    A extração dos componentes divide-se em três partes lineares consecutivas:
    1.  Primeira varredura DFS para obtenção do empilhamento de tempos: $O(V + E)$.
    2.  Computação do Grafo Transposto $G^T$: Consiste em inicializar uma nova estrutura vazia e iterar sobre as adjacências originais invertendo os sentidos (adicionando arestas $(v, u)$). Demanda $O(V + E)$ em tempo.
    3.  Segunda varredura DFS sob a ordem da pilha no Grafo Transposto: $O(V + E)$.
    **Geral:** Sendo composta por rotinas somadas que operam na proporção de vértices e arestas, a complexidade final de classificar os CFCs pelo método de Kosaraju detém limite de tempo ótimo de $O(V + E)$, solucionando todas as diretrizes da Questão 4 em tempo estritamente linear, coerente e com mínimo *overhead* de memória atrelado à Lista de Adjacências.
