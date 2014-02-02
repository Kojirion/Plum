#include "Element.hpp"
#include "Matrix.hpp"

Element::Element(const Node &node_1, const Node &node_2, double youngsModulus, double area, double area_2):
    type(Type::Frame),
    node_1(node_1),
    node_2(node_2)
{

}

Matrix Element::getStiffnessMatrix() const
{

}
