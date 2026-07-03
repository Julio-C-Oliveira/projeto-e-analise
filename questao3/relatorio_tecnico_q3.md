# Relatório Técnico: Comparativo entre Kruskal e Prim para Árvore Geradora Mínima (MST)

## 1. Listagem e Caracterização dos Testes

Para realizar um estudo empírico do desempenho dos algoritmos na construção da Árvore Geradora Mínima (MST), os experimentos abrangeram diferentes cenários e instâncias de grafos:

* **Tamanho dos Grafos (Número de Vértices - $V$):** Os grafos foram gerados variando sistematicamente o número de vértices, contemplando instâncias em diferentes ordens de grandeza, com o objetivo de observar o crescimento do tempo de execução à medida que o tamanho da entrada escala assintoticamente.
* **Densidade do Grafo:**
  * **Grafos Esparsos:** Utilizou-se uma probabilidade de conexão $p = O(\frac{1}{V^2})$. Sendo assim, o número esperado de arestas aleatórias manteve-se mínimo, sendo somado a um caminho de comprimento $V-1$ adicionado preliminarmente para garantir a conectividade. Portanto, o número total de arestas $E$ cresce linearmente em relação aos vértices, ou seja, $E = O(V)$.
  * **Grafos Densos:** Utilizou-se uma probabilidade de conexão fixa e constante ($p = 0.5$). Dessa forma, a proporção das possíveis conexões entre vértices foi preenchida de forma escalar, resultando em um número de arestas $E = O(V^2)$.
* **Variação por Sementes (Seeds):** A massa de dados contém diferentes sementes (seeds) para a mesma combinação de vértices e densidade. A análise do comportamento assintótico médio reduz eventuais ruídos e anomalias estatísticas oriundas de uma topologia isolada de pior ou melhor caso, consolidando os padrões de desempenho.

## 2. Aspectos de Implementação

A escolha das estruturas de suporte e de representação teve grande influência sobre o limite assintótico e o estudo:

* **Representação dos Grafos:** O algoritmo gerador optou por modelar os grafos estritamente através de uma **Matriz de Adjacência**. Essa decisão exige um acesso e espaço na ordem de $O(V^2)$ para qualquer operação inicial, independentemente da densidade do grafo. Isso influenciou as implementações da seguinte forma:
  * **Kruskal:** No passo de inicialização, é forçado a realizar a varredura da matriz para extrair as arestas existentes, o que estabelece um limite de tempo estrito mínimo de $O(V^2)$, para só então usar a lista de arestas na ordenação e processamento.
  * **Prim:** Consegue iterar sobre as adjacências simplesmente percorrendo a matriz linha a linha.
* **Estruturas de Suporte (Algoritmo de Kruskal):**
  * Para realizar a verificação de ciclos de forma otimizada, adotou-se a estrutura **Disjoint-Set (Union-Find)**. Sua implementação inclui as otimizações de *Path Compression* e *Union by Rank*, fazendo com que as operações de localização do representante de um conjunto e de união ocorram em tempo praticamente constante: $O(\alpha(V))$, em que $\alpha$ é a função inversa de Ackermann de crescimento extremamente lento.
* **Estruturas de Suporte (Algoritmo de Prim):**
  * Devido à modelagem ser uma **Matriz de Adjacência**, o algoritmo não fez uso de um **Heap Binário** ou *Priority Queue* externa. Empregou apenas arranjos para as variáveis de `parent`, `key` e conjuntos de estado na MST.
  * **Justificativa para a decisão sem Heap:** Para encontrar o vértice válido de menor peso a cada iteração, optou-se por uma busca linear em vez do uso do Heap. Como a matriz de adjacência forçaria o tempo geral para $O(V^2)$ em grafos densos de qualquer forma, a implementação tradicional em arranjos elimina o alto *overhead* (constantes ocultas maiores e gerenciamento dinâmico) do Heap. Logo, o uso da busca linear simples mostra-se coeso com a restrição de dados e simplifica a implementação, entregando o processamento também em $O(V^2)$.

## 3. Análise de Complexidade e Resultados

A avaliação experimental das métricas concentra-se nos limites superior e inferior (teoria vs. prática) de cada algoritmo.

### Complexidade Assintótica Teórica

* **Kruskal:** 
  1. Varredura da matriz inicial: $O(V^2)$.
  2. Ordenação das arestas extraídas: $O(E \log E)$.
  3. Formação da árvore (Union-Find): $O(E \alpha(V))$.
  **Geral:** A complexidade final de Kruskal sob esse modelo de dados é de $O(V^2 + E \log E)$.
  
* **Prim (Matriz sem Heap):** 
  Executa estruturalmente $V$ iterações, fazendo varreduras lineares de tamanho $V$ (uma para buscar o próximo vértice e a outra para atualizar vizinhos adjacentes). 
  **Geral:** A complexidade final é sempre $O(V^2)$, não dependendo ativamente do número real de arestas.

### Confronto Experimental

**1. Desempenho em Grafos Esparsos ($E = O(V)$):**
Em cenários de baixa densidade, a complexidade teórica global de Kruskal é dominada pela etapa de leitura da matriz, totalizando $O(V^2 + V \log V) \approx O(V^2)$. Para o Prim, a complexidade também fica estabelecida puramente pelo limite de sua estrutura iterativa matriz $O(V^2)$. 
Embora ambos possuam limites limitados por $O(V^2)$, Kruskal executa a lógica complexa de processamento de arestas ($E \log E$) um número radicalmente menor de vezes, utilizando rotinas nativas de ordenação extremamente eficientes no hardware. Em contrapartida, Prim realiza varreduras integrais para toda a ordem iterativa $V$. Os experimentos corroboraram que os fatores de constante oculta do processamento do Prim são bem mais pesados que no Kruskal. Portanto, em grafos esparsos com as atuais estruturas, Kruskal performa visivelmente mais rápido perante um limite equivalente.

**2. Desempenho em Grafos Densos ($E = O(V^2)$):**
No limite superior (super densos), o cenário teórico sofre uma inversão. A complexidade geral do Kruskal sofre um agravante em função da sobrecarga nas arestas que devem ser comparadas e organizadas, totalizando $O(V^2 + V^2 \log (V^2))$, recaindo a um limite superior de $O(V^2 \log V)$. Já o Prim, cujos passos e varreduras independem do número de conexões ativas, continua operando em $O(V^2)$ de tempo.
Conforme as restrições teóricas assintóticas, esperaríamos que Prim superasse o Kruskal substancialmente em eficiência em altas matrizes (sendo $O(V^2)$ frente a $O(V^2 \log V)$). Contudo, na prática empírica, a otimização em memória das rotinas internas e a eficiência da organização estrutural do União/Busca (Union-Find) compensam significativamente a diferença limite, diminuindo de forma brusca os fatores constantes do Kruskal e fazendo com que ambos possuam um crescimento e eficiência altamente comparáveis no hardware e, em vários casos práticos, as rotinas de Kruskal ainda assim finalizem mais rápido devido a penalidades de saltos condicionais do Prim. O Prim contém com sucesso o escalonamento, mas a execução final revela uma equiparidade em eficiência assintótica.
