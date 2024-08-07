import math

def mesclar(array, inicio, meio, fim):
    # Tamanho dos sub-arrays esquerdo e direito
    tamanho_esquerdo = meio - inicio + 1
    tamanho_direito = fim - meio

    # Criar arranjos temporários para sub-arrays esquerdo e direito
    array_esquerdo = [0] * (tamanho_esquerdo + 1)
    array_direito = [0] * (tamanho_direito + 1)

    # Copiar dados para os arranjos temporários
    for i in range(tamanho_esquerdo):
        array_esquerdo[i] = array[inicio + i]

    for j in range(tamanho_direito):
        array_direito[j] = array[meio + 1 + j]

    # Definir sentinelas no final dos arranjos
    array_esquerdo[tamanho_esquerdo] = math.inf
    array_direito[tamanho_direito] = math.inf

    # Inicializar índices para sub-arrays e array principal
    i = 0
    j = 0

    # Mesclar os arranjos temporários de volta no array
    for k in range(inicio, fim + 1):
        if array_esquerdo[i] <= array_direito[j]:
            array[k] = array_esquerdo[i]
            i += 1
        else:
            array[k] = array_direito[j]
            j += 1

# Exemplo de uso da função mesclar
if __name__ == "__main__":
    array = [12, 11, 13, 5, 6, 7]
    inicio = 0
    meio = 2  # ponto médio
    fim = 5
    print("Array original:", array)
    mesclar(array, inicio, meio, fim)
    print("Array após mesclar:", array)
