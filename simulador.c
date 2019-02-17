#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "jogo.h"

int main(void)
{
	int jogar = 1, i = 0;

	FILE* arq = fopen("preset", "r"); //abrir arquivo

	char tipo;
	char* continuar = (char*) malloc (15 * sizeof(char));
	if(continuar == NULL)
	{
		puts("Erro interno.");
		exit(1);
	}


	char* usar_preset = (char*) malloc(4 * sizeof(char));
	if(usar_preset == NULL)
	{
		puts("Erro  interno.");
		exit(1);
	}

	Char jogador; // sem arquivo
	if(arq == NULL)
	{
		tipo = menu_escolha();
		jogador = criar_char(tipo);
		distribuir(&jogador);
	}
	else // caso onde um arquivo já feito é encontrado
	{
		system("clear");

		printf("\n+-----------------------------------------------------------+\n");
		printf("|------------------ SIMULADOR DE BATALHAS ------------------|\n");
		printf("+-----------------------------------------------------------+\n\n\n");

		printf("Um arquivo de ja pronto foi encontrado. Deseja utiliza-lo? (sim/nao)\n>>");
		gets(usar_preset);

		i = 0;
		while(i < strlen(usar_preset))
		{
			usar_preset[i] = toupper(usar_preset[i]);
			i++;
		}

		while((strcmp(usar_preset, "SIM")) != 0 && (strcmp(usar_preset, "NAO")) != 0)
		{
			printf("Comando nao reconhecido. Utilizar arquivo? (sim/nao)\n>>");
			gets(usar_preset);

			i = 0;

			while(i < strlen(usar_preset))
			{
				usar_preset[i] = toupper(usar_preset[i]);
				i++;
			}
		}

		if(usar_preset[0] == 'N')
		{
			tipo = menu_escolha();
			jogador = criar_char(tipo);
			distribuir(&jogador);
		}
		else
		{
			ler_preset(&jogador, arq);
		}

		fclose(arq);
	}

	// apos pontos extras
	printf("\033[2J");
  printf("\033[%d;%dH", 0, 0); // limpando a tela
	printf("Seus novos atributos sao:\n");
	imp_char(jogador);
	printf("\nPressione ENTER para continuar...");
	getchar(); // esperando enter ser pressionado

	// limpando a tela
	printf("\033[2J");
  printf("\033[%d;%dH", 0, 0);

	// criar inimigo
	Char inimigo = criar_inimigo();
	puts("Um inimigo hostil surgiu !!! ");
	printf("tipo: %s\n\n", (inimigo.tipo == 'M')? "Mago" : ((inimigo.tipo == 'G')? "Guerreiro" : "Ladino"));

	while(jogar)
	{
		// status inicial do turno
		printf("\033[47mJogador\033[0m\n\tHP: %d\n\tMP: %d\n\tEstamina: %d\n\n", jogador.hp, jogador.mp, jogador.stam);
		printf("\033[41mInimigo\033[0m\n\tHP: %d\n\tMP: %d\n\tEstamina: %d\n\n", inimigo.hp, inimigo.mp, inimigo.stam);

		// debuff do jogador
		if(jogador.dextra == 1)
		{
			if(jogador.tipo == 'P')
			{
				jogador.dex -= 2;
			}

			else
			{
				jogador.dex -= 3;
			}

			jogador.dextra = 0;
		}

		if(jogador.defextra == 1)
		{
			if(jogador.tipo == 'M')
			{
				jogador.def -= 2;
			}

			else if(jogador.tipo == 'P')
			{
				jogador.def -= 4;
			}

			else
			{
				jogador.def -= 3;
			}

			jogador.defextra = 0;
		}

		// ataque do jogador
		menu_ataca(&jogador, &inimigo);

		if(inimigo.hp <= 0)
		{
			puts("Inimigo derrotado !!! Voce venceu !!!");
			printf("Gostaria de continuar ? (Sim/Nao)\n>>");
			gets(continuar);

			i = 0;

			while(i < strlen(continuar))
			{
				continuar[i] = toupper(continuar[i]);
				i++;
			}

			while ((strcmp(continuar,"SIM") != 0) && (strcmp(continuar,"NAO") != 0))
			{
				printf("\nEntrada não reconhecida.\nGostaria de continuar ? (Sim/Nao)\n>>");
				gets(continuar);

				i = 0;

				while(i < strlen(continuar))
				{
					continuar[i] = toupper(continuar[i]);
					i++;
				}
			}

			if(continuar[0] == 'S')
			{
				tipo = menu_escolha();
				jogador = criar_char(tipo);
				inimigo = criar_inimigo();
				break;
			}

			else
			{
				exit(1);
			}

		}

		// buff do jogador
		if(jogador.defextra == 1) //sobe def e recupera mp
		{
			if(jogador.tipo == 'M')
			{
				jogador.def += 2;
				jogador.mp += 4;
			}

			else if(jogador.tipo == 'P')
			{
				jogador.def += 4;
				jogador.mp += 3;
			}

			else
			{
				jogador.def += 3;
				jogador.mp += 1;
			}

			jogador.stam += 3;
		}

		if(jogador.dextra == 1)
		{

			if(jogador.tipo == 'P')
			{
				jogador.dex += 2;
			}

			else
			{
				jogador.dex += 3;
			}
		}

		printf("Pressione ENTER para continuar...\n");
		getchar();

		// limpando a tela
		printf("\033[2J");
	  printf("\033[%d;%dH", 0, 0);

		// status inicial do turno
		printf("\033[47mJogador\033[0m\n\tHP: %d\n\tMP: %d\n\tEstamina: %d\n\n", jogador.hp, jogador.mp, jogador.stam);
		printf("\033[41mInimigo\033[0m\n\tHP: %d\n\tMP: %d\n\tEstamina: %d\n\n", inimigo.hp, inimigo.mp, inimigo.stam);

		//debuff inimigo
		if(inimigo.dextra == 1)
		{

			if(inimigo.tipo == 'P')
			{
				inimigo.dex -= 2;
			}

			else
			{
				inimigo.dex -= 3;
			}

			inimigo.dextra = 0;
		}

		if(inimigo.defextra == 1)
		{
			if(inimigo.tipo == 'M')
			{
				inimigo.def -= 2;
			}

			else if(inimigo.tipo == 'P')
			{
				inimigo.def -= 4;
			}

			else
			{
				inimigo.def -= 3;
			}

			inimigo.defextra = 0;
		}

		// ataque do inimigo

		inimigo_ataca(&inimigo, &jogador);

		if(jogador.hp <= 0)
		{
			puts("Voce Perdeu...");
			printf("Gostaria de continuar ? (Sim/Nao)\n>>");
			gets(continuar);

			i = 0;

			while(i < strlen(continuar))
			{
				continuar[i] = toupper(continuar[i]);
				i++;
			}

			while ((strcmp(continuar,"SIM") != 0) && (strcmp(continuar,"NAO") != 0))
			{
				printf("\nEntrada não reconhecida.\nGostaria de continuar ? (Sim/Nao)\n>>");
				gets(continuar);

				i = 0;

				while(i < strlen(continuar))
				{
					continuar[i] = toupper(continuar[i]);
					i++;
				}
			}

			if(continuar[0] == 'S')
			{
				tipo = menu_escolha();
				jogador = criar_char(tipo);
				inimigo = criar_inimigo();
				break;
			}

			else
			{
				exit(1);
			}
		}

		// buff inimigo
		if(inimigo.defextra == 1) //sobe def e recupera mp
		{
			if(inimigo.tipo == 'M')
			{
				inimigo.def += 2;
				inimigo.mp += 4;
			}

			else if(inimigo.tipo == 'P')
			{
				inimigo.def += 4;
				inimigo.mp += 3;
			}

			else
			{
				inimigo.def += 3;
				inimigo.mp += 1;
			}

			inimigo.stam += 3;
		}

		if(inimigo.dextra == 1)
		{

			if(inimigo.tipo == 'P')
			{
				inimigo.dex += 2;
			}

			else
			{
				inimigo.dex += 3;
			}
		}

		printf("Pressione ENTER para continuar...\n");
		getchar();

		// limpando a tela
		printf("\033[2J");
	  printf("\033[%d;%dH", 0, 0);

	}

	return 0;
}
