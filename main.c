#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void) {

  double time_spent = 0.0;
  clock_t begin, end;

  
  // Permuta de Loops

  // Antes
  
  begin = clock();
  
  int x[5000][100];

  for (int k = 0; k < 100; k = k + 1)
    for (int j = 0; j < 100; j = j + 1)
      for (int i = 0; i < 5000; i = i + 1)
        x[i][j] = x[i][j] * 2;

  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo sem permuta de loop: %f segundos\n", time_spent);

  // Depois

  begin = clock();

  for (int k = 0; k < 100; k = k + 1)
    for (int i = 0; i < 5000; i = i + 1)
      for (int j = 0; j < 100; j = j + 1)
        x[i][j] = x[i][j] * 2;

  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo com permuta de loop: %f segundos\n", time_spent);

  printf("\n");

  //*****************************************************************
  // Fusão de Loops

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

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo sem fusao de loop: %f segundos\n", time_spent);

  // Depois
  
  begin = clock();

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 5000; j++) {
      aux[i][j] = aux[i][j] - 2;
      aux2[i][j] = aux2[i][j] - 2;
    }
  }

  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo com fusao de loop: %f segundos\n", time_spent);

  printf("\n");

  //**************************************************************
  // Blocagem

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

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo sem blocagem: %f segundos\n", time_spent);

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

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Tempo com blocagem: %f segundos\n", time_spent);

  return 0;
}
