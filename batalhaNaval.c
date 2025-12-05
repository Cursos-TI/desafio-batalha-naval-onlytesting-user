#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Nível Novato
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.

// Inicializa o tabuleiro com um determinado tamanho (linhas/colunas)
void inicializar_tabuleiro(int tabuleiro[][10], const int tam_tabuleiro, const int agua)
{
  for (int i = 0; i < tam_tabuleiro; i++)
  {
    for (int j = 0; j < tam_tabuleiro; j++)
    {
      tabuleiro[i][j] = agua;
    }
  }
}

/* Verifica se um navio na horizontal pode ser posicionado e o posiciona se possível. Para isso, essa função utiliza como parâmetros: o tabuleiro do jogo e o seu tamanho; o tamanho dos navios e a posição deles no tabuleiro (linha e coluna). Retorna erro em caso de sobreposição */
int posicionar_navio_horizontal(int tabuleiro[][10], const int tam_tabuleiro, const int tam_navio, const int linha, const int coluna, const int navio)
{
  // Verifica se o navio está dentro dos limites do tabuleiro
  if (linha < 0 || linha >= tam_tabuleiro || coluna < 0 || coluna + tam_navio > tam_tabuleiro)
  {
    printf("ERRO: Navio Horizontal fora dos limites do tabuleiro! (Início: [%d, %d])\n", linha, coluna);
    return 0;
  }

  // Verifica se há sobreposição entre navios
  for (int j = 0; j < tam_navio; j++)
  {
    if (tabuleiro[linha][coluna + j] == navio)
    {
      printf("ERRO: Navio Horizontal se sobrepõe a outro navio! (Início: [%d, %d])\n", linha, coluna);
      return 0;
    }
  }

  /* Caso o navio seja colocado dentro dos limites do tabuleiro e não haja sobreposição, ele é posicionado corretamente nas coordenadas indicadas */
  for (int j = 0; j < tam_navio; j++)
  {
    tabuleiro[linha][coluna + j] = navio;
  }
  printf("SUCESSO: Navio Horizontal posicionado na %d° Linha, Colunas %d a %d\n", linha, coluna, coluna + tam_navio - 1);
  return 1;
}

/* Verifica se um navio na vertical pode ser posicionado e o posiciona se possível. Para isso, essa função utiliza como parâmetros: o tabuleiro do jogo e o seu tamanho; o tamanho dos navios e a posição deles no tabuleiro (linha e coluna). Retorna erro em caso de sobreposição */
int posicionar_navio_vertical(int tabuleiro[][10], const int tam_tabuleiro, const int tam_navio, int linha, int coluna, const int navio)
{
  // Verifica se o navio está dentro dos limites do tabuleiro
  if (coluna < 0 || coluna >= tam_tabuleiro || linha < 0 || linha + tam_navio > tam_tabuleiro)
  {
    printf("ERRO: Navio Vertical fora dos limites do tabuleiro! (Início: [%d, %d])\n", linha, coluna);
    return 0;
  }

  // Verifica se há sobreposição entre navios
  for (int i = 0; i < tam_navio; i++)
  {
    if (tabuleiro[linha + i][coluna] == navio)
    {
      printf("ERRO: Navio Vertical se sobrepõe a outro navio! (Início: [%d, %d])\n", linha, coluna);
      return 0;
    }
  }

  /* Caso o navio seja colocado dentro dos limites do tabuleiro e não haja sobreposição, ele é posicionado corretamente nas coordenadas indicadas */
  for (int i = 0; i < tam_navio; i++)
  {
    tabuleiro[linha + i][coluna] = navio;
  }
  printf("SUCESSO: Navio Vertical posicionado na %d° Coluna, Linhas %d a %d\n", coluna, linha, linha + tam_navio - 1);
  return 1;
}

/* Exibe o tabuleiro completo no terminal tendo como parâmetros o próprio tabuleiro e seu tamanho */
void exibir_tabuleiro(int tabuleiro[][10], const int tam_tabuleiro)
{
  printf("\nBatalha Naval:\n\n");

  /* Imprime o cabeçalho das colunas. Esse cabeçalho, nesse caso, vai de 0 a 9 e serve de guia e mapeamento das coordenadas para que fique mais fácil identificá-las e ter uma melhor noção do posicionamento dos navios */
  printf("   ");
  for (int j = 0; j < tam_tabuleiro; j++)
  {
    printf("%2d ", j);
  }
  printf("\n");

  /* Imprime o cabeçalho das linhas. Esse cabeçalho, nesse caso, vai de 0 a 9 e serve de guia e mapeamento das coordenadas para que fique mais fácil identificá-las e ter uma melhor noção do posicionamento dos navios */
  for (int i = 0; i < tam_tabuleiro; i++)
  {
    printf("%2d ", i);
    for (int j = 0; j < tam_tabuleiro; j++)
    {
      printf("%2d ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

int main()
{
  /* Declaração das Constantes necessárias para criação do tabuleiro e posicionamento dos navios */
  const int AGUA = 0;
  const int NAVIO = 3;
  const int TAMANHO_TABULEIRO = 10;
  const int TAMANHO_NAVIO = 3;

  /* Definição do tabuleiro como o tamanho 10x10
   O valor 10 é passado diretamente na declaração, mas usamos a constante
   TAMANHO_TABULEIRO para as funções, dessa forma temos mais controle e flexibilidade */
  int tabuleiro[10][10];

  // Inicializa o tabuleiro
  inicializar_tabuleiro(tabuleiro, TAMANHO_TABULEIRO, AGUA);

  // Coordenadas dos navios
  int navio_h_lin = 2;
  int navio_h_col = 1;

  int navio_v_lin = 5;
  int navio_v_col = 6;

  // Posiciona os navios no tabuleiro, passando as constantes como parâmetros
  // Navio Horizontal: [2, 1], [2, 2], [2, 3] - Colunas 1, 2 e 3 dentro de uma mesma linha (2)
  posicionar_navio_horizontal(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, navio_h_lin, navio_h_col, NAVIO);

  // Navio Vertical: [5, 6], [6, 6], [7, 6] - Linhas 5, 6 e 7 dentro de uma mesma coluna (6)
  posicionar_navio_vertical(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, navio_v_lin, navio_v_col, NAVIO);

  // Chamada à função responsável por exibir o tabuleiro completo, passando a constante como parâmetro
  exibir_tabuleiro(tabuleiro, TAMANHO_TABULEIRO);

  return 0;
}
