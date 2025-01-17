#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H
#endif

#include <stdlib.h>

void gaussianElimination(int size, float coefficient[size][size], float augmented[size])
{
	// Solve a linear equation using Gaussian Elimination.
	// Coefficient matrix is of size n x n and augmented vector is of size n
	float temp, scalingFactor, sum;

	// Converts the matrix to row echelon form

	for (int i = 0; i < size; i++)
	{
		// For handling zero divisions
		if (coefficient[i][i] == 0)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (coefficient[j][i])
				{
					// temp is used here
					for (int k = 0; k < size; k++)
					{
						temp = coefficient[i][k];
						coefficient[i][k] = coefficient[j][k];
						coefficient[j][k] = temp;
					}
					temp = augmented[i];
					augmented[i] = augmented[j];
					augmented[j] = temp;
					break;
				}
			}
		}

		for (int j = i + 1; j < size; j++)
		{
			// If scalingFactor is zero, then there will be no changes
			if (coefficient[j][i] == 0)
				continue;
			scalingFactor = coefficient[j][i] / coefficient[i][i];
			coefficient[j][i] = 0;
			for (int k = i + 1; k < size; k++)
				coefficient[j][k] -= coefficient[i][k] * scalingFactor;
			augmented[j] -= augmented[i] * scalingFactor;
		}
	}

	// Calculating the result by back substitution
	// sum is used here
	for (int i = size - 1; i >= 0; i--)
	{
		sum = 0;
		for (int j = i + 1; j < size; j++)
			sum += coefficient[i][j] * augmented[j];
		augmented[i] = (augmented[i] - sum) / coefficient[i][i];
	}
}

void gaussJordanElimination(int size, float coefficient[size][size], float augmented[size])
{
	// Solve a linear equation using Gaussian - Jordan Elimination.
	// Coefficient matrix is of size n x n and augmented vector is of size n
	float temp, scalingFactor;

	// Converts the matrix to row echelon form
	for (int i = 0; i < size; i++)
	{
		// For handling zero divisions
		if (coefficient[i][i] == 0)
		{
			for (int j = i + 1; j < size; j++)
			{
				// temp is used here
				if (coefficient[j][i])
				{
					for (int k = 0; k < size; k++)
					{
						temp = coefficient[i][k];
						coefficient[i][k] = coefficient[j][k];
						coefficient[j][k] = temp;
					}
					temp = augmented[i];
					augmented[i] = augmented[j];
					augmented[j] = temp;
					break;
				}
			}
		}

		// scalingFactor is used here to convert the pivot to 1 and
		// the subsequent row so that the system remain equivalent
		scalingFactor = coefficient[i][i];
		coefficient[i][i] = 1;

		// Setting the pivot to 1
		for (int j = i + 1; j < size; j++)
			coefficient[i][j] /= scalingFactor;
		augmented[i] /= scalingFactor;

		// Computing the result
		// scalingFactor is used here to make all the rows other than
		// the pivotal row to zero
		for (int k = 0; k < size; k++)
		{
			if (k != i)
			{
				scalingFactor = coefficient[k][i];
				for (int j = i; j < size; j++)
					coefficient[k][j] -= scalingFactor * coefficient[i][j];
				augmented[k] -= scalingFactor * augmented[i];
			}
		}
	}
}

void rowEchelon(int rows, int columns, float matrix[rows][columns])
{
    // Converts a matrix into row echelon form
	int row, column;
    float temp, scalingFactor;

    // Checking for non-zero pivot and interchanging
    // rows if a non-zero number is spotted below a zero

	// Keeps track of rows and columns
	row = column = 0;

	// This flag checks whether to increment column only or not
	int flag;

	while (row < rows && column < columns)
	{
		flag = 1;
		if (matrix[row][column] == 0)
		{
			flag = 0;
			for (int i = row + 1; i < rows; i++)
			{
				if (matrix[i][column])
				{
					flag = 1;
					// Swapping the two rows and then, breaking the loop
					for (int j = column; j < columns; j++)
					{
						temp = matrix[row][j];
						matrix[row][j] = matrix[i][j];
						matrix[i][j] = temp;
					}
					break;
				}
			}
		}

		if (flag)
		{
			// scalingFactor is used here
			for (int i = row + 1; i < rows; i++)
			{

				// If scalingFactor is zero, then there will be no changes
				if (matrix[i][column] == 0)
					continue;
				scalingFactor = matrix[i][column] / matrix[row][column];
				matrix[i][column] = 0;
				for (int j = column + 1; j < columns; j++)
				{
					matrix[i][j] -= matrix[row][j] * scalingFactor;
				}
			}

			// Incrementing row and column if necessary operation is over
			row++;
			column++;
		}
		else
		{
			// Incrementing column if all the numbers below and including pivot is zero
			column++;
			continue;
		}
	}
}

void reducedRowEchelon(int rows, int columns, float matrix[rows][columns])
{
    // Converts a matrix into row echelon form
	int row, column;
    float temp, scalingFactor;

    // Checking for non-zero pivot and interchanging
    // rows if a non-zero number is spotted below a zero

	// Keeps track of rows and columns
	row = column = 0;

	// This flag checks whether to increment column only or not
	int flag;

	while (row < rows && column < columns)
	{
		flag = 1;
		if (matrix[row][column] == 0)
		{
			flag = 0;
			for (int i = row + 1; i < rows; i++)
			{
				if (matrix[i][column])
				{
					flag = 1;
					// Swapping the two rows and then, breaking the loop
					for (int j = column; j < columns; j++)
					{
						temp = matrix[row][j];
						matrix[row][j] = matrix[i][j];
						matrix[i][j] = temp;
					}
					break;
				}
			}
		}

		if (flag)
		{

			// Scaling the pivot to 1
			scalingFactor = matrix[row][column];
			matrix[row][column] = 1;
			for (int i = column + 1; i < columns; i++)
				matrix[row][i] /= scalingFactor;

			// scalingFactor is used here
			for (int i = 0; i < rows; i++)
			{
				if (i != row)
				{
					// If scalingFactor is zero, then there will be no changes
					if (matrix[i][column] == 0)
						continue;
					scalingFactor = matrix[i][column];
					matrix[i][column] = 0;
					for (int j = column + 1; j < columns; j++)
						matrix[i][j] -= matrix[row][j] * scalingFactor;
				}
			}

			// Incrementing row and column if necessary operation is over
			row++;
			column++;
		}
		else
		{
			// Incrementing column if all the numbers below and including pivot is zero
			column++;
			continue;
		}
	}
}

int rank(int rows, int columns, float matrix[rows][columns])
{
	int flag;
	int rank = 0;
	rowEchelon(rows, columns, matrix);
	for (int i = 0; i < rows; i++)
	{
		flag = 0;
		for (int j = 0; j < columns; j++)
		{
			if (matrix[i][j])
				flag = 1;
		}
		if (flag)
			rank++;
	}
	return rank;
}

void matrixAdd(int rows, int columns, float matrix1[rows][columns], float matrix2[rows][columns], float matrixSum[rows][columns])
{
	// Adding matrix
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			matrixSum[i][j] = matrix1[i][j] + matrix2[i][j];
	}
}

void scalarMultiplication(int rows, int columns, float matrix[rows][columns], float scalar)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			matrix[i][j] *= scalar;
	}
}

void transpose(int rows, int columns, float matrix[rows][columns], float matrixTranspose[columns][rows])
{
	// Transposing matrix
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
			matrixTranspose[i][j] = matrix[j][i];
	}
}

int isSymmetric(int size, float matrix[size][size])
{
	// Transposing Matrix
	float matrixTranspose[size][size];
	transpose(size, size, matrix, matrixTranspose);

	// Stores the condition whether a matrix is symmetric or not
	int flag = 1;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
		if (matrix[i][j] != matrixTranspose[i][j])
			{
				flag = 0;
				break;
			}
			if (flag == 0)
				break;
		}
	}

	return flag;
}

void matrixMultiply(int m, int p, int n, float matrix1[m][p], float matrix2[p][n], float matrixProduct[m][n])
{
	// Multiplying matrices
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrixProduct[i][j] = 0;
			for (int k = 0; k < p; k++)
				matrixProduct[i][j] += matrix1[i][k] * matrix2[k][j];
		}
	}
}

void matrixInverse(int size, float matrix[size][size], float identity[size][size])
{
	// Inversing a matrix
	float temp, scalingFactor;

	// Creating Identity Matrix
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			identity[i][j] = 0;
		identity[i][i] = 1;
	}

	// Creating an inverse matrix by converting the matrix into its
	// reduced row echelon form and applying the same elementary matrix operations
	// on the identity matrix
	for (int i = 0; i < size; i++)
	{
		// If the pivot is zero
		if (matrix[i][i] == 0)
		{
			for (int j = i + 1; j < size; j++)
			{
				// temp is used here
				if (matrix[i][j])
				{
					for (int k = 0; k < size; k++)
					{
						// Swapping rows of the matrix
						temp = matrix[i][k];
						matrix[i][k] = matrix[j][k];
						matrix[j][k] = temp;

						// Swapping rows of Identity matrix
						temp = identity[i][k];
						identity[i][k] = identity[j][k];
						identity[j][k] = temp;
					}
					break;
				}
			}
		}

		// scalingFactor is used here to convert the pivot to 1
		scalingFactor = matrix[i][i];
		matrix[i][i] = 1;

		// Scaling the matrix
		for (int j = i + 1; j < size; j++)
			matrix[i][j] /= scalingFactor;

		// Scaling the Identity matrix
		for (int j = 0; j < size; j++)
			identity[i][j] /= scalingFactor;

		// Computing the result
		// scalingFactor is used to convert all the rows other than the pivotal row
		// to zero and performing the same operations on the Identity matrix
		for (int j = 0; j < size; j++)
		{
			if (j != i)
			{
				scalingFactor = matrix[j][i];

				// On matrix
				matrix[j][i] = 0;
				for (int k = i + 1; k < size; k++)
					matrix[j][k] -= scalingFactor * matrix[i][k];

				// On Identity matrix
				for (int k = 0; k <= i; k++)
					identity[j][k] -= scalingFactor * identity[i][k];
			}
		}
	}
}

void rankNormal(int rows, int columns, float matrix[rows][columns])
{
	int rankMatrix = rank(rows, columns, matrix);
	for (int i = 0; i < rankMatrix; i++)
	{
		for (int j = 0; j < columns; j++)
			matrix[i][j] = 0;
		matrix[i][i] = 1;
	}
	for (int i = rankMatrix; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
			matrix[i][j] = 0;
	}
}


float determinant(int size, float matrix[size][size])
{
	int inversion = 0;
	int flag = 0;
	float scalingFactor, temp;
	float determinant = 1;

	for (int i = 0; i < size; i++)
	{
		// For handling zero divisions
		if (matrix[i][i] == 0)
		{
			for (int j = i + 1; j < size; j++)
			{
				if (matrix[j][i])
				{
					// temp is used here
					for (int k = 0; k < size; k++)
					{
						temp = matrix[i][k];
						matrix[i][k] = matrix[j][k];
						matrix[j][k] = temp;
					}
					inversion += 1;
					flag = 1;
				}
			}
		}

		if (flag)
		{
			return 0;
			break;
		}

		else
		{
			for (int j = i + 1; j < size; j++)
			{
				// If scalingFactor is zero, then there will be no changes
				if (matrix[j][i] == 0)
					continue;
				scalingFactor = matrix[j][i] / matrix[i][i];
				matrix[j][i] = 0;
				for (int k = i + 1; k < size; k++)
					matrix[j][k] -= matrix[i][k] * scalingFactor;
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		determinant *= matrix[i][i];
	}

	if (inversion % 2) determinant *= -1;

	return determinant;
}
