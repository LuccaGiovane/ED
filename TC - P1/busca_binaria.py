def busca_binaria(lista, inicio, fim, elemento):
    # Caso base: quando há apenas um elemento na sub-lista
    if inicio == fim:
        if lista[inicio] == elemento:
            return inicio  # Elemento encontrado
        else:
            return -1  # Elemento não encontrado
    else:
        # Calcula o índice do meio
        meio = (inicio + fim) // 2

        # Decide qual metade continuar a busca
        if elemento <= lista[meio]:
            return busca_binaria(lista, inicio, meio, elemento)
        else:
            return busca_binaria(lista, meio + 1, fim, elemento)


# Exemplo de uso
lista = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
elemento_procurado = 6
resultado = busca_binaria(lista, 0, len(lista) - 1, elemento_procurado)
print(
    f"Elemento {elemento_procurado} {'encontrado no índice ' + str(resultado) if resultado != -1 else 'não encontrado'}")
