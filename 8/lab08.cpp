#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_ITERATIONS = 20;

template<typename T>
T getValueOfDerivative(T x)
{
    return cos(x);
}

// O(h)
template<typename T>
T getTwoPointBackwardDifference(T x, T h)
{
    return (sin(x) - sin(x - h)) / h;
}
// O(h^2)
template<typename T>
T getTwoPointCentralDifference(T x, T h)
{
    return (sin(x + h) - sin(x - h)) / (T(2.0) * h);
}
// O(h)
template<typename T>
T getTwoPointForwardDifference(T x, T h)
{
    return (sin(x + h) - sin(x)) / h;
}
// O(h^2)
template<typename T>
T getThreePointBackwardDifference(T x, T h)
{
    return (T(1.0) / T(2.0) * sin(x - T(2.0) * h) - T(2.0) * sin(x - h) + T(3.0) / T(2.0) * sin(x)) / h;
}
// O(h^2)
template<typename T>
T getThreePointForwardDifference(T x, T h)
{
    return (T(-3.0) / T(2.0) * sin(x) + T(2.0) * sin(x + h) - T(1.0) / T(2.0) * sin(x + T(2.0) * h)) / h;
}


template<typename T>
void calculate(string FileName)
{
    ofstream output;
    output.open(FileName, ios::out);
    ofstream output2;
    output2.open("rzad" + FileName, ios::out);
    T firstIter[8];
    T secondIter[8];
    T currentValues[8];
    T rowValues[8];
    //cout.setf(ios::scientific);
    cout.precision(16);
    cout.left;
    output.precision(16);

    T left = 0;
    T mid = M_PI_4;
    T right = M_PI_2;
    T step = 0.1;
    int iteration = 0;
    cout << setw(7) << "STEP" << setw(28) << "0 PROGRESYWNA DWUPUNKTOWA" << setw(28) << "0 PROGRESYWNA TRZYPUNKTOWA" << setw(28) << "PI/4 PROGRESYWNA DWUPUNKTOWA";
    cout << setw(28) << "PI/4 CENTRALNA DWUPUNKTOWA" << setw(28) << "PI/4 WSTECZNA DWUPUNKTOWA" << setw(28) << "PI/2 WSTECZNA DWUPUNKTOWA" << setw(28) << "PI/2 WSTECZNA TRZYPUNKTOWA" << endl;
    while (true)
    {

        iteration++;
        if (iteration > MAX_ITERATIONS)
            break;
        currentValues[0] = log10(step);
        output << currentValues[0];
        output << " ";

        cout << setw(7) << log10(step);
        // progresywna dla left
        currentValues[1] = log10(fabs(getValueOfDerivative(left) - getTwoPointForwardDifference(left, step)));
        output << currentValues[1];
        output << " ";
        cout << setw(28) << currentValues[1];
        //progresywna 3punktowa dla left
        currentValues[2] = log10(fabs(getValueOfDerivative(left) - getThreePointForwardDifference(left, step)));
        output << currentValues[2];
        output << " ";
        cout << setw(28) << currentValues[2];

        // progresywna 2 punktowa dla mid
        currentValues[3] = log10(fabs(getValueOfDerivative(mid) - getTwoPointForwardDifference(mid, step)));
        output << currentValues[3];
        output << " ";
        cout << setw(28) << currentValues[3];
        // centralna mid
        currentValues[4] = log10(fabs(getValueOfDerivative(mid) - getTwoPointCentralDifference(mid, step)));
        output << currentValues[4];
        output << " ";
        cout << setw(28) << currentValues[4];
        // wsteczna mid
        currentValues[5] = log10(fabs(getValueOfDerivative(mid) - getTwoPointBackwardDifference(mid, step)));
        output << currentValues[5];
        output << " ";
        cout << setw(28) << currentValues[5];
        // wsteczna 2 punktowa right
        currentValues[6] = log10(fabs(getValueOfDerivative(right) - getTwoPointBackwardDifference(right, step)));
        output << currentValues[6];
        output << " ";
        cout << setw(28) << currentValues[6];
        // wsteczna 3punktowa right
        currentValues[7] = log10(fabs(getValueOfDerivative(right) - getThreePointBackwardDifference(right, step)));
        output << currentValues[7];
        output << endl;
        cout << setw(28) << currentValues[7] << endl;

        step *= 0.1;

        if (iteration == 1)
        {
            for (int i = 0; i < 8; i++)
            {
                firstIter[i] = currentValues[i];
            }
        }
        if (iteration == 2)
        {
            for (int i = 0; i < 8; i++)
            {
                secondIter[i] = currentValues[i];
            }
        }
    }

    for (int i = 1; i < 8; i++)
    {
        rowValues[i - 1] = (secondIter[i] - firstIter[i]) / (secondIter[0] - firstIter[0]);
    }

    cout << "ROW VALUES" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << setw(28) << setw(28) << rowValues[i];
        output2 << rowValues[i];
        output2 << " ";
    }
    cout << endl;
    
}



int main()
{
    cout << "======================================== DOUBLE ========================================" << endl;
    calculate<double>("resultDouble.txt");
    cout << "======================================== FLOAT ========================================" << endl << endl;
    calculate<float>("resultFloat.txt");
    system("PAUSE");
}

