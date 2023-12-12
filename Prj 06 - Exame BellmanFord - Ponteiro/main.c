#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define INFINITO 9999
#define VERTICES 5

// Struct que representa uma aresta no grafo
struct Aresta
{
    int destino;
    int peso;
    struct Aresta* proxima;
};

// Struct que representa um vértice em um grafo
struct Vertice
{
    struct Aresta* listaAdj;
};

// Função que cria o grafo
struct Vertice* criaGrafo()
{
    struct Vertice* grafo = (struct Vertice*)malloc(VERTICES * sizeof(struct Vertice));

    for (int i = 0; i < VERTICES; i++)
    {
        grafo[i].listaAdj = NULL;
    }

    return grafo;
}

// Função que cria uma aresta com destino e peso
struct Aresta* criaAresta(int destino, int peso)
{
    struct Aresta* novaAresta = (struct Aresta*)malloc(sizeof(struct Aresta));

    novaAresta->destino = destino;
    novaAresta->peso = peso;
    novaAresta->proxima = NULL;

    return novaAresta;
}

// Função que adiciona uma aresta no grafo
void adicionaAresta(struct Vertice* grafo, int origem, int destino, int peso)
{
    struct Aresta* novaAresta = criaAresta(destino, peso);

    novaAresta->proxima = grafo[origem].listaAdj;
    grafo[origem].listaAdj = novaAresta;
}


// Função para verificar se é possível alcançar um vértice a partir da origem
int podeAlcancar(int dist, int origem)
{
    return dist != INFINITO && dist != INT_MIN;
}

// Função para mostrar o caminho mínimo de origem para destino
void mostraCaminho(int origem, int destino, int* predecessores)
{
    if (destino == origem)
    {
        printf("[V%d]", origem);
    }
    else if (predecessores[destino] == -1)
    {
        printf("Caminho de V[%d] para V[%d] nao existe.", origem, destino);
    }
    else
    {
        mostraCaminho(origem, predecessores[destino], predecessores);
        printf("->[V%d]", destino);
    }
}

/*
    Função principal para o algoritmo de Bellman-Ford
    - Totalmente baseada no pseudo-codigo contido nos slides da disciplina
    - Possui funções adicionais:
        • Mostrar a distância do vertice x ao y
        • Mostrar o menor caminho (caso não exista caminho possivel uma mensagem de erro aparecerá)
        • Mostrar a possibilidade da existência de um caminho de 'x' até 'y'

    - Função relaxa dentro da Bellman-Ford:
        • Estava dando um erro por conta da forma que pensei para mostrar o caminho, então implementei o que a função
        relaxa faria dentro do código da função.
*/
void bellmanFord(struct Vertice* grafo, int origem)
{

    int dist[VERTICES];
    int predecessores[VERTICES];

    // Inicializa todas as distâncias como INFINITO e todos os predecessores como -1
    for (int i = 0; i < VERTICES; i++)
    {
        dist[i] = INFINITO;
        predecessores[i] = -1;
    }

    // A distância do vértice de origem para ele mesmo é 0
    dist[origem] = 0;


    // Controla o número total de iterações, garantindo que todas as arestas sejam consideradas para relaxamento.
    for (int i = 1; i <= VERTICES - 1; i++)
    {
        // Itera sobre todos os vértices do grafo.
        for (int u = 0; u < VERTICES; u++)
        {
            struct Aresta* atual = grafo[u].listaAdj;
            //Percorre todas as arestas adjacentes ao vértice atual u.
            while (atual != NULL)
            {
                int v = atual->destino;
                int peso = atual->peso;

                /*
                    ------------------------------- Relaxa -------------------------------
                    -Verifica se a distância estimada até o vértice v pode ser melhorada relaxando a aresta (u, v)
                    -O if garante que a distância seja atualizada caso exista um caminho mais curto passando por u
                */
                if (dist[u] != INFINITO && dist[v] > dist[u] + peso) {
                    dist[v] = dist[u] + peso;
                    predecessores[v] = u; // Atualiza o predecessor
                }

                atual = atual->proxima;
            }
        }
    }

    // Mostra a distância mínima do vértice escolhido para cada outro vértice do grafo
    printf("\nDistancias minimas do vertice [%d]\n\n", origem);
    for (int i = 0; i < VERTICES; i++)
    {
        if (dist[i] == INFINITO)
        {
            // Caso não seja possível chegar do vértice 'x' ao 'y' a mensagem a seguir é mostrada na tela
            printf("Distancia do vertice [%d]->[%d] = [!E]\n", origem, i);
        }
        else
        {
            printf("Distancia do vertice [%d]->[%d] = [%d]\n", origem, i, dist[i]);
        }
    }

    /*
     Mostra o caminho percorrido do vértice de origem 'x' ao 'y' para conferir na imagem do grafo
     [x]->[p]->[t]->[o]->[y]
     */
    printf("\nCaminhos minimos do vertice [%d]\n\n", origem);
    for (int i = 0; i < VERTICES; i++)
    {
        if (i != origem)
        {
            printf("Caminho de V[%d] para V[%d]: ", origem, i);
            mostraCaminho(origem, i, predecessores);
            printf("\n");
        }
    }

    printf("\n"); // Para o código ficar Aesthetic

    // Verifica a existência do caminho do vértice de partida 'x' ao 'y'
    for (int i = 0; i < VERTICES; i++)
    {
        if (i != origem)
        {
            // Verifica se é possível chegar de origem até o vértice i
            if (podeAlcancar(dist[i], origem))
            {
                printf("E possivel chegar de V[%d] ate V[%d]\n", origem, i);
            }
            else
            {
                printf("Nao existe caminho de V[%d] ate V[%d]\n", origem, i);
            }
        }
    }
}


int main()
{
    printf("============== Bellman-Ford ==============\n\n");

    int loop = 1, origem;

    struct Vertice* grafo = criaGrafo();

    // Adiciona arestas ao grafo via ponteiro (uhuuuullll)
    adicionaAresta(grafo, 0, 1, 4);
    adicionaAresta(grafo, 0, 2, 2);
    adicionaAresta(grafo, 1, 2, 3);
    adicionaAresta(grafo, 1, 3, 2);
    adicionaAresta(grafo, 1, 4, 3);
    adicionaAresta(grafo, 2, 1, 1);
    adicionaAresta(grafo, 2, 3, 4);
    adicionaAresta(grafo, 2, 4, 5);
    adicionaAresta(grafo, 4, 3, -5);

    while (loop != 0)
    {
        switch (loop)
        {

            case 1:

                printf("Digite o numero do vertice de origem [entre 0 e %d]\nVertice:", VERTICES - 1);
                scanf("%d", &origem);

                // Verifica se o vértice é válido
                if (origem < 0 || origem >= VERTICES)
                {
                    printf("Vertice invalido.\n");
                    return 1;
                }

                printf("\n\n-------------------------------------\n");
                // Chama a função Bellman-Ford para encontrar o caminho mais curto a partir do vértice escolhido
                bellmanFord(grafo, origem);
                printf("\n-------------------------------------\n\n");

                break;

            case 0:

                loop = 0;
                break;

            default:

                printf("\nOpcao Invalida!!\n");
                break;
        }

        printf("\nDeseja continuar?\n"
               "[1] Sim\n"
               "[0] Nao\n");
        scanf("%d", &loop);

    }

    printf("\n\n=========================================");

    return 0;
}