#include <stdio.h>
#include <stdlib.h>

// Desafio Batalha Naval - MateCheck - Nível Mestre
// Este programa implementa um sistema completo de posicionamento de navios e habilidades especiais
// Inclui suporte para navios em todas as orientações e habilidades: Cone, Cruz e Octaedro
// Autor: Sistema de Batalha Naval
// Data: 2024

// Constantes do jogo
#define TAMANHO_TABULEIRO 10    // Dimensão do tabuleiro (10x10)
#define TAMANHO_NAVIO 3         // Tamanho fixo de cada navio
#define TAMANHO_HABILIDADE 5    // Dimensão das matrizes de habilidade (5x5)
#define TOTAL_NAVIOS 4          // Número total de navios no jogo
#define TOTAL_HABILIDADES 3     // Número total de habilidades especiais

// Valores para representar elementos no tabuleiro
#define AGUA 0                  // Valor que representa água no tabuleiro
#define NAVIO 3                 // Valor que representa parte de navio no tabuleiro
#define HABILIDADE 5            // Valor que representa área afetada por habilidade

// Tipos de habilidades especiais
typedef enum {
    CONE = 0,       // Habilidade em forma de cone
    CRUZ = 1,       // Habilidade em forma de cruz
    OCTAEDRO = 2    // Habilidade em forma de octaedro (losango)
} TipoHabilidade;

// Estrutura para representar coordenadas
typedef struct {
    int linha;    // Coordenada da linha (0-9)
    int coluna;   // Coordenada da coluna (0-9)
} Coordenada;

// Estrutura para representar um navio
typedef struct {
    Coordenada inicio;    // Coordenada inicial do navio
    char orientacao;      // 'H' = horizontal, 'V' = vertical, 'D' = diagonal principal, 'A' = diagonal secundária
} Navio;

// Estrutura para representar uma habilidade especial
typedef struct {
    TipoHabilidade tipo;                                      // Tipo da habilidade
    Coordenada origem;                                        // Ponto de origem no tabuleiro
    int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];      // Matriz de efeito da habilidade
} HabilidadeEspecial;

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
 * Função para obter o nome da habilidade especial
 * Parâmetro: tipo - tipo da habilidade
 * Retorna: string com o nome da habilidade
 */
const char* obterNomeHabilidade(TipoHabilidade tipo) {
    switch (tipo) {
        case CONE: return "Cone";
        case CRUZ: return "Cruz";
        case OCTAEDRO: return "Octaedro";
        default: return "Inválida";
    }
}

/**
 * Função para criar matriz de habilidade em forma de cone dinamicamente
 * Utiliza loops aninhados e condicionais para construir a forma
 * Parâmetro: matriz - matriz 5x5 para armazenar o padrão do cone
 */
void criarHabilidadeCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Criar formato de cone usando condicionais
    // O cone tem ponto na parte superior e se expande para baixo
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Centro da matriz (ponto de origem do cone)
            int centro = TAMANHO_HABILIDADE / 2;
            
            // Calcular a largura permitida para cada linha baseada na distância do topo
            int larguraMaxima = i + 1;  // Linha 0 = largura 1, linha 1 = largura 2, etc.
            
            // Verificar se a posição está dentro da largura do cone para esta linha
            int distanciaFromCentro = abs(j - centro);
            
            if (distanciaFromCentro < larguraMaxima && larguraMaxima <= centro + 1) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * Função para criar matriz de habilidade em forma de cruz dinamicamente
 * Utiliza loops aninhados e condicionais para construir a forma
 * Parâmetro: matriz - matriz 5x5 para armazenar o padrão da cruz
 */
void criarHabilidadeCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Criar formato de cruz usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;  // Centro da matriz
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Linha horizontal (linha central) ou coluna vertical (coluna central)
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * Função para criar matriz de habilidade em forma de octaedro (losango) dinamicamente
 * Utiliza loops aninhados e condicionais para construir a forma
 * Parâmetro: matriz - matriz 5x5 para armazenar o padrão do octaedro
 */
void criarHabilidadeOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    // Inicializar toda a matriz com 0
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            matriz[i][j] = 0;
        }
    }
    
    // Criar formato de octaedro (losango) usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;  // Centro da matriz
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcular distância Manhattan do centro
            int distanciaLinha = abs(i - centro);
            int distanciaColuna = abs(j - centro);
            int distanciaTotal = distanciaLinha + distanciaColuna;
            
            // Se a distância total for menor ou igual ao raio, está dentro do losango
            if (distanciaTotal <= centro) {
                matriz[i][j] = 1;
            }
        }
    }
}

/**
 * Função para aplicar uma habilidade especial ao tabuleiro
 * Sobrepõe a matriz de habilidade no tabuleiro, centrando no ponto de origem
 * Parâmetros: tabuleiro - matriz do jogo, habilidade - estrutura da habilidade
 */
void aplicarHabilidadeNoTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                                  HabilidadeEspecial habilidade) {
    
    // Calcular offset para centralizar a habilidade no ponto de origem
    int offsetLinha = habilidade.origem.linha - (TAMANHO_HABILIDADE / 2);
    int offsetColuna = habilidade.origem.coluna - (TAMANHO_HABILIDADE / 2);
    
    // Aplicar a matriz de habilidade ao tabuleiro usando loops aninhados
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Calcular posição no tabuleiro
            int linhaTabu = offsetLinha + i;
            int colunaTabu = offsetColuna + j;
            
            // Verificar se a posição está dentro dos limites do tabuleiro
            if (linhaTabu >= 0 && linhaTabu < TAMANHO_TABULEIRO &&
                colunaTabu >= 0 && colunaTabu < TAMANHO_TABULEIRO) {
                
                // Se a habilidade afeta esta posição (valor 1), marcar no tabuleiro
                if (habilidade.matriz[i][j] == 1) {
                    // Não sobrescrever navios, apenas água
                    if (tabuleiro[linhaTabu][colunaTabu] == AGUA) {
                        tabuleiro[linhaTabu][colunaTabu] = HABILIDADE;
                    }
                }
            }
        }
    }
    
    printf("Habilidade %s aplicada na posição (%d,%d)\n", 
           obterNomeHabilidade(habilidade.tipo),
           habilidade.origem.linha, 
           habilidade.origem.coluna);
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
            if (navio.inicio.coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'V':  // Navio vertical
            if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'D':  // Diagonal principal
            if (navio.inicio.linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO ||
                navio.inicio.coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) {
                return 0;
            }
            break;
            
        case 'A':  // Diagonal secundária
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
        
        // Se a posição já está ocupada por navio, há sobreposição
        if (tabuleiro[linha][coluna] == NAVIO) {
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
 * Função para exibir o tabuleiro completo com navios e habilidades
 * Mostra diferentes caracteres para água, navios e áreas afetadas por habilidades
 * Parâmetro: tabuleiro - matriz 10x10 do jogo
 */
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL COM HABILIDADES ESPECIAIS ===\n");
    printf("0 = Água | 3 = Navio | 5 = Área de Habilidade\n\n");
    
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
 * Função para exibir uma matriz de habilidade específica
 * Parâmetros: habilidade - estrutura da habilidade a ser exibida
 */
void exibirMatrizHabilidade(HabilidadeEspecial habilidade) {
    printf("Matriz de Habilidade %s (%dx%d):\n", 
           obterNomeHabilidade(habilidade.tipo), 
           TAMANHO_HABILIDADE, TAMANHO_HABILIDADE);
    
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        printf("  ");
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            printf("%d ", habilidade.matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Função para exibir o resumo detalhado das posições dos navios
 * Parâmetros: navios - array com todos os navios posicionados
 */
void exibirResumoNavios(Navio navios[TOTAL_NAVIOS]) {
    printf("=== RESUMO DOS NAVIOS ===\n");
    
    for (int n = 0; n < TOTAL_NAVIOS; n++) {
        printf("Navio %d (%s): ", n + 1, obterNomeOrientacao(navios[n].orientacao));
        
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
 * Implementa o nível mestre com navios e habilidades especiais
 */
int main() {
    // Declaração da matriz do tabuleiro 10x10
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    printf("=== SISTEMA DE BATALHA NAVAL - NÍVEL MESTRE ===\n");
    printf("Tabuleiro 10x10 com navios e habilidades especiais\n\n");
    
    // Passo 1: Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Passo 2: Definir e posicionar os navios
    Navio navios[TOTAL_NAVIOS] = {
        {{1, 2}, 'H'},  // Navio 1 - Horizontal
        {{4, 8}, 'V'},  // Navio 2 - Vertical
        {{6, 1}, 'D'},  // Navio 3 - Diagonal Principal
        {{2, 7}, 'A'}   // Navio 4 - Diagonal Secundária
    };
    
    printf("--- POSICIONAMENTO DOS NAVIOS ---\n");
    int naviosPosicionados = 0;
    for (int i = 0; i < TOTAL_NAVIOS; i++) {
        if (posicionarNavio(tabuleiro, navios[i], i + 1)) {
            printf("✓ Navio %d posicionado corretamente\n", i + 1);
            naviosPosicionados++;
        } else {
            printf("✗ Falha ao posicionar navio %d\n", i + 1);
        }
    }
    
    if (naviosPosicionados != TOTAL_NAVIOS) {
        printf("\nERRO: Nem todos os navios puderam ser posicionados!\n");
        return 1;
    }
    
    // Passo 3: Criar e aplicar habilidades especiais
    printf("\n--- CRIAÇÃO DAS HABILIDADES ESPECIAIS ---\n");
    
    HabilidadeEspecial habilidades[TOTAL_HABILIDADES];
    
    // Definir posições de origem para cada habilidade
    habilidades[0] = (HabilidadeEspecial){CONE, {3, 3}, {{0}}};      // Cone no centro-esquerda
    habilidades[1] = (HabilidadeEspecial){CRUZ, {7, 6}, {{0}}};      // Cruz no centro-direita
    habilidades[2] = (HabilidadeEspecial){OCTAEDRO, {1, 8}, {{0}}}; // Octaedro no canto superior direito
    
    // Criar as matrizes de habilidade dinamicamente
    criarHabilidadeCone(habilidades[0].matriz);
    criarHabilidadeCruz(habilidades[1].matriz);
    criarHabilidadeOctaedro(habilidades[2].matriz);
    
    printf("✓ Todas as matrizes de habilidade criadas dinamicamente\n");
    
    // Exibir as matrizes de habilidade
    printf("\n--- MATRIZES DAS HABILIDADES ---\n");
    for (int i = 0; i < TOTAL_HABILIDADES; i++) {
        exibirMatrizHabilidade(habilidades[i]);
    }
    
    // Aplicar as habilidades ao tabuleiro
    printf("--- APLICAÇÃO DAS HABILIDADES NO TABULEIRO ---\n");
    for (int i = 0; i < TOTAL_HABILIDADES; i++) {
        aplicarHabilidadeNoTabuleiro(tabuleiro, habilidades[i]);
        printf("✓ Habilidade %s aplicada com sucesso\n", obterNomeHabilidade(habilidades[i].tipo));
    }
    
    // Passo 4: Exibir resultado final
    printf("\n--- RESULTADO FINAL ---\n");
    exibirTabuleiro(tabuleiro);
    
    // Exibir resumos
    exibirResumoNavios(navios);
    
    printf("=== RESUMO DAS HABILIDADES ===\n");
    for (int i = 0; i < TOTAL_HABILIDADES; i++) {
        printf("Habilidade %s: Origem (%d,%d)\n", 
               obterNomeHabilidade(habilidades[i].tipo),
               habilidades[i].origem.linha,
               habilidades[i].origem.coluna);
    }
    
    printf("\n=== ESTATÍSTICAS FINAIS ===\n");
    printf("• Tabuleiro: 10x10 (%d posições)\n", TAMANHO_TABULEIRO * TAMANHO_TABULEIRO);
    printf("• Navios posicionados: %d\n", TOTAL_NAVIOS);
    printf("• Habilidades aplicadas: %d\n", TOTAL_HABILIDADES);
    printf("• Orientações de navios: Horizontal, Vertical, Diagonal Principal, Diagonal Secundária\n");
    printf("• Tipos de habilidades: Cone, Cruz, Octaedro\n");
    printf("\nPrograma do nível mestre executado com sucesso!\n");
    
    return 0;
}
