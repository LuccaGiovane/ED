def busca_linear(lista, tamanho, elemento):
    # Caso base: quando a lista tem apenas um elemento
    if tamanho == 1:
        if lista[tamanho - 1] == elemento:
            return tamanho - 1  # Elemento encontrado
        else:
            return -1  # Elemento não encontrado
    else:
        # Verifica o último elemento da sublista
        if lista[tamanho - 1] == elemento:
            return tamanho - 1  # Elemento encontrado
        else:
            return busca_linear(lista, tamanho - 1, elemento)

# Exemplo de uso
lista = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
elemento_procurado = 6
resultado = busca_linear(lista, len(lista), elemento_procurado)
print(f"Elemento {elemento_procurado} {'encontrado no índice ' + str(resultado) if resultado != -1 else 'não encontrado'}")
