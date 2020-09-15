#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <math.h>
using namespace std;


double function(double x)
{
    return (1.0 - exp(-x)) / x;
}

double sequenceExp(double x)
{
    /*
        e^x = the sum of x^n/n! as n goes from 0 to infinity
    */

    double result = 1.0;
    double value = 1.0;

    for (int i = 1; i < 50; i++)
    {
        value *= -(x / ((double)i + 1.0));
        result += value;
    }
    return result;
}

int main()
{
    double x, result, difference, log10, preciseValue, error;
    ifstream input;
    input.open("w2.txt");

    ofstream output;
    output.open("data2.txt", ios::out);

    cout.setf(ios::scientific);
    cout.precision(30);
    input.precision(30);
    output.precision(30);
    cout << left;
    input.left;
    cout << setw(50) << " x " << setw(50) << " Wartosc dokladna " << setw(50) << " Wynik " << setw(50) << "Roznica" << setw(50) << " Blad wzgledny " << endl;

    while (!input.eof())
    {
       
        input >> log10;
        input >> x;
        input >> preciseValue; // pobieranie wartosci dokladnej

        //output << setw(50) << log10;
        //wypisywanie i liczenie

        //output << setw(50) << preciseValue;

        result = function(x);

        //output << setw(50) << result;

        //roznica miedzy wartoscia dokladna a uzyskana
        difference = fabs(preciseValue - result);

        //output << setw(50) << difference;
        //blad wzgledny
        error = fabs(difference / preciseValue);

        if (fabs(difference) > DBL_EPSILON)
        {
            result = sequenceExp(x);
            difference = fabs(preciseValue - result);
            error = fabs(difference / preciseValue);
        }


        //output << error << " " << x << endl;
       output << x << " " << error << endl;
        //cout << setw(50) << log10 << setw(50) << x << setw(50) << preciseValue << endl;
        //cout << log10 << x << result;
        cout << setw(50) << x;
        cout << setw(50) << preciseValue;
        cout << setw(50) << result;
        cout << setw(50) << difference;
        cout << setw(50) << error;
        cout << endl;
    }

    input.close();
    output.close();
    //system("gnuplot -persist -e \"set xlabel 'log10(x)'; set ylabel 'log10(|blad wzgledny|)'; set logscale xy; set trange [1.0e-30:1.0e+10]; plot 2.22045e-16, 'data2.txt'\"");
    system("PAUSE");
    return 0;

}