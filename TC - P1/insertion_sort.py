def insertionSort(vetor):
    #começa do segundo elemento [1] pois o primeiro ja esta ordenado
    for j in range(1, len(vetor)):
        valor = vetor[j] #valor a ser inserido na posição ordenada
        i = j - 1 #esse 'i' recebe o valor anterior no vetor do nosso elemento

        # aqui vai começar a mover os elementos que sao maiores que nosso valor para a direita dele
        # e ele vai andar para a esquerda ate achar um valor que seja menor que ele descobrindo assim
        # sua posicao no vetor.
        # i >=0 -> isso é pq como estamos decrementando o 'i' caso ele chegue em 'i=0' nao tentar pegar valores negativos
        # vetor[i] > valor -> verifica o valor a esquerda com nosso valor atual para ver se e menor
        while i >=0 and vetor[i] > valor:
            vetor[i + 1] = vetor[i] #copiamos o valor anterior (menor que o nosso valor) uma casa para a direita
            i -= 1 #decrementa o valor de i para na proxima execução do loop pegar outro elemento mais a esquerda

        #como o loop acabou sabemos que o valor na posição i é menor que o valor de estudos, colocamos nosso
        # valor em 'i+1'
        vetor[i+1] = valor

vetor = [5, 2, 4, 6, 1, 3]
print(f'Vetor = {vetor}')
insertionSort(vetor)
print(f'Vetor pós INSERTION-SORT = {vetor}')

def insertionSortDescrescente(vetor):
    # percorre a partir do 2 elemento do vetor
    for j in range(1, len(vetor)):
        valor = vetor[j] #elemento atual da verificação
        i = j - 1 #compara com o valor imediatamente a esquerda

        #i >=0 para nao sair do range do vetor e compara se o valor a esquerda é menor que o atual
        while(i >=0 and vetor[i] < valor):
            vetor[i + 1] = vetor[i] #move o elemento menor para a direita para a ordenação decrescente
            i -= 1 #decrementa o 'i' para ir para o proximo elemento a esquerda

        #como o 'i' parou em uma posição de item que e maior (nesse caso) que ela, colocamos na posição i+1
        vetor[i+1] = valor

insertionSortDescrescente(vetor)
print(f'Vetor pós INSERTION-SORT-DECRESCENTE = {vetor}')