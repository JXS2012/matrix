/*
c cla * matrix.h
 *
 *  Created on: Mar 27, 2015
 *      Author: jianxin
 */

#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct {
	int row, column;
	float *head;
} Matrix;

Matrix initMatrix(int row, int column, float *head);

void printMatrix(Matrix a);

Matrix matrixProduct(Matrix a, Matrix b);
Matrix scalarMatrixProduct(float k, Matrix a);
float norm2(Matrix a);

float detMatrix3(Matrix a);
Matrix inverseMatrix3(Matrix a);


Matrix transposeMatrix(Matrix a);
Matrix matrixSubtraction(Matrix a, Matrix b);
Matrix matrixPlus(Matrix a, Matrix b);

//Matrix normalizeMatrix(Matrix a);

float invSqrt(float x);

#endif /* MATRIX_H_ */
