#define TAMANHO_PALAVRA 20
#define MAX_TENTATIVA 26

int enforcou(char palavrasecreta[20], char chutes[26], int tentativas);
void abertura();
int jachutou(char letra, char chutes[26], int tentativas);
void desenhaforca(char palavrasecreta[20], char chutes[26], int tentativas);
int acertou(char palavrasecreta[20], char chutes[26], int tentativas);
void escolhepalavra(char  palavrasecreta[20]);
void adicionapalavra();
int chuteserrados(char palavrasecreta[TAMANHO_PALAVRA], char chutes[MAX_TENTATIVA], int tentativas);