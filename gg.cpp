#include "function.h"
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int const NN = 1000;
double const eps = 0.00000000000001;
double const pi = 3.1415926;

double f(int k, int n, int i, int j) {
  if (k == 1) {
    return double(n - max(i, j) + 1.0);
  }
  if (k == 2) {
    return double(max(i, j));
  }
  if (k == 3) {
    return double(abs(i - j));
  }


  if (k == 4) {
    return double(1.0 / (i + j - 1));
  }
  return 0;
}

double err(double *b, int n) {
  int i;
  double norm[n + 1];
  double s = 0;
  for (i = 1; i <= n; i++) {
    norm[i] = i % 2;
  }
  for (i = 1; i <= n; i++) {
    s += (b[i] - norm[i]) * (b[i] - norm[i]);
  }
  return sqrt(s);
}

double nev(double *x, double *b, double **a, int n) {
  int i, j;
  double Ax[n + 1];
  double sq1 = 0, sq2 = 0;
  for (i = 1; i <= n; i++) {
    Ax[i] = 0;
    for (j = 1; j <= n; j++) {
      Ax[i] += a[i][j] * x[j];
    }
  }
  for (i = 1; i <= n; i++) {
    sq1 += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    sq2 += (b[i]) * (b[i]);
  }
  return (sqrt(sq1)) / (sqrt(sq2));
  //||Ax-b||/||b||
}





//new
void create_b(int n, double *b, double **a) {
  double h = 1/n;
  double *x = new double[n + 1];
  for(int j=0;j<n+1;j++){
    x[j] = h*j;
  }
  for(int i=2;i<n-1;i++){
  b[i] = 1 / 2 * (sin(x[i]) - cos(pi * x[i]) * (pi*pi*pi*pi + sin(x[i])) - pi*pi*pi * sin(pi * x[i]))*h*h*h*h;
  }
  b[0] = 0;
  b[1] = 0;
  b[n - 1] = 0;
  b[n] = 1;
}
//new




int main(int argc, char *argv[]) {
  // ofstream fout("output.txt");

  int n = 0;
  int m = 0;
  int k = 0;
  int i;
  int j;
  int ss[4];
  string filename;
  string s;

  if (argc < 3) {
    cout << "not enough numbers";
    return -1;
  }

  for (i = 1; i < 4; i++) {
    s = argv[i];
    ss[i] = s.size();
  }
  for (i = 1; i < 4; i++) {
    for (j = 0; j < ss[i]; j++) {
      if (!isdigit(argv[i][j])) {
        cout << "not a number\n";
        return -1;
      }
    }
  }
  n = (atoi(argv[1]));
  m = (atoi(argv[2]));
  k = (atoi(argv[3]));
  if (k > 4) {
    cout << "k very large\n";
    return -1;
  }
  if (n == 0) {
    cout << "matrix size = 0\n";
    return -1;
  }
  if (n < 0) {
    cout << "not a natural number\n";
    return -1;
  }
  if (m > n) {
    cout << "m > n\n";
    return -1;
  }
  if (n > NN) {
    cout << "very big n";
    return -2;
  }
  if (k == 0) {
    if (argc < 5) {
      cout << "file not defined";
      return -1;
    }
    filename = argv[4];
  }
    double **a = new double *[n + 1];
  for (i = 0; i < n + 1; i++) {
    a[i] = new double[n + 1];
  }
  
  ifstream fin(filename);
    if (fin.is_open() == 0 && (k == 0)) {
    cout << "Filename is bad\n";
                     for (i = 0; i < n + 1; i++) {
                delete[] a[i];
                    }
                    delete[] a;
    return -3;
  }
  

  if (k == 0) {
    if (fin.is_open()) {
        int count = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if(fin >> a[i][j]){if (!(fin.fail())){count++;}}
            if (fin.fail() && count!=0){
             cout << "char in file";
               for (int y = 0; y < n + 1; y++) {
                delete[] a[y];
                    }
                    delete[] a;
             return -3;
                 }
        }
      if (count == 0) {
        for (i = 0; i < n + 1; i++) {
                delete[] a[i];
                    }
                    delete[] a;
        cout << "empty file or only chars in file\n";
        return -3;
      }
    }
  }
  }




    double **cop = new double *[n + 1];
  for (i = 0; i < n + 1; i++) {
    cop[i] = new double[n + 1];
  }


double h = 1/n;
  if (k != 0) {
    for(i=0;i<n+1;i++){
      for(j=0;j<n+1;j++){
        a[i][j]=0;
      }
    }
    for (i = 2; i < n-1; i++) {
     // for (j = 2; j < n-1; j++) {
        a[i][i - 2] = (1 - h);
        a[i][i - 1] = (3 * h - 4);
        a[i][i] = (6 - 3 * h + (h * h*h*h) * sin(i*h));
        a[i][i + 1] = (h - 4);
        a[i][i + 2] = 1;
        //a[i][j] = f(k, n, i, j);
      //}
    }
  }
a[0][0] = 1;
a[1][0] = -3;
a[1][1] = 4;
a[1][2] = -1;
a[n-1][n-2] = 1;
a[n-1][n - 1] = -4;
a[n - 1][n] = 3;
a[n][n] = 1;

  double *b = new double[n + 1];
  double *x = new double[n + 1];
  create_b(n, b, a); /////////////
  for (i = 0; i <= n; i++) {
    x[i] = b[i];
  }
  for (i = 0; i <= m; i++) {
    for (int j = 0; j <= m; j++) {
      printf("%.3e", a[i][j]);
      if (j != m) {
        cout << " ";
      }
    }
    printf(" %.3e", b[i]);
    cout << '\n';
    cout << " ";
  }

  for (i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      cop[i][j]=a[i][j];
    }
  }
    srand(time(0));
  double start = clock();
  if (gauss(a, b, n) == 5) { ///////////
    cout << "determinant=0";
    for (i = 0; i < n + 1; i++) {
      delete[] a[i];
    }
    for (i = 0; i < n + 1; i++) {
    delete[] cop[i];
  }
    delete[] cop;
    delete[] b;
    delete[] a;
    delete[] x;
    fin.close();
    return -4;
  }
  double finish = clock();
  cout << "Time: " << (finish-start) / 1000.0 << " sec\n";
  //double res = nev(b, x, cop, n);
  //double error = err(b, n);
  //cout << "Residual: " << res << "\n";
  //cout << "Error: " << error << '\n';
  cout << "Solution: "
       << " " << '\n';
  for (i = 0; i <= m; i++) {
    printf("%.3e ", b[i]);
  }
  for (i = 0; i < n + 1; i++) {
    delete[] a[i];
  }
    for (i = 0; i < n + 1; i++) {
    delete[] cop[i];
  }
  delete[] cop;
  delete[] b;
  delete[] a;
  delete[] x;
  fin.close();
  // fout.close();
  return 0;
}

