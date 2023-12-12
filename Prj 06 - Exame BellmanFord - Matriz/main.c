#include <stdio.h>
#include <limits.h>

// Valor que representa "infinito" para distâncias
#define INFINITO 9999
#define VERTICES 5

// Função para relaxar uma aresta (u, v)
void relaxa(int u, int v, int* dist, int peso)
{
    if (dist[u] != INFINITO && dist[v] > dist[u] + peso)
    {
        dist[v] = dist[u] + peso;
    }
}

/*
    Função para verificar se é possível chegar a um vértice a partir do vértice de origem
    definido no input pelo usuário
*/
int podeAlcancar(int dist, int origem)
{
    return dist != INFINITO && dist != INT_MIN && origem != INFINITO && origem != INT_MIN;
}

/*
    A função BellmanFord para encontrar o caminho minimo foi baseado no pseudocódigo contido no slide
    das aulas de Estrutura de Dados 2. Modificações foram feitas para a Bellman-Ford mostrar os
    resultados:

        i) Mostra a distancia minima para CADA vertice do grafo baseado no vertice escolhido pelo
        usuario na função main. Caso não seja possivel chegar em uma determinada aresta por conta
        do grafo ser dirigido, uma mensagem de erro aparecerá.
        Ex: Distancia do vertice [i]->[j] = [k]
            Distancia do vertice [i]->[j] = [Erro]

        ii) Mostra na tela se existe o caminho de um vertice a outro. Achei meio besta isso kkkkk mas
        mostra o por que da mensagem de erro do print i).
        Ex:Nao existe caminho de V[i] ate V[j]
           E possivel chegar de V[i] ate V[j]

 */
void bellmanFord(int grafo[VERTICES][VERTICES], int origem)
{
    int dist[VERTICES];

    // Inicializa as distâncias de todos os vértices como "infinito"
    for (int i = 0; i < VERTICES; i++)
    {
        dist[i] = INFINITO;
    }

    // Define a distância do vértice de origem como 0
    dist[origem] = 0;

    // Relaxa todas as arestas V-1 vezes
    for (int i = 1; i <= VERTICES - 1; i++)
    {
        for (int u = 0; u < VERTICES; u++)
        {
            for (int v = 0; v < VERTICES; v++)
            {
                if (grafo[u][v] != 0)
                { // Se há uma aresta de u para v
                    relaxa(u, v, dist, grafo[u][v]);
                }
            }
        }
    }

    // Imprime as distâncias mínimas do vértice de origem para todos os outros vértices
    printf("\n\tDistancias minimas do vertice [%d]\n\n", origem);
    for (int i = 0; i < VERTICES; i++)
    {
        if(dist[i] == 9999)
        {
            /*
                Para nao printar 9999 na distancia, coloquei essa gambiarra como mensagem de erro.
                apenas entra aqui se nao existe caminho algum do vertice Vk -> Vn.
            */
             printf("Distancia do vertice [%d]->[%d] = [Erro]\n",origem,i);
        }
        else
        {
            printf("Distancia do vertice [%d]->[%d] = [%d]\n",origem,i,dist[i]);
        }

    }

    printf("\n");// Para o código ficar Aesthetic

    // Verifica se é possível alcançar cada vértice a partir do vértice de origem
    for (int i = 0; i < VERTICES; i++)
    {
        if (i != origem)
        {
            if (podeAlcancar(dist[i], grafo[origem][i]))
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
    int loop = 1,
        origem;

    /*
        Matriz de adjacência representando o grafo com pesos. Como são
        poucas arestas optei por utilizar a matriz ao inves de fazer as
        arestas via ponteiros.
    */
    int grafo[VERTICES][VERTICES] =
    {
            {0, 4, 2, 0, 0},
            {0, 0, 3, 2, 3},
            {0, 1, 0, 4, 5},
            {0, 0, 0, 0, 0},
            {0, 0, 0, -5, 0}
    };

    while(loop != 0)
    {
        // Recebe um vértice arbitrário do usuário dentro do range dos vertices do Grafo
        printf("Digite o numero do vertice de origem [entre 0 e %d]\nVertice:", VERTICES - 1);
        scanf("%d", &origem);

        // Verifica se o vértice fornecido é válido
        if (origem < 0 || origem >= VERTICES)
        {
            printf("Vertice invalido.\n");
            return 1;
        }

        // Executa o algoritmo de Bellman-Ford
        bellmanFord(grafo, origem);

        printf("\nDeseja continuar?\n"
               "[1] Sim\n"
               "[0] Nao\n");
        scanf("%d",&loop);

    }
    printf("\n\n=========================================");
    return 0;
}