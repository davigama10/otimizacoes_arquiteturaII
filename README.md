# Atividade 5 de Arquitetura II

01) Faça um programa para demonstrar as técnicas de otimização de memória cache vistas nas aulas (slides 73-80). Apresente em um arquivo único: 1) código-fonte antes; 2) apresentação de quais otimizações foram realizadas; 3) código fonte após as otimizações; 4) tabela ou gráfico apresentando as melhorias alcançadas com as otimizações. Dica: execute com diferentes tamanho de dados. Quanto maiores as estruturas de dados, mais visível a otimização se torna.

## Permuta de Loops

```C
// Antes
  
  begin = clock();
  
  int x[5000][100];

  for (int k = 0; k < 100; k = k + 1)
    for (int j = 0; j < 100; j = j + 1)
      for (int i = 0; i < 5000; i = i + 1)
        x[i][j] = x[i][j] * 2;

  end = clock();
  
  // Depois

  begin = clock();

  for (int k = 0; k < 100; k = k + 1)
    for (int i = 0; i < 5000; i = i + 1)
      for (int j = 0; j < 100; j = j + 1)
        x[i][j] = x[i][j] * 2;

  end = clock();
  ```
  
  ## Fusão de Loops
  
  ```C
  // Antes

  int aux[100][5000];
  int aux2[100][5000];

  begin = clock();

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 5000; j++) {
      aux[i][j] = aux[i][j] + 2;
    }
  }
  for (int i = 0; i < 100; i = i + 1) {
    for (int j = 0; j < 5000; j = j + 1) {
      aux2[i][j] = aux2[i][j] + 2;
    }
  }

  end = clock();
  
  // Depois
  
  begin = clock();

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 5000; j++) {
      aux[i][j] = aux[i][j] - 2;
      aux2[i][j] = aux2[i][j] - 2;
    }
  }

  end = clock();
  ```
  
  ## Blocagem
  
  ```C
  // Antes

  int a[500][500];
  int b[500][500];
  int c[500][500];

  begin = clock();

  for (int i = 0; i < 500; i++) {
    for (int j = 0; j < 500; j++) {
      a[i][j] = rand() % 10;
      for (int k = 0; k < 500; k++) {
        b[j][k] = rand() % 10;
        c[j][k] = rand() % 10;
      }
    }
  }

  end = clock();
  
  // Depois

  begin = clock();

  for (int jj = 0; jj < 500; jj = jj + 2) {
    for (int kk = 0; kk < 500; kk = kk + 2) {
      for (int i = 0; i < 500; i = i + 1) {
        for (int j = jj; j < jj + 2 - 1; j = j + 1) {
          a[i][j] = rand() % 10;
          for (int k = kk; k < kk + 2 - 1; k = k + 1) {
            b[j][k] = rand() % 10;
            c[j][k] = rand() % 10;
          }
        }
      }
    }
  }

  end = clock();
  ```
  
  ## Resultados
  
  Tempo sem permuta de loop: 0.055196 segundos  
  Tempo com permuta de loop: 0.006071 segundos

  Tempo sem fusao de loop: 0.002366 segundos  
  Tempo com fusao de loop: 0.000181 segundos

  Tempo sem blocagem: 2.125947 segundos  
  Tempo com blocagem: 0.727063 segundos
