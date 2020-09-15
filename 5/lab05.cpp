
#include <iostream>
#include <iomanip>
#include <cmath>>
using namespace std;


double matrix[4][4] =
{
    {1.0, -20.0, 30.0, -4.0},
    {2.0, -40.0, -6.0, 50.0},
    {9.0, -180.0, 11.0, -12.0},
    {-16.0, 15.0, -140.0, 13.0}
};

double vector[4] = { 35.0, 104.0, -366.0 , -354.0 };

void printMatrix(double matrix[4][4])
{
    cout << "--------------------------------------------------------------" << endl;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout <<setw(15) << matrix[i][j] << "";
        cout << endl;
    }
    cout << "--------------------------------------------------------------" << endl;

}

void printVector(double vector[4])
{
    cout << "--------------------------------------------------------------" << endl;

    for (int i = 0; i < 4; i++)
        cout<< setw(15) << vector[i] << "";
    cout << endl;
    cout << "--------------------------------------------------------------" << endl;

}

//szukanie elementu maksymalnego, jesli takiego nie ma to funkcja zwraca false w celu przerwania petli
bool partialPickBasicElement(double matrix[4][4], double matrix2[4][4], double vector[4], int index)
{
    double maxValue = 0;
    int indexOfMaxValue = index;
    double tempValue;
    for (int i = index; i < 4; i++)
    {
        if (fabs(matrix[i][index]) > maxValue)
        {
            maxValue = fabs(matrix[i][index]);
            indexOfMaxValue = i;
        }
    }
    if (maxValue == 0)
        return false;
    // jezeli jest maxValue -> zamiana wierszy
    for (int i = 0; i < 4; i++)
    {
        tempValue = matrix[index][i];
        matrix[index][i] = matrix[indexOfMaxValue][i];
        matrix[indexOfMaxValue][i] = tempValue;

        tempValue = matrix2[index][i];
        matrix2[index][i] = matrix2[indexOfMaxValue][i];
        matrix2[indexOfMaxValue][i] = tempValue;
    }
    double temp = vector[indexOfMaxValue];
    vector[indexOfMaxValue] = vector[index];
    vector[index] = temp;
    return true;
}

// W Funkcji matrix traktujemy jako macierz U
void LUdecomposition(double matrix[4][4], double vector[4])
{
    double L[4][4] = { 0 };
    double ySollutions[4] = { 0 };
    double xSollutions[4] = { 0 };
    double coefficient;
    // Iteracja po trzech wierszach macierzy
    int step = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            // rozwiazanie problemu zwiazanego z dzieleniem przez liczbe rowna zero, badz bliskie zeru
            if (matrix[i][i] == 0)
            {
                if (partialPickBasicElement(matrix, L, vector, i) == false)
                    break;
            }

            coefficient = matrix[j][i] / matrix[i][i];
            L[j][i] = coefficient; //zapisanie wspolczynnika do macierzy L

            for (int k = i; k < 4; k++)
            {
                //wykonanie operacji miedzy wierszami
                matrix[j][k] = matrix[j][k] - matrix[i][k] * coefficient;
            }
        }
    }
    for (int i = 0; i < 4; i++)
        L[i][i] = 1;
    cout <<"\t\t\tMacierze po dekompozycji LU\n";
    cout << "MACIERZ U" << endl;
    printMatrix(matrix);
    cout << "MACIERZ L" << endl;
    printMatrix(L);

    double lastValues;
    //wyznaczenie wartosci y1, y2 ...
    // LY = B
    for (int i = 0; i < 4; i++)
    {
        lastValues = 0;
        for (int j = 0; j < i; j++)
        {
            lastValues += L[i][j] * ySollutions[j];
        }
        ySollutions[i] = (vector[i] - lastValues);
    }

    //wyznaczenie wartosci x1, x2 ...
    // UX = Y
    for (int i = 3; i >= 0; i--)
    {
        double temp = 0.0;
        for (int j = i + 1; j < 4; j++)
        {
            temp += matrix[i][j] * xSollutions[j];
        }

        xSollutions[i] = (1 / matrix[i][i]) * (ySollutions[i] - temp);
    }
    //printMatrix(matrix);
    
    cout << "Rozwiazania X :" << endl;;
    printVector(xSollutions);
    cout << "Wektor Y :" << endl;
    printVector(ySollutions);
}
int main()
{
    LUdecomposition(matrix, vector);
    return 0;
}

