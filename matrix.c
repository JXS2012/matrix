/*
 * matrix.c
 *
 *  Created on: Mar 27, 2015
 *      Author: jianxin
 */

/*
 * matrix.c
 *
 *  Created on: Mar 27, 2015
 *      Author: jianxin
 */

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>


Matrix subMatrix3(Matrix a);

Matrix matrixSubtraction(Matrix a, Matrix b) {
	Matrix c = initMatrix(a.row, a.column);
	int i, j;
	for (i = 0; i < a.row; i++)
		for (j = 0; j < a.column; j++)
			*(c.head + i * c.column + j) = *(a.head + i * a.column + j)
					- *(b.head + i * b.column + j);
	return c;
}

Matrix matrixPlus(Matrix a, Matrix b) {
	Matrix c = initMatrix(a.row, a.column);
	int i, j;
	for (i = 0; i < a.row; i++)
		for (j = 0; j < a.column; j++)
			*(c.head + i * c.column + j) = *(a.head + i * a.column + j)
					+ *(b.head + i * b.column + j);
	return c;
}

float detMatrix3(Matrix a) {
	if ((a.row == 3) && (a.column == 3)) {
		float sum1 = (*a.head) * (*(a.head + 4)) * (*(a.head + 8))
				+ (*a.head + 1) * (*(a.head + 5)) * (*(a.head + 6))
				+ (*a.head + 2) * (*(a.head + 3)) * (*(a.head + 7));
		float sum2 = (*a.head) * (*(a.head + 5)) * (*(a.head + 7))
				+ (*a.head + 1) * (*(a.head + 3)) * (*(a.head + 8))
				+ (*a.head + 2) * (*(a.head + 4)) * (*(a.head + 6));
		return sum1 - sum2;
	} else if ((a.row == 2) && (a.column == 2)) {
		return (*a.head) * (*(a.head + 3)) - (*(a.head + 1)) * (*(a.head + 2));
	} else if ((a.row == 1) && (a.column == 1)) {
		return *a.head;
	} else
		return 0;
}

Matrix subMatrix3(Matrix a) {
	Matrix t = initMatrix(a.row, a.column);

	int i, j;

	for (i = 0; i < t.row; i++)
		for (j = 0; j < t.column; j++) {
			Matrix subMatrix = initMatrix(a.row - 1, a.column - 1);
			int m, n, k;
			k = 0;
			for (m = 0; m < t.row; m++)
				for (n = 0; n < t.row; n++)
					if (m != i && n != j) {
						*(subMatrix.head + k) = *(a.head + m * a.column + n);
						k += 1;
					}
			if (t.column == 3 && t.row == 3)
				if ((i * t.column + j) % 2 == 0)
					*(t.head + i * t.column + j) = detMatrix3(subMatrix);
				else
					*(t.head + i * t.column + j) = (-1) * detMatrix3(subMatrix);
			else if (t.column == 2 && t.row == 2)
				switch (i * t.column + j) {
				case 0:
					*(t.head + i * t.column + j) = detMatrix3(subMatrix);
					break;
				case 1:
					*(t.head + i * t.column + j) = -detMatrix3(subMatrix);
					break;
				case 2:
					*(t.head + i * t.column + j) = -detMatrix3(subMatrix);
					break;
				case 3:
					*(t.head + i * t.column + j) = detMatrix3(subMatrix);
					break;
				}
		}

	return t;
}

Matrix transposeMatrix(Matrix a) {
	Matrix t = initMatrix(a.column, a.row);
	int i, j;
	for (i = 0; i < t.row; i++)
		for (j = 0; j < t.column; j++)
			*(t.head + i * t.column + j) = *(a.head + j * a.column + i);
	return t;
}

Matrix inverseMatrix3(Matrix a) {
	Matrix t;
	t = subMatrix3(a);
	t = transposeMatrix(t);
	t = scalarMatrixProduct(1 / detMatrix3(a), t);
	return t;
}

float norm2(Matrix a) {
	int i, j;
	float norm = 0;
	for (i = 0; i < a.row; i++)
		for (j = 0; j < a.column; j++)
			norm += *(a.head + i * a.column + j)
					* (*(a.head + i * a.column + j));
	return norm;
}

Matrix matrixProduct(Matrix a, Matrix b) {
	Matrix c = initMatrix(a.row, b.column);
	int i, j, k;
	for (i = 0; i < c.row; i++)
		for (j = 0; j < c.column; j++) {
			*(c.head + i * c.column + j) = 0;
			for (k = 0; k < a.column; k++)
				*(c.head + i * c.column + j) += *(a.head + i * a.column + k)
						* (*(b.head + k * b.column + j));
		}
	return c;
}

Matrix scalarMatrixProduct(float k, Matrix a) {
	Matrix t = initMatrix(a.row, a.column);
	int i, j;
	for (i = 0; i < t.row; i++)
		for (j = 0; j < t.row; j++)
			*(t.head + i * t.column + j) = *(a.head + i * t.column + j) * k;
	return t;
}

Matrix initMatrix(int row, int column) {
	Matrix t;
	t.row = row;
	t.column = column;
	int i;
	for (i = 0; i < row*column; i ++)
		t.head[i] = 0;
	return t;
}

Matrix initMatrixValue(int row, int column, float *array) {
	Matrix t;
	t.row = row;
	t.column = column;
	int i;
	for (i = 0; i < row*column; i ++)
		t.head[i] = array[i];
	return t;
}


void printMatrix(Matrix a) {
	int i, j;
	for (i = 0; i < a.row; i++) {
		for (j = 0; j < a.column; j++)
			printf("%f\t", *(a.head + i * a.column + j));
		printf("\n");
	}
	printf("\n");
}

Matrix normalizeMatrix(Matrix a) {
	return scalarMatrixProduct(invSqrt(norm2(a)), a);
}

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*) &i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

void changeMatrix(Matrix *x)
{
	float v[6] = {1,1,1,1,1,1};
	Matrix temp = initMatrixValue(2,3,v);
	printMatrix(temp);
	copyMatrix(temp, x);
}

void copyMatrix(Matrix a, Matrix *b)
{
	b->row = a.row;
	b->column = a.column;
	int i;
	for (i = 0; i < a.row*a.column; i ++)
	{
		b->head[i] = a.head[i];
	}
}

int main() {
	int row = 3;
	int column = 3;
	Matrix a = initMatrix(row, column);
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			*(a.head + i * column + j) = 0;
	for (i = 0; i < row; i++)
		for (j = i; j < i + 1; j++)
			*(a.head + i * column + j) = i * column + j + 1;

	printMatrix(a);

	row = 3;
	column = 1;
	Matrix b = initMatrix(row, column);
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			*(b.head + i * column + j) = i * column + j;

	printMatrix(b);

	b = scalarMatrixProduct(2, b);
	printMatrix(b);
	b = transposeMatrix(b);
	printMatrix(b);

	Matrix c = matrixProduct(b, a);
	printMatrix(c);

	Matrix d;
	d = inverseMatrix3(a);
	printMatrix(d);

	Matrix e = matrixProduct(a, d);
	printMatrix(e);

	Matrix f = matrixPlus(a, e);
	printMatrix(f);

	f = matrixSubtraction(matrixPlus(a, e), e);
	printMatrix(f);

	f = normalizeMatrix(f);
	printMatrix(f);

	Matrix g = initMatrix(2, 2);
	*(g.head) = 1;
	*(g.head + 1) = 2;
	*(g.head + 2) = 2;
	*(g.head + 3) = 1;
	printMatrix(g);

	Matrix h = inverseMatrix3(g);
	printMatrix(h);

	printMatrix(matrixProduct(g, inverseMatrix3(g)));

	float p_value[4] = {2,2,3,4};
	Matrix p =initMatrixValue(2,2,p_value);
	printMatrix(p);

	changeMatrix(&p);
	printf("%d,%d\n",p.row,p.column);
	printMatrix(p);
	return 0;
}
