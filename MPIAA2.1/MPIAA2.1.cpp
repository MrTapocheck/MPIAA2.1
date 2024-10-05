#include <omp.h>
#include <iostream>
#include <chrono>
#include <Windows.h>

using namespace std;
int main()
{
   SetConsoleOutputCP(1251);

   int n = 100000000;
   double s = 0;

   double* x = NULL; // объ€вление
   if (x == NULL)
      x = new double[n]; // выделение пам€ти

   for (int i = 0; i < n; i++)
      x[i] = rand() % 10;

   double* y = NULL;
   if (y == NULL)
      y = new double[n];

   for (int i = 0; i < n; i++)
      y[i] = rand() % 10;

   double start_time = clock();
   for (int i = 0; i < n; i++)
      s += x[i] * y[i];
   s = sqrt(s);
   double end_time = clock();
   double search_time1 = end_time - start_time;
   cout << "врем€ работы последовательной программы: " << search_time1 << "\n";
   cout << "результат работы последовательной программы: " << s << "\n";
   
   s = 0;
   start_time = clock();
#pragma omp parallel for num_threads(2) reduction(+:s)
   for (int i = 0; i < n; i++)
      s += x[i] * y[i];
   s = sqrt(s);
   end_time = clock();
   double search_time2 = end_time - start_time;
   cout << "\nврем€ работы последовательной(2 потока) программы: " << search_time2 << "\n";
   cout << "результат работы параллельной(2 потока) программы: " << s << "\n";
   
   s = 0;
   start_time = clock();
#pragma omp parallel for num_threads(16) reduction(+:s)
   for (int i = 0; i < n; i++)
      s += x[i] * y[i];
   s = sqrt(s);
   end_time = clock();
   double search_time16 = end_time - start_time;
   cout << "\nврем€ работы последовательной(16 потоков) программы: " << search_time16 << "\n";
   cout << "результат работы параллельной(16 потоков) программы: " << s << "\n";

   cout << "ускорени€ при использовании 2 потоков: " << search_time1 / search_time2 << endl;
   cout << "ускорени€ при использовании 16 потоков: " << search_time1 / search_time16 << endl;
}
