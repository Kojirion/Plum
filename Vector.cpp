#include "Vector.hpp"

Vector::Vector(std::initializer_list<double> coords):
    m_coords(coords)
{
}

double Vector::operator[](unsigned int index) const
{
    return m_coords[index];
}

double &Vector::operator[](unsigned int index)
{
    return m_coords[index];
}

unsigned int Vector::size() const
{
    return m_coords.size();
}

bool Vector::operator==(const Vector &rhs) const
{
    return m_coords == rhs.m_coords;
}


std::ostream &operator<<(std::ostream &os, const Vector &vector)
{
    os << "( ";
    for (unsigned int i=0; i<vector.size(); ++i)
        os << vector[i] << " ";
    os << ")";
    return os;
}
