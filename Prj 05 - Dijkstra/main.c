#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define TIPOPESO int

typedef struct adjacencia
{
    int vertice;
    TIPOPESO peso;
    struct adjacencia *prox;
} ADJACENCIA;

typedef struct vertice
{
    /*Dados armazenados vao aqui*/
    ADJACENCIA *cab;
} VERTICE;

typedef struct grafo
{
    int vertices;
    int arestas;
    VERTICE *adj;
} GRAFO;

bool existeAberto(const GRAFO *g, bool *aberto)
{
    for (int i = 0; i < g->vertices; i++)
    {
        if (aberto[i])
        {
            return true;
        }
    }
    return false;
}

void inicializaGrafo(GRAFO *g, int numVertices)
{
    g->vertices = numVertices;
    g->arestas = 0;
    // Inicialização da matriz de listas de adjacência
    g->adj = (VERTICE *)malloc(numVertices * sizeof(VERTICE));

    for (int i = 0; i < numVertices; i++)
    {
        g->adj[i].cab = NULL;
    }
}

/*
   Inicializa os vetores de distâncias (d) e predecessores (p) para a execução do algoritmo de Dijkstra.
   Define a distância do vértice de origem s como 0 e as demais como infinito (INT_MAX/2).
*/
void inicializaD(GRAFO *g, int *d, int *p, int s)
{
    for (int v = 0; v < g->vertices; v++)
    {
        d[v] = INT_MAX / 2;  // Inicializa as distâncias com um valor grande (representando infinito)
        p[v] = -1;           // Inicializa os predecessores como -1 (ainda não definidos)
    }

    d[s] = 0;               // A distância do vértice de origem para ele mesmo é zero
}

void adicionaAresta(GRAFO *g, int u, int v, TIPOPESO peso)
{
    if(u >= 0 && u < g->vertices && v >= 0 && v < g->vertices)
    {
        ADJACENCIA *novo = (ADJACENCIA *)malloc(sizeof(ADJACENCIA));

        novo->vertice = v;
        novo->peso = peso;
        novo->prox = g->adj[u].cab;
        g->adj[u].cab = novo;
        g->arestas++;
    }
}

/*
   Relaxa a aresta entre os vértices u e v, atualizando a distância e o predecessor se necessário.
   Utiliza a lista de adjacência para encontrar o peso da aresta correspondente.
*/
void relaxa(GRAFO *g, int *d, int *p, int u, int v)
{
    ADJACENCIA *ad = g->adj[u].cab;  // Obtém a lista de adjacência do vértice u

    while (ad && ad->vertice != v)
    {
        ad = ad->prox;  // Procura pela aresta que conecta u e v na lista de adjacência
    }

    if (ad)
    {
        if (d[v] > d[u] + ad->peso)
        {
            d[v] = d[u] + ad->peso;  // Atualiza a distância se uma distância menor for encontrada
            p[v] = u;                // Atualiza o predecessor de v para u
        }
    }
}

/*
   Retorna o vértice com a menor distância no conjunto de vértices ainda não visitados.
   Utiliza o vetor de distâncias (d) e o conjunto de vértices abertos.
*/
int menorDist(const GRAFO *g, bool *aberto, int *d) {
    int menor = -1;

    for (int i = 0; i < g->vertices; i++) {
        if (aberto[i]) {
            menor = i;  // Inicializa o menor valor com o primeiro vértice aberto encontrado
            break;
        }
    }

    if (menor == -1)
        return (-1);  // Retorna -1 se nenhum vértice aberto for encontrado

    for (int i = menor + 1; i < g->vertices; i++) {
        if (aberto[i] && (d[i] < d[menor])) {
            menor = i;  // Atualiza o menor valor se uma distância menor for encontrada
        }
    }
    return (menor);  // Retorna o vértice com a menor distância
}

/*
   Implementa o algoritmo de Dijkstra para encontrar as menores distâncias a partir de um vértice de origem s.
   Retorna um vetor com as distâncias mínimas.
*/
int *dijkstra(GRAFO *g, int s, int *p) {
    int *d = (int *)malloc(g->vertices * sizeof(int));  // Aloca o vetor de distâncias
    bool aberto[g->vertices];

    inicializaD(g, d, p, s);  // Inicializa os vetores de distâncias e predecessores
    for (int i = 0; i < g->vertices; i++) {
        aberto[i] = true;  // Inicializa todos os vértices como abertos
    }

    while (existeAberto(g, aberto)) {
        int u = menorDist(g, aberto, d);  // Obtém o vértice com a menor distância entre os abertos
        aberto[u] = false;  // Fecha o vértice, indicando que foi visitado

        ADJACENCIA *ad = g->adj[u].cab;  // Obtém a lista de adjacência do vértice u
        while (ad) {
            relaxa(g, d, p, u, ad->vertice);  // Relaxa as arestas do vértice u
            ad = ad->prox;  // Move para a próxima aresta na lista de adjacência
        }
    }
    return d;  // Retorna o vetor de distâncias mínimas
}

void imprimirCaminho(int *p, int v, int s)
{

    if (v == s)
    {
        printf("%d", s);
    }
    else if (p[v] == -1)
    {
        printf("Nenhum caminho de %d para %d\n", s, v);

    }
    else
    {
        imprimirCaminho(p, p[v], s);
        printf(" -> %d", v);
    }
}

void mostraResultado(GRAFO *g, int *d, int *p, int s)
{
    for (int i = 0; i < g->vertices; i++)
    {
        printf("Distancia saindo de [%d] para [%d] = [%d], Vertices percorridos:\n", s, i, d[i]);
        imprimirCaminho(p, i, s);
        printf("\n");
    }
}

void visualizarGrafo(GRAFO* g)
{
    for (int i = 0; i < g->vertices; i++)
    {
        ADJACENCIA* atual = g->adj[i].cab;
        printf("Vertice %d:", i);

        // Coloca os vértices em um array para ordenação
        int verticesOrdenados[g->vertices];
        int pesos[g->vertices];

        int count = 0;

        while (atual != NULL)
        {
            verticesOrdenados[count] = atual->vertice;
            pesos[count] = atual->peso;
            atual = atual->prox;
            count++;
        }

        // Ordena os vértices
        for (int j = 0; j < count - 1; j++)
        {
            for (int k = 0; k < count - j - 1; k++)
            {
                if (verticesOrdenados[k] > verticesOrdenados[k + 1])
                {
                    // Troca os vértices
                    int tempVertice = verticesOrdenados[k];
                    verticesOrdenados[k] = verticesOrdenados[k + 1];
                    verticesOrdenados[k + 1] = tempVertice;

                    // Troca os pesos correspondentes
                    int tempPeso = pesos[k];
                    pesos[k] = pesos[k + 1];
                    pesos[k + 1] = tempPeso;
                }
            }
        }

        // Imprimi os vértices e pesos ordenados
        for (int j = 0; j < count; j++)
        {
            printf(" ( -> %d, peso[%d] )", verticesOrdenados[j], pesos[j]);
            if(j+1 == count)
            {
                break;
            }
            else
            {
                printf(" -");
            }
        }

        printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("========== Dijkstra ==========\n\n");


    GRAFO grafo;
    int vertices = 6, s;
    int *predecessores = (int *)malloc(vertices * sizeof(int));

    // Inicializa o grafo com 6 vértices
    inicializaGrafo(&grafo, vertices);

    // Adição de arestas com pesos
    adicionaAresta(&grafo, 0, 1, 10);
    adicionaAresta(&grafo, 0, 2, 5);
    adicionaAresta(&grafo, 1, 3, 1);
    adicionaAresta(&grafo, 2, 1, 3);
    adicionaAresta(&grafo, 2, 3, 8);
    adicionaAresta(&grafo, 2, 4, 2);
    adicionaAresta(&grafo, 3, 4, 4);
    adicionaAresta(&grafo, 3, 5, 4);
    adicionaAresta(&grafo, 4, 5, 6);

    printf("\t\t*** Grafo ***\n");
    visualizarGrafo(&grafo);

    printf("Informe o valor de inicio [entre 0 e 5]\nInicio:");
    scanf("%d", &s);

    // Chama a função Dijkstra para calcular as distâncias mínimas
    int *distancias = dijkstra(&grafo, 0, predecessores);


    // Mostra os resultados para todos os pares em relação ao vertice de inicio
    printf("\t\t*** Distancias Dijkstra ***\n");
    mostraResultado(&grafo, distancias, predecessores, s);

    // Libera a memória alocada para o vetor de listas de adjacência
    free(grafo.adj);
    // Libera a memória alocada para o vetor de distâncias
    free(distancias);

    return 0;
}