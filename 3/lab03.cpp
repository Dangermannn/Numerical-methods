
#include <iostream>
#include <cmath>

using namespace std;

const double PRECISION_0 = 1e-8;  // dokladność porównania z zerem (zadana tolerancja reziduum)
const double PRECISION_X = 1e-8;  // dokładność wyznaczenia pierwiastka (zadana toleracja bledu)
const int MAX_ITERATION = 100;

// sin(x/4) ^ 2 - x
double func1(double x)
{
    return sin(x / 4.0) * sin(x / 4.0) - x;
}

// 1/4 * sin(x/2) - 1
double func1_derivative(double x)
{
    return (1.0 / 4.0) * sin(x / 2.0) - 1;
}

// tan(2x) - x - 1
double func2(double x)
{
    return tan(2.0 * x) - x - 1.0;
}

// 2 / ([cos(2x)] ^ 2 ) - 1
double func2_derivative(double x)
{
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x)) - 1.0;
}

// przeksztalcenia f(x) = 0 do fi(x) = x

// [sin(x/4)]^2 - x = 0     =>      x = [sin(x/4)]^2
double func1_picard(double x)
{
    return sin(x / 4.0) * sin(x / 4.0);
}

// tan(2x) - x - 1      =>      tan(2x) - 1
double func2_picard(double x)
{
    return tan(2.0 * x) - 1.0;
}
// 1/2 * sin(x/4) * cos(x/4)
double func1_picard_derivative(double x)
{
    return (1.0 / 2.0) * sin(x / 4.0) * cos(x / 4.0);
}

// 2/[cos(2x)*cos(2x)]
double func2_picard_derivative(double x)
{
    return 2.0 / (cos(2.0 * x) * cos(2.0 * x));
}

/*
 * Metoda Picarda polega na sprowadzeniu funkcji f(x) = 0 do postawci x = fi(x), oraz wykorzystanie tej funkcji do iteracji.
 */

double Picard(double (*f)(double x), double (*f_picard)(double x), double (*f_picard_derivative)(double x), double x, int max_iteration)
{
    // sprawdzenie zbieznosci
    if (fabs(f_picard_derivative(x)) >= 1)
    {
        cout << "DIVERGENT\n\n" << endl;
        return -1;
    }

    double estimator = 0;
    double x1= 0;

    for (int i = 0; i < max_iteration; i++)
    { 
        // wyznaczenie wartośći funkcji postaci x = fi(x)
        x1 = f_picard(x);
        // wyznaczenie estymatora bledu
        estimator = fabs(x1 - x);
        x = x1;

        cout << "ITERATION: " << i + 1 << "\tx = " << x << "\tEstimator = " << estimator << "\tResiduum = " << fabs(f(x)) << endl;

        // warunek zakonczenia iteraci (uzyskanie odpowiedniej dokladnosci)
        if (fabs(f(x)) <= PRECISION_0 || estimator <= PRECISION_X)
            break;
    }
    cout << "x0 = " << x << "\tF(x0) = " << f(x) << endl;
    return x;
}


/**
 * Metoda bisekcji polega na dzieleniu przedziału [a, b] na dwie połowy.
 * Następnie wybieramy ten podprzedział, dla którego f(x) jest różnego znaku na krańcach przedziału
 * Estymator błedu pierwiastka wynosi e = (bn - an) / 2
 * Algorytm zostaje przerwany, gdy przejdzie przez wszystkie iteraje, bład jest dostatecznie mały lub
 * wartości na krańcach przedziału nie są przeciwnego znaku.
 * Środek przedziału zostaje wyznaczony przez a + (b - a)/2, nie przez (a + b)/2.
 * Forsythe, Malcolm i Moler udowodnili, że punkt środkowy liczony jako (a + b)/2 na komputerze ze skończoną precyzją
 * może wyjść poza przedział [a, b]
 */
double Bisection(double (*f)(double x), double a, double b, int max_iteration)
{
    double mid = 0; // srodek przedzialu
    double estimator; // estymator bledu
    for (int i = 0; i < max_iteration; i++)
    {      
        //przerwanie programu, jesli wartosc funkcji na krancach przedzialu sa tego samego znaku
        if ((f(a) < 0 && f(b) < 0) || (f(a) > 0 && f(b) > 0))
        {
            cout << "WRONG INTERVAL\n\n";
            return -1;
        }
   
        // wyznaczenie srodka przezdzialu
        mid = a + (b - a) / 2;
        //mid = (a + b) / 2;
        // wyznaczenie estymatora bledu
        estimator = fabs((b - a) / 2.0);
        cout << "ITERATION: " << i + 1 << "\ta = " << a << "\tb = " << b << "\tmid = " << mid << "\tEstimator = " << estimator << "\tResiduum = " << fabs(f(mid)) << endl;

        //zwężenie przedziału
        if((f(a) < 0 && f(mid) > 0) || (f(mid) < 0 && f(a) > 0))
            b = mid;
        else
            a = mid;
        // Warunek zakonczenia iteracji (uzyskanie odpowiedniej dokladnosci)
        if ((fabs(f(mid)) <= PRECISION_0) || (estimator <= PRECISION_X))
            break;
    }
    
    cout << "x0 = " << mid << "\tF(x0) = " << f(mid) << endl;
    return mid;
}

/**
 * Metoda Newtoda polega na rekurencyjnym stosowaniu wzoru: Xn+1 = Xn - f(Xn)/f'(Xn)
 */

double Newton(double (*f)(double x), double (*f_derivative)(double x), double x, int max_iteration)
{
    double x1 = 0;
    double estimator = 0;

    for (int i = 0; i < max_iteration; i++)
    {
        x1 = x - (f(x) / f_derivative(x));
        // wyznaczenie Estimatora błędu
        estimator = fabs(x - x1);
        x = x1;
        cout << "ITERATION: " << i + 1<< "\tx1 = " << x1 << "\tEstimator = " << estimator << "\tResiduum = " << fabs(f(x)) << endl;

        // Warunek zakończenia iteracji
        if (fabs(f(x)) <= PRECISION_0 || estimator <= PRECISION_X)
            break;
    }
    cout << "x0 = " << x << "\tF(x0) = " << f(x) << endl;
    return x;
}

/**
 * Jest to metoda podobna do metody Newtona. Różni się tmy, że zamiast prostych stycznych stosujemy proste sieczne.
 * Jedną z wad metody Newtona jest to, że wymaga ona obliczenia wartości pochodnej funkcji f. W tej metodzie ten problem znika,
 * i x wyznaczany jest z poniższego wzoru:
 * Xn+2 = Xn+1 - (f(Xn+1)/[(f(Xn+1) - f(Xn)/(Xn+1 - Xn)]
 * Do tej metody potrzebne są dwa punkty początkowe
 */
double SecantMethod(double (*f)(double x), double x0, double x1, int max_iteration)
{
    double x2 = 0;
    double estimator = 0;

    for (int i = 0; i < max_iteration; i++)
    {
        x2 = x1 - f(x1) / ((f(x1) - f(x0)) / (x1 - x0));

        // wyznaczenie estymatora błędu

        estimator = fabs(x2 - x1);

        cout << "ITERATION: " << i + 1 << "\tx2 = " << x2 << "\tEstimator = " << estimator << "\tResiduum = " << fabs(f(x2)) << endl;
        
        x0 = x1;
        x1 = x2;

        // Warunek zakończenia iteracji (uzyskanie odpowiedniej dokladnosci)
        if (fabs(x2) <= PRECISION_0 || estimator <= PRECISION_X)
            break;
    }
    cout << "x0 = " << x2 << "\tF(x0) = " << f(x2) << endl;
    return x2;
}

int main()
{
    cout.setf(ios::scientific);
    cout.precision(16);
    cout << "FUNCTION NR 1" << endl;
    cout << "---------------------------------------------------------" << endl;
    std::cout << "PICARD" << endl;
    cout << "---------------------------------------------------------" << endl;
    Picard(func1, func1_picard, func1_picard_derivative, 0.2, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    cout << "BISECTION" << endl;
    cout << "---------------------------------------------------------" << endl;
    Bisection(func1, -0.5, 1.0, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    cout << "NEWTON" << endl;
    cout << "---------------------------------------------------------" << endl;
    Newton(func1, func1_derivative, -0.1, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    std::cout << "SECANT" << endl;
    cout << "---------------------------------------------------------" << endl;
    SecantMethod(func1, -0.5, 1.0, MAX_ITERATION);

    cout << "\n\n\n\n";
    cout << "FUNCTION NR 2" << endl;
    cout << "---------------------------------------------------------" << endl;
    std::cout << "PICARD" << endl;
    cout << "---------------------------------------------------------" << endl;
    Picard(func2, func2_picard, func2_picard_derivative, 2.2, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    cout << "BISECTION" << endl;
    cout << "---------------------------------------------------------" << endl;
    Bisection(func2, 2.0, 2.3, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    cout << "NEWTON" << endl;
    cout << "---------------------------------------------------------" << endl;
    Newton(func2, func2_derivative, 2.2, MAX_ITERATION);
    cout << "---------------------------------------------------------" << endl;
    std::cout << "SECANT" << endl;
    cout << "---------------------------------------------------------" << endl;
    SecantMethod(func2, 2.0, 2.3, MAX_ITERATION);
}