#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * Definição da struct Territorio.
 * Armazena informações de um território no jogo War:
 * - nome: Nome do território (string de até 29 caracteres + null terminator).
 * - cor: Cor do exército que controla o território (string de até 9 caracteres + null terminator).
 * - tropas: Número de tropas no território (inteiro positivo).
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

/*
 * Função para cadastrar territórios dinamicamente.
 * Solicita ao usuário o número de territórios e preenche os dados via terminal.
 * Retorna o ponteiro para o vetor alocado e define o tamanho via parâmetro.
 */
struct Territorio* cadastrarTerritorios(int* tamanho) {
    int n;
    printf("Digite o numero de territorios a cadastrar: ");
    scanf("%d", &n);
    while (n <= 0) {  // Valida entrada positiva
        printf("Numero invalido! Digite um numero maior que 0: ");
        scanf("%d", &n);
    }
    
    // Alocação dinâmica com calloc para inicializar com zeros
    struct Territorio* mapa = (struct Territorio*)calloc(n, sizeof(struct Territorio));
    if (mapa == NULL) {
        printf("Erro na alocacao de memoria!\n");
        exit(1);
    }
    
    // Cadastro dos territórios
    int c;
    while ((c = getchar()) != '\n' && c != EOF);  // Limpa buffer
    for (int i = 0; i < n; i++) {
        printf("=== Cadastro do Territorio %d ===\n", i + 1);
        printf("Digite o nome do territorio: ");
        scanf("%s", mapa[i].nome);
        
        printf("Digite a cor do exercito: ");
        scanf("%s", mapa[i].cor);
        
        printf("Digite o numero de tropas: ");
        scanf("%d", &mapa[i].tropas);
        while (mapa[i].tropas < 0) {  // Valida tropas não negativas
            printf("Numero de tropas invalido! Digite um numero maior ou igual a 0: ");
            scanf("%d", &mapa[i].tropas);
        }
        
        while ((c = getchar()) != '\n' && c != EOF);  // Limpa buffer
    }
    
    *tamanho = n;
    return mapa;
}

/*
 * Função para exibir os dados de todos os territórios.
 * Recebe o vetor de territórios e seu tamanho via ponteiros.
 */
void exibirTerritorios(struct Territorio* mapa, int tamanho) {
    printf("\n=== Territorios Cadastrados ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", mapa[i].nome);
        printf("  Cor: %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("\n");
    }
}

/*
 * Função para simular um ataque entre dois territórios.
 * Usa números aleatórios (1 a 6) como dados de ataque e defesa.
 * Atualiza tropas e controle (cor) conforme o resultado.
 */
void atacar(struct Territorio* atacante, struct Territorio* defensor) {
    // Simulação de rolagem de dados (1 a 6)
    int dado_atacante = (rand() % 6) + 1;
    int dado_defensor = (rand() % 6) + 1;
    
    printf("\n=== Simulacao de Ataque ===\n");
    printf("Atacante (%s): Dado = %d\n", atacante->nome, dado_atacante);
    printf("Defensor (%s): Dado = %d\n", defensor->nome, dado_defensor);
    
    if (dado_atacante > dado_defensor) {
        printf("Atacante venceu! %s agora controla %s.\n", atacante->cor, defensor->nome);
        strcpy(defensor->cor, atacante->cor);  // Transfere controle
        defensor->tropas = atacante->tropas / 2;  // Transfere metade das tropas
        atacante->tropas -= defensor->tropas;  // Atacante perde tropas transferidas
    } else {
        printf("Defensor venceu! %s perde 1 tropa.\n", atacante->nome);
        atacante->tropas--;  // Atacante perde 1 tropa
        if (atacante->tropas < 0) atacante->tropas = 0;  // Garante tropas não negativas
    }
}

/*
 * Função para liberar a memória alocada dinamicamente.
 */
void liberarMemoria(struct Territorio* mapa) {
    free(mapa);
}

int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    
    int tamanho;
    // Cadastra territórios dinamicamente
    struct Territorio* mapa = cadastrarTerritorios(&tamanho);
    
    // Exibe territórios iniciais
    exibirTerritorios(mapa, tamanho);
    
    // Simulação de ataque
    int atacante_idx, defensor_idx;
    char continuar;
    do {
        // Exibe territórios para facilitar escolha
        exibirTerritorios(mapa, tamanho);
        
        // Solicita índices dos territórios
        printf("Escolha o territorio atacante (1 a %d): ", tamanho);
        scanf("%d", &atacante_idx);
        atacante_idx--;  // Ajusta para índice baseado em 0
        
        printf("Escolha o territorio defensor (1 a %d): ", tamanho);
        scanf("%d", &defensor_idx);
        defensor_idx--;  // Ajusta para índice baseado em 0
        
        // Validações
        if (atacante_idx < 0 || atacante_idx >= tamanho || defensor_idx < 0 || defensor_idx >= tamanho) {
            printf("Indices invalidos! Tente novamente.\n");
            continue;
        }
        if (atacante_idx == defensor_idx) {
            printf("Nao e possivel atacar o mesmo territorio! Tente novamente.\n");
            continue;
        }
        if (strcmp(mapa[atacante_idx].cor, mapa[defensor_idx].cor) == 0) {
            printf("Nao e possivel atacar um territorio da mesma cor! Tente novamente.\n");
            continue;
        }
        if (mapa[atacante_idx].tropas <= 0) {
            printf("O territorio atacante nao tem tropas suficientes! Tente novamente.\n");
            continue;
        }
        
        // Realiza o ataque
        atacar(&mapa[atacante_idx], &mapa[defensor_idx]);
        
        // Exibe estado atualizado
        exibirTerritorios(mapa, tamanho);
        
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
    
    // Libera memória
    liberarMemoria(mapa);
    
    return 0;
}