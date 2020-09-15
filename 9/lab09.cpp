#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

const int MAX_ITERATION = 20;
const double X1 = 0.0;
const double X2 = 1.0;

const double P = 1.0;
const double Q = 0.0;
const double R = -4.0;

const double ALPHA = 0.0;
const double BETA = 1.0;
const double GAMMA = -1.0;
const double PHI = 0.0;
const double PSI = 1.0;
const double THETA = 0.0;

double analitycalFunction(double x)
{
	return (exp(2.0 - 2.0 * x) - 4.0 * exp(4.0 - 2.0 * x) + 4.0 * exp(2.0 * x) - exp(2.0 + 2.0 * x) - x + x * exp(4.0)) / (4.0 - 4.0 * exp(4));
}

void conventionalMethod(double* l, double* d, double* u, double* b, double h, int n)
{
	d[0] = BETA - ALPHA / h;
	u[0] = ALPHA / h;
	b[0] = -GAMMA;

	for (int i = 1; i < n - 1; i++)
	{
		l[i - 1] = P / (h * h) - Q / (2.0 * h);
		d[i] = R - 2.0 * P / (h * h);
		u[i] = P / (h * h) + Q / (2.0 * h);
		b[i] = (X1 + h * i);
	}

	d[n - 1] = PHI / h + PSI;
	l[n - 2] = -PHI / h;
	b[n - 1] = -THETA;
}

void numerowMethod(double* l, double* d, double* u, double* b, double h, int n)
{
	d[0] = BETA - ALPHA / h;
	u[0] = ALPHA / h;
	b[0] = -GAMMA;

	for (int i = 1; i < n - 1; i++)
	{
		l[i - 1] = P / (h * h) + R / (12.0);
		d[i] = (-2.0 * P) / (h * h) + R * (10.0 / 12.0);
		u[i] = P / (h * h) + R / 12.0;
		b[i] = (X1 + i * h - h) / 12.0 + (10.0 / 12.0) * (X1 + i * h) + (X1 + i * h + h) / 12.0;
	}

	l[n - 2] = -PHI / h;
	d[n - 1] = PHI / h + PSI;
	b[n - 1] = -THETA;
}

// Function for Thomas' alghorithm p1
void calculateEta(double* l, double* d, double* u, int n) {
	for (int i = 1; i < n; i++) {
		d[i] = d[i] - ((l[i - 1] / d[i - 1]) * u[i - 1]);
	}
}

// Function for Thomas' algorithm p2
void calculateR( double* l, double* d, double* u, double* b, int n)
{
	for (int i = 1; i < n; i++)
	{
		b[i] = b[i] - ((l[i - 1] / d[i - 1]) * b[i - 1]);
	}
}

void calculateX(double* results, double* b, double* l, double* d, double* u, int n)
{
	results[n - 1] = (1.0 / d[n - 1]) * b[n - 1];
	for (int i = n - 2; i >= 0; i--)
	{
		results[i] = (b[i] - u[i] * results[i + 1]) / d[i];
	}
}

double calculateWtihConventionalMethod(double h, int n)
{
	cout.left;
	double* vector_d, * vector_u, * vector_l, * vector_b, * vector_x, * vector_error;
	double x1 = X1, x2 = X1, zwroc;
	ofstream output;

	vector_d = new double[n];
	vector_u = new double[n];
	vector_l = new double[n];
	vector_b = new double[n];
	vector_x = new double[n];
	vector_error = new double[n];
	
	conventionalMethod(vector_l, vector_d, vector_u, vector_b, h, n);
	calculateEta(vector_l, vector_d, vector_u, n);
	calculateR(vector_l, vector_d, vector_u, vector_b, n);
	calculateX(vector_x, vector_b, vector_l, vector_d, vector_u, n);

	double x_temp = X1;
	for (int i = 0; i < n; i++)
	{
		x_temp = X1 + i * h;
		vector_error[i] = fabs(vector_x[i] - analitycalFunction(x_temp));
	}

	if (n == 50)
	{
		output.open("conventionalResult.txt", ios::out);

		cout << "==================================================================================" << endl;
		cout << "|					Conventional								   |" << endl;
		cout << "==================================================================================" << endl;

		cout << setw(8) << "i" << setw(16) << "POINT" << setw(16) << "Xn" << setw(16) << "u(x)" << endl;
		x_temp = X1;
		for (int i = 0; i < n; i++)
		{
			x_temp = X1 + i * h;
			vector_error[i] = fabs(vector_x[i] - analitycalFunction(x_temp));
			output << x_temp << " " << vector_x[i] << " " << analitycalFunction(x_temp) << endl;
			cout << setw(8) << i << setw(16) << x_temp << setw(16) << vector_x[i] << setw(16) << analitycalFunction(x_temp) << endl;
		}
		output.close();
	}

	double maxVal = fabs(vector_error[0]);
	double tempVal;

	for (int i = 1; i < n; i++)
	{
		tempVal = fabs(vector_error[i]);
		if (maxVal < tempVal)
			maxVal = tempVal;
	}
	delete[] vector_d;
	delete[] vector_u;
	delete[] vector_l;
	delete[] vector_b;
	delete[] vector_x;
	delete[] vector_error;
	return maxVal;
}

double calculateWithNumerowMethod(double h, int n)
{
	cout.left;
	double* vector_d, * vector_u, * vector_l, * vector_b, * vector_x, * vector_error;
	double x1 = X1, x2 = X1, zwroc;
	ofstream output;

	vector_d = new double[n];
	vector_u = new double[n];
	vector_l = new double[n];
	vector_b = new double[n];
	vector_x = new double[n];
	vector_error = new double[n];

	numerowMethod(vector_l, vector_d, vector_u, vector_b, h, n);
	calculateEta(vector_l, vector_d, vector_u, n);
	calculateR(vector_l, vector_d, vector_u, vector_b, n);
	calculateX(vector_x, vector_b, vector_l, vector_d, vector_u, n);

	double x_temp = X1;
	for (int i = 0; i < n; i++)
	{
		x_temp = X1 + i * h;
		vector_error[i] = fabs(vector_x[i] - analitycalFunction(x_temp));
	}
	if (n == 50)
	{
		output.open("numerowResult.txt", ios::out);
		cout << "==================================================================================" << endl;
		cout << "|					Numerow								   |" << endl;
		cout << "==================================================================================" << endl;
		cout << setw(8) << "i" << setw(16) << "POINT" << setw(16) << "Xn" << setw(16) << "u(x)" << endl;
		x_temp = X1;
		for (int i = 0; i < n; i++)
		{
			x_temp = X1 + i * h;
			vector_error[i] = fabs(vector_x[i] - analitycalFunction(x_temp));
			output << x_temp << " " << vector_x[i] << " " << analitycalFunction(x_temp) << endl;
			cout << setw(8) << i << setw(16) << x_temp << setw(16) << vector_x[i] << setw(16) << analitycalFunction(x_temp) << endl;		
		}
		output.close();
	}

	double maxVal = fabs(vector_error[0]);
	double tempVal;

	for (int i = 1; i < n; i++)
	{
		tempVal = fabs(vector_error[i]);
		if (maxVal < tempVal)
			maxVal = tempVal;
	}
	delete[] vector_d;
	delete[] vector_u;
	delete[] vector_l;
	delete[] vector_b;
	delete[] vector_x;
	delete[] vector_error;
	return maxVal;
}

void errorsToFile()
{
	double conv_error, num_error;
	double h = 0.1;
	ofstream errors;
	errors.open("errors.txt", ios::out);
	for (int i = 10; i < 50000; i += 40)
	{
		h = (X2 - X1) / (i - 1);
		conv_error = log10(calculateWtihConventionalMethod(h, i));
		num_error = log10(calculateWithNumerowMethod(h, i));
		errors << log10(h) << " " << conv_error << " " << num_error << endl;
	}
	errors.close();
}

int main()
{
	errorsToFile();
	system("PAUSE");
	return 0;
}