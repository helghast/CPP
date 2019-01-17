/**
http://archive.oreilly.com/oreillyschool/courses/data-structures-algorithms/mathematical.html
https://es.wikipedia.org/wiki/Eliminación_de_Gauss-Jordan
https://en.wikipedia.org/wiki/Gaussian_elimination
https://en.wikipedia.org/wiki/Pivot_element
https://www.geeksforgeeks.org/program-check-diagonal-matrix-scalar-matrix/

In mathematics, the Gauss-Jordan elimination, named in honor of Carl Friedrich Gauss and Wilhelm Jordan is an algorithm of linear
algebra that is used to determine the solutions of a system of linear equations, to find matrices and inverse. A system of equations
is solved by the Gaussian method when its solutions are obtained by reducing the given system to another equivalent in which each
equation has one less unknown than the previous one. The Gaussian method transforms the coefficient matrix into a superior triangular
matrix. The Gauss-Jordan method continues the transformation process until obtaining a diagonal matrix.
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <cmath>

using namespace std;

static const double epsilon = 1e-9;

static void printMatrix(const vector<vector<double>>& a)
{
    const int n = a.size();
    for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j <= n; ++j)
		{
			cout << a[i][j] << "\t";// << setw(16);
			if (j == n - 1)
            {
                cout << "|";
            }
		}
		cout << endl;
	}
	cout << endl;
}

static void gaussJordan(vector<vector<double>>& A)
{
    const int n = A.size();

    for (int base = 0; base < n; ++base)
    {
        //pivotisation
        double pivot = 0;
        int r = -1;

        for (int k = base; k < n; ++k)
        {
            const double absolute = abs(A[k][base]);
            if (absolute > pivot)
            {
                pivot = absolute;
                r = k;
            }
        }

        if (pivot < epsilon && pivot > -epsilon)
        {
            continue;
        }

        if (r != base)
        {
            for (int c = base; c < n + 1; ++c)
            {
                double tmp = A[base][c];
                A[base][c] = A[r][c];
                A[r][c] = tmp;
            }
        }

        const double baseCoeff = A[base][base];
        if (baseCoeff < epsilon && baseCoeff > -epsilon)
        {
            continue;
        }

        //gauss elimination
        for (int row = 0; row < n; ++row)
        {
            if (row != base)
            {
                const double innerCoeff = A[row][base];
                for (int c = base; c <= n; ++c)
                {
                    A[row][c] -= (innerCoeff / baseCoeff) * A[base][c];
                    if (A[row][c] < epsilon && A[row][c] > -epsilon)
                    {
                        A[row][c] = 0;
                    }
                }
            }
        }
    }
}

static void backSubstitution(const vector<vector<double>>& a, vector<double>& x)
{
    const int n = a.size();
    for (int i = n - 1; i >= 0; --i)
	{
		//x is an array whose values correspond to the values of x,y,z...
		x[i] = a[i][n];
		//make the variable to be calculated equal to the rhs(right hand side) of the last equation
		for (int j = i + 1; j < n; ++j)
		{
			if (j != i)
			{
				//then subtract all the lhs (left hand side) values except the coefficient of the variable whose value is being calculated
				x[i] -= a[i][j] * x[j];
			}
		}
		//now finally divide the rhs (right hand side) by the coefficient of the variable to be calculated
		x[i] /= a[i][i];
	}
}

//a diagonal matrix is a square matrix in which the entries are all null except for the main diagonal, and these can be null or not.
static bool isDiagonal(const vector<vector<double>>& a)
{
    const int n = a.size();

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            // condition to check other elements except main diagonal are zero or not.
            if (i != j && a[i][j] != 0)
            {
                cout << "Not is a diagonal matrix -> [" << i << "][" << j << "] = " << a[i][j] << endl << endl;
                return false;
            }
        }
    }

    cout << "Is a Diagonal matrix" << endl;
    return true;
}

int main()
{
    //set precision
    cout.precision(4);
    cout.setf(ios::fixed);

    vector<vector<double>> matrix{ {1,3,5,9}, {2,7,2,2}, {1,1,4,2} }; //starting case
    //Computations performed on floating numbers can produce infinitessimal differences in results, which is on the order of 10-15.
    //vector<vector<double>> matrix{ {1,3,5,9}, {2,7,2,2}, {100000,100000,400000,200000} };
    //The third row is simply twice the first row, is dependent
    //vector<vector<double>> matrix{ {1,3,5,9}, {2,7,2,2}, {2,6,10,18} };
    //no equation uses more than two variables; note that the coefficient of x in the first equation is zero.
    //vector<vector<double>> matrix{ {0,2,1,7}, {1,2,0,3}, {2,0,5,3} }; //infinite solution for x
    //However, if you reorder the rows—which ultimately should have no effect on the solution—a solution can be found.
    //vector<vector<double>> matrix{ {1,2,0,3}, {0,2,1,7}, {2,0,5,3} };
    //diagonal matrix
    //vector<vector<double>> matrix{ {1,0,0,3}, {0,1,0,7}, {0,0,1,4} };

    printMatrix(matrix);

    if (!isDiagonal(matrix))
    {
        gaussJordan(matrix);
        printMatrix(matrix);
    }

    vector<double> x(matrix.size());
    backSubstitution(matrix, x);

    // Print the values of x, y, z,....
    cout << "The values of the variables are as follows: " << endl;
    std::stringstream result;
    std::copy(x.begin(), x.end(), std::ostream_iterator<double>(result, "; "));
    cout << result.str() << endl;

    return 0;
}
