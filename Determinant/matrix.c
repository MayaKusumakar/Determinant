#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "matrix.h"
/* This program finds the determinant of a square matrix given the dimensions and matrix values in a file
*/

/*
typedef struct matrix 
{
    Defines a struct type Matrix that has 3 variables: 
    @rows: the number of rows the matrix has
    @cols: the number of cols the matrix has
    @vals: the matrix of values 
    
    int rows;
    int cols;
    double** vals;
} Matrix;
*/

int* GetDimensions(char* fileName)
{
    /*Gets the dimensions from the file
    @fileName: the name of the file to get the dimensions from
    @returns an array of ints containing the two dimensions: rows and columns
    */
    FILE* file = fopen(fileName, "r");

    int* dims = (int*)malloc(2*sizeof(int));

    fscanf(file, "%d", &dims[0]);
    fscanf(file, "%d", &dims[1]);

    fclose(file);
    return dims;
}

double** GetVals(char* fileName, int* dims)
{
    /*Gets the values of the matrix from the file
    @fileName: the name of the file to get the values from
    @dims: the array of integers containing the dimensions (rows and cols) ** this comes from GetDimensions
    @returns: a matrix of doubles containing the values from the file
    */
    FILE* file = fopen(fileName, "r");

    fscanf(file, "%d %d", &dims[0], &dims[1]);

    int rows = dims[0];
    int cols = dims[1];

    double** vals = (double**)malloc(sizeof(double*) * rows);

    for (int i=0; i < rows; i++) 
    {
        vals[i] = (double*)malloc(sizeof(double) * cols);
        for (int j=0; j < cols; j++)
        {
            fscanf(file, "%lf", &vals[i][j]);
        }    
    }

    fclose(file);

    return vals;
}

Matrix BuildMatrix(int r, int c, double** vals)
{
    /*Builds a struct of type, Matrix, given certain values
    @r: the number of rows in the matrix
    @c: the number of columns in the matrix
    @vals: the matrix of doubles with values
    @returns: A Matrix (struct) containing these 3 "variables"
    */
    
    Matrix matrix;

    matrix.rows = r;
    matrix.cols = c;
    matrix.vals = (double**)malloc(sizeof(double*) * r);

    for (int i=0; i < matrix.rows; i++) 
    {
        (matrix.vals)[i] = (double*)malloc(sizeof(double) * c);
        for (int j=0; j < matrix.cols; j++)
        {
            matrix.vals[i][j] = vals[i][j];
        }    
    }
    return matrix;

}

Matrix copyMatrix(Matrix m, int rows, int cols)
{
    /* Copies a Matrix given into another Matrix
    @m: the Matrix needed to be copied into another Matrix
    @rows: the number of rows in the matrix
    @cols: the number of cols in the matrix
    @returns: a Matrix with values and dimensions copied from the original
    */
    Matrix m2;

    m2.rows = rows;
    m2.cols = cols;

    m2.vals = (double**)malloc(rows * sizeof(double*));

    for (int i=0; i < rows; i++) 
    {
        m2.vals[i] = (double*)malloc(sizeof(double) * cols);
        for (int j=0; j < cols; j++)
        {
            m2.vals[i][j] = m.vals[i][j];
        }    
    }

    
    return m2;
}

void FreeMatrix(Matrix matrix){
    /*Frees the memory of a given matrix
    @matrix: the matrix that needs its memory to be stored
    @returns: nothing, but modifies the memory for matrix
    */
    int rows = matrix.rows;

    for(int i = 0; i < rows; i++){
        free(matrix.vals[i]);
    }
    free (matrix.vals);
}

void PrintMatrix(Matrix m){
    /*Prints a matrix to the user **this is used for debugging, not necessary
    #m: the Matrix needed to be printed
    @returns: nothing
    */
    int rows = m.rows;
    int cols = m.cols;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j<cols; j++){
            printf("%.1lf ", m.vals[i][j]);
        }
        printf("\n");
    }
}


Matrix subMatrix(Matrix m, int colToRemove)
{
    /*Creates a submatrix of the given Matrix by removing the top row and a specified column
    @m: the Matrix that we will create a submatrix out of
    @colToRemove: the specified column that we will remove from the Matrix as well as the first row
    @returns: a new Matrix, with the first row and specified column removed
    */
    Matrix subM = copyMatrix(m, m.rows, m.cols);
    Matrix newMatrix;
    newMatrix.rows = subM.rows-1;
    newMatrix.cols = subM.cols-1;

    newMatrix.vals = (double**)malloc(sizeof(double*) * newMatrix.rows);

    for(int i = 0; i < newMatrix.rows; i++){
        newMatrix.vals[i] = (double*)malloc(sizeof(double)*newMatrix.cols);
    }
    //int countRow = 0;
    int countCol = 0;

    for(int row = 0; row < subM.rows; row++){
        for(int col = 0; col< subM.cols; col++) {
            if(row == 0){
                subM.vals[row][col] = 0;
            }
            else if(col == colToRemove){
                subM.vals[row][col] = 0;
            }
            else{
                
                newMatrix.vals[row-1][countCol] = subM.vals[row][col];
                countCol++;
                if(countCol == newMatrix.cols){
                    countCol = 0;
                }
                
            }
        }
    }
    return newMatrix;
}

double* FillFirstRow(Matrix m){
    /*Fills an array of doubles with the first row of a given Matrix
    @m: the given matrix we will get the first row from
    @returns: an array of doubles with the first row from Matrix m in it
    */
    int cols = m.cols;
    double* firstRow = (double*)malloc(sizeof(double)*cols);
    for(int c = 0; c < cols; c++){
        firstRow[c] = m.vals[0][c];
    }
    return firstRow;
}


double Determinant(Matrix m, double* firstRow, int numElementsInRow, Matrix originalMatrix)
{
    /*This program recursivley calls itself to find the determinant of a matrix using Laplace Expansion
    @m: Matrix that holds the current matrix of values
    @firstRow: the current firstRow of the current matrix
    @numElementsInRow: the number of elements in the current first row
    @originalMatrix: the original matrix, unchanged with finding submatrices
    @returns: a double that is the determinant of the given matrix
    */
    if (m.rows == 2 && m.cols == 2)
    { 
        return (m.vals[0][0] * m.vals[1][1]) - (m.vals[0][1] * m.vals[1][0]);
    }
    else
    {
        double sum = 0;
        for (int i=0; i < numElementsInRow; i++)
        {
            
            //FreeMatrix(m);
            //m = BuildMatrix(originalMatrix.rows, originalMatrix.cols, originalMatrix.vals);
            
            Matrix subMat = subMatrix(m,i);
            //printf("num in row: %lf \n", firstRow[i]);
            //PrintMatrix(subMat);
            //printf("\n\n");
            double* firstRowOfSub;
            firstRowOfSub = FillFirstRow(subMat);
            sum += pow((-1), i) * firstRow[i] * Determinant(subMat, firstRowOfSub, subMat.cols, originalMatrix);
            FreeMatrix(subMat);
            
        }
        return sum;
    }
}