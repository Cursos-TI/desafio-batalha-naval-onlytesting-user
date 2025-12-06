#include <stdio.h>
#include <stdlib.h>

// Desafio Batalha Naval - MateCheck
// Nível Mestre
// Neste desafio final, você adicionará um toque estratégico ao seu jogo de Batalha Naval, implementando habilidades especiais com áreas de efeito distintas.

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
int posicionar_navio_vertical(int tabuleiro[][10], const int tam_tabuleiro, const int tam_navio, const int linha, const int coluna, const int navio)
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

/* Verifica se um navio na diagonal pode ser posicionado e o posiciona se possível. Para isso, essa função utiliza o parâmetro de direção para definir se o navio está em uma posição diagonal crescente ou descrescente. Retorna erro em caso de sobreposição */
int posicionar_navio_diagonal(int tabuleiro[][10], const int tam_tabuleiro, const int tam_navio, const int linha, const int coluna, const int navio, const int direcao)
{
  // i_vetor_direcao está para linha como j_vetor_direcao está para coluna
  int i_vetor_direcao, j_vetor_direcao;

  // Constantes responsáveis por conter o valor que define a direção da diagonal
  const int DIAG_CRESCENTE_VAL = 1;
  const int DIAG_DECRESCENTE_VAL = 2;

  // Determina os incrementos/decrementos com base na direção
  if (direcao == DIAG_CRESCENTE_VAL)
  {
    i_vetor_direcao = 1;
    j_vetor_direcao = 1;
  }
  else if (direcao == DIAG_DECRESCENTE_VAL)
  {
    i_vetor_direcao = 1;
    j_vetor_direcao = -1;
  }
  else
  {
    printf("ERRO: Direção Diagonal inválida!\n");
    return 0;
  }

  /* Loop para verificar a posição de inserção do navio e prevenir que ele seja alocado em coordenadas fora dos limites ou que gere sobreposição com outros navios */
  for (int k = 0; k < tam_navio; k++)
  {
    int r = linha + k * i_vetor_direcao;  // Nova linha
    int c = coluna + k * j_vetor_direcao; // Nova coluna

    // Verifica se o navio está dentro dos limites do tabuleiro
    if (r < 0 || r >= tam_tabuleiro || c < 0 || c >= tam_tabuleiro)
    {
      printf("ERRO: Navio Diagonal %s fora dos limites do tabuleiro! (Posição de erro: [%d, %d])\n", (direcao == DIAG_CRESCENTE_VAL ? "Crescente" : "Decrescente"), r, c);
      return 0;
    }

    // Verifica se há sobreposição entre navios
    if (tabuleiro[r][c] == navio)
    {
      printf("ERRO: Navio Diagonal %s se sobrepõe a outro navio! (Posição de erro: [%d, %d])\n", (direcao == DIAG_CRESCENTE_VAL ? "Crescente" : "Decrescente"), r, c);
      return 0;
    }
  }

  // Posiciona o navio se ele passar em todas as avaliações
  for (int k = 0; k < tam_navio; k++)
  {
    int r = linha + k * i_vetor_direcao;
    int c = coluna + k * j_vetor_direcao;
    tabuleiro[r][c] = navio;
  }

  printf("SUCESSO: Navio Diagonal %s posicionado com início na %d° linha, %d° coluna\n", (direcao == DIAG_CRESCENTE_VAL ? "Crescente" : "Decrescente"), linha, coluna);
  return 1;
}

// Aplica o padrão de ataque em formato de Cone
void ataque_cone(int tabuleiro[][10], const int tam_tabuleiro, const int linha_origem, const int coluna_origem, const int AREA_AFETADA)
{
  // Define a altura do Cone
  const int ALTURA = 2; // Para um cone com 3 linhas de altura

  printf("\n▲ Ataque Cone (Coordenadas do Topo: [%d, %d], Altura do Cone: %d)\n", linha_origem, coluna_origem, ALTURA);

  /* Os loops aninhados iteram sobre a área do cone, de linha_origem até linha_origem + ALTURA */
  for (int i = linha_origem; i <= linha_origem + ALTURA; i++)
  {
    // Calcula a distância vertical
    int dist_vertical = i - linha_origem;

    // Loop responsável pela preenchimento horizontal
    for (int j = coluna_origem - dist_vertical; j <= coluna_origem + dist_vertical; j++)
    {
      // Verifica se a posição está dentro dos limites do tabuleiro
      if (i >= 0 && i < tam_tabuleiro && j >= 0 && j < tam_tabuleiro)
      {
        /* Verifica se na posição atual já não há um navio (3), caso não, posiciona a área afetada */
        if (tabuleiro[i][j] != 3)
        {
          tabuleiro[i][j] = AREA_AFETADA;
        }
      }
    }
  }
}

// Aplica o padrão de ataque em formato de Cruz
void ataque_cruz(int tabuleiro[][10], const int tam_tabuleiro, const int linha_origem, const int coluna_origem, const int AREA_AFETADA)
{
  // Define o raio da Cruz
  const int RAIO = 2;

  printf("\n+ Ataque Cruz (Coordenadas do Centro: [%d, %d], Raio da Cruz: %d)\n", linha_origem, coluna_origem, RAIO);

  /* Os loops aninhados iteram sobre a área ao redor do ponto de origem tendo como baso o tamanho do raio definido para a Cruz */
  for (int i = linha_origem - RAIO; i <= linha_origem + RAIO; i++)
  {
    for (int j = coluna_origem - RAIO; j <= coluna_origem + RAIO; j++)
    {
      // Verifica se a posição está dentro dos limites do tabuleiro
      if (i >= 0 && i < tam_tabuleiro && j >= 0 && j < tam_tabuleiro)
      {
        // A condicional abaixo é responsável por criar a forma de CRUZ:
        if (i == linha_origem || j == coluna_origem)
        {
          /* Verifica se na posição atual já não há um navio (3), caso não, posiciona a área afetada */
          if (tabuleiro[i][j] != 3)
          {
            tabuleiro[i][j] = AREA_AFETADA;
          }
        }
      }
    }
  }
}

/* Aplica um padrão de ataque em formato de Octaedro/Losango */
void ataque_octaedro(int tabuleiro[][10], const int tam_tabuleiro, const int linha_origem, const int coluna_origem, const int AREA_AFETADA)
{
  // Define a dimensão do Losango
  const int AREA = 2;

  printf("\n◆ Ataque Octaedro (Coordenadas do Centro: [%d, %d], Área: %d)\n", linha_origem, coluna_origem, AREA);

  // Os loops aninhados iteram sobre o quadrado ao redor do ponto de origem
  for (int i = linha_origem - AREA; i <= linha_origem + AREA; i++)
  {
    for (int j = coluna_origem - AREA; j <= coluna_origem + AREA; j++)
    {
      // Verifica se a posição está dentro dos limites do tabuleiro
      if (i >= 0 && i < tam_tabuleiro && j >= 0 && j < tam_tabuleiro)
      {
        /* Calcula a distância vertical e horizontal do losango a partir do centro */
        int dist_vertical = abs(i - linha_origem);
        int dist_horizontal = abs(j - coluna_origem);

        // Impede o excedimento em relação a AREA:
        if (dist_vertical + dist_horizontal <= AREA)
        {
          /* Verifica se na posição atual já não há um navio (3), caso não, posiciona a área afetada */
          if (tabuleiro[i][j] != 3)
          {
            tabuleiro[i][j] = AREA_AFETADA;
          }
        }
      }
    }
  }
}

/* Exibe o tabuleiro completo no terminal, utilizando diferentes caracteres para representar a aguá (~), os navios (T) e área afetada (X). Caso seja passado um valor não mapeado, ele retorna as coordendas para inspeção */
void exibir_tabuleiro(int tabuleiro[][10], const int tam_tabuleiro)
{
  printf("\nBatalha Naval:\n\n");

  // Imprime o cabeçalho das colunas
  printf("   ");
  for (int j = 0; j < tam_tabuleiro; j++)
  {
    printf("%2d ", j);
  }
  printf("\n");

  // Imprime o cabeçalho das linhas
  for (int i = 0; i < tam_tabuleiro; i++)
  {
    printf("%2d ", i);
    for (int j = 0; j < tam_tabuleiro; j++)
    {
      /* Usa caracteres diferentes para cada elemento do jogo para melhor visualização */
      if (tabuleiro[i][j] == 0)
      {
        printf(" ~ "); // Se for "Água"
      }
      else if (tabuleiro[i][j] == 3)
      {
        printf(" T "); // Se for "Navio"
      }
      else if (tabuleiro[i][j] == 1)
      {
        printf(" X "); // Se for "Área Afetada""
      }
      else
      {
        printf("%2d ", tabuleiro[i][j]); // Se for um valor não mapeado
      }
    }
    printf("\n");
  }
}

int main()
{
  // Declaração das Constantes
  const int AGUA = 0;
  const int NAVIO = 3;
  const int TAMANHO_TABULEIRO = 10;
  const int TAMANHO_NAVIO = 3;
  const int AREA_AFETADA = 1;
  // Para construção de Navios Diagonais
  const int DIAGONAL_CRESCENTE = 1;
  const int DIAGONAL_DECRESCENTE = 2;

  int tabuleiro[10][10];

  // Inicializa o tabuleiro
  inicializar_tabuleiro(tabuleiro, TAMANHO_TABULEIRO, AGUA);

  // Posiciona os navios no tabuleiro, passando as constantes como parâmetros:

  // Navio 1: Horizontal
  // Posições: [2, 1], [2, 2], [2, 3]
  posicionar_navio_horizontal(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, 2, 1, NAVIO);

  // Navio 2: Vertical
  // Posições: [5, 6], [6, 6], [7, 6]
  posicionar_navio_vertical(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, 5, 6, NAVIO);

  // Navio 3: Diagonal Crescente
  // Início: [6, 0]. Posições: [6, 0], [7, 1], [8, 2]
  posicionar_navio_diagonal(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, 6, 0, NAVIO, DIAGONAL_CRESCENTE);

  // Navio 4: Diagonal Decrescente
  // Início: [1, 8]. Posições: [1, 8], [2, 7], [3, 6]
  posicionar_navio_diagonal(tabuleiro, TAMANHO_TABULEIRO, TAMANHO_NAVIO, 1, 8, NAVIO, DIAGONAL_DECRESCENTE);

  // Chamada à função responsável por aplicar o ataque de Cone:
  /* A linha abaixo foi comentada apenas para não atrapalhar a visualização no terminal. Caso queira utilizá-la, descomente */
  // ataque_cone(tabuleiro, TAMANHO_TABULEIRO, 3, 2, AREA_AFETADA);

  // Chamada à função responsável por aplicar o ataque de Cruz:
  /* A linha abaixo foi comentada apenas para não atrapalhar a visualização no terminal. Caso queira utilizá-la, descomente */
  // ataque_cruz(tabuleiro, TAMANHO_TABULEIRO, 4, 4, AREA_AFETADA);

  // Chamada à função responsável por aplicar o ataque de Octaedro:
  ataque_octaedro(tabuleiro, TAMANHO_TABULEIRO, 4, 4, AREA_AFETADA);

  // Chamada à função responsável por exibir o tabuleiro completo, passando a constante como parâmetro
  exibir_tabuleiro(tabuleiro, TAMANHO_TABULEIRO);

  return 0;
}
