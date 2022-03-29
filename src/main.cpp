#include "Matrix.hpp"

int main()
{
    Matrix<int> matrix;
    Matrix<int> matrixXY(3, 6);


    matrixXY(2, 4) = 10;

    matrixXY.print();

    matrix = matrixXY;
    matrix.print();


    return 0;
}