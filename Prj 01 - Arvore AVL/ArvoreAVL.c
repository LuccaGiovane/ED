#include<stdio.h>
#include<stdlib.h>

typedef struct AVL_arvore
{
    int valor;
    struct AVL_arvore *esq;
    struct AVL_arvore *dir;
    int altura;
} arvore;



//========== Prototipos ==========

int fatorDeBalanceamento(arvore* t);
int retornaAlturaDaMaiorSubArvore(int a, int b);
int retornaAlturaDoNo(arvore* t);


arvore* insereDadoArvore(arvore* t, int num);
arvore* removeElementoDaArvore(arvore* t, int num);
arvore* rotacaoSimplesEsquerda(arvore* t);
arvore* rotacaoSimplesDireita(arvore* t);
arvore* rotacaoDireitaEsquerda(arvore* t);
arvore* rotacaoEsquerdaDireita(arvore* t);
arvore* balancear(arvore* t);

//================================

int fatorDeBalanceamento(arvore* t)
//Calcula o fator de balanceamento para as rotações da AVL
{
    if(t)
    {
        /*
              Fator de Balanceamento FB = hd – he
              Se o FB:
                  ==  0, a árvore está balanceada.
                  == -x, a árvore está desbalanceada para a esquerda -> rotações para a direita.
                  == +x, a árvore está desbalanceada para a direita -> rotações para a esquerda.
          */

        return retornaAlturaDoNo(t->esq) - retornaAlturaDoNo(t->dir);
    }
    else
    {
        return 0;
    }



}

int retornaAlturaDaMaiorSubArvore(int a, int b)
{
    return (a > b) ? a : b;
}

int retornaAlturaDoNo(arvore* t)
{
    if (t == NULL)
    {
        return -1;
    }
    else
    {
        return t -> altura;
    }
}


//arvore* novoNo(int num)
//{
//    arvore *novo = malloc(sizeof(arvore));
//
//    if(novo)
//    {
//        novo -> valor = num;
//        novo -> esq = NULL;
//        novo -> dir = NULL;
//        novo -> altura = 0;
//    }
//    else
//    {
//        printf("\n ERRO_novoNo, Erro ao alocar nó!\n");
//    }
//
//    return novo;
//}

arvore* insereDadoArvore(arvore* t, int num)
{

    if (t == NULL)
    {

        t = (arvore*)malloc(sizeof(arvore));

        t -> valor = num;
        t -> esq = NULL;
        t -> dir = NULL;
        //altura da folha sempre sera 0
        t -> altura = 0;
    }
    else
    {

        if (num < t -> valor)
        {
            t -> esq = insereDadoArvore(t -> esq, num);
        }
        if (num > t -> valor)
        {
            t -> dir = insereDadoArvore(t -> dir, num);
        }
    }
    //Recalcula a altura de todos os nos entre a raiz e o novo no inserido

    t -> altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(t -> esq), retornaAlturaDoNo(t -> dir)) + 1;

    //verifica a nescessidade de rebalancear a arvore
    t = balancear(t);

    return t;
}

arvore* removeElementoDaArvore(arvore* t, int num)
{
    if(t == NULL)
    {
        printf("Elemento nao encontrado\n");
        return NULL;
    }
    else//procura o nó que sera removido
    {
        if(t -> valor == num){
            //remove nós sem filhos (folhas)
            if(t -> esq == NULL && t -> dir == NULL)
            {
                free(t);
                t = NULL;

                printf("Elemento [%d] removido. tipo:[Folha]\n",num);

                return t;
            }
            else
            {
                //remove nós com dois filhos
                if(t -> esq != NULL && t -> dir != NULL)
                {
                    arvore* aux = t -> esq;

                    while(aux -> dir != NULL)
                    {
                        aux = aux -> dir;
                    }

                    t -> valor = aux -> valor;
                    aux -> valor = num;

                    printf("Elemento [%d] removido. tipo:[Dois filhos]\n",num);

                    t -> esq = removeElementoDaArvore(t -> esq, num);

                    return t;
                }
                else
                {
                    //remove nos com um filho
                    arvore* aux;

                    if(t -> esq != NULL)
                    {
                        aux = t -> esq;
                    }
                    else
                    {
                        aux = t -> dir;
                    }
                    free(t);
                    printf("Elemento [%d] removido. tipo:[Um filho]\n",num);
                    return aux;
                }

            }
        }
        else
        {
            if(num < t -> valor)
            {
                t -> esq = removeElementoDaArvore(t -> esq, num);
            }
            else
            {
                t -> dir = removeElementoDaArvore(t -> dir, num);
            }
        }

        //Recalcula a altura de todos os nos entre a raiz e o novo no inserido
        t -> altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(t -> esq), retornaAlturaDoNo(t -> dir)) + 1;

        //verifica a nescessidade de rebalancear a arvore
        printf("Trace, Remoção antes de balancear\n");
        t = balancear(t);
        printf("Trace, Remoção apos de balancear\n");

        return t;
    }
}

arvore* rotacaoSimplesEsquerda(arvore* t)
{

    //Rotação para caso: RR
    /*
     variaveis usadas: arvore *t, arvore *y, arvore *f:

       Raiz(t)                            (y) Nova Raiz
            \                                 /       \
             Nó(y)       ->           (t) Folha       Folha
            /   \
         (f)     Folha
    */

    arvore *y, *f;//f é um possivel filho que por ventura possa existir

    y = t->dir; // y aponta pra perninha direita da raiz t
    f = y->esq; // recebe o possivel filho a esquerda

    y->esq = t; // nova raiz recebe na perninha esquerda a antiga
    t->dir = f; // se existir o possivel filho f, vai pra perninha direita da antiga raiz

    //recalcula as novas alturas dos nos t e y
    t->altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(t->esq), retornaAlturaDoNo(t->dir) + 1);
    y->altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(y->esq), retornaAlturaDoNo(y->dir) + 1);


    return y; // retorna a nova raiz da arvore ou sub arvore
}

arvore* rotacaoSimplesDireita(arvore* t)
{
    //Rotação para caso: LL
    /*
     variaveis usadas: arvore *t, arvore *y, arvore *f:

            Raiz (r)               Nova Raiz (y)
           /                    /       \
          (y)Nó         ->     Folha       Folha (t)
         /     \
      Folha      (f)
    */

    arvore *y, *f;

    y = t->esq;
    f = y->dir;

    y->dir = t;
    t->esq = f;

    t->altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(t->esq),retornaAlturaDoNo(t->dir) + 1);
    y->altura = retornaAlturaDaMaiorSubArvore(retornaAlturaDoNo(y->esq), retornaAlturaDoNo(y->dir) + 1);

    // retorna um ponteiro para a nova raiz
    return y;
}

arvore* rotacaoDireitaEsquerda(arvore *t)
{
    //Rotação para caso: RL
    /*
        Raiz                      (antigo Nó) Nova Raiz
            \                                 /       \
             Nó       ->    (antiga raiz) Folha       Folha
            /
        Folha
    */

    t -> dir = rotacaoSimplesDireita(t -> dir); //troca a posição do Nó e da Folha. Ex:
    /*
        Raiz                  100                100
            \                    \                  \
             Nó       ->         200      ->        150
            /                    /                     \
        Folha                 150                      200
    */

    return rotacaoSimplesEsquerda(t); // retorna a nova raiz da arvore ou sub arvore rotacionada a esquerda:
    /*
        100
          \                                   150
           150         ->        return      /   \
             \                             100   200
              200

    */

}

arvore* rotacaoEsquerdaDireita(arvore *t)
{
    //Rotação para caso: LR
    /*
            Raiz                Nova Raiz (antigo Nó)
           /                    /       \
          Nó         ->     Folha       Folha (antiga raiz)
           \
            Folha
    */

    t -> esq = rotacaoSimplesEsquerda(t -> esq); //troca a posição do Nó e da Folha. Ex:
    return rotacaoSimplesDireita(t);

}

arvore* balancear(arvore* t)
{

    int fb = fatorDeBalanceamento(t);

    //rotacao simples a esquerda
    if(fb < -1 && fatorDeBalanceamento(t -> dir) <= 0)
    {
        t =  rotacaoSimplesEsquerda(t);
    }
        //rotacao simples a direita
    else if(fb > 1 && fatorDeBalanceamento(t -> esq) >= 0)
    {
        t =  rotacaoSimplesDireita(t);
    }
        //rotacao dupla a esquerda
    else if(fb > 1 && fatorDeBalanceamento(t -> esq) < 0)
    {
        printf("Trace, rotacao dupla a esquerda 1\n");
        t = rotacaoEsquerdaDireita(t);
    }
        //rotacao dupla a direita
    else if(fb < -1 && fatorDeBalanceamento(t -> dir) > 0)
    {
        printf("Trace, rotacao dupla a direita 2\n");
        t = rotacaoDireitaEsquerda(t);
    }
    return t;
}


void mostraArvore(arvore* t, int nivel)
{
    int i;
    if (t)
    {
        mostraArvore(t->dir, nivel + 1);
        printf("\n\n");

        for (i = 0; i < nivel; i++)
        {
            printf("\t");
        }
        printf("%d", t->valor);

        mostraArvore(t->esq, nivel + 1);
    }
}


int main()
{
    int flag = 999;
    int num;

    //explicando as gambiarra
    printf("\t\t******************\n"
           "\t\t*** IMPORTANTE ***\n"
           "\t\t******************\n"
           "- A arvore sera mostrada da esquerda para a direita.\n"
           "  Ex:\n"
           "                (folha)\n"
           "              /\n"
           "         (No)\n"
           "       /      \\ \n"
           " (raiz)         (folha)\n"
           "       \\ \n"
           "         (folha)\n");

    //cria a arvore
    arvore *tree = NULL;

    printf("\n======== Arvore AVL ========\n\n");


    while(flag != 0)
    {
        printf(
                "[1] Inserir elementos na arvore\n"
                "[2] Remover elementos da arvore\n"
                "[3] Mostrar arvore\n"
                "[0] Sair\n"
                "Acao desejada:");
        scanf("%d",&flag);

        switch (flag)
        {
            case 0:
                flag = 0;
                printf("\tSaindo..."
                       "\t\n======== Arvore AVL ========\n");
                break;

            case 1:

                printf("\n===== Inserindo elementos na arvore =====\n\n");

                printf("\nDigite o numero que deseja inserir na arvore: ");
                scanf("%d",&num);

                tree = insereDadoArvore(tree, num);


                printf("\n===== Elemento inserido com sucesso! =====\n\n");

                break;

            case 2:

                printf("\n===== Removendo elementos da arvore =====\n");

                printf("\nDigite o numero que deseja remover da arvore: ");
                scanf("%d",&num);
                tree = removeElementoDaArvore(tree, num);

                printf("\n===== Elemento removido com sucesso! =====\n\n");

                break;

            case 3:

                printf("\n===== Mostrando arvore =====\n");


                mostraArvore(tree, 1); // Atualize a árvore com o retorno da função
                printf("\n============================\n\n");

                break;

            default:

                printf("\n*** Opcao invalida! ***\n");
                flag = 999;

                break;
        }

    }
    return 0;
}

