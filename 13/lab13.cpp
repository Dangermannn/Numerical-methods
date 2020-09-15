#include <iostream>
#include <fstream>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

const long double BEFORE_INTEGRAL = 2.0 / sqrt(M_PI);

long double getValueFunctionInIntegral(long double y)
{
    return exp(-(y * y));
}

long double rectangleLeftSideValue(long double x, long double h)
{
    long double iter = 0;
    long double sum = 0;
    while (iter < x)
    {
        sum += h * getValueFunctionInIntegral(iter);
        iter += h;
    }
    return sum;
}

long double rectangleRightSideValue(long double x, long double h)
{
    long double iter = 0;
    long double sum = 0;
    while (iter < x)
    {
        sum += h * getValueFunctionInIntegral(iter + h);
        iter += h;
    }
    return sum;
}

long double rectangleMiddleSideValue(long double x, long double h)
{
    long double iter = 0;
    long double sum = 0;
    while (iter < x)
    {
        sum += h * getValueFunctionInIntegral(iter + h / 2.0);
        iter += h;
    }
    return sum;
}

long double trapezoidValue(long double x, long double h)
{
    long double iter = 0;
    long double sum = 0;

    while (iter < x)
    {
        sum += (getValueFunctionInIntegral(iter) + getValueFunctionInIntegral(iter + h)) / 2.0 * h;
        iter += h;
    }
    return sum;
}

long double parabolValue(long double x, long double h)
{
    long double iter = 0;
    long double sum = 0;
    while (iter < x)
    {
        sum += (1.0 / 6.0 * getValueFunctionInIntegral(iter) + 4.0 / 6.0 * getValueFunctionInIntegral(iter + h / 2.0) + 1.0 / 6.0 * getValueFunctionInIntegral(iter + h)) * h;
        iter += h;
    }
    return sum;
}

int main()
{
    cout << "STARTING PROGRAM\n";
    long double funcVal, val, error;
    long double accurateVal = erfl(3.0);
    ofstream x1_out, x2_out, x3_out, x3_error_out;
    x1_out.open("x1_out.txt", ios::out);
    x2_out.open("x2_out.txt", ios::out);
    x3_out.open("x3_out.txt", ios::out);
    x3_error_out.open("x3_error_out.txt", ios::out);
    cout << "GOING INTO LOOP\n";
    cout << "Calculating";
    for (long double h = 0.5; h > 10e-6; h /= 2)
    {
        // columns:
        // 1 - h, 2-rec left , 3 - rec right, 4 - rec mid
        // x = 1
        funcVal = rectangleLeftSideValue(1.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x1_out << h << " " << val << " ";

        funcVal = rectangleRightSideValue(1.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x1_out << val << " ";
        funcVal = rectangleMiddleSideValue(1.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x1_out << val << " ";

        funcVal = trapezoidValue(1.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x1_out << val << " ";

        funcVal = parabolValue(1.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x1_out << val << endl;

        // x = 2
        funcVal = rectangleLeftSideValue(2.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x2_out << h << " " << val << " ";

        funcVal = rectangleRightSideValue(2.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x2_out << val << " ";

        funcVal = rectangleMiddleSideValue(2.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x2_out << val << " ";

        funcVal = trapezoidValue(2.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x2_out << val << " ";

        funcVal = parabolValue(2.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x2_out << val << endl;

        // x = 3
        funcVal = rectangleLeftSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x3_out << h << " " << val << " ";

        funcVal = rectangleRightSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x3_out << val << " ";

        funcVal = rectangleMiddleSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x3_out << val << " ";

        funcVal = trapezoidValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x3_out << val << " ";

        funcVal = parabolValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        x3_out << val << endl;

        // x = 3 error
        funcVal = rectangleLeftSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        error = log10(fabs(accurateVal - val));
        x3_error_out << log10(fabs(h)) << " " << error << " ";

        funcVal = rectangleRightSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        error = log10(fabs(accurateVal - val));
        x3_error_out << error << " ";

        funcVal = rectangleMiddleSideValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        error = log10(fabs(accurateVal - val));
        x3_error_out << error << " ";

        funcVal = trapezoidValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        error = log10(fabs(accurateVal - val));
        x3_error_out << error << " ";

        funcVal = parabolValue(3.0, h);
        val = BEFORE_INTEGRAL * funcVal;
        error = log10(fabs(accurateVal - val));
        x3_error_out << error << endl;
        cout << ".";
    }
    return 0;
}