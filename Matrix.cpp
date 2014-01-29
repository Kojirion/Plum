#include "Matrix.hpp"

Matrix::Matrix(unsigned int rows, unsigned int columns):
    cells(rows*columns, 0.),
    nr_columns(columns)
{
}

double Matrix::operator()(unsigned int row, unsigned int column) const
{
    return cells[row*nr_columns+column];
}
