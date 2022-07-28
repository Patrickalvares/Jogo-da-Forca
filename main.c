#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[TAMANHO_PALAVRA];
int chutesdados = 0;
void limparTela() {
  fprintf(stdout, "\033[2J\033[0;0f");
  fflush(stdout);
}
int chuteserrados() {
  int erros = 0;
  for (int i = 0; i < chutesdados; i++) {
    int existe = 0;
    for (int j = 0; j < strlen(palavrasecreta); j++) {
      if (chutes[i] == palavrasecreta[j]) {
        existe = 1;
        break;
      }
    }
    if (!existe) erros++;
  }
  return erros;
}
void abertura() {
  printf("*********************\n");
  printf("****Jogo da forca****\n");
  printf("*********************\n\n");
  printf("vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n");
  printf("Tente acertar o nome de um ANIMAL em ate 6 tentativas\n");
  printf("*** USE APENAS LETRA MAIUSCULA E IGNORE ACENTUACAO ***n\n");
  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
}
void chuta() {
  char chute;
  printf("Qual letra? ");
  scanf(" %c", & chute);
  limparTela();
  chutes[chutesdados] = chute;
  chutesdados++;
}
int jachutou(char letra) {
  int achou = 0;
  for (int j = 0; j < chutesdados; j++) {
    if (chutes[j] == letra) {
      achou = 1;
      break;
    }
  }
  return achou;
}
void desenhaforca() {

  int erros = chuteserrados();

  printf("  _______         \n");
  printf(" |/      |        \n");
  printf(" |      %c%c%c    \n", (erros >= 1 ? '(' : ' '), (erros >= 1 ? '_' : ' '), (erros >= 1 ? ')' : ' '));
  printf(" |      %c%c%c    \n", (erros >= 3 ? '\\' : ' '), (erros >= 2 ? '|' : ' '), (erros >= 4 ? '/' : ' '));
  printf(" |       %c       \n", (erros >= 2 ? '|' : ' '));
  printf(" |      %c %c     \n", (erros >= 5 ? '/' : ' '), (erros >= 6 ? '\\' : ' '));
  printf(" |                \n");
  printf("_|___             \n");
  printf("\n\n");

  for (int i = 0; i < strlen(palavrasecreta); i++) {

    if (jachutou(palavrasecreta[i])) {
      printf("%c ", palavrasecreta[i]);
    } else {
      printf("_ ");
    }

  }
  printf("\n");
}
void escolhepalavra() {
  FILE * f;

  f = fopen("palavras.txt", "r");
  if (f == 0) {
    printf("Desculpe, banco de dados nao disponivel\n\n");
    exit(1);
  }

  int qtddepalavras;
  fscanf(f, "%d", & qtddepalavras);

  srand(time(0));
  int randomico = rand() % qtddepalavras;

  for (int i = 0; i <= randomico; i++) {
    fscanf(f, "%s", palavrasecreta);
  }
  fclose(f);
}
int enforcou() {

  return chuteserrados() >= 6;
}
int acertou() {
  for (int i = 0; i < strlen(palavrasecreta); i++) {
    if (!jachutou(palavrasecreta[i])) {
      return 0;
    }
  }
  return 1;
}

void adicionapalavra() {

  char quer;

  printf("Voce deseja adicionar uma nova palavra no jogo? (S/N)");
  scanf(" %c", & quer);
  if (quer == 'S') {
    char novapalavra[TAMANHO_PALAVRA];
    printf("USE APENAS LETRA MAIUSCULA, SEM ACENTOS\n\n");
    printf("Qual a nova palavra?\n");
    scanf("%s", novapalavra);

    FILE * f;

    f = fopen("palavras.txt", "r+");

    if (f == 0) {
      printf("Desculpe, banco de dados nao disponivel\n\n");
      exit(1);

    }

    int qtd;
    fscanf(f, "%d", & qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);

    fprintf(f, "\n%s", novapalavra);

    fclose(f);
  }

}

int main() {

  abertura();
  escolhepalavra();

  do {
    desenhaforca();
    chuta();

  }
  while (!acertou() && !enforcou());

  if (acertou()) {
    printf("\nParabens, voce ganhou\n\n");
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
    printf("\nVoce perdeu, a palavra secreta era *%s*, tente novamente\n\n", palavrasecreta);
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
    printf("       \\_______/           \n\n");
  }

  printf("\n\n\n\n\n");

  adicionapalavra();
  system("PAUSE");
}