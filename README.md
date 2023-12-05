# Determinant
## Problem
This program finds the determinant of a matrix.

## Specifications
  - The name of the file containing the matrix will be passed as the first command line parameter
  - The structure of a Matrix File is as follows:
      - number_of_rows number_of_columns
      - row1_val1 row1_val2 row1_val3…
      - row2_val1 row2_val2 row2_val3…
   
  - Program consists of at least 3 source files
      - matrix.c
      - matrix.h
      - main.c
  
## Assumptions
  - The program assumes the files will always be structured correctly
  - The matrices will always be square, ie N X N
  - The values in the matrices can be real numbers, ie doubles




## Assumptions
Program assumes that input will always be valid

### Valid Input
  - Path To the Matrix File
    - This value will be passed as the first command line parameter
    
# Examples
## Example 1
Assume the file 3X3Matrix.txt had the following contents

3 3
1 2 3
4 5 6
7 8 9
./findDeterminant.out 3X3Matrix.txt

The determinant is 0.00
