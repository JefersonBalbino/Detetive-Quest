#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower()

// -------------------------------------------------------------------
// ESTRUTURA DA SALA (NÓ DA ÁRVORE)
// -------------------------------------------------------------------

/**
  @brief Estrutura que representa um cômodo (Sala) da mansão, 
  atuando como um nó em uma Árvore Binária.
  Cada sala possui um nome e ponteiros para os caminhos à esquerda e à direita.
 */
struct Sala {
    char *nome;
    struct Sala *esquerda;
    struct Sala *direita;
};


// -------------------------------------------------------------------
// FUNÇÕES AUXILIARES
// -------------------------------------------------------------------

/**
 * @brief Cria, de forma dinâmica, uma nova sala com o nome especificado.
 * * Aloca memória para a estrutura da sala e inicializa seus campos.
 * * @param nome O nome da sala.
 * @return struct Sala* Um ponteiro para a sala recém-criada.
 */
struct Sala* criarSala(const char *nome) {
    // 1. Aloca memória para a estrutura do nó
    struct Sala *novaSala = (struct Sala *)malloc(sizeof(struct Sala));

    if (novaSala == NULL) {
        perror("Erro ao alocar memória para a sala");
        exit(EXIT_FAILURE);
    }

    // 2. Aloca memória para o nome e copia a string
    // strdup (ou usar malloc/strcpy) é usado para garantir que o nome seja armazenado
    novaSala->nome = strdup(nome); 

    if (novaSala->nome == NULL) {
        free(novaSala);
        perror("Erro ao alocar memória para o nome da sala");
        exit(EXIT_FAILURE);
    }
    
    // 3. Inicializa os ponteiros dos caminhos como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Libera recursivamente toda a memória alocada para o mapa (árvore).
 * (Boa prática, não é requisito funcional, mas é essencial em C).
 * * @param sala O nó (sala) a partir do qual a liberação deve começar.
 */
void liberarMapa(struct Sala* sala) {
    if (sala != NULL) {
        liberarMapa(sala->esquerda);
        liberarMapa(sala->direita);
        free(sala->nome); // Libera a string do nome
        free(sala);       // Libera a estrutura da sala
    }
}


// -------------------------------------------------------------------
// FUNÇÃO DE EXPLORAÇÃO PRINCIPAL
// -------------------------------------------------------------------

/**
 * @brief Permite a navegação interativa do jogador pela mansão (árvore).
 * * O jogador pode escolher ir para a esquerda ('e') ou para a direita ('d')
 * até chegar a um cômodo sem caminhos (folha) ou digitar 's' para sair.
 * * @param raiz O nó atual (sala atual) onde o jogador está.
 */
void explorarSalas(struct Sala *raiz) {
    char escolha;
    struct Sala *salaAtual = raiz;

    // Loop principal para a exploração contínua
    while (salaAtual != NULL) {
        
        // Exibe a sala atual
        printf("----------------------------------------\n");
        printf("VOCÊ ESTÁ EM: %s\n", salaAtual->nome);
        printf("----------------------------------------\n");

        // Verifica se é um nó-folha (cômodo sem saída)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\n-- FIM DA EXPLORAÇÃO --\n");
            printf("Você encontrou um cômodo sem mais caminhos. A exploração termina aqui.\n");
            break; 
        }

        // Exibe as opções de navegação
        printf("Caminhos disponiveis:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Esquerda -> %s\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Direita -> %s\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair do jogo\n");
        printf("Sua escolha (e/d/s): ");
        
        // Lê a entrada do usuário
        scanf(" %c", &escolha);
        escolha = tolower(escolha); // Simplifica a entrada (e/E, d/D, s/S)

        // Processa a escolha
        if (escolha == 's') {
            printf("\nSaindo do Detective Quest. Volte sempre!\n");
            break;
        } else if (escolha == 'e') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda; // Move para a esquerda
            } else {
                printf("\n--- ERRO: Não há caminho à esquerda neste cômodo! ---\n\n");
            }
        } else if (escolha == 'd') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita; // Move para a direita
            } else {
                printf("\n--- ERRO: Não há caminho à direita neste cômodo! ---\n\n");
            }
        } else {
            printf("\n--- ESCOLHA INVÁLIDA: Por favor, digite 'e', 'd' ou 's'. ---\n\n");
        }
    }
}


// -------------------------------------------------------------------
// FUNÇÃO PRINCIPAL
// -------------------------------------------------------------------

/**
 * @brief Monta o mapa inicial da mansão e dá início à exploração.
 */
int main() {
    printf("========================================\n");
    printf("   BEM-VINDO(A) AO DETECTIVE QUEST\n");
    printf("     Exploração do Mapa da Mansão\n");
    printf("========================================\n\n");
    
    // -------------------------------------------------------------------
    // MONTAGEM MANUAL DA ÁRVORE (MAPA DA MANSÃO)
    // -------------------------------------------------------------------
    
    // Nível 0: Raiz
    struct Sala *hall = criarSala("Hall de Entrada");

    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");

    // Nível 2 - Esquerda
    hall->esquerda->esquerda = criarSala("Escritorio");
    hall->esquerda->direita = criarSala("Sala de Jantar"); // Nó-folha!

    // Nível 2 - Direita
    hall->direita->esquerda = criarSala("Despensa"); // Nó-folha!
    hall->direita->direita = criarSala("Jardim");

    // Nível 3 - Esquerda (a partir do Escritório)
    hall->esquerda->esquerda->esquerda = criarSala("Biblioteca"); // Nó-folha!
    hall->esquerda->esquerda->direita = criarSala("Quarto Principal");

    // Nível 3 - Direita (a partir do Jardim)
    hall->direita->direita->esquerda = criarSala("Piscina"); // Nó-folha!
    // hall->direita->direita->direita = NULL (Folha, não precisa de chamada)

    // Nível 4 (a partir do Quarto Principal)
    hall->esquerda->esquerda->direita->direita = criarSala("Banheiro Privativo"); // Nó-folha!

    // -------------------------------------------------------------------
    // INÍCIO DA EXPLORAÇÃO
    // -------------------------------------------------------------------
    
    explorarSalas(hall);
    
    // Liberação de memória ao sair do programa
    liberarMapa(hall);

    printf("\nPrograma finalizado com sucesso.\n");
    return 0;
}