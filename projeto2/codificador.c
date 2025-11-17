#include <stdio.h>
#include "codificador.h"

int uniforme(int matriz[LINHAS_MAX][COLUNAS_MAX],
                int linhasI, int linhasF,
                int colunasI, int colunasF) {

    // Pega a cor do primeiro pixel como referência (1=Preto, 0=Branco)
    int cor_base = matriz[linhasI][colunasI];

    // Percorre a sub-região para checar homogeneidade
    for (int i = linhasI; i <= linhasF; i++) {
        for (int j = colunasI; j <= colunasF; j++) {
            // Se encontrar qualquer pixel diferente, não é uniforme
            if (matriz[i][j] != cor_base) {
                return -1;
            }
        }
    }

    // Se todos os pixels foram da mesma cor, retorna essa cor
    return cor_base;
}

int codificar_imagem(int matriz[LINHAS_MAX][COLUNAS_MAX],
                       int linhasI, int linhasF,
                       int colunasI, int colunasF,
                       char *codigo_saida,
                       int index_inicio) {

    int uniformidade = uniforme(matriz, linhasI, linhasF, colunasI, colunasF);

    if (uniformidade != -1) {
        if (uniformidade == 1) {    // Preto
            codigo_saida[index_inicio] = 'P';
        } else {                    // Branco
            codigo_saida[index_inicio] = 'B';
        }

        // Retorna o índice seguinte (o tamanho da string cresceu 1)
        return index_inicio + 1;
    }

    codigo_saida[index_inicio] = 'X';
    int index_atual = index_inicio + 1; // O índice de escrita avança

    int N = linhasF - linhasI + 1; // Altura
    int M = colunasF - colunasI + 1; // Largura

    // Regra para dimensões ímpares: Superior (meio_L) e Esquerda (meio_C) ficam com a coluna/linha a mais.
    
    // meio_L é o índice da última linha do quadrante superior/primeira metade
    int meio_L = linhasI + (N + 1) / 2 - 1;

    // meio_C é o índice da última coluna do quadrante esquerdo/primeira metade
    int meio_C = colunasI + (M + 1) / 2 - 1;

    // 3. Chamadas Recursivas

    // Q1: Superior Esquerda
    index_atual = codificar_imagem(matriz, linhasI, meio_L, colunasI, meio_C,
                                 codigo_saida, index_atual);

    // Q2: Superior Direita
    if (meio_C + 1 <= colunasF) {
        index_atual = codificar_imagem(matriz, linhasI, meio_L, meio_C + 1, colunasF,
                                 codigo_saida, index_atual);
    }

    // Q3: Inferior Esquerda
    if (meio_L + 1 <= linhasF) {
    index_atual = codificar_imagem(matriz, meio_L + 1, linhasF, colunasI, meio_C,
                                 codigo_saida, index_atual);
    }

    // Q4: Inferior Direita
    if (meio_L + 1 <= linhasF && meio_C + 1 <= colunasF) {
    index_atual = codificar_imagem(matriz, meio_L + 1, linhasF, meio_C + 1, colunasF,
                                 codigo_saida, index_atual);
    }

    // O índice retornado da última chamada (Q4) é o novo final da string para a instância anterior.
    return index_atual;
}