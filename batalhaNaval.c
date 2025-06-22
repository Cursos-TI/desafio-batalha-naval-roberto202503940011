#include <stdio.h>

// Desafio Batalha Naval - MateCheck - Nível Novato
// Este programa implementa um sistema básico de posicionamento de navios em um tabuleiro 10x10
// Autor: Sistema de Batalha Naval
// Data: 2024

// Constantes do jogo
#define TAMANHO_TABULEIRO 10  // Dimensão do tabuleiro (10x10)
#define TAMANHO_NAVIO 3       // Tamanho fixo de cada navio
#define AGUA 0                // Valor que representa água no tabuleiro
#define NAVIO 3               // Valor que representa parte de navio no tabuleiro

// Estrutura para representar coordenadas
typedef struct {
    int linha;    // Coordenada da linha (0-9)
    int coluna;   // Coordenada da coluna (0-9)
} Coordenada;

// Estrutura para representar um navio
typedef struct {
    Coordenada inicio;    // Coordenada inicial do navio
    char orientacao;      // 'H' para horizontal, 'V' para vertical
} Navio;

/**
 * Função para inicializar o tabuleiro com água (valor 0)
 * Parâmetro: tabuleiro - matriz 10x10 que representa o campo de batalha
 */
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Loop aninhado para percorrer toda a matriz
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;  // Inicializa com água
        }
    }
    printf("Tabuleiro inicializado com sucesso!\n");
}

/**
 * Função para validar se as coordenadas do navio estão dentro dos limites do tabuleiro
 * Parâmetros: navio - estrutura contendo informações do navio
 * Retorna: 1 se válido, 0 se inválido
 */
int validarCoordenadas(Navio navio) {
    // Verifica se a coordenada inicial está dentro dos limites
    if (navio.inicio.linha < 0 || navio.inicio.linha >= TAMANHO_TABULEIRO ||
        navio.inicio.coluna < 0 || navio.inicio.coluna >= TAMANHO_TABULEIRO) {
        return 0;  // Coordenada inicial inválida
    }
    
    // Verifica se o navio inteiro cabe no tabuleiro
    if (navio.orientacao == 'H') {
        // Navio horizontal: verifica se não ultrapassa a direita
        if (navio.inicio.coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;
        }
    } else if (navio.orientacao == 'V') {
        // Navio vertical: verifica se não ultrapassa para baixo
        if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
            return 0;
        }
    } else {
        return 0;  // Orientação inválida
    }
    
    return 1;  // Coordenadas válidas
}

/**
 * Função para verificar se há sobreposição entre navios
 * Parâmetros: tabuleiro - matriz do jogo, navio - estrutura do navio a ser verificado
 * Retorna: 1 se há sobreposição, 0 se não há
 */
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio) {
    // Verifica cada posição que o navio irá ocupar
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        if (navio.orientacao == 'H') {
            // Navio horizontal: incrementa coluna
            linha = navio.inicio.linha;
            coluna = navio.inicio.coluna + i;
        } else {
            // Navio vertical: incrementa linha
            linha = navio.inicio.linha + i;
            coluna = navio.inicio.coluna;
        }
        
        // Se a posição já está ocupada, há sobreposição
        if (tabuleiro[linha][coluna] != AGUA) {
            return 1;
        }
    }
    
    return 0;  // Não há sobreposição
}

/**
 * Função para posicionar um navio no tabuleiro
 * Parâmetros: tabuleiro - matriz do jogo, navio - estrutura do navio
 * Retorna: 1 se posicionado com sucesso, 0 se falhou
 */
int posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio, int numeroNavio) {
    // Validar coordenadas
    if (!validarCoordenadas(navio)) {
        printf("ERRO: Coordenadas inválidas para o navio %d!\n", numeroNavio);
        return 0;
    }
    
    // Verificar sobreposição
    if (verificarSobreposicao(tabuleiro, navio)) {
        printf("ERRO: Navio %d sobrepõe outro navio!\n", numeroNavio);
        return 0;
    }
    
    // Posicionar o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        if (navio.orientacao == 'H') {
            // Navio horizontal
            linha = navio.inicio.linha;
            coluna = navio.inicio.coluna + i;
        } else {
            // Navio vertical
            linha = navio.inicio.linha + i;
            coluna = navio.inicio.coluna;
        }
        
        // Marca a posição com o valor do navio
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    printf("Navio %d posicionado com sucesso na posição (%d,%d) - %s\n", 
           numeroNavio, navio.inicio.linha, navio.inicio.coluna, 
           (navio.orientacao == 'H') ? "Horizontal" : "Vertical");
    
    return 1;  // Sucesso
}

/**
 * Função para exibir o tabuleiro no console
 * Parâmetro: tabuleiro - matriz 10x10 do jogo
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n");
    printf("0 = Água | 3 = Navio\n\n");
    
    // Exibir numeração das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Exibir o tabuleiro linha por linha
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);  // Numeração da linha
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);  // Valor da posição
        }
        printf("\n");  // Nova linha após cada linha do tabuleiro
    }
    printf("\n");
}

/**
 * Função principal do programa
 */
int main() {
    // Declaração da matriz do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    printf("=== SISTEMA DE BATALHA NAVAL - NÍVEL NOVATO ===\n\n");
    
    // Passo 1: Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Passo 2: Definir e posicionar os navios
    
    // Definição do Navio 1 - Horizontal
    // Posição inicial: linha 2, coluna 1
    // Ocupará as posições: (2,1), (2,2), (2,3)
    Navio navio1 = {
        .inicio = {2, 1},    // Coordenada inicial
        .orientacao = 'H'    // Orientação horizontal
    };
    
    // Definição do Navio 2 - Vertical  
    // Posição inicial: linha 5, coluna 7
    // Ocupará as posições: (5,7), (6,7), (7,7)
    Navio navio2 = {
        .inicio = {5, 7},    // Coordenada inicial
        .orientacao = 'V'    // Orientação vertical
    };
    
    // Posicionar os navios no tabuleiro
    printf("\n--- POSICIONAMENTO DOS NAVIOS ---\n");
    
    // Tentar posicionar o primeiro navio
    if (posicionarNavio(tabuleiro, navio1, 1)) {
        printf("✓ Navio 1 posicionado corretamente\n");
    } else {
        printf("✗ Falha ao posicionar navio 1\n");
        return 1;  // Encerra o programa em caso de erro
    }
    
    // Tentar posicionar o segundo navio
    if (posicionarNavio(tabuleiro, navio2, 2)) {
        printf("✓ Navio 2 posicionado corretamente\n");
    } else {
        printf("✗ Falha ao posicionar navio 2\n");
        return 1;  // Encerra o programa em caso de erro
    }
    
    // Passo 3: Exibir o tabuleiro final
    printf("\n--- RESULTADO FINAL ---\n");
    exibirTabuleiro(tabuleiro);
    
    // Resumo dos navios posicionados
    printf("=== RESUMO DOS NAVIOS ===\n");
    printf("Navio 1: Horizontal - Posições (2,1), (2,2), (2,3)\n");
    printf("Navio 2: Vertical   - Posições (5,7), (6,7), (7,7)\n");
    printf("\nPrograma executado com sucesso!\n");
    
    return 0;
}
