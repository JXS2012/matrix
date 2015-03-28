/*
 * matrix.c
 *
 *  Created on: Mar 27, 2015
 *      Author: jianxin
 */

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

float norm2(Matrix a)
{
	int i,j;
	return 0;
}
Matrix matrixProduct(Matrix a, Matrix b)
{
	Matrix c;
	c.row = a.row;
	c.column = b.column;
	c.head = (float *) malloc(sizeof(float)*c.row*c.column);
	int i,j,k;
	for (i = 0; i < c.row; i ++)
		for (j = 0; j < c.column; j ++)
		{
			*(c.head + i * c.column + j) = 0;
			for (k = 0; k < a.column; k ++)
				*(c.head + i*c.column + j) += *(a.head + i*a.column + k) * (*(b.head + k*b.column + j));
		}
	return c;
}

Matrix scalarMatrixProduct(float k, Matrix a)
{
	Matrix t;
	t.row = a.row;
	t.column = a.column;
	t.head = (float *) malloc(sizeof(float)*t.row*t.column);
	int i,j;
	for (i = 0; i < t.row; i ++)
		for (j = 0; j < t.row; j ++)
			*(t.head + i*t.column + j) = *(a.head + i*t.column + j)*k;
	return t;
}

Matrix initMatrix(int row, int column, float *head)
{
	Matrix t;
	t.row = row;
	t.column = column;
	t.head = head;
	return t;
}

void printMatrix(Matrix a)
{
	int i,j;
	for (i = 0; i < a.row; i ++)
	{
		for (j = 0; j < a.column; j ++)
			printf("%f\t", *(a.head + i*a.column+j));
		printf("\n");
	}
}

int main()
{
	int row = 3;
	int column = 3;
	float *heada = (float *) malloc(sizeof(float)*row*column);
	int i,j;
	for (i = 0; i < row; i ++)
		for (j = 0; j < column; j ++)
			*(heada + i*column + j) = i*column + j;
	Matrix a = initMatrix(row,column,heada);
	printMatrix(a);

	row = 3;
	column = 1;
	float *headb = (float *) malloc(sizeof(float)*row*column);
	for (i = 0; i < row; i ++)
		for (j = 0; j < column; j ++)
			*(headb + i*column + j) = i*column + j;
	Matrix b = initMatrix(row,column,headb);
	printMatrix(b);
	b = scalarMatrixProduct(2, b);

	Matrix c = matrixProduct(b,a);
	printMatrix(c);
	return 0;
}
