#include <iostream>
#include <cmath>

using namespace std;

const double PRECISION = 1e-8;
const int MAX_ITERATIONS = 100;

// pierwsze rownanie
double f1(double x, double y, double z)
{
	return x * x + y * y + z * z - 2.0;
}
//drugie rownananie
double f2(double x, double y)
{
	return x * x + y * y - 1.0;
}
//trzecie rownanie
double f3(double x, double y)
{
	return x * x - y;
}
double maxValue_2Num(double a, double b)
{
	return (a > b) ? a : b;
}
// zwraca maksymalna wartosc z 3 liczb
double maxValue_3Num(double a, double b, double c)
{
	return maxValue_2Num(maxValue_2Num(a, b), c);
}

// wyzerowanie wektora
void fillArrayWithZeros(double arr[], int n)
{
	for (int i = 0; i < n; i++)
		arr[i] = 0;
}

void Newton(double x, double y, double z)
{
	// transponowana macierz jakobianu przeksztalcenia 
	double transposedJacobianMatrix[3][3];

	// aktualne wartosci poszczególnych równań
	double currentValueArray[3] = { 0 };

	//roznica miedzy przyblizeniami
	double differenceArray[3] = { 0 };

	currentValueArray[0] = f1(x, y, z);
	currentValueArray[1] = f2(x, y);
	currentValueArray[2] = f3(x, y);
	//wyznacznik
	double detInversed;

	for (int i = 0; i < MAX_ITERATIONS; i++) 
	{
		// aby przy obliczaniu wyznacznika nie dzielilo przez 0
		if (x == 0 || z == 0) {
			cout << "Dzielenie przez zero" << endl;
			break;
		}

		// 1 / wyznacznik jakobianu
		detInversed = 1 / (-4 * x * z - 8 * x * y * z);
		fillArrayWithZeros(differenceArray, 3);

		// transponowana macierz dopelnien
		transposedJacobianMatrix[0][0] = 0;
		transposedJacobianMatrix[0][1] = (-2 * z) * detInversed;
		transposedJacobianMatrix[0][2] = (-4 * y * z) * detInversed;
		transposedJacobianMatrix[1][0] = 0;
		transposedJacobianMatrix[1][1] = (-4 * x * z) * detInversed;
		transposedJacobianMatrix[1][2] = (4 * x * z) * detInversed;
		transposedJacobianMatrix[2][0] = (-2 * x - 4 * x * y) * detInversed;
		transposedJacobianMatrix[2][1] = (2 * x + 4 * x * y) * detInversed;
		transposedJacobianMatrix[2][2] = 0;

		// Mnozenie macierzy (wektora wartosci i Jakobianu)
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				differenceArray[j] = differenceArray[j] + (transposedJacobianMatrix[j][k] * currentValueArray[k]);
			}
		}


		//odjecia od punktu startowego (i nastepnych) iloczynu wektora wartosci i Jakobianu
		x = x - differenceArray[0];
		y = y - differenceArray[1];
		z = z - differenceArray[2];

		// zapisanie wartosci z aktualnej iteracji
		currentValueArray[0] = f1(x, y, z);
		currentValueArray[1] = f2(x, y);
		currentValueArray[2] = f3(x, y);

		// wyznaczenie estymatora ledu 

		double estimator = maxValue_3Num(fabs(differenceArray[0]), fabs(differenceArray[1]), fabs(differenceArray[2]));
		double residuum = maxValue_3Num(fabs(currentValueArray[0]), fabs(currentValueArray[1]), fabs(currentValueArray[2]));
		//(jest tu funkcja znajdujaca maksymalna liczbe z differenceArray/currentValueArray w celu uzyskania oczekiwanej precyzji
		// dla kazdej zmiennej x, y, z, a nie tylko np. x i z itp. / otrzymanie wystarczajaco malego bledu
		cout << "ITERATION: " << i + 1 << "\tx = " << x << "\ty = " << y << "\tz = " << z << "\tEstimator = " << estimator << "\tResiduum = " << residuum << endl;

		// warunki zakonczenia iteracji (uzyskanie odpowiedniej dokladnosci)
		if (estimator < PRECISION || residuum < PRECISION)
			break;
	}
}

int main() {
	cout.setf(ios::scientific);
	cout.precision(16);
	Newton(2.2, 2.1, 2.0);
	return 0;
}