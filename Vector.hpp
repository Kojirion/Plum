#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <vector>
#include <ostream>

class Vector
{
public:
    Vector(std::initializer_list<double> coords);

    double operator[](unsigned int index) const;
    double& operator[](unsigned int index);

    unsigned int size() const;

    bool operator==(const Vector& rhs) const;

private:
    std::vector<double> m_coords;
};

std::ostream& operator<<(std::ostream& os, const Vector& vector);

#endif // VECTOR_HPP
