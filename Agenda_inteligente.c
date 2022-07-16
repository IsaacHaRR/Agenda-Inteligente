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
    int grupo;
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

int edita_registro(dados *pessoas, char nome[], int total) {
    int campo = 0;
    int indice;
    int i = 0;
    int encontrado = 0;

    // Realiza a busca pelo indice do registro referente ao nome passado:
    while((encontrado == 0) && (i < total)) {
        if(strcmp(nome, pessoas[i].nome_completo) == 0) {
            indice = i;
            printf("Indice encontrado! (%d) \n", indice);
            encontrado = 1;
        }
        i++;
    }

    if(encontrado == 0) {
        printf("ATENCAO! Nome nao encontrado! \n");
    }
    else {
        // Menu de campos a serem editados:
        do {
            printf("[1] - Nome\n");
            printf("[2] - Data de nascimento\n");
            printf("[3] - Cidade\n");
            printf("[4] - UF\n");
            printf("[5] - Preferencias\n");
            printf("[0] - Parar de editar\n\n");
            printf("Escolha qual campo deseja alterar, ou digite 0 para parar de editar: ");
            scanf("%d", &campo);
            printf("\n");

            switch(campo) {
                case 1:
                    printf("Insira o novo nome: ");
                    scanf(" %[^\n]%*c", pessoas[indice].nome_completo);
                    break;
                case 2:
                    printf("Insira a nova data de nascimento:\n");
                    printf("\tDia: ");
                    scanf("%d", &pessoas[indice].nascimento.dia);
                    printf("\tMes: ");
                    scanf("%d", &pessoas[indice].nascimento.mes);
                    printf("\tAno: ");
                    scanf("%d", &pessoas[indice].nascimento.ano);
                    break;
                case 3:
                    printf("Insira o nova Cidade: ");
                    scanf(" %[^\n]%*c", pessoas[indice].cidade);
                    break;
                case 4:
                    printf("Insira a nova UF: ");
                    scanf("%s", pessoas[indice].uf);
                    break;
                case 5:
                    printf("Insira as novas preferencias de %s: \n", pessoas[indice].nome_completo);
                    printf("\tPlaystation: ");
                    scanf("%f", &pessoas[indice].videogames.playstation);
                    printf("\tXbox: ");
                    scanf("%f", &pessoas[indice].videogames.xbox);
                    printf("\tPC: ");
                    scanf("%f", pessoas[indice].videogames.pc);
                    break;
                case 0:
                    printf("Parando de editar os campos de %s. \n", pessoas[indice].nome_completo);
                    break;
                default:
                    printf("Campo invalido, por favor digite uma das opcoes do menu: \n");
                    break;
            }
        } while(campo != 0);
    }

    return encontrado;
}

void agrupa_registros(dados *pessoas, int total) {
    float euclidiana;
    float x_ps, y_xbox, z_pc;
    int g = 1;

    // Atribui o grupo do primeiro registro como grupo 1:
    pessoas[0].grupo = g;
    
    // Passa por toda a agenda, calculando o grupo de cada registro:
    for(int i = 1; i < total; i++) {
        int agrupado = 0;

        // Para cada registro (pessoas[i]), calcula-se a distancia euclidiana para cada registro anterior pessoas[j]:
        for(int j = 0; j < i; j++) {
            x_ps = pessoas[i].videogames.playstation - pessoas[j].videogames.playstation;
            y_xbox = pessoas[i].videogames.xbox - pessoas[j].videogames.xbox;
            z_pc = pessoas[i].videogames.pc - pessoas[j].videogames.pc;

            euclidiana = sqrt(pow(x_ps, 2) + pow(y_xbox, 2) + pow(z_pc, 2));

            // Se distancia euclidiana < 0.5, entao pertence ao mesmo grupo:
            if(euclidiana < 0.5) {
                pessoas[i].grupo = pessoas[j].grupo;
                agrupado = 1;
                break;
            }
        }

        // Se nao pertence a nenhum grupo existente, cria um grupo novo:
        if(agrupado == 0) {
            g++;
            pessoas[i].grupo = g;
        }
    }
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
                    printf("\nnome: %s\n", pessoas[i].nome_completo);
                    printf("cidade: %s\n", pessoas[i].cidade);
                    printf("UF: %s\n", pessoas[i].uf);
                    printf("grupo: %d\n", pessoas[i].grupo);
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
                printf("EDICAO DE REGISTRO. \n");

                char nome[100];
                int sucesso;

                // Recebe o nome completo do registro que deseja editar:
                printf("Digite o nome completo do registro que deseja editar: ");
                scanf(" %[^\n]%*c", nome);

                sucesso = edita_registro(pessoas, nome, total);

                if(sucesso) {
                    printf("Edicao realizada com sucesso. \n");
                }
                else {
                    printf("Falha na edicao. \n");
                }

                break;
            case 4:
                printf("EXCLUSAO DE REGISTRO. \n");

                pessoas = exclui_registro(pessoas, total);

                total--;

                printf("Cadastro excluido com sucesso. \n");

                break;
            case 5:
                printf("BUSCA DE REGISTRO. \n");

                printf("Escolha por qual informacao deseja buscar o registro:\n");
                printf("[1] - Por nome ou parte do nome\n");
                printf("[2] - Por data de nascimento\n");
                printf("[3] - Pelo grupo\n");
                // ...

                break;
            case 6:
                printf("f");
                break;
            case 7:
                printf("AGRUPAMENTO DE REGISTROS. \n");

                agrupa_registros(pessoas, total);

                printf("Registros agrupados com sucesso. \n");

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