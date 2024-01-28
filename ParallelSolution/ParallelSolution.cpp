#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

int main()
{
    int n;

    // Generación o petición del tamaño de los arreglos
    cout << "Ingrese el tamaño de los arreglos: ";
    cin >> n;

    vector<float> a(n), b(n), c(n);

    // Semilla para el generador de números aleatorios
    srand(time(0));

    // Generación de valores aleatorios en el rango [1, n] para los arreglos
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        a[i] = 1 + static_cast<float>(rand()) / RAND_MAX * (n - 1);
        b[i] = 1 + static_cast<float>(rand()) / RAND_MAX * (n - 1);
    }

    // Medición del tiempo de la suma de los arreglos
    auto start_time = chrono::high_resolution_clock::now();

    // Suma de los arreglos en paralelo
#pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

    // Impresión del tiempo de ejecución
    cout << "Tiempo de ejecución de la suma: " << duration.count() << " microsegundos" << endl;

    // Impresión de los primeros 10 valores de cada arreglo
    cout << "Los primeros 10 valores del arreglo a son: ";
    for (int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    cout << "Los primeros 10 valores del arreglo b son: ";
    for (int i = 0; i < 10; i++)
    {
        cout << b[i] << " ";
    }
    cout << endl;

    cout << "Los primeros 10 valores del arreglo c son: ";
    for (int i = 0; i < 10; i++)
    {
        cout << c[i] << " ";
    }
    cout << endl;

    return 0;
}
