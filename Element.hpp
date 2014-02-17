#ifndef ELEMENT_HPP
#define ELEMENT_HPP
#include "Algebra.hpp"

class Node;

class Element{
public:

    Element(const Node& node_1, const Node& node_2, double youngsModulus, double area, double area_2);

    enum class Type {
        Frame,
        Truss,
        ContactBeam_1,
        ContactBeam_2
    };

    Matrix getStiffnessMatrix() const;



private:
    Type type;
    const Node& node_1;
    const Node& node_2;
    double youngsModulus;
    double area;
    double area_2;
};


#endif // ELEMENT_HPP
