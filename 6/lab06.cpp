#include <iostream>
#include <iomanip>
using namespace std;

double vector_b[6] = { 31.0, 165.0 / 4.0, 917.0 / 30.0, 851.0 / 28.0, 3637.0 / 90.0, 332.0 / 11.0 };
double vector_l[6] = { 0.0, 1.0 / 3.0, 1.0 / 5.0, 1.0 / 7.0, 1.0 / 9.0, 1.0 / 11.0 };
double vector_d[6] = { 10.0, 20.0, 30.0, 30.0, 20.0, 10.0 };
double vector_u[6] = { 1.0 / 2.0, 1.0 / 4.0, 1.0 / 6.0, 1.0 / 8.0, 1.0 / 10.0, 0.0 };


void printVector(double vector[], int n)
{
    cout << "----------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++)
        cout << setw(15) << vector[i] << "";
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------" << endl;
}

// eta2 = d2 - l2 * eta1^(-1) * u1
void calculateEta(double last_values[], double l[], double d[], double u[], int n)
{
    for (int i = 1; i < n; i++)
    {
        last_values[i] = l[i] * (1.0 / d[i - 1]);
        d[i] = d[i] - last_values[i] * u[i - 1];
    }
}

// r2 = b2 - l2 * eta1^(-1) * r1

void calculateR(double last_values[], double l[], double d[], double u[], double b[], int n)
{
    for (int i = 1; i < n; i++)
    {
        b[i] = b[i] - last_values[i] * b[i - 1];
    }
}

// wyznaczenie odpowiedzi

void calculateX(double results[], double b[], double l[], double d[], double u[], int n)
{
    results[n - 1] = (1.0 / d[n - 1]) * b[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        results[i] =  (b[i] - u[i] * results[i + 1]) / d[i];
    }
}

int main()
{
    double vector_lastD[6] = { 0 };
    double vector_x[6] = { 0 };
    cout << "\t\tWPROWADZONE DANE\n";
    cout << "WEKTOR B\n";
    printVector(vector_b, 6);   
    cout << "WEKTOR L\n";
    printVector(vector_l, 6);    
    cout << "WEKTOR D\n";
    printVector(vector_d, 6);    
    cout << "WEKTOR U\n";
    printVector(vector_u, 6);


    calculateEta(vector_lastD, vector_l, vector_d, vector_u, 6);
    calculateR(vector_lastD, vector_l, vector_d, vector_u, vector_b, 6);
    calculateX(vector_x, vector_b, vector_l, vector_d, vector_u, 6);

    cout << "\n\n";
    cout << "\t\tPO WYKONANIU ALGORYTMU THOMASA\n";
    cout << "WEKTOR B\n";
    printVector(vector_b, 6);
    cout << "WEKTOR L\n";
    printVector(vector_l, 6);
    cout << "WEKTOR D\n";
    printVector(vector_d, 6);
    cout << "WEKTOR U\n";
    printVector(vector_u, 6);
    cout << "ROZWIAZANIE\n";
    printVector(vector_x, 6);
    return 0;
}

