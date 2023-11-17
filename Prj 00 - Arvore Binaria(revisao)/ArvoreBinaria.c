#include<stdio.h>
#include <stdlib.h>

struct st_arvore
{
    int valor;
    struct st_arvore *sad; //sub arvore direita (sad)
    struct st_arvore *sae; //sub arvore esquerda (sae)
};

typedef struct st_arvore arvore;

arvore* criaArvore()
{
    return NULL;
};

int arvoreEstaVazia(arvore* t)
{
    return t == NULL;
}

void mostraArvore(arvore* t)
{
    printf("<");
    if(!arvoreEstaVazia(t))
    {
        printf("%d",t->valor);
        mostraArvore(t->sae);
        mostraArvore(t->sad);
    }
    printf(">");
}

void insereDadoArvore(arvore** t, int num)
{
    if (*t == NULL)
    {
        *t = (arvore*)malloc(sizeof(arvore));
        (*t) -> sae = NULL;
        (*t) -> sad = NULL;
        (*t) -> valor = num;
    }
    else
        {
            if (num < (*t) -> valor)
            {
                insereDadoArvore(&(*t) -> sae, num);
            }
            if (num > (*t) -> valor)
            {
                insereDadoArvore(&(*t) -> sad, num);
            }
        }
}

int estaNaArvore(arvore* t, int num)
{
    if(arvoreEstaVazia(t))
    {
        return 0;
    }

    return t -> valor == num || estaNaArvore(t -> sae, num) || estaNaArvore(t -> sad, num);
}

void recursoPosOrdem(arvore* t)
{
    if(!arvoreEstaVazia(t))
    {
        if(t -> sae != NULL)
        {
            recursoPosOrdem(t -> sae);
        }
        if(t -> sad != NULL)
        {
            recursoPosOrdem(t -> sad);
        }
        printf("%d",t->valor);
    }
}

int main()
{
    int opcao, quantidadeElementos, dado;
    arvore* t = criaArvore();

    printf("========== ARVORE BINARIA ==========\n\n");
    printf("[1] INSERIR DADO NA ARVORE\n");
    printf("[2] MOSTRAR ARVORE\n" );
    printf("[3] VERIFICAR SE ARVORE ESTA VAZIA\n" );
    printf("[4] VERIFICAR SE DADO ESTA NA ARVORE\n" );
    printf("[0] SAIR\n\n");
    scanf("%d", &opcao);

   

    switch (opcao)
    {

        case 1:
            printf("Insira a quantidade de elementos a serem inseridos: ");
            scanf("%d", &quantidadeElementos);

            for(int i=0; i<quantidadeElementos; i++)
            {
                int dado;
                printf("Insira o dado[&d]/[&d]: ", i+1, quantidadeElementos);
                scanf("%d", &dado);
                insereDadoArvore(&t, dado);
            }
            break;

        case 2:
            mostraArvore(t);
            break;

        case 3:
            if(arvoreEstaVazia(t))
            {
                printf("\nArvore vazia!\n");
            }
            else
            {
                printf("\nArvore populada!\n");
            }
            break;
        
        case 4:

            printf("Insira o dado a ser verificado: ");
            scanf("%d", &dado);

            if(estaNaArvore(t ,dado))
            {
                printf("\nO elemento %d esta na arvore\n", dado);
            }
            else
            {
                printf("\nO elemento %d nao esta na arvore\n", dado);
            }
            break;
        
        case 0:
            free(t);//libera memoria
            printf("Saindo...\n");
            ("====================================\n\n");
            break;
            
        default:
            printf("Opcao invalida!\n");
            break;
    }
   


    /*arvore* t = criaArvore();

    insereDadoArvore(&t, 12);
    insereDadoArvore(&t, 15);
    insereDadoArvore(&t, 10);
    insereDadoArvore(&t, 13);

    mostraArvore(t);

    if(arvoreEstaVazia(t))
    {
        printf("\nArvore vazia!\n");
    }
    else
    {
        printf("\nArvore populada!\n");
    }

    if(estaNaArvore(t ,15))
    {
        printf("\nO elemento 15 esta na arvore\n");
    }
    else
    {
        printf("\nO elemento 15 nao esta na arvore\n");
    }

    if(estaNaArvore(t ,62))
    {
        printf("\nO elemento 62 esta na arvore\n");
    }
    else
    {
        printf("\nO elemento 62 nao esta na arvore\n");
    }

    
    */

    return 0;
}