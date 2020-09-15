#include <iostream>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const double X_LEFT = -1.0;
const double X_RIGHT = 1.0;
const int MAX_ITERATION = 100;
const int KNOTS = 15; // predefined points
const double KNOTS_STEP = (X_RIGHT - X_LEFT) / (KNOTS - 1);
const double STEP = (X_RIGHT - X_LEFT) / MAX_ITERATION;


double func(double x)
{
    return 1.0 / (1.0 + 10.0 * x * x * x * x * x * x);
}

void onesToVector(double* vec, int n)
{
    for (int i = 0; i < n; i++)
        vec[i] = 1;
}


double newtonBase(double x, double* xi, double* yi)
{
    double* xValues = new double[KNOTS + 1];
    double* cValues = new double[KNOTS];
    onesToVector(xValues, KNOTS + 1);
    double ret = 0.0;
    for (int i = 0; i < KNOTS; i++)
    {
        cValues[i] = yi[0];
        for (int j = 0; j < KNOTS - i - 1; j++)
        {
            yi[j] = (yi[j + 1] - yi[j]) / (xi[i + j + 1] - xi[j]);
        }
    }
    for (int i = 1; i < KNOTS + 1; i++)
        xValues[i] = xValues[i - 1] * (x - xi[i - 1]);
    for (int i = 0; i < KNOTS; i++)
        ret += cValues[i] * xValues[i];

    return ret;
}


double chebyshevKnots(double x)
{
    double* tempX = new double[KNOTS];
    double* tempY = new double[KNOTS];

    // xi = (b + a)/2 + (b - a)/2 * ksi
    for (int i = 0; i < KNOTS; i++)
    {
        tempX[i] = (X_RIGHT + X_LEFT) / 2.0 + (X_RIGHT - X_LEFT) / 2.0 * cos((2.0 * i + 1.0) / (2.0 * KNOTS + 2.0) * M_PI);
        tempY[i] = func(tempX[i]);
    }

    return newtonBase(x, tempX, tempY);
}

double parallelKnots(double x)
{
    double* tempX = new double[KNOTS];
    double* tempY = new double[KNOTS];
    int iter = 0;
    for (double i = X_LEFT; i <= X_RIGHT; i += KNOTS_STEP, iter++)
    {
        tempX[iter] = i;
        tempY[iter] = func(i);
    }
    return newtonBase(x, tempX, tempY);
}

int main()
{
    double x = X_LEFT;
    int iter = 0;
    double* funcValues = new double[MAX_ITERATION];
    double* chebyshevValues = new double[MAX_ITERATION];
    double* parallelValues = new double[MAX_ITERATION];
    ofstream output;
    output.open("results.txt", ios::out);

    while (true)
    {
        if (iter > MAX_ITERATION)
            break;
        funcValues[iter] = func(x);
        chebyshevValues[iter] = chebyshevKnots(x);
        parallelValues[iter] = parallelKnots(x);
        cout << "PARA: " << x << endl;

        output << x;
        output << " ";
        output << funcValues[iter];
        output << " ";
        output << chebyshevValues[iter];
        output << " ";
        output << parallelValues[iter];
        output << endl;
        cout << "ITER: " << iter << endl;
        iter++;
        x += STEP;
    }
    output.close();


    return 0;
}
