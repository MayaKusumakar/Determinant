#include "matrix.h"

int main(int argc, char** argv)
{
    /*Initializes all necesssary variables as well as calls all necessary functions to print the determinant of a matrix from the given file.
    @argv: the number of arguments passed to the program
    @argc: the actual arguments in the form of an array of characters
    @returns 0 if the program runs sucessfully, another exit code if otherwise
    */

    char* fileName = argv[1];
    int* dims = GetDimensions(fileName);
    double** vals = GetVals(fileName, dims);

    int rows = dims[0];
    int cols = dims[1];

    Matrix matrix = BuildMatrix(rows, cols, vals);


    double* firstRow = (double*)malloc(matrix.cols * sizeof(double));

    for(int i = 0; i < matrix.cols; i++){
        firstRow[i] = matrix.vals[0][i];
    }

    printf("The determinant is %.2lf.", Determinant(matrix, firstRow, matrix.cols, matrix));
  
}