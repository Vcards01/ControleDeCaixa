/*Autoria: Victor Hugo Cardoso - Data: março de 2018. Este programa mantem o 
estoque de um mercadinho informatizado,utilizando um sistema para realizar suas
vendas e realizar consultas ao estoque e ao saldo atual do caixa. */
#include <stdio.h>
#include <string.h>
#include <locale.h>
/* Definicao de Constantes */ 
#define MAX 1000
// Protótipo das Funções
void menu();
int verificarSeExisite(int codigo,int qtdd);
void cadastrarProduto(int &qtdd,float &saldo);
void venderProduto(int &qtdd,float &saldo,float &lucro);
void consultarEstoque(int qtdd);
void consultarSaldo(float saldo);
void consularLucro(float lucro);

struct registro_produtos
	{
	   	int codigo;
	   	char nome[30];
	   	int quantidade;
	   	float precoCompra;
	   	float precoVenda;
	};
//Criando o vetor produto que é do tipo struct registro_produtos
	struct registro_produtos produtos[MAX];
int main()
{
	setlocale(LC_ALL,"Portuguese");
  	//Declaracao de Variaveis Locais da função
	float saldo=3000;
	float lucro=0;
	int opcao=-1;//variavel que controla o Menu
	int qtdd=0;//variavel de controle do vetor	
    while(opcao!=0)
	{
		menu();
		scanf("%d",&opcao);
		if(opcao==1)
		{
			cadastrarProduto(qtdd,saldo);
		}
		else if(opcao==2)
		{
			venderProduto(qtdd,saldo,lucro);
		}
		else if(opcao==3)
		{
			consultarEstoque(qtdd);
		}
		else if(opcao==4)
		{
			consultarSaldo(saldo);
		}
		else if(opcao==5)
		{
			consularLucro(lucro);
		}
		
	}
	
	return 0;
}
// Declaração das funções


void menu()
{
	printf("\n----------------------------------------");
	printf("\n\t\tMENU");
	printf("\n----------------------------------------");
	printf("\n[1]Inserir produto ao estoque.");
	printf("\n[2]Realizar uma venda.");
	printf("\n[3]Consultar o estoque dos produtos.");
	printf("\n[4]Consultar saldo do caixa.");
	printf("\n[5]Consultar lucro obtido.");
	printf("\n[0]Sair\n");
}


int verificarSeExiste(int codigo,int qtdd)
{
/*A função verificarSeExiste recebe um codigo de entrada e pode retornar dois
valores diferente,definindo assim se aquele codigo ja existe ou não.*/
	for(int i=0;i<qtdd;i++)
	{
		if(codigo==produtos[i].codigo)
		{
			return i;
		}
	}
	return -1;
}


void cadastrarProduto(int &qtdd,float &saldo)
{
//Declaracao de Variaveis Locais da função
	int codigoTeste;//Utilizada para testar se um produto ja existe ou não.
	int retorno;//Ira receber o valor retornado de "verificarSeExiste".
	int quantidadeSoma;//Utilizada para incrementar os produtos já em estoque.
	printf("\n\tAdicionar ao estoque");
	printf("\n----------------------------------------");
	printf("\nDigite o código do produto:");
	scanf("%d",&codigoTeste);
	retorno=verificarSeExiste(codigoTeste,qtdd);
	if(retorno==-1)
	{
	// entrada de dados 
		produtos[qtdd].codigo=codigoTeste;
		printf("\nDigite o nome do produto:");
		fflush(stdin);
		gets(produtos[qtdd].nome);
		printf("\nDigite a quantidade de produtos:");
		scanf("%d",&produtos[qtdd].quantidade);
		printf("\nDigite o preço de compra:R$");
		scanf("%f",&produtos[qtdd].precoCompra);
	// Saida de Dados 
		produtos[qtdd].precoVenda=(produtos[qtdd].precoCompra)+(produtos[qtdd].precoCompra/2);
		printf("\nPreço de venda:R$%.2f",produtos[qtdd].precoVenda);
		saldo-=produtos[qtdd].quantidade*produtos[qtdd].precoCompra;;
		qtdd++;
	}
	else
	{
		for(int i=0;i<qtdd;i++)
		{
			if(codigoTeste==produtos[i].codigo)
			{
				printf("\nNome do produto:%s",produtos[i].nome);
				printf("\nDigite a quantidade de produtos:");
				scanf("%d",&quantidadeSoma);
				saldo-=quantidadeSoma*produtos[i].precoCompra;
				produtos[i].quantidade+=quantidadeSoma;
				
			}
		}
	}
}


void venderProduto(int &qtdd,float &saldo,float &lucro)
{
//Declaracao de Variaveis Locais da função
	int codigoVenda;
	int quantidadeDeVenda;
	float precoTotalDeVenda;
	int retorno;//Ira receber o valor retornado de "verificarSeExiste"
	consultarEstoque(qtdd);//estoque deve ser mostrado na tela.
	printf("\n\n\nDigite o código do produto que deseja vender:");
	scanf("%d",&codigoVenda);
	retorno=verificarSeExiste(codigoVenda,qtdd);//Verifica se o produto existe no sistema
	if(retorno==-1)
	{
		printf("\nProduto não cadastrado no sistema");
		printf("\nVenda cancelada");
	}
	else
	{
		for(int i=0;i<qtdd;i++)
		{
			if(codigoVenda==produtos[i].codigo)
			{
				printf("\nProduto: %s",produtos[i].nome);
			   	printf("\nQuantidade que deseja vender:");
			   	scanf("%d",&quantidadeDeVenda);
				if(quantidadeDeVenda<=produtos[i].quantidade)
				{
					precoTotalDeVenda=quantidadeDeVenda*produtos[i].precoVenda;
				   	printf("\nPreço unitario:R$ %.2f",produtos[i].precoVenda);
					printf("\nPreço total:R$ %.2f",precoTotalDeVenda);
					printf("\nVenda concluida com sucesso");
				   	saldo+=precoTotalDeVenda;
					produtos[i].quantidade-=quantidadeDeVenda;
					lucro=lucro+(produtos[i].precoVenda-produtos[i].precoCompra)*quantidadeDeVenda;
			   	 }
				else
				{
					printf("\nProduto insuficiente em estoque");
				   	printf("\nVenda cancelada");
				}
			}
		}
	}
	

	   	
}


void consultarEstoque(int qtdd)
{
	printf("\n\tEstoque");
	for(int i=0;i<qtdd;i++)
	{
		printf("\n\nCodigo: %d | Nome: %s | Quantidade: %d | Preço de compra: R$%.2f | Preço de venda: R$%.2f",
		produtos[i].codigo,produtos[i].nome,produtos[i].quantidade,produtos[i].precoCompra,produtos[i].precoVenda);
	}
}


void consultarSaldo(float saldo)
{
	printf("\n\t\tSaldo do caixa");
	printf("\n----------------------------------------");
	printf("\nO saldo atual do Mercado é: R$%.2f",saldo);
}


void consularLucro(float lucro)
{
	printf("\n\tLucro obtido");
	printf("\n----------------------------------------");
	printf("\nO lucro atual do mercado é: R$%.2f",lucro);
}