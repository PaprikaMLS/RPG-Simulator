#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "jogo.h"


Char criar_char(char n)
{
	Char r; //classe

	if(n == 'M') // mago
	{
		r.atk = 5;
		r.def = 6;
		r.hp = 600;
		r.mp = 50;
		r.stam = 40;
		r.dex = 5;
		r.intel = 8;
		r.tipo = 'M';
	}

	else if(n == 'P') // paladino
	{
		r.atk = 6;
		r.def = 8;
		r.hp = 650;
		r.mp = 40;
		r.stam = 60;
		r.dex = 5;
		r.intel = 5;
		r.tipo = 'P';
	}

	else // guerreiro
	{
		r.atk = 8;
		r.def = 7;
		r.hp = 750;
		r.mp = 30;
		r.stam = 80;
		r.dex = 7;
		r.intel = 2;
		r.tipo = 'G';

	}

	r.defextra = 0;
	r.dextra = 0;
	return r;
}

void ler_preset(Char* r, FILE* arq) // modulo para ler o arquivo gerado
{
	int atk, def, dex, intel;
	char tipo;

	fscanf(arq, "%c,%d,%d,%d,%d", &tipo, &atk, &def, &dex, &intel);

	if(atk + def + dex + intel != 29) // valor max de pontos atigindo
	{
		puts("O preset esta mal configurado!");
		exit(1);
	}

	if(tipo != 'M' && tipo != 'G' && tipo != 'P')
	{
		puts("Classe nao reconhecida!");
		exit(1);
	}


    // atribuicao de status do arquivo lido
	r->atk = atk;
	r->def = def;
	r->dex = dex;
	r->intel = intel;
	r->tipo = tipo;

	if(tipo == 'M')
	{
		r->hp = 600;
		r->mp = 50;
		r->stam = 40;
	}
	else if(tipo == 'P')
	{
		r->hp = 650;
		r->mp = 40;
		r->stam = 60;
	}
	else
	{
		r->hp = 750;
		r->mp = 30;
		r->stam = 80;
	}
}

char menu_escolha(void) //menu para seleção da classe do personagem
{

	// confirmacao da classe
	char* confirmar = (char*) malloc(5 * sizeof(char));
	if(confirmar == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}


	// escolher tipo de classe
	char* tipo = (char*) malloc(15 * sizeof(char));
	if(tipo == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}

	system("clear");

	printf("\n+-----------------------------------------------------------+\n");
	printf("|------------------ SIMULADOR DE BATALHAS ------------------|\n");
	printf("+-----------------------------------------------------------+\n\n\n");

	printf("Escolha uma das classes: Mago - Paladino - Guerreiro\n>>");
	gets(tipo);

	int i = 0;

	// tratamento de string - colocando a entrada em caixa alta
	while(i < strlen(tipo))
	{
		tipo[i] = toupper(tipo[i]);
		i++;
	}

	// comparando a entrada do usuario com a classe
	while ((strcmp(tipo,"MAGO") != 0) && (strcmp(tipo,"PALADINO") != 0) && (strcmp(tipo,"GUERREIRO")) != 0)
	{
		printf("\nClasse não reconhecida.\nEscolha uma das classes: Mago - Paladino - Guerreiro\n>>");
		gets(tipo);

		i = 0;

		while(i < strlen(tipo))
		{
			tipo[i] = toupper(tipo[i]);
			i++;
		}
	}

	if(tipo[0] == 'M')
	{
		printf("\nO Mago apresenta as seguintes habilidades\n");
		printf("Cajadada - Dano fisico com pequeno dano arcano\nFogo - Dano arcano\nDefender - Aumento de defesa por uma rodada");
	}

	else if(tipo[0] == 'P')
	{
		printf("\nO Paladino apresenta as seguintes habilidades\n");
		printf("Justica - Dano fisico com pequeno dano arcano\nJulgamento - Dano arcano com aumento de destreza\nDefender - Aumento de defesa por uma rodada");
	}

	else
	{
		printf("\nO Guerreiro apresenta as seguintes habilidades\n");
		printf("Corte - Dano fisico com pequeno dano arcano\nFoco - Dano fisico com aumento de destreza e pequeno dano arcano\nDefender - Aumento de defesa por uma rodada");
	}

	printf("\n\nDeseja continuar com essa classe ?\n>>");
	gets(confirmar);

	i = 0;

	// confirmacao de classe
	// entrada em caixa alta
	while(i < strlen(confirmar))
	{
		confirmar[i] = toupper(confirmar[i]);
		i++;
	}

	//tratamento da string - usuario/programa
	while ((strcmp(confirmar,"SIM") != 0) && (strcmp(confirmar,"NAO") != 0))
	{
		printf("\nDigite sim ou nao para confirmar\n>>");
		gets(confirmar);

		i = 0;

		while(i < strlen(confirmar))
		{
			confirmar[i] = toupper(confirmar[i]);
			i++;
		}
	}

	if(confirmar[0] == 'S')
	{
		return tipo[0];
	}

	else
	{
		return menu_escolha();
	}
}


void imp_char(Char r) //imprime o personagem
{
	printf("\nClasse: %s\n", (r.tipo == 'M')? "Mago" : ((r.tipo == 'G')? "Guerreiro" : "Paladino"));
	printf("Ataque: %d\n", r.atk);
	printf("Defesa: %d\n", r.def);
	printf("HP: %d\n", r.hp);
	printf("MP: %d\n", r.mp);
	printf("Estamina: %d\n", r.stam);
	printf("Destreza: %d\n", r.dex);
	printf("Inteligencia: %d\n\n", r.intel);
}

void distribuir(Char* r) //distribuição de 5 pontos extras
{
	// limpando a tela
	printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);

	int i;
	char* confirmar = (char*) malloc(4 * sizeof(char)); // gerar arquivo com atributos

	if(confirmar == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}

	char* atributo = (char*) malloc (6 * sizeof(char)); // alocação de memória para a string de reconhecimento de atributo

	if(atributo == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}

	for(i = 5; i > 0; i--) // atribuição dos pontos
	{
		// limpando a tela
		printf("\033[2J");
	  printf("\033[%d;%dH", 0, 0);

		printf("\n");
		imp_char(*r); // impressão dos atributos antigos

		printf("Vc tem %d pontos extras para distribuir em seu personagem !\n", i);

		puts("Distribua com sabedoria!");
		printf("\n");

		printf("Escolha um atributo: ataque(atk) - defesa(def) - destreza(dex) - inteligencia(int)\n>>");
		gets(atributo);

		if(strcmp(atributo,"atk") == 0) // compara oque o usuário entrou como atributo
		{
			if(r->atk == 10)
			{
				puts("Atributo ja esta no valor maximo !"); // atributos de atk,def,dex e int são bufados no max até 10
				i++;
			}
			else
			{
				r->atk += 1;
			}
		}

		else if(strcmp(atributo,"def") == 0)
		{
			if(r->def == 10)
			{
				puts("Atributo ja esta no valor maximo !");
				i++;
			}
			else
			{
				r->def += 1;
			}
		}

		else if(strcmp(atributo,"dex") == 0)
		{
			if(r->dex == 10)
			{
				puts("Atributo ja esta no valor maximo !");
				i++;
			}
			else
			{
				r->dex += 1;
			}
		}

		else if(strcmp(atributo,"int") == 0)
		{
			if(r->intel == 10)
			{
				puts("Atributo ja esta no valor maximo !");
				i++;
			}
			else
			{
				r->intel += 1;
			}
		}

		else
		{
			puts("Atributo nao reconhecido !");
			i++;
		}
		printf("\n\n");
	}

	// gerar arquivo
	printf("\nDeseja salvar o status da classe para reutiliza-la mais tarde? (sim/nao)\n>>");
	gets(confirmar);

	i = 0;

	//tratamento da string de entrada do usuario
	while(i < strlen(confirmar))
	{
		confirmar[i] = toupper(confirmar[i]);
		i++;
	}

	while ((strcmp(confirmar,"SIM") != 0) && (strcmp(confirmar,"NAO") != 0))
	{
		printf("\nDigite sim ou nao para confirmar\n>>");
		gets(confirmar);

		i = 0;

		while(i < strlen(confirmar))
		{
			confirmar[i] = toupper(confirmar[i]);
			i++;
		}
	}

	if(confirmar[0] == 'S')
	{
		FILE* arq = fopen("preset", "w");
		if(arq == NULL)
		{
			puts("Erro interno.");
			exit(1);
		}

		fprintf(arq, "%c,%d,%d,%d,%d", r->tipo, r->atk, r->def, r->dex, r->intel);//gerando arquivo

		fclose(arq);
	}
}

Char criar_inimigo(void)
{
	char op;
	int i;
	int seed = time(NULL);

	srand(seed);
	int random = rand() % 3;//escolher aleatoriamente uma classe

	if (random == 0)
	{
		op = 'M';
	}

	else if (random == 1)
	{
		op = 'P';
	}

	else
	{
		op = 'G';
	}

	Char inimigo = criar_char(op);

	for(i = 5; i > 0; i--)
	{
		seed++;
		srand(seed);
		random = rand() % 4; //atribuindo aleatoriamente os pontos extras

		if(random == 0)
		{
			if(inimigo.atk == 10)
			{
				i++;
			}
			else
			{
				inimigo.atk++;
			}
		}

		else if(random == 1)
		{
			if(inimigo.def == 10)
			{
				i++;
			}
			else
			{
				inimigo.def++;
			}
		}

		else if(random == 2)
		{
			if(inimigo.dex == 10)
			{
				i++;
			}
			else
			{
				inimigo.dex++;
			}
		}

		else
		{
			if(inimigo.intel == 10)
			{
				i++;
			}
			else
			{
				inimigo.intel++;
			}
		}
	}
	return inimigo;
}

void menu_ataca(Char* r, Char* inimigo)
{
	int seed = time(NULL) ,i = 0;
	char* ataque = (char*) malloc (20 * sizeof(char));//alocacao para escolha do ataque
	if (ataque == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}

	if(r->tipo == 'M') //menu de ataque para o mago
	{
		printf("Escolha um ataque\nCajadada - Fogo - Defender\n>>");
		gets(ataque);

		printf("\n");

		//tratamento da string de entrada para ataque
		while(i < strlen(ataque))
		{
			ataque[i] = toupper(ataque[i]);
			i++;
		}

		while ((strcmp(ataque,"CAJADADA") != 0) && (strcmp(ataque,"FOGO") != 0) && (strcmp(ataque,"DEFENDER")) != 0)
		{
			printf("\nAtaque não reconhecido.\nEscolha um dos ataques: Cajadada - Fogo - Defender\n>>");
			gets(ataque);

			i = 0;

			while(i < strlen(ataque))
			{
				ataque[i] = toupper(ataque[i]);
				i++;
			}
		}

		//compara a entrada
		if(strcmp(ataque,"CAJADADA") == 0)
		{
			if(r->mp < 2 || r->stam < 4)
			{
				puts("Nao foi possivel atacar com cajadada!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1;//geracao de um numero aleatorio para dano critico

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 4 * r->intel + 3 * r->dex + 2 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else // dano normal
			{
				int dano = 3 * r->intel + 3 * r->dex + 2 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 2;
			r->stam -= 4;
		}

		if(strcmp(ataque,"FOGO") == 0) // compara entrada
		{
			if(r->mp < 6 || r->stam < 2)
			{
				puts("Nao foi possivel atacar com fogo!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1; // numero para critico

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 6 * r->intel + 3 * r->dex + 2 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else // dano normal
			{
				int dano = 4 * r->intel + 3 * r->dex + 1 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 6;
			r->stam -= 2;
		}

		if(strcmp(ataque,"DEFENDER") == 0)
		{
			r->defextra += 1; // defender bufa a defesa em +1
		}

		printf("\n");
	}

	if(r->tipo == 'P') //menu de ataque para o paladino
	{
		printf("Escolha um ataque\nJustica - Julgamento - Defender\n>>");
		gets(ataque);

		//tratamento da entrada
		while(i < strlen(ataque))
		{
			ataque[i] = toupper(ataque[i]);
			i++;
		}

		// comparacao da entrada
		while ((strcmp(ataque,"JUSTICA") != 0) && (strcmp(ataque,"JULGAMENTO") != 0) && (strcmp(ataque,"DEFENDER")) != 0)
		{
			printf("\nAtaque não reconhecido.\nEscolha um dos ataques: Justica - Julgamento - Defender\n>>");
			gets(ataque);

			i = 0;

			while(i < strlen(ataque))
			{
				ataque[i] = toupper(ataque[i]);
				i++;
			}
		}

		if(strcmp(ataque,"JUSTICA") == 0)
		{
			if(r->mp < 1 || r->stam < 4)
			{
				puts("Nao foi possivel atacar com justica!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1; // numero para dano

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 3 * r->intel + 3 * r->dex + 3 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else // dano normal
			{
				int dano = 3 * r->intel + 2 * r->dex + 2 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 1;
			r->stam -= 4;
		}

		if(strcmp(ataque,"JULGAMENTO") == 0)
		{
			if(r->mp < 5 || r->stam < 3)
			{
				puts("Nao foi possivel atacar com julgamento!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1;

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 5 * r->intel + 4 * r->dex + 2 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else
			{
				int dano = 4 * r->intel + 3 * r->dex + 1 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 5;
			r->stam -= 3;
			r->dextra += 1;
		}

		if(strcmp(ataque,"DEFENDER") == 0)
		{
			r->defextra += 1;
		}

		printf("\n");
	}

	if(r->tipo == 'G') //menu de ataque para o guerreiro
	{
		printf("Escolha um ataque\nCorte - Foco - Defender\n>>");
		gets(ataque);

		while(i < strlen(ataque))
		{
			ataque[i] = toupper(ataque[i]);
			i++;
		}

		while ((strcmp(ataque,"CORTE") != 0) && (strcmp(ataque,"FOCO") != 0) && (strcmp(ataque,"DEFENDER")) != 0)
		{
			printf("\nAtaque não reconhecido.\nEscolha um dos ataques: Corte - Foco - Defender\n>>");
			gets(ataque);

			i = 0;

			while(i < strlen(ataque))
			{
				ataque[i] = toupper(ataque[i]);
				i++;
			}
		}

		if(strcmp(ataque,"CORTE") == 0)
		{
			if(r->mp < 1 || r->stam < 5)
			{
				puts("Nao foi possivel atacar com corte!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1;

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 2 * r->intel + 4 * r->dex + 5 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else
			{
				int dano = 2 * r->intel + 3 * r->dex + 4 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 1;
			r->stam -= 5;
		}

		if(strcmp(ataque,"FOCO") == 0)
		{
			if(r->mp < 3 || r->stam < 7)
			{
				puts("Nao foi possivel atacar com foco!");
				return;
			}

			srand(seed);
			int chance = (rand() % 101) + 1;

			if(chance > 100 - r->dex) // ataque critico
			{
				int critico = 2 * r->intel + 5 * r->dex + 5 * r->atk;
				inimigo->hp -= critico;
				printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
			}

			else
			{
				int dano = 2 * r->intel + 3 * r->dex + 4 * r->atk + (chance/4) - 2 * inimigo->def;
				inimigo->hp -= dano;
				printf("O inimigo recebeu dano de %d.\n", dano);
			}

			r->mp -= 3;
			r->stam -= 7;
			r->dextra += 1;
		}

		if(strcmp(ataque,"DEFENDER") == 0)
		{
			r->defextra += 1;
		}

		printf("\n");
	}

}

void inimigo_ataca(Char* inimigo, Char* r) //menu de ataque do inimigo
{
	int seed = time(NULL);
	srand(seed);
	int chance = rand();
	int var = (chance % 100) + 1; // variacao  do ataque nao critico

	if((inimigo->mp) < 6 || (inimigo->stam < 7)) //mp max do mago e stam max do guerreiro
	{
		inimigo->defextra = 1;
		puts("inimigo usou defender!");
	}

	else
	{
		if ((chance % 100) +1 < 11) // 10% de chance de defesa
		{
			inimigo->defextra = 1;
			puts("inimigo usou defender!");
		}

		else
		{
			if((chance % 2) == 0)
			{
				if(inimigo->tipo == 'M') // cajadada inimigo
				{
					if((chance % 100) + 1 > 100 - inimigo->dex)
					{
						int critico = 4 * inimigo->intel + 3 * inimigo->dex + 2 * inimigo->atk;
						r->hp -= critico;
						printf("Dano critico!!! Voce recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 3 * inimigo->intel + 3 * inimigo->dex + 2 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);
					}

					inimigo->mp -= 2;
					inimigo->stam -= 4;
				}

				else if(inimigo->tipo == 'P') // justica inimigo
				{
					if((chance % 100) + 1 > 100 - inimigo->dex)
					{
						int critico = 3 * inimigo->intel + 3 * inimigo->dex + 3 * inimigo->atk;
						r->hp -= critico;
						printf("Dano critico!!! Voce recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 3 * inimigo->intel + 2 * inimigo->dex + 2 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);

					}
					inimigo->mp -= 1;
					inimigo->stam -= 4;
				}

				else
				{
					if((chance % 100) + 1 > 100 - inimigo->dex) // corte inimigo
					{
						int critico = 2 * r->intel + 4 * r->dex + 5 * r->atk;
						r->hp -= critico;
						printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 2 * inimigo->intel + 3 * inimigo->dex + 4 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);
					}
					inimigo->mp -= 1;
					inimigo->stam -= 5;
				}
			}
			else
			{
				if(inimigo->tipo == 'M') //fogo inimigo
				{
					if((chance % 100) + 1 > 100 - inimigo->dex)
					{
						int critico = 4 * inimigo->intel + 3 * inimigo->dex + 2 * inimigo->atk;
						r->hp -= critico;
						printf("Dano critico!!! Voce recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 3 * inimigo->intel + 3 * inimigo->dex + 2 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);
					}
					inimigo->mp -= 6;
					inimigo->stam -= 2;
				}

				else if(inimigo->tipo == 'P') // julgamento inimigo
				{
					if((chance % 100) + 1 > 100 - inimigo->dex)
					{
						int critico = 3 * inimigo->intel + 3 * inimigo->dex + 3 * inimigo->atk;
						r->hp -= critico;
						printf("Dano critico!!! Voce recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 3 * inimigo->intel + 2 * inimigo->dex + 2 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);

					}
					inimigo->mp -= 5;
					inimigo->stam -= 3;
					inimigo->dextra += 1;
				}

				else
				{
					if((chance % 100) + 1 > 100 - inimigo->dex) // foco inimigo
					{
						int critico = 2 * r->intel + 4 * r->dex + 5 * r->atk;
						r->hp -= critico;
						printf("Dano critico!!! O inimigo recebeu dano de %d.\n", critico);
					}

					else
					{
						int dano = 2 * inimigo->intel + 3 * inimigo->dex + 4 * inimigo->atk + (var/4) - 2 * r->def;
						r->hp -= dano;
						printf("Voce recebeu dano de %d.\n", dano);
					}
					inimigo->mp -= 3;
					inimigo->stam -= 7;
					inimigo->dextra += 1;
				}
			}
		}
	}
}
