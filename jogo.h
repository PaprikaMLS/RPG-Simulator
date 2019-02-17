typedef struct 
{
	char tipo;
	int atk;
	int def;
	int hp;
	int mp;
	int stam;
	int dex;
	int intel;
	int defextra;
	int dextra;
}Char;

Char criar_char(char n);

char menu_escolha(void);

void imp_char(Char r);

void distribuir(Char* r);

Char criar_inimigo(void);

void menu_ataca(Char* r, Char* inimigo);

void inimigo_ataca(Char* inimigo, Char* r);

void ler_preset(Char* r, FILE* arq);