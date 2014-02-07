#include "Mesh.hpp"
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

static const std::map<Element::Type, int> ldofn;

Mesh::Mesh()
{
}

Matrix Mesh::getStiffnessMatrix()
{
    //no const due to the map.at() ....
    Matrix toReturn(20, 20);
    m_dofn = m_nodes.size();

    for (auto& element : m_elements){
        //no const due to taking address...
        Matrix est = element->getStiffnessMatrix();

        assemble(toReturn, 1, 1, indices_1.at(element.get()), indices_2.at(element.get()), est, 3);
        assemble(toReturn, 1, 2, indices_1.at(element.get()), indices_2.at(element.get()), est, 3);
        assemble(toReturn, 2, 1, indices_1.at(element.get()), indices_2.at(element.get()), est, 3);
        assemble(toReturn, 2, 2, indices_1.at(element.get()), indices_2.at(element.get()), est, 3);


    }

    return toReturn;
}

void Mesh::addNode(const Node &node)
{
    m_nodes.push_back(node);
}

void Mesh::addElement(unsigned int nodeIndex_1, unsigned int nodeIndex_2, Element::Type type)
{
    m_elements.emplace_back(new Element(m_nodes.at(nodeIndex_1), m_nodes.at(nodeIndex_2), 2E8, 0.01, 3E-4));
    indices_1.emplace(m_elements.back().get(), nodeIndex_1);
    indices_2.emplace(m_elements.back().get(), nodeIndex_2);

}

void Mesh::load(const std::string &filename)
{
    boost::property_tree::ptree pt;

    boost::property_tree::read_info(filename, pt);

    for (const auto& node : pt.get_child("nodes"))
        addNode({pt.get<double>("nodes." + node.first + ".x"), pt.get<double>("nodes." + node.first + ".y")});

//    for (const auto& element : pt.get_child("elements"))
//        addElement();


}

void Mesh::assemble(Matrix &gst, int ii, int jj, int nodi, int nodj, const Matrix &est, int edofn) const
{
    for (int j=0; j<edofn; ++j){
        int kj = m_dofn*(nodj)+j;
        for (int i=0; i<edofn; ++i){
            int ki = m_dofn * (nodi) + i;
            int esti = edofn * (ii-1) + i;
            int estj = edofn * (jj-1) + j;
            gst(ki, kj) += est(esti, estj);
        }
    }
}
