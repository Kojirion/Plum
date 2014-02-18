#ifndef MESH_HPP
#define MESH_HPP
#include "Node.hpp"
#include "Element.hpp"
#include "Algebra.hpp"
#include <vector>
#include <map>
#include <memory>

class Mesh
{
public:
    Mesh();

    Matrix getStiffnessMatrix() const;
    Vector getLoadsVector() const;

    void addNode(const Vector3 &position, const OptionalVector3 &fixity, const Vector3 &load);
    void addElement(unsigned int nodeIndex_1, unsigned int nodeIndex_2, Element::Type type);

    void load(const std::string& filename);

private:
    std::vector<Node> m_nodes;
    std::vector<std::unique_ptr<Element>> m_elements;
    std::map<Element*, unsigned int> indices_1;
    std::map<Element*, unsigned int> indices_2;

};

#endif // MESH_HPP
