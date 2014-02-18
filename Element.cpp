#include "Element.hpp"
#include "Algebra.hpp"
#include "Node.hpp"
#include <cmath>

Element::Element(const Node &node_1, const Node &node_2, double youngsModulus, double area, double area_2):
    type(Type::Frame),
    node_1(node_1),
    node_2(node_2),
    youngsModulus(youngsModulus),
    area(area),
    area_2(area_2)
{

}

Matrix Element::getStiffnessMatrix() const
{
    double x1 = node_1.position(0);
    double y1 = node_1.position(1);
    double x2 = node_2.position(0);
    double y2 = node_2.position(1);
    double al = std::sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    double c = (x2 - x1) / al;
    double s = (y2 - y1) / al;
    double c2 = c * c;
    double s2 = s * s;
    double sc = s * c;
    double eal = youngsModulus * area / al;
    double teil3 = 12.e0 * youngsModulus * area_2 / (al * al * al);
    double seil2 = 6.e0 * youngsModulus * area_2 / (al * al);

    Matrix est(6, 6);

    est(0, 0) = c2 * eal + s2 * teil3;
    est(0, 1) = sc * (eal - teil3);
    est(0, 2) = -s * seil2;
    est(0, 3) = -(c2 * eal + s2 * teil3);
    est(0, 4) = sc * (teil3 - eal);
    est(0, 5) = -s * seil2;
    est(1, 1) = s2 * eal + c2 * teil3;
    est(1, 2) = c * seil2;
    est(1, 3) = sc * (teil3 - eal);
    est(1, 4) = -(s2 * eal + c2 * teil3);
    est(1, 5) = c * seil2;
    est(2, 2) = 4.e0 * youngsModulus * area_2 / al;
    est(2, 3) = s * seil2;
    est(2, 4) = -c * seil2;
    est(2, 5) = 2.e0 * youngsModulus * area_2 / al;
    est(3, 3) = c2 * eal + s2 * teil3;
    est(3, 4) = sc * (eal - teil3);
    est(3, 5) = s * seil2;
    est(4, 4) = s2 * eal + c2 * teil3;
    est(4, 5) = -c * seil2;
    est(5, 5) = 4.e0 * youngsModulus * area_2 / al;

    for (int i=1; i<6; ++i){
        for (int j=0; j<i; ++j){
            est(i, j) = est(j, i);
        }
    }

    return est;

}
