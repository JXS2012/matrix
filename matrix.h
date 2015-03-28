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
float norm(Matrix a);
#endif /* MATRIX_H_ */
