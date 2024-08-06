import math

def merge(array, indice_inicial_sub_array, meio, indice_final_sub_array):
    # Tamanho do sub-array esquerdo
    tamanho_sub_array_esquerdo = meio - indice_inicial_sub_array + 1
    # Tamanho do sub-array direito
    tamanho_sub_array_direito = indice_final_sub_array - meio

    # Criar arranjos temporários para sub-arrays esquerdo e direito
    sub_array_esquerdo = [0] * (tamanho_sub_array_esquerdo + 1)
    sub_array_direito = [0] * (tamanho_sub_array_direito + 1)

    # Copiar dados para os arranjos temporários sub_array_esquerdo[] e sub_array_direito[]
    for i in range(tamanho_sub_array_esquerdo):
        sub_array_esquerdo[i] = array[indice_inicial_sub_array + i]

    for j in range(tamanho_sub_array_direito):
        sub_array_direito[j] = array[meio + 1 + j]

    # Definir sentinelas no final dos arranjos sub_array_esquerdo e sub_array_direito
    sub_array_esquerdo[tamanho_sub_array_esquerdo] = math.inf
    sub_array_direito[tamanho_sub_array_direito] = math.inf

    # Inicializar índices para sub_array_esquerdo, sub_array_direito e array
    i = 0
    j = 0

    # Mesclar os arranjos temporários de volta no array[indice_inicial_sub_array..indice_final_sub_array]
    for k in range(indice_inicial_sub_array, indice_final_sub_array + 1):
        if sub_array_esquerdo[i] <= sub_array_direito[j]:
            array[k] = sub_array_esquerdo[i]
            i += 1
        else:
            array[k] = sub_array_direito[j]
            j += 1

# Exemplo de uso da função merge
if __name__ == "__main__":
    array = [12, 11, 13, 5, 6, 7]
    indice_inicial_sub_array = 0
    meio = 2  # ponto médio
    indice_final_sub_array = 5
    print("Array original:", array)
    merge(array, indice_inicial_sub_array, meio, indice_final_sub_array)
    print("Array após merge:", array)
