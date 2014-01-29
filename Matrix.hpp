#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>

class Matrix
{
public:
    Matrix(unsigned int rows, unsigned int columns);

    double operator()(unsigned int row, unsigned int column) const;

private:
    std::vector<double> cells;
    unsigned int nr_columns;
};

#endif // MATRIX_HPP
