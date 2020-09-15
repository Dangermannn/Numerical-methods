
#include <iostream>
#include <iomanip>

using namespace std;

const int N = 4;
const int M = 4;
const int MAX_ITERATION = 90;
const double EPSILON = 1e-16;

double** createMatrix(int n, int m)
{
    double** matrix = new double* [n];
    for (int i = 0; i < m; i++)
    {
        matrix[i] = new double[m];
    }
    return matrix;
}

void removeMatrix(double** mat, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        delete[] mat[i];
    }
    delete mat;
}

void printMatrix(double** mat, int n = N, int m = M)
{
    cout << "===============================================================" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << setw(8) << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "===============================================================" << endl << endl;
}

double* createVector(int n = N)
{
    double* vec = new double[n];
    return vec;
}

void printVector(double* vec, int n = N)
{
    cout << "===============================================================" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << setw(26) << vec[i] << " ";
    }
    cout << endl << "===============================================================" << endl << endl;
}

void printVectorInLine(double* vec, int n = N)
{
    cout << left;
    for (int i = 0; i < n; i++)
    {
        cout << setw(26) << vec[i] << " ";
    }
}

double normMaxForVector(double* v, int n = N)
{
    double max = fabs(v[0]);
    for (int i = 1; i < n; i++)
        if (fabs(v[i]) > max)
            max = fabs(v[i])    ;
    return max;
}

double* vectorResiduum(double** matrix, double* vector, double* x, int n = N, int m = M)
{
    double sum = 0;
    double* temp = createVector(n);
    for (int i = 0; i < n; i++)
    {
        sum = 0;
        for (int j = 0; j < m; j++)
        {
            sum += matrix[i][j] * x[j];
        }
        temp[i] = sum - vector[i];
    }
    return temp;
}

void jacobiMethod(double** matrix, double* vector, double* x, int n = N, int m = M)
{
    cout << left;
    int iterator = 0;
    double* currentX = createVector(n);
    double* oldX = createVector(n);
    for (int i = 0; i < n; i++)
    {
        currentX[i] = x[i];
        oldX[i] = x[i];
    }
    double sum = 0;
    double estimator;
    double residuum;
    cout << "===============================================================" << endl;
    cout << "JACOBI METHOD" << endl;
    cout << "===============================================================" << endl << endl;
    cout << setw(12) << "ITERATION" << setw(28 * n) << "Current X vector" << setw(24) << "Estimator" << "Residuum" << endl;
    while (true)
    {
        iterator++;
        if (iterator > MAX_ITERATION)
            return;

        for (int i = 0; i < n; i++)
        {
            sum = 0;
            for (int j = 0; j < m; j++)
            {
                if (i != j)
                {
                    sum += matrix[i][j] * oldX[j];
                }
            }
            currentX[i] = (vector[i] - sum) / matrix[i][i];

        }

        estimator = fabs(normMaxForVector(oldX) - normMaxForVector(currentX));
        residuum = fabs(normMaxForVector(vectorResiduum(matrix, vector, oldX)));
        for (int i = 0; i < n; i++)
        {
            oldX[i] = currentX[i];
        }
        
        if (estimator < EPSILON || residuum < EPSILON)
            break;
        cout << setw(12) << iterator; printVectorInLine(currentX); cout << setw(24) << estimator << residuum << endl;    
    }
    cout << "SOLLUTION" << endl;
    printVector(oldX);
}

void gaussSeidelMethod(double** matrix, double* vector, double* x, int n = N, int m = M)
{
    cout << left;
    int iterator = 0;
    double* prevValues = createVector(n);
    double* difference = createVector(n);
    double* oldX = createVector(n);
    double residuum;
    double estimator;

    for (int i = 0; i < n; i++)
    {
        oldX[i] = x[i];
    }
    double sum = 0;
    cout << "===============================================================" << endl;
    cout << "GAUSS-SEIDEL METHOD" << endl;
    cout << "===============================================================" << endl << endl;
    cout << setw(12) << "ITERATION" << setw(28 * n) << "Current X vector" << setw(24) << "Estimator" << "Residuum" << endl;
    while (true)
    {
        iterator++;
        if (iterator > MAX_ITERATION)
            break;

        for (int i = 0; i < n; i++)
        {
            sum = 0;
            for (int j = 0; j < m; j++)
            {
                if (i != j)
                {
                    sum += matrix[i][j] * oldX[j];
                }
            }
            prevValues[i] = oldX[i];
            oldX[i] = (vector[i] - sum) / matrix[i][i];
        }

        for (int j = 0; j < n; j++)
        {
            difference[j] = prevValues[j] - oldX[j];
        }
        estimator = fabs(normMaxForVector(difference));

        double* res = createVector(n);
        double tmp = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                tmp += matrix[i][j] * oldX[j];
            }
            res[i] = tmp - vector[i];
            tmp = 0;
        }
        residuum = fabs(normMaxForVector(res));
        //residuum = fabs(normMaxForVector(vectorResiduum(matrix, vector, oldX)));

        if (estimator < EPSILON || residuum < EPSILON)
            break;

        cout << setw(12) << iterator; printVectorInLine(oldX); cout << setw(24) << estimator << residuum << endl;
    }
    cout << "SOLLUTION" << endl;
    printVector(oldX);
}

void sorMethod(double** matrix, double* vector, double* x, double omega = 0.5, int n = N, int m = M)
{
    cout << left;
    int iterator = 0;
    double* prevValues = createVector(n);
    double* difference = createVector(n);
    double* oldX = createVector(n);
    for (int i = 0; i < n; i++)
    {
        oldX[i] = x[i];
    }
    double s = 0;
    double estimator;
    double residuum;
    cout << "===============================================================" << endl;
    cout << "SOR METHOD" << endl;
    cout << "===============================================================" << endl << endl;
    cout << setw(12) << "ITERATION" << setw(28 * n) << "Current X vector" << setw(24) << "Estimator" << "Residuum" << endl;
    while (true)
    {
        iterator++;
        if (iterator > MAX_ITERATION)
            break;

        for (int i = 0; i < n; i++)
        {
            s = 0;
            
            for (int j = 0; j < m; j++)
            {
                prevValues[i] = oldX[i];
                s += matrix[i][j] * oldX[j];
            }
            //cout << "ITER = " << iterator << " S = " << s << endl;
            oldX[i] = oldX[i] - omega / matrix[i][i] * (s - vector[i]);
        }
        for (int j = 0; j < n; j++)
        {
            difference[j] = prevValues[j] - oldX[j];
        }
        estimator = fabs(normMaxForVector(difference));
        residuum = fabs(normMaxForVector(vectorResiduum(matrix, vector, oldX)));
        if (estimator < EPSILON || residuum < EPSILON)
            break;
        cout << setw(12) << iterator; printVectorInLine(oldX); cout << setw(24) << estimator << residuum << endl;
    }
    cout << "SOLLUTION" << endl;
    printVector(oldX);
}

int main()
{
    cout.setf(ios::scientific);
    cout.precision(16);
    
    double** A = createMatrix(N, M);
    A[0][0] = 100.0; A[0][1] = -1.0; A[0][2] = 2.0; A[0][3] = -3.0;
    A[1][0] = 1.0; A[1][1] = 200.0; A[1][2] = -4.0; A[1][3] = 5.0;
    A[2][0] = -2.0; A[2][1] = 4.0; A[2][2] = 300.0; A[2][3] = -6.0;
    A[3][0] = 3.0; A[3][1] = -5.0; A[3][2] = 6.0; A[3][3] = 400.0;

    double* b = createVector(N);
    b[0] = 116.0; b[1] = -226.0; b[2] = 912.0; b[3] = -1174.0;

    double* x0 = createVector(N);
    for (int i = 0; i < N; i++)
        x0[i] = 2.0;

    jacobiMethod(A, b, x0);
    gaussSeidelMethod(A, b, x0);
    sorMethod(A, b, x0);
    system("PAUSE");
}


