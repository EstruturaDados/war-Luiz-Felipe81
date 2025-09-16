#include <stdio.h>
#include <string.h>  

/*
 * Definição da struct Territorio.
 * Esta estrutura armazena as informações básicas de um território no jogo War:
 * - nome: Nome do território (string de até 29 caracteres + null terminator).
 * - cor: Cor do exército que controla o território (string de até 9 caracteres + null terminator).
 * - tropas: Número de tropas estacionadas no território (inteiro positivo).
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração do vetor de structs com capacidade para 5 territórios.
    // Isso permite armazenar múltiplas instâncias da struct de forma organizada.
    struct Territorio territorios[5];

    // Laço de entrada de dados: cadastro dos 5 territórios.
    // Utiliza um for para iterar exatamente 5 vezes, solicitando dados via terminal.
    // scanf é usado para ler strings (%s) e inteiros (%d).

    for (int i = 0; i < 5; i++) {
        printf("=== Cadastro do Territorio %d ===\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf("%s", territorios[i].nome);  // Leitura do nome (string).
        
        printf("Digite a cor do exercito: ");
        scanf("%s", territorios[i].cor);  // Leitura da cor (string).
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &territorios[i].tropas);  // Leitura do número de tropas (inteiro).
        
        // Limpa o buffer de entrada para evitar problemas com scanf subsequentes.
        // (Boa prática para misturar scanf com entradas futuras.)
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Laço de saída: exibição dos dados cadastrados.
    // Percorre o vetor e imprime as informações de cada território com formatação clara.
    // Isso ocorre imediatamente após o cadastro, garantindo resposta < 2s.
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("\n");  // Linha em branco para melhor legibilidade.
    }

    return 0;  // Fim do programa com código de saída 0 (sucesso).
}