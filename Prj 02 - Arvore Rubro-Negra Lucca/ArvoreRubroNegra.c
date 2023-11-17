#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

enum Color { RED, BLACK };

typedef struct Node
{
    int val;
    enum Color cor;
    struct Node* parente;// era pra ser pai mas usava dento das funçoes confundia td ai mudei pra "parent" mas me dava toc so isso em ingles ai tirei kkkk
    struct Node* esq;
    struct Node* dir;
} Node;

typedef struct RedBlackTree
{
    Node* root;
} RedBlackTree;


Node* criaNo(int val, enum Color cor)
{
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo ->val = val;
    novoNo ->cor = cor;
    novoNo ->parente = NULL;//usei mt pai ao longo do código e estava aqui tbm. Estava um inferno de debugar kkkk entao mudei aqui
    novoNo ->esq = NULL;
    novoNo ->dir = NULL;

    return novoNo;
}

RedBlackTree* criaArvoreRB()
{
    RedBlackTree* newTree = (RedBlackTree*)malloc(sizeof(RedBlackTree));
    newTree->root = NULL;
    return newTree;
}

// Função de rotação à esquerda
void rotacaoEsquerda(RedBlackTree* tree, Node* node)
{
    // Verifica se o nó ou seu filho direito são nulos, pois não podemos
    // realizar uma rotação à esquerda nessas condições.
    if (node == NULL || node->dir == NULL)
    {
        return;
    }

    // Armazena uma referência ao filho direito do nó.
    Node* filhoDir = node->dir;

    // Atualiza os ponteiros para ajustar a subárvore direita do nó.
    node->dir = filhoDir->esq;

    // Se o filho esquerdo do filho direito não for nulo, atualiza o pai dele
    // para apontar para o nó atual.
    if (filhoDir->esq != NULL)
    {
        filhoDir->esq->parente = node;
    }

    // Atualiza o pai do filho direito para apontar para o pai do nó atual.
    filhoDir->parente = node->parente;

    // Atualiza o pai do nó atual para apontar para o filho direito.
    if (node->parente == NULL)
    {
        tree->root = filhoDir;
    }
    else if (node == node->parente->esq)
    {
        node->parente->esq = filhoDir;
    }
    else
    {
        node->parente->dir = filhoDir;
    }

    // Atualiza o filho esquerdo do filho direito para apontar para o nó atual.
    filhoDir->esq = node;

    // Atualiza o pai do nó atual para apontar para o filho direito.
    node->parente = filhoDir;
}


// Função de rotação à direita
void rotacaoDireita(RedBlackTree* tree, Node* node)
{
    // Verifica se o nó ou seu filho esquerdo são nulos, pois não podemos
    // realizar uma rotação à direita nessas condições.
    if (node == NULL || node->esq == NULL)
    {
        return;
    }

    // Armazena uma referência ao filho esquerdo do nó.
    Node* filhoEsq = node->esq;

    // Atualiza os ponteiros para ajustar a subárvore esquerda do nó.
    node->esq = filhoEsq->dir;

    // Se o filho direito do filho esquerdo não for nulo, atualiza o pai dele
    // para apontar para o nó atual.
    if (filhoEsq->dir != NULL)
    {
        filhoEsq->dir->parente = node;
    }

    // Atualiza o pai do filho esquerdo para apontar para o pai do nó atual.
    filhoEsq->parente = node->parente;

    // Atualiza o pai do nó atual para apontar para o filho esquerdo.
    if (node->parente == NULL)
    {
        tree->root = filhoEsq;
    }
    else if (node == node->parente->dir)
    {
        node->parente->dir = filhoEsq;
    }
    else
    {
        node->parente->esq = filhoEsq;
    }

    // Atualiza o filho direito do filho esquerdo para apontar para o nó atual.
    filhoEsq->dir = node;

    // Atualiza o pai do nó atual para apontar para o filho esquerdo.
    node->parente = filhoEsq;
}


// Função de balanceamento após a inserção
void arrumaInsercao(RedBlackTree* tree, Node* node)
{
    // Ponteiro para o nó pai do nó atual
    Node* pai = NULL;

    // Ponteiro para o nó avô do nó atual
    Node* avo = NULL;

    // Enquanto o nó atual é vermelho e o pai do nó atual é vermelho (violação da propriedade 4),
    // e enquanto o nó atual não é a raiz (violação da propriedade 2)
    while (node != tree->root && node->cor == RED && node->parente->cor == RED)
    {
        pai = node->parente;
        avo = pai->parente;

        // Se o pai do nó atual é o filho esquerdo do avô
        if (pai == avo->esq)
        {
            Node* tio = avo->dir; // Tio do nó atual

            // Caso 1: O tio do nó atual é vermelho
            if (tio != NULL && tio->cor == RED)
            {
                // Recolorir o pai, tio e avô
                pai->cor = BLACK;
                tio->cor = BLACK;
                avo->cor = RED;
                node = avo; // Move-se para o avô para continuar o balanceamento
            }
            else
            {
                // Caso 2: O tio do nó atual é preto ou nulo
                // e o nó atual é um filho direito
                if (node == pai->dir)
                {
                    // Rotação à esquerda em torno do pai
                    rotacaoEsquerda(tree, pai);
                    // Agora o nó atual se torna o antigo pai
                    node = pai;
                    pai = node->parente;
                }

                // Caso 3: O tio do nó atual é preto ou nulo
                // e o nó atual é um filho esquerdo
                // Recolorir o pai e o avô, em seguida, realizar uma rotação à direita em torno do avô
                pai->cor = BLACK;
                avo->cor = RED;
                rotacaoDireita(tree, avo);
            }
        }
        else
        {
            // Caso igual ao anterior, mas trocando esquerda por direita e vice-versa
            Node* tio = avo->esq;

            if (tio != NULL && tio->cor == RED)
            {
                pai->cor = BLACK;
                tio->cor = BLACK;
                avo->cor = RED;
                node = avo;
            }
            else
            {
                if (node == pai->esq)
                {
                    rotacaoDireita(tree, pai);
                    node = pai;
                    pai = node->parente;
                }

                pai->cor = BLACK;
                avo->cor = RED;
                rotacaoEsquerda(tree, avo);
            }
        }
    }

    // A raiz seja sempre preta (propriedade 2)
    tree->root->cor = BLACK;
}


// Função de inserção em uma árvore rubro-negra
void insercao(RedBlackTree* tree, int data) {
    // Criar um novo nó vermelho com os dados fornecidos
    Node* newNode = criaNo(data, RED);

    // Caso especial: árvore vazia
    if (tree->root == NULL) {
        tree->root = newNode;
        tree->root->cor = BLACK; // A raiz deve sempre ser preta (propriedade 2)
        return;
    }

    // Começar a inserção como em uma árvore binária de pesquisa normal
    Node* atual = tree->root;
    Node* pai = NULL;

    while (atual != NULL)
    {
        pai = atual;

        if (data < atual->val)
        {
            atual = atual->esq;
        }
        else if (data > atual->val)
        {
            atual = atual->dir;
        }
        else
        {
            // Valor duplicado
            free(newNode);
            //e feio ter print aqui mas vida q segue
            printf("\nValor ja inserido na arvore!\n\n");
            return;
        }
    }

    // Vincular o novo nó ao pai adequado
    newNode->parente = pai;

    if (data < pai->val)
    {
        pai->esq = newNode;
    }
    else
        pai->dir = newNode;

    // Chamar a função de balanceamento após a inserção
    arrumaInsercao(tree, newNode);
}



// Função auxiliar: Encontra o nó mínimo a partir de um dado nó
Node* encontraMinimo(Node* node) {
    while (node->esq != NULL) {
        node = node->esq;
    }
    return node;
}

// Função de balanceamento após a remoção
void arrumaDelecao(RedBlackTree* tree, Node* node, Node* pai) {
    while (node != NULL && node != tree->root && (node == NULL || node->cor == BLACK)) {
        if (node == pai->esq) {
            Node* irmao = pai->dir;

            if (irmao != NULL) {
                // Caso 1: O irmão do nó é vermelho
                if (irmao->cor == RED) {
                    irmao->cor = BLACK;
                    pai->cor = RED;
                    rotacaoEsquerda(tree, pai);
                    irmao = pai->dir;
                }

                // Caso 2: O irmão do nó é preto e ambos os filhos do irmão são pretos
                if ((irmao->esq == NULL || irmao->esq->cor == BLACK) &&
                    (irmao->dir == NULL || irmao->dir->cor == BLACK)) {
                    irmao->cor = RED;
                    node = pai;
                    pai = node->parente;
                } else {
                    // Caso 3: O irmão do nó é preto, o filho direito do irmão é vermelho e o filho esquerdo é preto
                    if (irmao->dir == NULL || irmao->dir->cor == BLACK) {
                        if (irmao->esq != NULL) {
                            irmao->esq->cor = BLACK;
                        }
                        irmao->cor = RED;
                        rotacaoDireita(tree, irmao);
                        irmao = pai->dir;
                    }

                    // Caso 4: O irmão do nó é preto e o filho direito do irmão é vermelho
                    irmao->cor = pai->cor;
                    pai->cor = BLACK;
                    if (irmao->dir != NULL) {
                        irmao->dir->cor = BLACK;
                    }
                    rotacaoEsquerda(tree, pai);
                    node = tree->root;
                }
            }
        } else {
            Node* irmao = pai->esq;

            if (irmao != NULL) {
                // Caso 1: O irmão do nó é vermelho
                if (irmao->cor == RED) {
                    irmao->cor = BLACK;
                    pai->cor = RED;
                    rotacaoDireita(tree, pai);
                    irmao = pai->esq;
                }

                // Caso 2: O irmão do nó é preto e ambos os filhos do irmão são pretos
                if ((irmao->esq == NULL || irmao->esq->cor == BLACK) &&
                    (irmao->dir == NULL || irmao->dir->cor == BLACK)) {
                    irmao->cor = RED;
                    node = pai;
                    pai = node->parente;
                } else {
                    // Caso 3: O irmão do nó é preto, o filho esquerdo do irmão é vermelho e o filho direito é preto
                    if (irmao->esq == NULL || irmao->esq->cor == BLACK) {
                        if (irmao->dir != NULL) {
                            irmao->dir->cor = BLACK;
                        }
                        irmao->cor = RED;
                        rotacaoEsquerda(tree, irmao);
                        irmao = pai->esq;
                    }

                    // Caso 4: O irmão do nó é preto e o filho esquerdo do irmão é vermelho
                    irmao->cor = pai->cor;
                    pai->cor = BLACK;
                    if (irmao->esq != NULL) {
                        irmao->esq->cor = BLACK;
                    }
                    rotacaoDireita(tree, pai);
                    node = tree->root;
                }
            }
        }
    }

    if (node != NULL) {
        node->cor = BLACK;
    }
}

// Função de remoção em uma árvore rubro-negra
void removeNo(RedBlackTree* tree, int data) {
    if (tree == NULL || tree->root == NULL) {
        printf("\n\nArvore vazia! :(\n");//e feio print aqui mas vida q segue
        return; // Árvore vazia
    }

    Node* node = tree->root;
    Node* pai = NULL;
    Node* temp = NULL;

    while (node != NULL) {
        if (data < node->val) {
            pai = node;
            node = node->esq;
        } else if (data > node->val) {
            pai = node;
            node = node->dir;
        } else {
            // Encontrou o nó a ser removido
            if (node->esq == NULL || node->dir == NULL) {
                // O nó tem no máximo um filho ou é uma folha
                temp = (node->esq != NULL) ? node->esq : node->dir;

                // Atualize o pai do novo nó filho (temp)
                if (temp != NULL) {
                    temp->parente = pai;
                }

                // Atualize os ponteiros do pai para apontar para o novo nó filho (temp)
                if (pai == NULL) {
                    tree->root = temp;
                } else if (node == pai->esq) {
                    pai->esq = temp;
                } else {
                    pai->dir = temp;
                }

                // Verifique a cor do nó removido
                if (node->cor == BLACK) {
                    // Após a remoção para balancear a árvore
                    arrumaDelecao(tree, temp, pai);
                }

                free(node); // Libera o nó removido
            } else {
                // O nó a ser removido tem dois filhos
                temp = encontraMinimo(node->dir); // Encontra o sucessor
                node->val = temp->val; // Copia o valor do sucessor para o nó atual
                pai = temp->parente;
                node = temp;

                // Após a remoção para balancear a árvore
                arrumaDelecao(tree, node, pai);

                // Remove nó sucessor, que é garantido ser um nó folha ou com um filho (caso semelhante ao primeiro if acima)
                if (node->esq == NULL || node->dir == NULL) {
                    temp = (node->esq != NULL) ? node->esq : node->dir;
                    if (temp != NULL) {
                        temp->parente = pai;
                    }
                    if (pai == NULL) {
                        tree->root = temp;
                    } else if (node == pai->esq) {
                        pai->esq = temp;
                    } else {
                        pai->dir = temp;
                    }
                    if (node->cor == BLACK) {
                        arrumaDelecao(tree, temp, pai);
                    }
                    free(node);
                }
            }
            break;
        }
    }

    if (node == NULL) {
        printf("Valor nao encontrado :(\n"); // feio mas vida q segue
        return; // Valor não encontrado na árvore
    }

    // Caso especial: o nó removido era a raiz
    if (node == tree->root) {
        tree->root = NULL;
        return;
    }
}


// Função auxiliar: Imprimir a árvore rubro-negra
void mostraNoArvoreRB(Node* root, int nivel) {
    if (root == NULL) {
        return;
    }
    int i;
    if (root)
    {
        mostraNoArvoreRB(root->dir, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
        {
            printf("\t");
        }
        printf("(%d)\n", root->val);

        for (i = 0; i < nivel; i++)
        {
            printf("\t");
        }

        if(root->cor == BLACK)
        {
            printf("[BLACK]");
        }
        else
        {
            printf("[RED]");
        }

        mostraNoArvoreRB(root->esq, nivel + 1);
    }

}

// Função de impressão da árvore rubro-negra
void mostraArvoreRB(RedBlackTree* tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Arvore vazia.\n");
        return;
    }

    //printf("Raiz[%s]\n", tree->root->cor == BLACK ? "BLACK" : "RED");
    mostraNoArvoreRB(tree->root, 1); // Começa a partir do nível 1
}


int main() {
    RedBlackTree* tree = criaArvoreRB();

    printf("\n========== ARVORE RUBRO-NEGRA ==========\n\n");

    int flag = 99;
    int quantValor, valorInsercaoDelecao;

    while (flag != 0)
    {

        printf("Escolha 1 opcao:\n"
               "[1] Inserir dados\n"
               "[2] Remover dados\n"
               "[3] Mostrar arvore\n"
               "[0] Sair\n"
               "Opcao:");
        scanf("%d",&flag);

        switch (flag)
        {
            case 0:
                printf("\n\t\tSaindo . . .\n");
                sleep(1);
                printf("\n\n========== ARVORE RUBRO-NEGRA ==========\n\n");

                break;

            case 1:
                printf("\n===== Inserindo elementos na arvore =====\n\n");

                printf("Para parar de inserir valores digite 9999\n");
                printf("\nInforme a quantidade de elementos a serem inseridos:");
                scanf("%d",&quantValor);


                for(int i=0; i<quantValor; i++)
                {

                    printf("Valor[%d/%d]:",i+1,quantValor);
                    scanf("%d",&valorInsercaoDelecao);
                    if(valorInsercaoDelecao == 9999)
                    {
                        break;
                    }

                    insercao(tree, valorInsercaoDelecao);
                }
                printf("\n\n====================================\n\n");
                break;

            case 2:
                printf("\n======== Removendo elementos da arvore ========\n");


                printf("Informe o valor do elemento para a delecao:");
                scanf("%d",&valorInsercaoDelecao);

                removeNo(tree, valorInsercaoDelecao);

                printf("\n\n=====================================\n\n");
                break;

            case 3:
                printf("\n========== Mostrando arvore ==========\n");
                sleep(1);

                mostraArvoreRB(tree);


                printf("\n\n====================================\n\n");
                break;

            default:
                printf("\nOpcao invalida!");
                printf("\n\n====================================\n\n");
                break;
        }
    }

    free(tree);
    tree = NULL;

    return 0;
}
