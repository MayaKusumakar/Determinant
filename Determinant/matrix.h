#ifndef DETERMINANT_H
#define DETERMINANT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
typedef struct matrix 
{
    /*Defines a struct type Matrix that has 3 variables: 
    @rows: the number of rows the matrix has
    @cols: the number of cols the matrix has
    @vals: the matrix of values 
    */
    int rows;
    int cols;
    double** vals;
} Matrix;
int* GetDimensions(char* fileName);
double** GetVals(char* fileName, int* dims);
Matrix BuildMatrix(int r, int c, double** vals);
Matrix copyMatrix(Matrix m, int rows, int cols);
void FreeMatrix(Matrix matrix);
void PrintMatrix(Matrix m);
Matrix subMatrix(Matrix m, int colToRemove);
double* FillFirstRow(Matrix m);
double Determinant(Matrix m, double* firstRow, int numElementsInRow, Matrix originalMatrix);

#endif