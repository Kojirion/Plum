#include "Matrix.hpp"
#include <cassert>

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
