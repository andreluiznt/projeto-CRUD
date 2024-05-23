#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

#define QUANT_PRODUTOS 100

enum categoria{
    AlimentosBasicos,
    MassasSopaseMolhos,
    LaticinioseFrios,
    ProdutosCongelados,
    Bebidas,
    ProdutosdePadeConf,
    PetiscoseGuloseimas,
    ProdutosHigieneLimpeza,
    CasaeJardim,
    NutricaoEspecial
};

/* Lista de enumerações representando cada categoria dos produtos.
0 - Alimentos Básicos
1 - Massas, Sopas e Molhos
2 - Laticínios e Frios
3 - Produtos Congelados
4 - Bebidas (álcool e não alcoólicas)
5 - Produtos de Padaria e Confeitaria
6 - Petiscos e Guloseimas
7 - Produtos de Higiene e Limpeza
8 - Artigos para Casa, Jardim e Descartáveis
- Nutrição Especial
*/

typedef struct{
    enum categoria categoria;
    int id;
    int peso;
    char nome[50];
    int tipo;
    char marca[50];
    float preco;
    int quantidade;
    unsigned long long int codigo;
    char mercado[20];
    char bairro[20];
}tProduto;

char texto[101];
tProduto produtos[QUANT_PRODUTOS];
int qProdutos = 0;

void apresentaMenu(){
    printf("\n\t\t--- MELHOR PREÇO ---\n\n"
            "\t 1 - Categoria\n"
            "\t 2 - Buscar Produto\n"
            "\t 3 - Simular compra\n"
            "\t 4 - Cadastrar Produtos\n"
            "\t 5 - Sair\n");

    printf("\nDigite a operaçao que você deseja realizar: ");
}

void cadastrarProduto(){
    FILE *file = fopen("produtos.txt", "a+");
    if (file == NULL){
        printf("Erro ao abrir o arquivo.\n");
    exit;
}

    while(qProdutos < QUANT_PRODUTOS){
        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite o nome do bairro: ");
        scanf(" %20[^\n]", produtos[qProdutos].bairro);
        system("cls");

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite o nome do mercado: ");
        scanf(" %20[^\n]", produtos[qProdutos].mercado);
        system("cls");

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite o codigo de Barras: ");
        scanf("%llu", &produtos[qProdutos].codigo);
        system("cls");

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite o nome do produto: ");
        scanf(" %50[^\n]", produtos[qProdutos].nome);
        system("cls");

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite a marca: ");
        scanf(" %50[^\n]", produtos[qProdutos].marca);
        system("cls");

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Embalagem (1 - Kg, 2 - Ml): ");
        int opcao;
        scanf("%d", &opcao);
        system("cls");

        if(opcao != 1 && opcao != 2){
            printf("----------Cadastrar Produtos----------\n\n");
            printf("Opção inválida, digite novamente: ");
            scanf(" %d", &opcao);
            system("cls");
        }

        if(opcao == 1){
            printf("----------Cadastrar Produtos----------\n\n");
            printf("Digite o peso do produto em Gramas: ");
            scanf("%d", &produtos[qProdutos].peso);
            system("cls");
        }

        if(opcao == 2){
            printf("----------Cadastrar Produtos----------\n\n");
            printf("Digite o peso do produto em Mililitro: ");
            scanf("%d", &produtos[qProdutos].peso);
            system("cls");
        }

        printf("----------Cadastrar Produtos----------\n\n");
        printf("Digite o preço: ");
        scanf("%f", &produtos[qProdutos].preco);
        system("cls");

        printf("Escolha a categoria do produto:\n");
        printf("1 - Alimentos Basicos\n2 - Massas, Sopas & Molhos\n3 - Laticínios e Frios\n4 - Produtos Congelados\n5 - Bebidas\n6 - Produtos de Padaria e Confeitaria\n7 - Petiscos e Guloseimas\n8 - Podutos de Higiene e Limpeza\n9 - Casa, Jardim e Descartáveis\n10 - Nutrição Especial\n");

        int escolher_cat;
        scanf("%d", &escolher_cat);

        if(escolher_cat >= 1 && escolher_cat <= 10){
            produtos[qProdutos].categoria = escolher_cat - 1;
        }else{
            printf("Categoria inválida.");
        }

        fprintf(file, "%s\t %s\t %s\t %llu\t %s\t %d\t %.2f\t %d\n",    produtos[qProdutos].nome,
                                                                        produtos[qProdutos].bairro,
                                                                        produtos[qProdutos].mercado,
                                                                        produtos[qProdutos].codigo,
                                                                        produtos[qProdutos].marca,
                                                                        produtos[qProdutos].peso,
                                                                        produtos[qProdutos].preco,
                                                                        produtos[qProdutos].categoria);
        qProdutos++;
        printf("----------Cadastrar Produtos----------\n\n");
        printf("Deseja cadastrar um novo produto (s/n): ");
        char continuar;
        scanf(" %c", &continuar);
        system("cls");
        if (continuar == 'n' || continuar == 'N'){
            system("cls");
            break;
        }
    }
    fclose(file);
}

void listarProdutos(){

    FILE *file = fopen("produtos.txt","r");
    if (file == NULL){
        printf("----------Cadastrar Produtos----------\n\n");
        printf("\tNenhum produto cadastrado!\n\n");
        printf("Digite Enter para voltar ao menu.");
        char menu;
        scanf("%*c%c", &menu);
        if(menu == '\n'){
            system("cls");
            return;
        }
    }

    printf("----------Lista de Produtos----------\n\n");
    printf("%-15s %15s %15s %15s %15s %15s %18s\n\n", "Produto", "Bairro", "Mercado", "Cod. de Barras",
    "Marca", "Peso(g/ml)", "Preço");

    while(fgets(texto,101,file)!=NULL){
        printf("%s", texto);
    }

    fclose(file);

    printf("\n\nDigite Enter para voltar ao menu.");
        char menu;
        scanf("%*c%c", &menu);
        if(menu == '\n'){
        system("cls");
        exit;
        }
}

void procurar(){

    char descricao[100];
    char linha[100];
    bool encontrou = false;

    FILE *file = fopen("produtos.txt", "r");
    if (file == NULL){
        printf("----------Buscar Produto----------\n\n");
        printf("\tNenhum produto cadastrado!\n\n");
        printf("Digite Enter para voltar ao menu.");
        char menu;
        scanf("%c", &menu);
        if(menu == '\n'){
        system("cls");
        return;
        }
    }

    printf("----------Buscar Produto----------\n\n");
    printf("Digite a descrição que você deseja procurar: ");

    fgets(descricao, sizeof(descricao), stdin);
    system("cls");

    size_t descricao_len = strlen(descricao);
        if (descricao_len > 0 && descricao[descricao_len - 1] == '\n') {
        descricao[descricao_len - 1] = '\0';
    }

    printf("----------Buscar Produto----------\n\n");
    printf("Produto - Bairro - Mercado - Cod. de Barras - Marca - Peso(g/ml) - Preço\n\n");

    while (fgets(linha, sizeof(linha), file) != NULL){
        if (strstr(linha, descricao) != NULL){
            printf("%s", linha);
            encontrou = true;
            }
        }

        if (!encontrou) {
            system("cls");
            printf("----------Busca Produto----------\n\n");
            printf("Produto não encontrado!\n");
        }

    printf("\nDeseja buscar um novo produto (s/n): ");

    char continuar;
    scanf(" %c", &continuar);
    system("cls");

    if (continuar == 'n' || continuar == 'N'){
        system("cls");
        exit;
    }

    if(continuar == 's' || continuar == 'S'){
        system("cls");
        scanf("%*c");
        procurar();
    }

    fclose(file);
}

void simucompra(){

    typedef struct{
        char Snome[40];
        char Sbairro[40];
        char Smercado[40];
        float Scodigo;
        char Smarca[40];
        float Speso;
        float Spreco;
    }Pproduto;

    Pproduto Sproduto[100];

    typedef struct{
        char Snome[40];
    }Sprodutos;

    typedef struct{
        float preco;
        char mercado[40];
    }sprecototal;

    sprecototal precototal[40];

    Sprodutos SprodutoS[100];
    int resposta = 1;
    char linha[300];
    FILE *arquivo;
    arquivo = fopen("produtos.txt","r");

    if(arquivo == NULL)
    {
        printf("erro ao abrir o arquivo");
    }
    else
    {
        while(resposta = 1)
        {
            int i = 0;
            int a = 0;
            int b = 0;
            int c = 0;
            int verificador = 1;

        system("cls");
        printf("digite suas compras e iremos mostrar mercado mais em conta\n digite n quando terminar");
        printf("\n");

        while(verificador == 1)
        {

            printf(":");
            scanf("%s",SprodutoS[i].Snome);
            if(strcmp(SprodutoS[i].Snome,"n") == 0)
            {
                verificador = 0;
            }
            else
            {
                i++;
            }
        }

while(fgets(linha, sizeof(linha), arquivo) != NULL){
    char *simb = strtok(linha, "\t");

    if (simb != NULL) strcpy(Sproduto[a].Snome, simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) strcpy(Sproduto[a].Sbairro, simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) strcpy(Sproduto[a].Smercado, simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) Sproduto[a].Scodigo = atof(simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) strcpy(Sproduto[a].Smarca, simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) Sproduto[a].Speso = atof(simb);
    simb = strtok(NULL, "\t");
    if (simb != NULL) Sproduto[a].Spreco = atof(simb);

    a++;
}

system("cls");

for(int b=0; b<=i; b++){
    for (int c = 0; c < a; c++){
        if (strcmp(SprodutoS[b].Snome, Sproduto[c].Snome) == 0){
            for (int d = 0; d < 40; d++){
                if (strcmp(Sproduto[c].Smercado, precototal[d].mercado) == 0){
                    precototal[d].preco += Sproduto[c].Spreco;
                    break;
                }else if(precototal[d].preco == 0){
                    strcpy(precototal[d].mercado, Sproduto[c].Smercado);
                    precototal[d].preco = Sproduto[c].Spreco;
                    break;
                }
            }
            printf("Produto encontrado: %s/%s/R$:%.2f\n", SprodutoS[b].Snome, Sproduto[c].Smercado, Sproduto[c].Spreco);
            }
        }

    }

        printf("\nResumo de preços por mercado:\n");
        for(int i=0; i<40; i++){
            if (precototal[i].preco > 0){
                printf("Mercado: %s, Preço Total: R$ %.2f\n", precototal[i].mercado, precototal[i].preco);
            }
        }

        printf("insira 0 para sair\n");
        scanf("%d", &resposta);
        if(resposta == 0){
            break;
        }
    }
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese");

    int opc;

    while(1){
        apresentaMenu();

        scanf("%d", &opc);

        switch(opc){
            case 1:
                system("clear");
                int escolher_categoria;

                printf("Selecione a categoria:\n");
                printf("1 - Alimentos Básicos\n");
                printf("2 - Massas, Sopas & Molhos\n");
                printf("3 - Laticínios e Frios\n");
                printf("4 - Produtos Congelados\n");
                printf("5 - Bebidas (alcoólicas e não alcoólicas)\n");
                printf("6 - Produtos de Padaria e Confeitaria\n");
                printf("7 - Petiscos e Guloseimas\n");
                printf("8 - Produtos de Higiene e Limpeza\n");
                printf("9 - Casa, Jardins e Descartáveis\n");
                printf("10 - Nutrição Especial\n");
                printf("11 - Listar todos os produtos\n\n");
                scanf("%d", &escolher_categoria);

                system("cls");
                if(escolher_categoria == 11){
                    listarProdutos();
                }
                printf("\t\tProdutos na categoria selecionada:\n\n");
                for (int i = 0; i < qProdutos; i++) {
                    if (produtos[i].categoria == escolher_categoria - 1) {
                        printf("\t%s - %s - R$%.2f - %s - %s\n", produtos[i].nome, produtos[i].marca, produtos[i].preco, produtos[i].mercado, produtos[i].bairro);
                    }
                }
                break;
            case 2:
                system("cls");
                scanf("%*c");
                procurar();
                break;
            case 3:
                system("cls");
                simucompra();
                break;
            case 4:
                system("cls");
                cadastrarProduto();
                break;
            case 5:
                system("cls");
                printf("\nSaindo do programa... Até mais.");
                return 0;
            default:
                system("cls");
                scanf("%*c");
                printf("\nErro... Opção inválida.");
                printf("\n\nDigite Enter para voltar ao menu.");
                char menu;
                scanf("%c", &menu);

                if(menu == '\n'){
                    system("cls");
                    exit;
                }
                break;
        }
}


    return 0;

}
