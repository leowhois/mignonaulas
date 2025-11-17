#ifndef CODIFICADOR_H
#define CODIFICADOR_H
#define LINHAS_MAX 1024
#define COLUNAS_MAX 768
#define TAMANHO_MAX_CODIGO 10000
int codificar_imagem(int matriz[LINHAS_MAX][COLUNAS_MAX],
                     int linhasI, int linhasF,
                     int colunasI, int colunasF,
                     char *codigo_saida, int index_inicio);
int entrada_manual(int matriz[LINHAS_MAX][COLUNAS_MAX], int *N_linhas, int *M_colunas);
int arquivo_pbm(const char *nome_arquivo, int matriz[LINHAS_MAX][COLUNAS_MAX], int *N_linhas, int *M_colunas);

#endif