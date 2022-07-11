#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct Para musica
struct musica{
    int Samba;
    int Rock;
    int MPB;
};

// Struct para Informações gerais
struct dados{
    char Nome_completo[100];
    char Nascimento[100];
    char Cidade[100];
    char UF[2];
    struct musica esta_musica;
    int grupo_registro;
};


int main (){
    int opt;
    char nome_arquivo[50];
    FILE *arq_dados;
    struct dados *pessoas;

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
        printf("[0] Agrupar registros\n");

        scanf("%d", &opt);
        switch (opt){

        case 1:
            //Recendo nome de arquivo e lendo arquivo
            gets(nome_arquivo, 50, stdin);
            arq_dados = fopen(nome_arquivo, "ab+");

            if (arq_dados == NULL){
                printf("Erro abrindo arquivo");
            }
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
            break;
        default:
            printf("Opção invalida!\n");
            printf("Digite uma nova opção\n");

            scanf("%d", &opt);
            break;
        }
    }while(opt != 0);
    return 0;
}