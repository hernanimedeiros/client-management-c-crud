/* Clients Management: Simple CRUD in C */

/* Loading Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include <math.h> */

/* Defining constants */
#define MAX_LINHA 322
#define MAX_NUMERO 2
#define MAX_NOME 100
#define MAX_MORADA 200
#define MAX_CONTATO 20
#define MAX_ARRAY 10
#define MAX_NOME_FICHEIRO 30
#define ITEMS 8

/* Defining Struct */
typedef struct{
    char numero[MAX_NUMERO];
    char nome[MAX_NOME];
    char morada[MAX_MORADA];
    char contato[MAX_CONTATO];
    }cliente;
cliente clientes[MAX_ARRAY];

// Clients list dimension
int total_linhas(){
    int mudar_linha;
    int nr_linha=0;

    FILE *fptr_linhas;
    fptr_linhas=fopen("clientes.txt","r");

    while((mudar_linha=fgetc(fptr_linhas))!=EOF){
        if(mudar_linha=='\n'){
            nr_linha++;
        }
    }
    fclose(fptr_linhas);
    return (nr_linha);
}

// Exit message
void saida(){
    printf("\n__________________________________________________________________________________\n"
           "\nObrigado pela escolha\n"
           "\n[Volte sempre!]\n"
           "__________________________________________________________________________________\n");
    exit(0);
}

// Error message
void menu_erro(){
    printf("\n__________________________________________________________________________________\n"
           "\nIntroduziu uma tecla incorreta.\n"
           "\nPor favor contate o administrador do programa!\n"
           "\n__________________________________________________________________________________\n");
    exit(0);
}

// File error
void erro_ficheiro(){
    char furtar_numero[2];
    char string_modificada[7]="; ; ; \n";

    FILE *fptr_erro;
    fptr_erro=fopen("clientes.txt","a");

    printf("Ficheiro ausente...\nA criar ficheiro...\nFicheiro OK...\n");
    for(int i=0;i<MAX_ARRAY;i++){
        sprintf(furtar_numero,"%d",i+1);
        strcat(furtar_numero,string_modificada);
        fputs(furtar_numero,fptr_erro);
    }
    fclose(fptr_erro);
}

// Format clients list
void formatar_clientes(){
    char linha_ler[MAX_LINHA];
    char string_default[4]=";;;";
    char linha_copia[MAX_LINHA];
    char string_modificada[7]="; ; ; \n";
    char *parcela;

    FILE *fptr_origem;
    FILE *fptr_copia;
    fptr_origem=fopen("clientes.txt","r");
    fptr_copia=fopen("clientes_temp.txt","a");

    while(fgets(linha_ler,MAX_LINHA,fptr_origem)){
        parcela=strstr(linha_ler,string_default);
        if(parcela){
        strcpy(parcela,string_modificada);
        strcpy(linha_copia,linha_ler);
        fputs(linha_copia,fptr_copia);
        }else{
        strcpy(linha_copia,linha_ler);
        fputs(linha_copia,fptr_copia);
        }
    }
    fclose(fptr_origem);
    fclose(fptr_copia);
    remove("clientes.txt");

    rename("clientes_temp.txt","clientes.txt");
    printf("\nDados OK...\n");
}

// Delimiters errors
void erro_delimitadores(){
    char delimitador[1]=";";
    char *tokens;
    char linha_ler[MAX_LINHA];
    int contador_linhas=1,contador_campos=0;

    FILE *fptr_delimitadores;
    fptr_delimitadores=fopen("clientes.txt","r");

    while (fgets(linha_ler,MAX_LINHA,fptr_delimitadores)!=NULL){
        contador_campos=0;
        tokens=strtok(linha_ler,delimitador);
        contador_linhas++;
        while (tokens!=NULL){
        tokens=strtok(NULL,delimitador);
        contador_campos++;
        if(contador_campos==5){
                printf("\n__________________________________________________________________________________\n"
                       "\nA linha nr. %d da base de dados possui mais do que 4 caracteres delimitadores [;].\n"
                       "Por favor edite o ficheiro clientes.txt\n"
                       "\n__________________________________________________________________________________\n",contador_linhas);
                saida();
            }
        }
    }
    fclose(fptr_delimitadores);
    printf("\nCaracteres OK...\n");
}

// Continue menu
int menu_continuar(){
    char resposta;

    printf("\n__________________________________________________________________________________\n"
           "\nPara ir para o menu principal prima [S] | Para sair prima qualquer outra tecla\n"
           "__________________________________________________________________________________\n");
    printf("\nA sua resposta por favor -> ");
    scanf(" %c",&resposta);
        if(!(resposta=='S'||resposta=='s')){
            saida();
            }else{
                return(1);
            }
}

// Main menu strings
int menu_principal(){
    int resposta;

    do{
        printf("\n__________________________________________________________________________________\n"
               "\nPor favor escolha um elemento da lista abaixo:"
               "\n1- Listar Clientes"
               "\n2- Inserir novo Cliente"
               "\n3- Alterar Cliente Existente"
               "\n4- Eliminar Cliente"
               "\n5- Ver linhas vazias da base de dados"
               "\n6- Ver o conteudo da base de dados"
               "\n7- Eliminar todos os clientes"
               "\n8- Imprimir clientes para ficheiro"
               "\n0- Sair do Programa\n"
               "__________________________________________________________________________________\n");
        printf("\nA sua resposta por favor -> ");
        scanf(" %d",&resposta);
        printf("__________________________________________________________________________________\n");
    }while(!(resposta>=0&&resposta<=ITEMS));
    return (resposta);
}

// Store menu
char menu_gravar(){
    char resposta;

    printf("\n__________________________________________________________________________________\n"
           "\nPara gravar prima [S] | Para cancelar prima qualquer outra tecla\n"
           "__________________________________________________________________________________\n");
    printf("\nA sua resposta por favor -> ");
    scanf(" %c",&resposta);
    return (resposta);
}

// Store clients
void gravar_clientes(){
    int num_clientes=total_linhas();

    FILE *fptr_gravar;
    fptr_gravar=fopen("clientes.txt","w+");

    for(int i=0;i<num_clientes;i++){
        fprintf(fptr_gravar,"%s;%s;%s;%s",clientes[i].numero,clientes[i].nome,clientes[i].morada,clientes[i].contato);
    }
    fclose(fptr_gravar);
}

// Load clients
void carregar_clientes(){
    char delimitador[1]=";";
    char *campos_array;
    char linha_ler[MAX_LINHA];
    int contador_linhas=0,contador_campos=0;

    FILE *fptr_carregar;
    fptr_carregar=fopen("clientes.txt","r");

    while (fgets(linha_ler,MAX_LINHA,fptr_carregar)!=NULL){
        contador_campos=0;
        campos_array=strtok(linha_ler,delimitador);

        while (campos_array!=NULL){
            switch(contador_campos){
                case 0:
                    strcpy(clientes[contador_linhas].numero,campos_array);
                break;
                case 1:
                    strcpy(clientes[contador_linhas].nome,campos_array);
                break;
                case 2:
                   strcpy(clientes[contador_linhas].morada,campos_array);
                break;
                case 3:
                    strcpy(clientes[contador_linhas].contato,campos_array);
                break;
                default:
                        menu_erro();
            }
                campos_array=strtok(NULL,delimitador);
                contador_campos++;
        }
        contador_linhas++;
    }
    fclose(fptr_carregar);
}

// List clients
void listar_clientes(){
    int num_clientes=total_linhas();

    for(int i=0;i<num_clientes;i++){
        printf("__________________________________________________________________________________\n\n"
               "Nr. do cliente... %s\n"
               "Nome do cliente.. %s\n"
               "Morada........... %s\n"
               "Contato.......... %s",clientes[i].numero,clientes[i].nome,clientes[i].morada,clientes[i].contato);
    }
}

// Create clients
void inserir_clientes(){
    int num_clientes=total_linhas();
    int resposta;
    char resposta_char;
    char input_numero[4];
    char input_nome[100];
    char input_morada[200];
    char input_contato[20];

    do{
        printf("\n__________________________________________________________________________________\n"
                   "Escolha um cliente para inserir de 1-%d | Para sair prima 0\n"
                   "__________________________________________________________________________________\n",num_clientes);
        printf("\nA sua resposta por favor -> ");
        scanf(" %d",&resposta);
    }while(!(resposta>=0&&resposta<=num_clientes));

    if((resposta>=1)&&(resposta<=num_clientes)&&(clientes[(resposta-1)].nome[0]==' ')){
        sprintf(input_numero,"%d",resposta);
        strcpy(clientes[resposta-1].numero,input_numero);
        printf("Insira o nome do novo cliente -> ");
        gets(input_nome);
        gets(input_nome);
        strcpy(clientes[resposta-1].nome,input_nome);
        printf("Insira a morada do novo cliente -> ");
        gets(input_morada);
        strcpy(clientes[resposta-1].morada,input_morada);
        printf("Insira o contato do novo cliente -> ");
        gets(input_contato);
        strcat(input_contato,"\n");
        strcpy(clientes[resposta-1].contato,input_contato);

        listar_clientes();

        printf("\n__________________________________________________________________________________\n"
        "\nObserve acima lista que obteve.\n"
        "__________________________________________________________________________________\n");
        resposta_char=menu_gravar();
        if(!(resposta_char=='S'||resposta_char=='s')){
        printf("Os dados inseridos foram rejeitados");
        }else{
            gravar_clientes();
            }
    }else{
        printf("\n__________________________________________________________________________________\n"
               "\nPor favor tente mais tarde\n"
               "\nDica: Pode escolher [Alterar Cliente] no menu principal"
               "\n__________________________________________________________________________________\n");
        }
}

// Update clients
void alterar_clientes(){
    int num_clientes=total_linhas();
    int resposta;
    char resposta_char;
    char input_numero[4];
    char input_nome[100];
    char input_morada[200];
    char input_contato[20];

    do{
        printf("\n__________________________________________________________________________________\n"
                   "Escolha um cliente para modificar de 1-%d | Para sair prima 0\n"
                   "__________________________________________________________________________________\n",num_clientes);
        printf("\nA sua resposta por favor -> ");
        scanf(" %d",&resposta);
    }while(!(resposta>=0&&resposta<=num_clientes));

    if((resposta>=1)&&(resposta<=num_clientes)){
        sprintf(input_numero,"%d",resposta);
        strcpy(clientes[resposta-1].numero,input_numero);
        printf("\nPrima [S] para modificar o nome do cliente? Para cancelar prima outra tecla\n");
        printf("\nA sua resposta por favor -> ");
        scanf(" %c",&resposta_char);
        if(resposta_char=='S'||resposta_char=='s'){
        printf("Insira o nome do cliente -> ");
        gets(input_nome);
        gets(input_nome);
        strcpy(clientes[resposta-1].nome,input_nome);
        }
        printf("\nPrima [S] para modificar a morada do cliente? Para cancelar prima outra tecla\n");
        printf("\nA sua resposta por favor -> ");
        scanf(" %c",&resposta_char);
        if(resposta_char=='S'||resposta_char=='s'){
        printf("Insira a morada do novo cliente ->");
        gets(input_morada);
        gets(input_morada);
        strcpy(clientes[resposta-1].morada,input_morada);
        }
        printf("\nPrima [S] para modificar o contato do cliente? Para cancelar prima outra tecla\n");
        printf("\nA sua resposta por favor -> ");
        scanf(" %c",&resposta_char);
        if(resposta_char=='S'||resposta_char=='s'){
        printf("Insira o contato do novo cliente -> ");
        gets(input_contato);
        gets(input_contato);
        strcat(input_contato,"\n");
        strcpy(clientes[resposta-1].contato,input_contato);
        }

        listar_clientes();

        printf("\n__________________________________________________________________________________\n"
        "\nObserve acima lista que obteve.\n"
        "__________________________________________________________________________________\n");
        resposta_char=menu_gravar();
        if(!(resposta_char=='S'||resposta_char=='s')){
        printf("Os dados inseridos foram rejeitados");
        }else{
            gravar_clientes();
        }
    }else{
        printf("\n__________________________________________________________________________________\n"
               "\nPor favor volte mais tarde\n"
               "\nDica: Pode escolher [Inserir Cliente] no menu principal"
               "\n__________________________________________________________________________________\n");
        }
}

// Delete clients
void eliminar_clientes(){
    int num_clientes=total_linhas();
    int resposta;
    char resposta_char;
    char input_numero[4];
    char input_nome[100];
    char input_morada[200];
    char input_contato[20];

    do{
        printf("\n__________________________________________________________________________________\n"
                   "Escolha um cliente para inserir de 1-%d | Para sair prima 0\n"
                   "__________________________________________________________________________________\n",num_clientes);
        printf("\nA sua resposta por favor -> ");
        scanf(" %d",&resposta);
    }while(!(resposta>=0&&resposta<=num_clientes));

    if(resposta>=1&&resposta<=num_clientes){
        strcpy(clientes[resposta-1].nome," ");
        strcpy(clientes[resposta-1].morada," ");
        strcpy(clientes[resposta-1].contato,"\n");

        listar_clientes();

        printf("\n__________________________________________________________________________________\n"
        "\nObserve acima a lista que obteve.\n"
        "__________________________________________________________________________________\n");
        resposta_char=menu_gravar();
        if(!(resposta_char=='S'||resposta_char=='s')){
        printf("Os dados inseridos foram rejeitados");
        }
        else{
            gravar_clientes();
            }
    }
}

// Read clients
void ler_linhas(){
    char linha_ler[MAX_LINHA];
    int num_clientes=total_linhas();

    FILE *fptr_apresentar;
    fptr_apresentar=fopen("clientes.txt","r");

    printf("\n__________________________________________________________________________________\n"
           "\nAbaixo apresentamos o atual conteudo do ficheiro (%d clientes) \n"
           "__________________________________________________________________________________\n",num_clientes);
    while(fgets(linha_ler,MAX_LINHA,fptr_apresentar)!=NULL){
	printf("%s",linha_ler);
    }
    fclose(fptr_apresentar);
}

// Delete clients
void limpar_clientes(){
    int contador=1;
    int num_clientes=total_linhas();
    char resposta;
    char input_numero[4];


    for(int i=0;i<num_clientes;i++){
        sprintf(input_numero,"%d",contador);
        strcpy(clientes[i].numero,input_numero);
        strcpy(clientes[i].nome," ");
        strcpy(clientes[i].morada," ");
        strcpy(clientes[i].contato,"\n");
        contador++;
    }
    listar_clientes();

    printf("\n__________________________________________________________________________________\n"
           "\nObserve acima a lista que obteve.\n"
           "__________________________________________________________________________________\n");
    resposta=menu_gravar();
    if(!(resposta=='S'||resposta=='s')){
        printf("Os dados modificados foram rejeitados");
    }else{
        gravar_clientes();
        }
}

// Free spots
void lugares_livres(){
    int num_clientes=total_linhas();
    int conversor;

    printf("\n__________________________________________________________________________________\n"
           "\nLinhas de clientes vazias:\n");

    for(int i=0;i<num_clientes;i++){
        if(clientes[i].nome[0]==' '){
        conversor=atoi(clientes[i].numero);
        printf("[%d]\t",conversor);
        }
    }
    printf("\n__________________________________________________________________________________\n",conversor);
}

// Show clients
void imprimir_clientes(){

    remove("clientes_print.txt");
    int num_clientes=total_linhas();

    FILE *fptr_imprimir;
    fptr_imprimir=fopen("clientes_print.txt","a");

    printf("\nConsulte a lista de clientes em clientes_print.txt\n");

    for(int i=0;i<num_clientes;i++){
        fprintf(fptr_imprimir,"__________________________________________________________________________________\n\n"
                              "Nr. do cliente... %s\n"
                              "Nome do cliente.. %s\n"
                              "Morada........... %s\n"
                              "Contato.......... %s",clientes[i].numero,clientes[i].nome,clientes[i].morada,clientes[i].contato);
    }
    fclose(fptr_imprimir);
}

// Main menu
int main(){
    int escolha;
    //int num_clientes=total_linhas();
    char iniciar,continuar;

    FILE *fptr_ficheiro;
    fptr_ficheiro=fopen("clientes.txt","r");

    if(fptr_ficheiro==NULL){
        fclose(fptr_ficheiro);
        erro_ficheiro();
    }else{
        fclose(fptr_ficheiro);
        printf("\nFicheiro OK...\n");
        formatar_clientes();
        }

    erro_delimitadores();
    //printf("%d",num_clientes);
    printf(
           "\n__________________________________________________________________________________\n"
           "\nBem-vindo ao programa LISTA DE CLIENTES\n"
           "__________________________________________________________________________________\n"
           "\nPara continuar prima [S] | Para sair prima qualquer outra tecla\n"
           "__________________________________________________________________________________\n");

    printf("\nA sua resposta por favor -> ");
    scanf(" %c",&iniciar);
    if(!(iniciar=='S'||iniciar=='s')){
        saida();
        }else{
            do{
                carregar_clientes();
                escolha=menu_principal();
                switch(escolha){
                    case 0:
                        saida();
                    break;
                    case 1:
                        listar_clientes();
                        continuar=menu_continuar();
                    break;
                    case 2:
                        listar_clientes();
                        lugares_livres();
                        inserir_clientes();
                        continuar=menu_continuar();
                    break;
                    case 3:
                        listar_clientes();
                        alterar_clientes();
                        continuar=menu_continuar();
                    break;
                    case 4:
                        listar_clientes();
                        eliminar_clientes();
                        continuar=menu_continuar();
                    break;
                    case 5:
                        lugares_livres();
                        continuar=menu_continuar();
                    break;
                    case 6:
                        ler_linhas();
                        continuar=menu_continuar();
                    break;
                    case 7:
                        limpar_clientes();
                        continuar=menu_continuar();
                    break;
                    case 8:
                        imprimir_clientes();
                        continuar=menu_continuar();
                    break;
                    default:
                        menu_erro();
                }
            }while (continuar==1);
        }
    return 0;
}
