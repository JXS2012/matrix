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
	Matrix c;
	c.row = a.row;
	c.column = a.column;
	c.head = (float *) malloc(sizeof(float) * c.row * c.column);
	int i, j;
	for (i = 0; i < a.row; i++)
		for (j = 0; j < a.column; j++)
			*(c.head + i * c.column + j) = *(a.head + i * a.column + j)
					- *(b.head + i * b.column + j);
	return c;
}

Matrix matrixPlus(Matrix a, Matrix b) {
	Matrix c;
	c.row = a.row;
	c.column = a.column;
	c.head = (float *) malloc(sizeof(float) * c.row * c.column);
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
	} else
		return 0;
}

Matrix subMatrix3(Matrix a) {
	Matrix t;
	t.row = a.row;
	t.column = a.column;
	t.head = (float *) malloc(sizeof(float) * t.row * t.column);

	int i, j;

	for (i = 0; i < t.row; i++)
		for (j = 0; j < t.column; j++) {
			Matrix subMatrix;
			subMatrix.row = 2;
			subMatrix.column = 2;
			subMatrix.head = (float *) malloc(sizeof(float) * 4);
			int m, n, k;
			k = 0;
			for (m = 0; m < t.row; m++)
				for (n = 0; n < t.row; n++)
					if (m != i && n != j) {
						*(subMatrix.head + k) = *(a.head + m * a.column + n);
						k += 1;
					}
			if ((i * t.column + j) % 2 == 0)
				*(t.head + i * t.column + j) = detMatrix3(subMatrix);
			else
				*(t.head + i * t.column + j) = (-1) * detMatrix3(subMatrix);
		}

	return t;
}

Matrix transposeMatrix(Matrix a) {
	Matrix t;
	t.row = a.column;
	t.column = a.row;
	t.head = (float *) malloc(sizeof(float) * t.row * t.column);
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
	Matrix c;
	c.row = a.row;
	c.column = b.column;
	c.head = (float *) malloc(sizeof(float) * c.row * c.column);
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
	Matrix t;
	t.row = a.row;
	t.column = a.column;
	t.head = (float *) malloc(sizeof(float) * t.row * t.column);
	int i, j;
	for (i = 0; i < t.row; i++)
		for (j = 0; j < t.row; j++)
			*(t.head + i * t.column + j) = *(a.head + i * t.column + j) * k;
	return t;
}

Matrix initMatrix(int row, int column, float *head) {
	Matrix t;
	t.row = row;
	t.column = column;
	t.head = head;
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

float invSqrt(float x) {
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*) &y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*) &i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}

int test() {
	int row = 3;
	int column = 3;
	float *heada = (float *) malloc(sizeof(float) * row * column);
	int i, j;
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			*(heada + i * column + j) = 0;
	for (i = 0; i < row; i++)
		for (j = i; j < i + 1; j++)
			*(heada + i * column + j) = i * column + j + 1;
	Matrix a = initMatrix(row, column, heada);
	printMatrix(a);

	row = 3;
	column = 1;
	float *headb = (float *) malloc(sizeof(float) * row * column);
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
			*(headb + i * column + j) = i * column + j;
	Matrix b = initMatrix(row, column, headb);
	printMatrix(b);

	b = scalarMatrixProduct(2, b);
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

	f = matrixSubtraction(f,e);
	printMatrix(f);

	return 0;
}
