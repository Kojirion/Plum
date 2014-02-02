#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include <ostream>

class Matrix
{
public:
    Matrix(unsigned int rows, unsigned int columns);
    Matrix(std::initializer_list<std::initializer_list<double>> rows);

    double operator()(unsigned int row, unsigned int column) const;
    double& operator()(unsigned int row, unsigned int column);

    Matrix operator*(const Matrix& rhs) const;
    bool operator==(const Matrix& rhs) const;

    unsigned int getNrColumns() const;
    unsigned int getNrRows() const;

private:
    std::vector<double> cells;
    unsigned int nr_columns;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

#endif // MATRIX_HPP
