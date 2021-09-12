#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "forca.h"

void abertura() {
    printf("**************************\n");
    printf("******** abertura ********\n");
    printf("**************************\n");
}

void adicionapalavra() {
    char quer = NULL;
    printf("\nDeseja adicionar uma nova palavra? S/n ");
    scanf(" %c", &quer);

    if (quer == 'S' || quer == 's') {
        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavras?");
        scanf("%s", &novapalavra);

        FILE *f;
        f = fopen("palavras.txt", "r+");
        if (f == 0) {
            printf("Banco de dados indisponivel!!");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}

void escolhepalavra(char palavrasecreta[TAMANHO_PALAVRA]) {
    FILE *f;
    int quantpalavras;

    f = fopen("palavras.txt", "r");
    if (f == 0) {
        printf("Banco de dados indisponivel!!");
        exit(1);
    }

    fprintf(f, "r");
    fscanf(f, "%d", &quantpalavras);
    srand(time(0));
    int numrand = rand() % quantpalavras;

    for (int i = 0; i <= numrand; ++i) {
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

void chuta(char chutes[MAX_TENTATIVA], int *tentativas) {
    char chute;
    printf("\nUma letra? ");
    scanf(" %c", &chute);
    chutes[(*tentativas)] = chute;
    (*tentativas)++;
}

int jachutou(char letra, char chutes[MAX_TENTATIVA], int tentativas) {
    int achou = 0;
    for (int j = 0; j < tentativas; ++j) {
        if (chutes[j] == letra) {
            achou = 1;
            break;
        }
    }
    return achou;
}

void desenhaforca(char palavrasecreta[TAMANHO_PALAVRA], char chutes[MAX_TENTATIVA], int tentativas) {
    int erros = chuteserrados(palavrasecreta, chutes, tentativas);
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n",
           (erros >= 1 ? '(' : ' '),
           (erros >= 1 ? '_' : ' '),
           (erros >= 1 ? ')' : ' '));
    printf(" |      %c%c%c  \n",
           (erros >= 2 ?'\\': ' '),
           (erros >= 2 ? '|': ' '),
           (erros >= 2 ? '/': ' '));
    printf(" |       %c     \n",
           (erros >= 3 ?'|': ' '));
    printf(" |      %c %c   \n",
           (erros >= 3 ? '/': ' '),
           (erros >= 4 ?'\\' : ' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i = 0; i < strlen(palavrasecreta); ++i) {

        int achou = jachutou(palavrasecreta[i], chutes, tentativas);
        if (achou) {
            printf("%c ", palavrasecreta[i]);
        } else {
            printf("_ ");
        }
    }
}

int acertou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[MAX_TENTATIVA], int tentativas) {
    for (int i = 0; i < strlen(palavrasecreta); ++i) {
        if (!jachutou(palavrasecreta[i], chutes, tentativas)) {
            return 0;
        }
    }
    return 1;
}

int chuteserrados(char palavrasecreta[TAMANHO_PALAVRA], char chutes[MAX_TENTATIVA], int tentativas) {
    int erros = 0;

    for (int i = 0; i < tentativas; ++i) {
        int existe = 0;

        for (int j = 0; j < strlen(palavrasecreta); ++j) {
            if (chutes[i] == palavrasecreta[j]) {
                existe = 1;
                break;
            }
        }
        if (!existe) erros++;
    }
    return erros;
}

int enforcou(char palavrasecreta[TAMANHO_PALAVRA], char chutes[MAX_TENTATIVA], int tentativas) {
    return chuteserrados(palavrasecreta, chutes, tentativas) >= 5;
}

int main() {
    char palavrasecreta[TAMANHO_PALAVRA];
    escolhepalavra(palavrasecreta);
    char chutes[MAX_TENTATIVA];
    int chutesdados = 0;

    abertura();

    do {
        desenhaforca(palavrasecreta, chutes, chutesdados);
        chuta(chutes, &chutesdados);

    } while (!acertou(palavrasecreta, chutes, chutesdados) &&
             !enforcou(palavrasecreta, chutes, chutesdados));

    if(acertou(palavrasecreta, chutes, chutesdados)) {
        printf("\nParabéns, você ganhou!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");

    } else {
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra era **%s**\n\n", palavrasecreta);

        printf("    _______________         \n");
        printf("   /               \\       \n");
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionapalavra();
}


