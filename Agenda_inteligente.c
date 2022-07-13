#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct Para musica
typedef struct {
    float sertanejo;
    float rock;
    float funk;
} musica;

// Struct para Informações gerais
typedef struct {
    char nome_completo[100];
    char nascimento[100];
    char cidade[100];
    char uf[2];
    musica esta_musica;
    int grupo_registro;
} dados;


dados *aloca_pessoas(int n) {
    dados *pessoas;

    pessoas = calloc(n, sizeof(dados));
    if(pessoas == NULL) {
        printf("Erro ao alocar pessoas. \n");
        return NULL;
    }

    return pessoas;
}


dados *le_pessoas_arquivo(FILE *arq_dados, int *total) {
    dados *pessoas;

    // Conta o total de pessoas:
    pessoas = aloca_pessoas(1);
    if(pessoas == NULL) {
        exit(1);
    }

    while(feof(arq_dados) == 0) {
        fread(pessoas, sizeof(dados), 1, arq_dados);
        *total++;
    }

    free(pessoas);

    // Volta o cursor para o inicio do arquivo:
    fseek(arq_dados, 0, SEEK_SET);

    // Aloca pessoas novamente, mas agora com o valor correto de "total":
    pessoas = aloca_pessoas(total);
    if(pessoas == NULL) {
        exit(1);
    }

    // Le, de fato, o arquivo e guarda os dados em "pessoas":
    fread(pessoas, sizeof(dados), total, arq_dados);
}


int main (){
    int opt;
    int total = 0;
    char nome_arquivo[50];
    FILE *arq_dados;
    dados *pessoas;

    do{
        // Menu
        printf("\t\tMenu\n");
        printf("[1] Importar registros de um arquivo\n");
        printf("[2] Cadastrar novo registro\n");
        printf("[3] Editar registro\n");
        printf("[4] Excluir registro\n");
        printf("[5] Buscar registro\n");
        printf("[6] Ordenar registros\n");
        printf("[7] Agrupar registros\n");
        printf("[8] Exportar registros para um arquivo\n");
        printf("[0] Sair\n");

        scanf("%d", &opt);
        switch (opt) {

            case 1:
                //Recendo nome de arquivo e lendo arquivo
                // fgets(nome_arquivo, 50, stdin);
                scanf("%s", nome_arquivo);

                arq_dados = fopen(nome_arquivo, "ab+");

                if(arq_dados == NULL) {
                    printf("Erro abrindo arquivo");
                    exit(1);
                }

                pessoas = le_pessoas_arquivo(arq_dados, &total);

                printf("Total de pessoas: %d \n", total);

                break;
            case 2:
                printf("b");
                break;
            case 3:
                printf("c");
                break;
            case 4:
                printf("d");
                break;
            case 5:
                printf("e");
                break;
            case 6:
                printf("f");
                break;
            case 7:
                printf("g");
                break;
            case 8:
                printf("h");
                break;
            case 0:
                printf("Fechando a agenda. Ate mais!\n");
                break;
            default:
                printf("Opção invalida!\n");
                printf("Digite uma nova opção:\n");
                break;
        }
    } while(opt != 0);

    return 0;
}