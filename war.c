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
 * Função para atribuir uma missão aleatória ao jogador.
 * Copia a missão sorteada para a variável destino usando strcpy.
 */
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;  // Sorteia um índice
    strcpy(destino, missoes[indice]);    // Copia a missão sorteada
}

/*
 * Função para exibir a missão do jogador.
 * Recebe a missão por valor para exibição.
 */
void exibirMissao(char* missao) {
    printf("\n=== Missao do Jogador ===\n");
    printf("Sua missao: %s\n\n", missao);
}

/*
 * Função para verificar se a missão foi cumprida.
 * Implementa uma lógica simples para algumas missões.
 */
int verificarMissao(char* missao, struct Territorio* mapa, int tamanho) {
    // Verifica missão: "Conquistar 3 territórios de uma mesma cor"
    if (strcmp(missao, "Conquistar 3 territorios de uma mesma cor") == 0) {
        for (int i = 0; i < tamanho; i++) {
            int contagem = 0;
            for (int j = 0; j < tamanho; j++) {
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    contagem++;
                }
            }
            if (contagem >= 3) {
                return 1;  // Missão cumprida
            }
        }
    }
    // Verifica missão: "Eliminar todas as tropas da cor vermelha"
    else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "Vermelho") == 0 && mapa[i].tropas > 0) {
                return 0;  // Ainda há tropas vermelhas
            }
        }
        return 1;  // Nenhuma tropa vermelha
    }
    // Verifica missão: "Controlar 50% dos territórios"
    else if (strcmp(missao, "Controlar 50% dos territorios") == 0) {
        char* cor_jogador = mapa[0].cor;  // Assume a cor do primeiro território como a do jogador
        int contagem = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0) {
                contagem++;
            }
        }
        if (contagem >= tamanho / 2) {
            return 1;  // Missão cumprida
        }
    }
    // Verifica missão: "Ter pelo menos 10 tropas em um território"
    else if (strcmp(missao, "Ter pelo menos 10 tropas em um territorio") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10 && strcmp(mapa[i].cor, mapa[0].cor) == 0) {
                return 1;  // Missão cumprida
            }
        }
    }
    // Verifica missão: "Conquistar um território inimigo"
    else if (strcmp(missao, "Conquistar um territorio inimigo") == 0) {
        // Assume que a conquista é verificada pelo ataque bem-sucedido
        // Como o ataque já modifica a cor, verificamos se algum território tem a cor do jogador
        char* cor_jogador = mapa[0].cor;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, cor_jogador) == 0 && i != 0) {
                return 1;  // Território conquistado
            }
        }
    }
    
    return 0;  // Missão não cumprida
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
 * Libera o vetor de territórios e a missão do jogador.
 */
void liberarMemoria(struct Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

int main() {
    srand(time(NULL));  // Inicializa gerador de números aleatórios
    
    // Vetor de missões pré-definidas
    char* missoes[] = {
        "Conquistar 3 territorios de uma mesma cor",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar 50% dos territorios",
        "Ter pelo menos 10 tropas em um territorio",
        "Conquistar um territorio inimigo"
    };
    int totalMissoes = 5;
    
    // Alocação dinâmica para a missão do jogador
    char* missao = (char*)malloc(100 * sizeof(char));
    if (missao == NULL) {
        printf("Erro na alocacao de memoria para missao!\n");
        exit(1);
    }
    
    // Atribui e exibe a missão
    atribuirMissao(missao, missoes, totalMissoes);
    exibirMissao(missao);
    
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
        
        // Verifica se a missão foi cumprida
        if (verificarMissao(missao, mapa, tamanho)) {
            printf("\nParabens! Voce cumpriu sua missao: %s\n", missao);
            liberarMemoria(mapa, missao);
            return 0;  // Encerra o jogo
        }
        
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');
    
    // Libera memória
    liberarMemoria(mapa, missao);
    
    return 0;
}