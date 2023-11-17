#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INFINITY 9999

// Protótipos
struct Queue *createQueue(unsigned capacity);
int isEmpty(struct Queue *queue);               // Verifica se a fila está vazia
void enqueue(struct Queue *queue, int item);    // Adiciona um item à fila
int dequeue(struct Queue *queue);               // Remove um item da fila

struct AdjListNode
{
    int dest;
    struct AdjListNode *next;
};

struct AdjList
{
    struct AdjListNode *head;
};

struct Graph
{
    int V;
    struct AdjList *array;
};

// Cria um novo nó da lista de adjacência
struct AdjListNode *newAdjListNode(int dest)
{
    struct AdjListNode *newNode = (struct AdjListNode *)malloc(sizeof(struct AdjListNode));

    newNode->dest = dest;
    newNode->next = NULL;

    return newNode;
}

// Cria um novo grafo com V vértices
struct Graph *createGraph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));

    graph->V = V;
    graph->array = (struct AdjList *)malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
    {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Cria uma fila com capacidade dada
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    int *array;
};

//Cria uma fila com a capacidade dada
struct Queue *createQueue(unsigned capacity)
{
    // Aloca memória para a fila
    struct Queue *queue = (struct Queue *)malloc(sizeof(struct Queue));

    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;                                  // Isso é importante, veja a função enqueue
    queue->array = (int *)malloc(queue->capacity * sizeof(int)); // Aloca espaço para os elementos da fila

    return queue; // Retorna a fila criada
}

// Adiciona uma aresta ao grafo não direcionado
void addEdge(struct Graph *graph, int src, int dest)
{
    // Cria um novo nó de lista de adjacência
    struct AdjListNode *newNode = newAdjListNode(dest);

    // Adiciona o nó ao início da lista de adjacência do vértice de origem
    newNode->next = graph->array[src - 1].head;
    graph->array[src - 1].head = newNode;

    // Repete o processo acima para o vértice de destino para criar uma aresta não direcionada
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest - 1].head;
    graph->array[dest - 1].head = newNode;
}

// Imprime o grafo
void printGraph(struct Graph *graph)
{
    printf("\n * Grafo Casinha *\n\n");
    printf(" (4)----------(5)\n");
    printf(" /           /   \\ \n");
    printf("(1)-------(3)----(6)\n");
    printf("|          |      |\n");
    printf("|          |      |\n");
    printf("(2)-------(7)----(8)\n\n");

    printf("[Valor]\t[Coneccoes diretas]\n");

    for (int v = 1; v <= graph->V; ++v)
    {
        printf(" [%d]\t", v);

        struct AdjListNode *pCrawl = graph->array[v - 1].head;
        while (pCrawl)
        {
            printf("[%d] ", pCrawl->dest);
            pCrawl = pCrawl->next;
        }

        printf("\n");
    }
    printf("\n\n");
}

// Verifica se o valor está no intervalo de 1 a 8
int checkRange(int root)
{
    if (root >= 1 && root <= 8)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Implementação do algoritmo BFS
void BFS(struct Graph *graph, int s)
{
    // Aloca memória para os arrays de cor, distância e pai
    int *color = (int *)malloc(graph->V * sizeof(int));
    int *d = (int *)malloc(graph->V * sizeof(int));
    int *pai = (int *)malloc(graph->V * sizeof(int));

    // Inicializa as estruturas de dados do BFS
    for (int i = 0; i < graph->V; i++)
    {
        color[i] = WHITE;   // Define todas as cores como branca
        d[i] = INFINITY;    // Define todas as distâncias como infinito
        pai[i] = -1;         // Define todos os pais como -1
    }

    color[s - 1] = GRAY;    // Define a cor do vértice de origem como cinza
    d[s - 1] = 0;           // Define a distância do vértice de origem como 0
    struct Queue *queue = createQueue(graph -> V); // Cria uma fila com capacidade 's'
    enqueue(queue, s); // Adiciona o vértice de origem à fila

    // Enquanto a fila não estiver vazia, continue a busca
    while (!isEmpty(queue))
    {
        int u = dequeue(queue); // Remove o primeiro elemento da fila

        // Percorre todos os vértices adjacentes de u
        struct AdjListNode *node = graph->array[u - 1].head;
        while (node != NULL)
        {
            int v = node->dest;
            if (color[v - 1] == WHITE)      // Se o vértice não foi visitado
            {
                color[v - 1] = GRAY;        // Define o vértice como visitado
                d[v - 1] = d[u - 1] + 1;    // Atualiza a distância do vértice
                pai[v - 1] = u;              // Define o pai do vértice
                enqueue(queue, v);     // Adiciona o vértice à fila para visita posterior
            }
            node = node->next; // Vai para o próximo vértice adjacente
        }
        color[u - 1] = BLACK; // Marca o vértice como visitado
    }
    printf("***   (vertice,distancia da raiz)   ***\n");
    printf(" (4,%d)-----------(5,%d)\n", d[3], d[4]);
    printf(" /               /    \\ \n");
    printf("(1,%d)-------(3,%d)-----(6,%d)\n", d[0], d[2], d[5]);
    printf("|              |         |\n");
    printf("|              |         |\n");
    printf("(2,%d)-------(7,%d)------(8,%d)\n", d[1], d[6], d[7]);
    for (int i = 0; i < graph->V; i++)
    {
        printf("Vertex %d: Distance = %d, Parent = %d\n", i + 1, d[i], pai[i]);
    }
    printf("\n\n");
}

// Verifica se a fila está cheia
int isFull(struct Queue *queue)
{
    return (queue->size == queue->capacity);
}

// Verifica se a fila está vazia
int isEmpty(struct Queue *queue)
{
    return (queue->size == 0);
}

// Adiciona um item à fila
void enqueue(struct Queue *queue, int item)
{
    if (isFull(queue))
    {
        return; // Se a fila estiver cheia, sai da função
    }

    queue->rear = (queue->rear + 1) % queue->capacity;  // Atualiza a posição traseira da fila
    queue->array[queue->rear] = item;                   // Adiciona o item à posição traseira
    queue->size = queue->size + 1;                      // Atualiza o tamanho da fila
}

// Remove um item da fila
int dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        return -1; // Se a fila estiver vazia, retorna -1
    }

    int item = queue->array[queue->front];                  // Obtém o primeiro elemento da fila
    queue->front = (queue->front + 1) % queue->capacity;    // Atualiza a posição frontal da fila
    queue->size = queue->size - 1;                          // Atualiza o tamanho da fila
    return item;                                            // Retorna o elemento removido da fila
}

void exitMessage()
{
    printf("\n          Grafo - Busca BFS\n");
    sleep(1);
    printf("=======================================\n");
}

int main()
{
    int V = 8, flag = 1, opt, root;
    struct Graph *graph = createGraph(V);
    //struct Queue *queue = createQueue(V); // Corrigido para passar o argumento 'V'

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 7);
    addEdge(graph, 3, 5);
    addEdge(graph, 3, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 4, 5);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 8);
    addEdge(graph, 7, 8);

    printf("========== Grafo - Busca BFS ==========\n\n");
    while (flag != 0)
    {
        printf("[1] Mostrar Grafo.\n"
               "[2] Efetuar a busca por largura BFS.\n"
               "[3] Sair.\n"
               "Opcao desejada:");
        scanf("%d", &opt);

        switch (opt)
        {
            case 1:

                printGraph(graph);

                break;

            case 2:
                printf("Escolha um dos valores do grafo (entre 1~8) como a RAIZ para efetuar a busca a partir dela:\n");
                scanf("%d", &root);

                if (checkRange(root) == 1)
                {
                    BFS(graph, root);
                }
                break;

            case 3:
                flag = 0;

                exitMessage();

                break;
        }
    }

    return 0;
}
