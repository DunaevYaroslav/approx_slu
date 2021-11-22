#include "function.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
const double eps = 0.000001;
using namespace std;

int change(int n, int i, double **A, double *B) {
  double temp;
  int flag = 0;
  if (abs(A[i][i]) > eps) {
    flag = 1;
  }
  if (abs(A[i][i]) < eps) {
    for (int s = i + 1; s <= n; s++) {
      if (abs(A[s][i]) > eps) {
        for (int j = i; j <= n; j++) {
          temp = A[i][j];
          A[i][j] = A[s][j];
          A[s][j] = temp;
          temp = B[i];
          B[i] = B[s];
          B[s] = temp;
        }
        flag = 1;
      }
    }
  }
  if (flag == 0) {
    return 5;
  }
  return 0;
}

void diagonal(int n, int i, double **A, double *B) {
  double temp = A[i][i];
  
     if(i==n){
       B[n]/=A[n][n];
       A[n][n]=1;
       for(int s=1;s<=n-1;s++){
           B[s]-= A[s][n] * B[n];
           A[s][n]=0;
        }
    }
  else{
  for (int j = i; j <= n; j++) {
    A[i][j] /= temp;
  }
  B[i] /= temp;
  for (int r = 1; r < i; r++) {
    temp = A[r][i];
    for (int j = i; j <= n; j++) {
      A[r][j] -= (temp * A[i][j]);
    }
    B[r] -= (temp * B[i]);
  }
  for (int r = i + 1; r <= n; r++) {
    temp = A[r][i];
    for (int j = i; j <= n; j++) {
      A[r][j] -= (temp * A[i][j]);
    }
    B[r] -= (temp * B[i]);
  }
}
}


int func(int n, double **A, double *B) {
  for (int i = 1; i < n; i++) {
    if (change(n, i, A, B) == 5) {
      return 5;
    }
    diagonal(n, i, A, B);
  }
  if(change(n, n, A, B)==5){return 5;} 
  diagonal(n, n, A, B);
  return 0;
}

int gauss(double **a, double *y, int n) 
{
  double max;
  int k,i, index;
  const double eps = 0.00001;  // точность
double * x = new double[n+1];
  k = 1;
  while (k <= n) 
  {
    // Поиск строки с максимальным a[i][k]
    max = abs(a[k][k]);
    index = k;
    for (int i = k + 1; i <= n; i++) 
    {
      if (abs(a[i][k]) > max)
      {
        max = abs(a[i][k]);
        index = i;
      }
    }
    // Перестановка строк
    if (max < eps) 
    {
      // нет ненулевых диагональных элементов
      //cout << "Решение получить невозможно из-за нулевого столбца ";
      //cout << index << " матрицы A" << endl;
            delete[] x;
      return 5;
    }
    for (int j = 1; j <= n; j++) 
    {
      double temp = a[k][j];
      a[k][j] = a[index][j];
      a[index][j] = temp;
    }
    double temp = y[k];
    y[k] = y[index];
    y[index] = temp;
    // Нормализация уравнений
    for (int i = k; i <= n; i++) 
    {
      double temp = a[i][k];
      if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
      for (int j = 1; j <= n; j++) 
        a[i][j] = a[i][j] / temp;
      y[i] = y[i] / temp;
      if (i == k)  continue; // уравнение не вычитать само из себя
      for (int j = 1; j <= n; j++)
        a[i][j] = a[i][j] - a[k][j];
      y[i] = y[i] - y[k];
    }
    k++;
  }
  // обратная подстановка
  for (k = n; k >=1; k--)
  {
    x[k] = y[k];
    for (int i = 1; i <= k; i++)
      y[i] = y[i] - a[i][k] * x[k];
  }
  for(i=1;i<=n;i++){
      y[i]=x[i];
  }
        delete[] x;
  return 0;
}
