#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Struct para data de nascimento
typedef struct {
    int dia;
    int mes;
    int ano;
} data;

// Struct Para musica
typedef struct {
    float playstation;
    float xbox;
    float pc;
} preferencia;

// Struct para Informações gerais
typedef struct {
    char nome_completo[100];
    data nascimento;
    char cidade[100];
    char uf[2];
    preferencia videogames;
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
    int total_pessoas = 0;

    // Conta o total de pessoas:
    pessoas = aloca_pessoas(1);
    if(pessoas == NULL) {
        exit(1);
    }

    while(fread(pessoas, sizeof(dados), 1, arq_dados)) {
        total_pessoas++;
    }

    *total = total_pessoas;

    free(pessoas);

    // Volta o cursor para o inicio do arquivo:
    fseek(arq_dados, 0, SEEK_SET);

    // Aloca pessoas novamente, mas agora com o valor correto de "total":
    pessoas = aloca_pessoas(total_pessoas);
    if(pessoas == NULL) {
        exit(1);
    }

    // Le, de fato, o arquivo e guarda os dados em "pessoas":
    fread(pessoas, sizeof(dados), total_pessoas, arq_dados);

    return pessoas;    
}

void cadastra_registro(dados *pessoas, int total) {
    printf("Insira os dados do novo registro: \n");

    printf("Nome completo: ");
    scanf(" %[^\n]%*c", pessoas[total-1].nome_completo);
    printf("Data de nascimento:\n");
    printf("\tDia: ");
    scanf("%d", &pessoas[total-1].nascimento.dia);
    printf("\tMes: ");
    scanf("%d", &pessoas[total-1].nascimento.mes);
    printf("\tAno: ");
    scanf("%d", &pessoas[total-1].nascimento.ano);
    printf("Cidade: ");
    scanf(" %[^\n]%*c", pessoas[total-1].cidade);
    printf("UF: ");
    scanf("%s", pessoas[total-1].uf);
    printf("Preferencias:\n");
    printf("\tPlaystation (De 0 a 1): ");
    scanf("%f", &pessoas[total-1].videogames.playstation);
    printf("\tXbox (De 0 a 1): ");
    scanf("%f", &pessoas[total-1].videogames.xbox);
    printf("\tPC (De 0 a 1): ");
    scanf("%f", &pessoas[total-1].videogames.pc);
}

dados *exclui_registro(dados *pessoas, int total) {
    dados *novo_pessoas;
    char nome[100];
    int j = 0;

    novo_pessoas = aloca_pessoas(total-1);
    if(novo_pessoas == NULL) {
        printf("Erro ao alocar novo_pessoas. \n");
        return NULL;
    }

    printf("Digite o nome da pessoas que deseja excluir: ");
    scanf(" %[^\n]%*c", nome);

    for(int i = 0; i < total; i++) {
        if(strcmp(pessoas[i].nome_completo, nome) != 0) {
            novo_pessoas[j] = pessoas[i];
            j++;
        }
    }

    return novo_pessoas;
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
                printf("IMPORTACAO DE REGISTROS \n\n");
                printf("Digite o nome do arquivo do qual deseja importar os registros: \n");
                //Recendo nome de arquivo e lendo arquivo
                // fgets(nome_arquivo, 50, stdin);
                scanf("%s", nome_arquivo);

                arq_dados = fopen(nome_arquivo, "rb");
                if(arq_dados == NULL) {
                    printf("Erro abrindo arquivo");
                    exit(1);
                }

                pessoas = le_pessoas_arquivo(arq_dados, &total);

                fclose(arq_dados);

                printf("Total de pessoas: %d \n", total);
                
                for(int i = 0; i < total; i++) {
                    printf("%s\n", pessoas[i].nome_completo);
                    printf("%s\n", pessoas[i].cidade);
                    printf("%s\n", pessoas[i].uf);
                }
                
                printf("Registros importados com sucesso. \n");

                break;
            case 2:
                printf("CADASTRO DE REGISTRO \n\n");
                total++;
                
                // Alocacao de "pessoas":
                if(total == 1) {
                    // Se eh o primeiro registro a ser feito, aloca-se 1 posicao:
                    pessoas = aloca_pessoas(total);
                    if(pessoas == NULL) {
                        exit(1);
                    }
                }
                else {
                    // Se nao eh o primeiro registro, entao realoca uma posicao a mais:
                    pessoas = realloc(pessoas, total * sizeof(dados));
                    if(pessoas == NULL) {
                        printf("Erro ao realocar pessoas. \n");
                        exit(1);
                    }
                }

                cadastra_registro(pessoas, total);

                printf("Cadastro realizado com sucesso. \n");

                break;
            case 3:
                printf("c");
                break;
            case 4:
                printf("EXCLUSAO DE REGISTRO. \n");

                pessoas = exclui_registro(pessoas, total);

                total--;

                printf("Cadastro excluido com sucesso. \n");

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
                printf("EXPORTACAO DE REGISTROS \n\n");
                printf("Digite o nome do arquivo para o qual deseja exportar os registros: \n");
                
                // Recendo nome de arquivo:
                scanf("%s", nome_arquivo);

                // Abre arquivo para escrita:
                arq_dados = fopen(nome_arquivo, "wb");
                if(arq_dados == NULL) {
                    printf("Erro ao abrir arquivo para exportacao. \n");
                    exit(1);
                }

                // Escreve os registros no arquivo:
                fwrite(pessoas, sizeof(dados), total, arq_dados);
            
                printf("Exportacao de registros realizada com sucesso. \n");

                fclose(arq_dados);

                break;
            case 0:
                free(pessoas);
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