#include "Matrix.hpp"
#include <cassert>
#include "Vector.hpp"
#include <iostream>

Matrix::Matrix(unsigned int rows, unsigned int columns):
    cells(rows*columns, 0.),
    nr_columns(columns)
{
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double> > rows)
{
    if (rows.begin() == rows.end()) return;
    else nr_columns = rows.begin()->size();

    for (const auto& row : rows){
        assert(row.size() == nr_columns);
        cells.insert(cells.end(), row.begin(), row.end());
    }
}

double Matrix::operator()(unsigned int row, unsigned int column) const
{
    //return cells[row*nr_columns+column];
    return cells.at(row*nr_columns+column);
}

double &Matrix::operator()(unsigned int row, unsigned int column)
{
    //return cells[row*nr_columns+column];
    return cells.at(row*nr_columns+column);
}

Matrix Matrix::operator*(const Matrix &rhs) const
{
    assert(getNrColumns()==rhs.getNrRows());

    Matrix toReturn(getNrRows(), rhs.getNrColumns());

    for (unsigned int i=0; i<getNrRows(); ++i){
        for (unsigned int j=0; j<rhs.getNrColumns(); ++j){
            double result = 0.;
            for (unsigned int k=0; k<getNrColumns(); ++k){
                result += operator()(i,k) * rhs(k, j);
            }
            toReturn(i, j) = result;
        }
    }

    return toReturn;
}

bool Matrix::operator==(const Matrix &rhs) const
{
    return cells == rhs.cells;
}

unsigned int Matrix::getNrColumns() const
{
    return nr_columns;
}

unsigned int Matrix::getNrRows() const
{
    return cells.size()/nr_columns;
}


std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
{
    for (unsigned int i=0; i<matrix.getNrRows(); ++i){
        os << "( ";
        for (unsigned int j=0; j<matrix.getNrColumns(); ++j){
            os << matrix(i, j) << " ";
        }
        os << ")" << std::endl;
    }
    return os;
}


Vector gauss(const Matrix &matrix, const Vector &b)
{
    Matrix A(matrix);

    std::cout << A << std::endl;

    Vector x(b);
    unsigned int colCount = A.getNrRows();
    int n = colCount;

    for (int k=1; k <= n - 1; ++k) {
        for (int i=k + 1; i<=n; ++i) {
            double c = A(i-1, k-1) / A (k-1, k-1);
            for (int j = k; j<=n; ++j) {
                A(i-1, j-1) = A(i-1, j-1) - c * A(k-1, j-1);
            }
            x[i-1] = x[i-1] - c * x[k-1];
        }
    }

    assert(colCount == x.size());

    //forward elimination
//    for (unsigned int k=0; k<colCount-1; ++k){
//        for (unsigned int i=k+1; i<colCount; ++i){
//            double c = A(k, i) / A(k, k);
//            for (unsigned int j=i; j<colCount; ++j){
//                A(i, j) -= c * A(k, j);
//            }
//            x[i] -= c * x[k];
//            std::cout << A << std::endl;
//        }
//    }

//    back substitution
//        x[colCount-1] /= A(A.getNrRows()-1, A.getNrColumns()-1);
//        for (unsigned int i = colCount-1; i != 1; --i){
//            for (unsigned int j = i+1; j<colCount; ++j){
//                x[i] -= A(i, j) * x[j];
//            }
//            x[i] /= A(i, i);
//        }

    std::cout << A << std::endl;

    return x;
}
