#ifndef MESH_HPP
#define MESH_HPP
#include "Node.hpp"
#include "Element.hpp"
#include "Matrix.hpp"
#include <vector>
#include <map>
#include <memory>

class Mesh
{
public:
    Mesh();

    Matrix getStiffnessMatrix();

    void addNode(const Node& node);
    void addElement(unsigned int nodeIndex_1, unsigned int nodeIndex_2, Element::Type type);

    void load(const std::string& filename);

private:
    std::vector<Node> m_nodes;
    std::vector<std::unique_ptr<Element>> m_elements;
    std::map<Element*, unsigned int> indices_1;
    std::map<Element*, unsigned int> indices_2;
    int m_dofn;

    void assemble(Matrix& gst, int ii, int jj, int nodi, int nodj, const Matrix& est, int edofn) const;

};

#endif // MESH_HPP
