void BFS(int V, int **A, int s) 
{
    // Aloca memória para as propriedades dos vértices
    int *color = (int *)malloc(V * sizeof(int));
    int *d = (int *)malloc(V * sizeof(int));
    int *π = (int *)malloc(V * sizeof(int));
    int *Q = (int *)malloc(V * sizeof(int));

    // No inicio todos os vértices são BRANCOS (não visitados), a distância é INFINITO e o predecessor é Nulo
    for (int u = 0; u < V; u++)
    {
        color[u] = WHITE;  // Define a cor como BRANCO (não visitado)
        d[u] = INFINITY;   // Define a distância como infinito
        π[u] = NIL;        // Define o predecessor como NIL
    }


    // Inicializa as propriedades do vértice de origem
    color[s] = GRAY;  // Define a cor como CINZA (atualmente visitando)
    d[s] = 0;         // Define a distância como 0 para o vértice de origem
    π[s] = NIL;       // Define o predecessor como NIL para o vértice de origem

    // Inicializa a fila
    int front = 0, rear = 0;
    Q[rear++] = s;  // Enfileira o vértice de origem



    // Executa a BFS enquanto a fila não estiver vazia
    while (front < rear) 
    {
        int u = Q[front++];  // Desenfileira um vértice do início da fila

        // Explora os vértices adjacentes ao vértice desenfileirado
        for (int v = 0; v < V; v++) {
            if (A[u][v] == 1 && color[v] == WHITE) {
                d[v] = d[u] + 1;  // Atualiza a distância até v a partir da origem
                π[v] = u;         // Define u como predecessor de v
                Q[rear++] = v;    // Enfileira v para exploração posterior
                color[v] = GRAY;  // Define a cor de v como CINZA (visitado)
            }
        }

        color[u] = BLACK;  // Marca o vértice desenfileirado como NEGRO (visitado e explorado)
    }
}