#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const double MAX_ITERATION = 1000;

double analitycalFunction(double t)
{
    return 1.0 - exp(-10.0 * (t + atan(t)));
}

double getValueForForwardEulerMethod(double h, double t_max)
{
    double y = 0.0;
    for (double i = 0.0; i < t_max; i += h)
    {
        y = y + h * (-((10.0 * i * i + 20.0) / (i * i + 1.0)) * (y - 1.0));
    }
    return y;
}

double getValueForBackwardEulerMethod(double h, double t_max) 
{
    double y = 0.0;
    double temp, K_1;
    for (double i = 0.0; i < t_max; i += h) {
        K_1 = i + h;
        temp = (10.0 * K_1 * K_1 + 20.0) / (K_1 * K_1 + 1.0);
        y = (y + h * temp) / (1.0 + h * temp);
    }
    return y;
}

double getValueForTrapezoidMethod(double h, double t_max) 
{
    double y = 0.0;
    double temp, temp2, K_1;
    for (double i = 0.0; i < t_max; i += h)
    {
        K_1 = i + h;
        temp= (10.0 * i * i + 20.0) / (i * i + 1.0);
        temp2 = (10.0 * K_1 * K_1 + 20.0) / (K_1 * K_1 + 1.0);
        y = ((-h / 2.0) * (temp * (y - 1.0) - temp2) + y) / (1.0 + (h / 2.0) * temp2);
    }
    return y;
}

double getErrorForForwardEulerMethod(double h, int n)
{
    double error = 0.0, y = 0.0, t = h;
    double analyticalValue;

    for (int i = 0; i < n; i++)
    {
        analyticalValue = analitycalFunction(t);
        y = y + h * (-((10.0 * t * t + 20.0) / (t * t + 1.0)) * (y - 1.0));
        analyticalValue = fabs(analyticalValue - y);
        if (analyticalValue > error)
            error = analyticalValue;
        t += h;
    }
    return error;

}

double getErrorForBackwardEulerMethod(double h, int n)
{
    double error = 0.0, y = 0.0, t = h;
    double analyticalValue, temp, K_1;

    for (int i = 0; i < n; i++)
    {
        K_1 = t + h;
        analyticalValue = analitycalFunction(t);
        temp = (10.0 * K_1 * K_1 + 20.0) / (K_1 * K_1 + 1.0);
        y = (y + h * temp) / (1.0 + h * temp);
        analyticalValue = fabs(analyticalValue - y);
        if (analyticalValue > error)
            error = analyticalValue;
        t += h;
    }
    return error;
}

double getErrorForTrapezoidMethod(double h, int N)
{
    double error = 0.0, y = 0.0, t = h;
    double analyticalValue, temp, temp2, K_1;

    for (int i = 0; i < N; i++)
    {
        K_1 = t + h;
        analyticalValue = analitycalFunction(t);
        temp = ((10.0 * t * t + 20.0) / (t * t + 1.0));
        temp2 = (10.0 * K_1 * K_1 + 20.0) / (K_1 * K_1 + 1.0); ;
        y = ((-h / 2.0) * (temp * (y - 1.0) - temp2) + y) / (1.0 + (h / 2.0) * temp2);
        analyticalValue = fabs(analyticalValue - y);
        if (analyticalValue > error)
            error = analyticalValue;
        t += h;
    }
    return error;

}

int main()
{
    double forwardEuler, backwardEuler, trapezoid;
    double analitycalResult;
    ofstream errors, stable_output, unstable_output;
    double step;

    errors.open("errors.txt", ios::out);
    step = 0.1;
    for (double i = step; i > 1e-20; i /= 2)
    {
        forwardEuler = getErrorForForwardEulerMethod(i, MAX_ITERATION);
        backwardEuler = getErrorForBackwardEulerMethod(i, MAX_ITERATION);
        trapezoid = getErrorForTrapezoidMethod(i, MAX_ITERATION);

        errors << log10(i);
        errors << " ";
        errors << log10(forwardEuler);
        errors << " ";
        errors << log10(backwardEuler);
        errors << " ";
        errors << log10(trapezoid);
        errors << endl;
    }

    stable_output.open("stable_data.txt", ios::out);
    step = 0.01;
    for (double i = 0; i < 6.0; i += step)
    {
        forwardEuler = getValueForForwardEulerMethod(step, i);
        backwardEuler = getValueForBackwardEulerMethod(step, i);
        trapezoid = getValueForTrapezoidMethod(step, i);

        stable_output << i;
        stable_output << " ";
        stable_output << analitycalFunction(i);
        stable_output << " ";
        stable_output << forwardEuler;
        stable_output << " ";
        stable_output << backwardEuler;
        stable_output << " ";
        stable_output << trapezoid;
        stable_output << endl;
    }


    unstable_output.open("unstable_data.txt", ios::out);
    for (double i = 0; i < 5.0; i += 0.15)
    {
        forwardEuler = getValueForForwardEulerMethod(0.15, i);
        unstable_output << i;
        unstable_output << " ";
        unstable_output << analitycalFunction(i);
        unstable_output << " ";
        unstable_output << forwardEuler;
        unstable_output << endl;
    }
    errors.close(); 
    stable_output.close();
    unstable_output.close();
    
    system("PAUSE");
    return 0;
}