#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codificador.h"

int entrada_manual(int matriz[LINHAS_MAX][COLUNAS_MAX], int *N_linhas, int *M_colunas){
    printf("MODO MANUAL ATIVADO. \nDigite a altura (N): ");
    if (scanf("%d", N_linhas) != 1) {
        return 0; // Falha na leitura
    }
    printf("Digite a largura (M): ");
    
    if (scanf("%d", M_colunas) != 1) {
        return 0; // Falha na leitura
    }
    if (*N_linhas <= 0 || *N_linhas > LINHAS_MAX || *M_colunas <= 0 || *M_colunas > COLUNAS_MAX) {
         printf("Dimensões inválidas ou excedem o limite (%dx%d).\n", LINHAS_MAX, COLUNAS_MAX);
         return 0;
    }
    printf("Digite os %d pixels (0 ou 1):\n", (*N_linhas) * (*M_colunas));
    // Lê cada pixel da matriz
    for (int i = 0; i < *N_linhas; i++) {
        for (int j = 0; j < *M_colunas; j++) {
            if (scanf("%d", &matriz[i][j]) != 1) {
                printf("Erro ao ler pixel.\n");
                return 0;
            }
        }
    }
    return 1;
}

int arquivo_pbm(const char *nome_arquivo, int matriz[LINHAS_MAX][COLUNAS_MAX], int *N_linhas, int *M_colunas){
    FILE *file;
    char magic[3];

    // Abre o arquivo em modo leitura
    file = fopen(nome_arquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return 0;
    }

    // Lê e verifica o tipo de arquivo (P1 = PBM ASCII)
    if (fscanf(file, "%s", magic) != 1 || strcmp(magic, "P1") != 0) {
        printf("Formato PBM inválido. Esperado 'P1'.\n");
        fclose(file);
        return 0;
    }

    // Lê as dimensões: largura (M) e altura (N)
    if (fscanf(file, "%d %d", M_colunas, N_linhas) != 2) {
        printf("Erro ao ler as dimensões da imagem.\n");
        fclose(file);
        return 0;
    }

    // Valida as dimensões
    if (*N_linhas <= 0 || *N_linhas > LINHAS_MAX || *M_colunas <= 0 || *M_colunas > COLUNAS_MAX) {
        printf("Dimensões do arquivo excedem o limite (%dx%d).\n", LINHAS_MAX, COLUNAS_MAX);
        fclose(file);
        return 0;
    }

    // Lê cada pixel (0 ou 1) e armazena na matriz
    for (int i = 0; i < *N_linhas; i++) {
        for (int j = 0; j < *M_colunas; j++) {
            if (fscanf(file, "%d", &matriz[i][j]) != 1) {
                printf("Erro ao ler pixel na posição (%d, %d).\n", i, j);
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);
    return 1;
}

// Função para exibir as instruções de uso (Help)
void exibir_ajuda() {
    printf("\nUso: ./ImageEncoder [-? | -m | -f ARQ]\n");
    printf("Codifica imagens binárias dadas em arquivos PBM ou por dados informados manualmente.\n\n");
    printf("Argumentos:\n");
    printf("-?, --help  : apresenta essa orientação na tela.\n");
    printf("-m, --manual: ativa o modo de entrada manual.\n");
    printf("-f, --file  : considera a imagem representada no arquivo PBM.\n");
}

int main(int argc, char *argv[]) {
    int matriz_imagem[LINHAS_MAX][COLUNAS_MAX]; // Limite 1024x768
    int N_linhas = 0;
    int M_colunas = 0;
    char codigo_saida[TAMANHO_MAX_CODIGO];

    // Verificação de Argumentos (CLI)
    if (argc < 2) {
        exibir_ajuda();
        return 0;
    }

    if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0) {
        exibir_ajuda();
        return 0;
    }

    // Modo Manual (-m)
    else if (strcmp(argv[1], "-m") == 0 || strcmp(argv[1], "--manual") == 0) {
        if (!entrada_manual(matriz_imagem, &N_linhas, &M_colunas)) {
            printf("Erro na leitura manual da imagem.\n");
            return 1;
        }
    }

    // Modo Arquivo PBM (-f)
    else if (strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) {
        if (argc < 3) {
            printf("Erro: Nome do arquivo PBM não especificado após -f.\n");
            exibir_ajuda();
            return 1;
        }
        const char *nome_arquivo = argv[2];

        if (!arquivo_pbm(nome_arquivo, matriz_imagem, &N_linhas, &M_colunas)) {
            printf("Erro ao processar o arquivo PBM ou formato inválido.\n");
            return 1;
        }
    }

    // Tratamento de Argumentos Inválidos
    else {
        printf("Argumento inválido: %s\n", argv[1]);
        exibir_ajuda();
        return 1;
    }

    // Chamada da Função de Codificação (Se os dados foram carregados com sucesso)
    if (N_linhas > 0 && M_colunas > 0) {
        int index_atual = codificar_imagem(matriz_imagem, 0, N_linhas - 1, 0, M_colunas - 1, codigo_saida, 0);

        // Terminação da String e Saída
        codigo_saida[index_atual] = '\0';
        printf("\nCÓDIGO CORRESPONDENTE: %s\n", codigo_saida);
    }

    return 0;
}