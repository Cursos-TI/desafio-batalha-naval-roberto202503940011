#include <stdio.h>

// Desafio Batalha Naval - MateCheck - Nível Aventureiro
// Este programa implementa um sistema de posicionamento de navios em um tabuleiro 10x10
// Inclui suporte para navios horizontais, verticais e diagonais
// Autor: Sistema de Batalha Naval
// Data: 2024

// Constantes do jogo
#define TAMANHO_TABULEIRO 10  // Dimensão do tabuleiro (10x10)
#define TAMANHO_NAVIO 3       // Tamanho fixo de cada navio
#define AGUA 0                // Valor que representa água no tabuleiro
#define NAVIO 3               // Valor que representa parte de navio no tabuleiro
#define TOTAL_NAVIOS 4        // Número total de navios no jogo

// Estrutura para representar coordenadas
typedef struct {
    int linha;    // Coordenada da linha (0-9)
    int coluna;   // Coordenada da coluna (0-9)
} Coordenada;

// Estrutura para representar um navio
typedef struct {
    Coordenada inicio;    // Coordenada inicial do navio
    char orientacao;      // 'H' = horizontal, 'V' = vertical, 'D1' = diagonal principal, 'D2' = diagonal secundária
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
    printf("Tabuleiro 10x10 inicializado com sucesso!\n");
}

/**
 * Função para obter o nome da orientação do navio
 * Parâmetro: orientacao - caractere representando a orientação
 * Retorna: string com o nome da orientação
 */
const char* obterNomeOrientacao(char orientacao) {
    switch (orientacao) {
        case 'H': return "Horizontal";
        case 'V': return "Vertical";
        case 'D': return "Diagonal Principal";
        case 'A': return "Diagonal Secundária";
        default: return "Inválida";
    }
}

/**
 * Função para validar se as coordenadas do navio estão dentro dos limites do tabuleiro
 * Considera todas as orientações: horizontal, vertical e diagonais
 * Parâmetros: navio - estrutura contendo informações do navio
 * Retorna: 1 se válido, 0 se inválido
 */
int validarCoordenadas(Navio navio) {
    // Verifica se a coordenada inicial está dentro dos limites
    if (navio.inicio.linha < 0 || navio.inicio.linha >= TAMANHO_TABULEIRO ||
        navio.inicio.coluna < 0 || navio.inicio.coluna >= TAMANHO_TABULEIRO) {
        return 0;  // Coordenada inicial inválida
    }
    
    // Verifica se o navio inteiro cabe no tabuleiro baseado na orientação
    switch (navio.orientacao) {
        case 'H':  // Navio horizontal
            // Verifica se não ultrapassa a direita
            if (navio.inicio.coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'V':  // Navio vertical
            // Verifica se não ultrapassa para baixo
            if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'D':  // Diagonal principal (linha e coluna aumentam juntas)
            // Verifica se não ultrapassa os limites direita e inferior
            if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
                navio.inicio.coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'A':  // Diagonal secundária (linha aumenta, coluna diminui)
            // Verifica se não ultrapassa os limites inferior e esquerda
            if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
                navio.inicio.coluna - (TAMANHO_NAVIO - 1) < 0) {
                return 0;
            }
            break;
            
        default:
            return 0;  // Orientação inválida
    }
    
    return 1;  // Coordenadas válidas
}

/**
 * Função para calcular as coordenadas de uma posição específica do navio
 * Parâmetros: navio - estrutura do navio, posicao - índice da posição (0, 1, 2)
 *            linha - ponteiro para armazenar a linha calculada
 *            coluna - ponteiro para armazenar a coluna calculada
 */
void calcularPosicaoNavio(Navio navio, int posicao, int* linha, int* coluna) {
    switch (navio.orientacao) {
        case 'H':  // Horizontal: incrementa coluna
            *linha = navio.inicio.linha;
            *coluna = navio.inicio.coluna + posicao;
            break;
            
        case 'V':  // Vertical: incrementa linha
            *linha = navio.inicio.linha + posicao;
            *coluna = navio.inicio.coluna;
            break;
            
        case 'D':  // Diagonal principal: incrementa linha e coluna
            *linha = navio.inicio.linha + posicao;
            *coluna = navio.inicio.coluna + posicao;
            break;
            
        case 'A':  // Diagonal secundária: incrementa linha, decrementa coluna
            *linha = navio.inicio.linha + posicao;
            *coluna = navio.inicio.coluna - posicao;
            break;
    }
}

/**
 * Função para verificar se há sobreposição entre navios
 * Suporta todas as orientações incluindo diagonais
 * Parâmetros: tabuleiro - matriz do jogo, navio - estrutura do navio a ser verificado
 * Retorna: 1 se há sobreposição, 0 se não há
 */
int verificarSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], Navio navio) {
    // Verifica cada posição que o navio irá ocupar
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha, coluna;
        
        // Calcula a posição atual do navio baseada na orientação
        calcularPosicaoNavio(navio, i, &linha, &coluna);
        
        // Se a posição já está ocupada, há sobreposição
        if (tabuleiro[linha][coluna] != AGUA) {
            return 1;
        }
    }
    
    return 0;  // Não há sobreposição
}

/**
 * Função para posicionar um navio no tabuleiro
 * Suporta todas as orientações: horizontal, vertical e diagonais
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
        
        // Calcula a posição atual baseada na orientação
        calcularPosicaoNavio(navio, i, &linha, &coluna);
        
        // Marca a posição com o valor do navio
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    printf("Navio %d posicionado com sucesso na posição (%d,%d) - %s\n", 
           numeroNavio, navio.inicio.linha, navio.inicio.coluna, 
           obterNomeOrientacao(navio.orientacao));
    
    return 1;  // Sucesso
}

/**
 * Função para exibir o tabuleiro completo no console
 * Mostra a matriz 10x10 com formatação clara e organizada
 * Parâmetro: tabuleiro - matriz 10x10 do jogo
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL 10x10 ===\n");
    printf("0 = Água | 3 = Navio\n\n");
    
    // Exibir numeração das colunas
    printf("   ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Exibir o tabuleiro linha por linha com numeração
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);  // Numeração da linha
        
        // Exibir cada posição da linha atual
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);  // Valor da posição com espaçamento
        }
        printf("\n");  // Nova linha após cada linha do tabuleiro
    }
    printf("\n");
}

/**
 * Função para exibir o resumo detalhado das posições dos navios
 * Parâmetros: navios - array com todos os navios posicionados
 */
void exibirResumoNavios(Navio navios[TOTAL_NAVIOS]) {
    printf("=== RESUMO DETALHADO DOS NAVIOS ===\n");
    
    for (int n = 0; n < TOTAL_NAVIOS; n++) {
        printf("Navio %d (%s):\n", n + 1, obterNomeOrientacao(navios[n].orientacao));
        printf("  Posições ocupadas: ");
        
        // Exibe todas as posições ocupadas pelo navio
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            int linha, coluna;
            calcularPosicaoNavio(navios[n], i, &linha, &coluna);
            printf("(%d,%d)", linha, coluna);
            if (i < TAMANHO_NAVIO - 1) printf(", ");
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Função principal do programa
 * Implementa o nível aventureiro com 4 navios incluindo diagonais
 */
int main() {
    // Declaração da matriz do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    printf("=== SISTEMA DE BATALHA NAVAL - NÍVEL AVENTUREIRO ===\n");
    printf("Tabuleiro expandido para 10x10 com 4 navios incluindo diagonais\n\n");
    
    // Passo 1: Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Passo 2: Definir os quatro navios com diferentes orientações
    Navio navios[TOTAL_NAVIOS];
    
    // Navio 1 - Horizontal
    // Posição inicial: linha 1, coluna 2
    // Ocupará as posições: (1,2), (1,3), (1,4)
    navios[0] = (Navio){
        .inicio = {1, 2},
        .orientacao = 'H'
    };
    
    // Navio 2 - Vertical  
    // Posição inicial: linha 4, coluna 8
    // Ocupará as posições: (4,8), (5,8), (6,8)
    navios[1] = (Navio){
        .inicio = {4, 8},
        .orientacao = 'V'
    };
    
    // Navio 3 - Diagonal Principal
    // Posição inicial: linha 6, coluna 1
    // Ocupará as posições: (6,1), (7,2), (8,3)
    navios[2] = (Navio){
        .inicio = {6, 1},
        .orientacao = 'D'
    };
    
    // Navio 4 - Diagonal Secundária
    // Posição inicial: linha 2, coluna 7
    // Ocupará as posições: (2,7), (3,6), (4,5)
    navios[3] = (Navio){
        .inicio = {2, 7},
        .orientacao = 'A'
    };
    
    // Passo 3: Posicionar todos os navios no tabuleiro
    printf("--- POSICIONAMENTO DOS 4 NAVIOS ---\n");
    
    int naviosPosicionados = 0;
    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        if (posicionarNavio(tabuleiro, navios[i], i + 1)) {
            printf("✓ Navio %d posicionado corretamente\n", i + 1);
            naviosPosicionados++;
        } else {
            printf("✗ Falha ao posicionar navio %d\n", i + 1);
        }
    }
    
    // Verificar se todos os navios foram posicionados
    if (naviosPosicionados != TOTAL_NAVIOS) {
        printf("\nERRO: Nem todos os navios puderam ser posicionados!\n");
        return 1;
    }
    
    // Passo 4: Exibir o resultado final
    printf("\n--- RESULTADO FINAL ---\n");
    exibirTabuleiro(tabuleiro);
    
    // Exibir resumo detalhado
    exibirResumoNavios(navios);
    
    printf("=== ESTATÍSTICAS ===\n");
    printf("• Tabuleiro: 10x10 (%d posições)\n", TAMANHO_TABULEIRO * TAMANHO_TABULEIRO);
    printf("• Navios posicionados: %d\n", TOTAL_NAVIOS);
    printf("• Posições ocupadas: %d\n", TOTAL_NAVIOS * TAMANHO_NAVIO);
    printf("• Orientações utilizadas: Horizontal, Vertical, Diagonal Principal, Diagonal Secundária\n");
    printf("\nPrograma executado com sucesso!\n");
    
    return 0;
}
