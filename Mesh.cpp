#include "Mesh.hpp"
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <array>
#include <cassert>

static const std::map<Element::Type, int> ldofn = {
    {Element::Type::Frame, 3},
    {Element::Type::Truss, 2},
    {Element::Type::ContactBeam_1, 1},
    {Element::Type::ContactBeam_2, 2}
};

Mesh::Mesh()
{
}

Matrix Mesh::getStiffnessMatrix() const
{   
    int ndf = 3;
    Matrix toReturn(m_nodes.size() * ndf, m_nodes.size() * ndf, arma::fill::zeros);

    for (const auto& element : m_elements) {
        Matrix est = element->getStiffnessMatrix();
        int offset_1 = ndf * indices_1.at(element.get());
        int offset_2 = ndf * indices_2.at(element.get());

        const auto& fixity_1 = element->node_1.fixity;
        const auto& fixity_2 = element->node_2.fixity;
        for (int i=0; i<ndf; ++i){
            if (fixity_1.coords[i])
                toReturn(offset_1 + i, offset_1 + i) +=  1.0e20;
            if (fixity_2.coords[i])
                toReturn(offset_2 + i, offset_2 + i) +=  1.0e20;
        }

        for (int i=0; i<ndf; ++i) {
            for (int j=0; j<ndf; ++j) {
                toReturn(offset_1 + i, offset_1 + j) = est(i, j);
                toReturn(offset_2 + i, offset_2 + j) = est(ndf + i, ndf+ j);            
            }
        }
    }

    return toReturn;
}

Vector Mesh::getLoadsVector() const
{
    int ndf = 3;

    Vector toReturn(m_nodes.size() * ndf);

    for (std::size_t i=0; i<m_nodes.size(); ++i){
        for (int j=0; j<ndf; ++j){
            toReturn(i*ndf + j) = m_nodes[i].load(j);
            const auto& fixity = m_nodes[i].fixity;
            for (std::size_t i=0; i<fixity.coords.size(); ++i){
                if (fixity.coords[i])
                    toReturn(i*ndf + j) += *fixity.coords[i];
            }
        }
    }

    return toReturn;
}

void Mesh::addNode(const Vector3& position, const OptionalVector3& fixity, const Vector3& load)
{
    m_nodes.emplace_back(position, fixity, load);
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

    for (const auto& node : pt.get_child("nodes")){
        auto path = "nodes." + node.first +".";
        Vector3 position = {pt.get<double>(path + "x"), pt.get<double>(path + "y"), pt.get(path + "z", 0.)};
        Vector3 load = {pt.get(path + "Load.x", 0.), pt.get(path + "Load.y", 0.), pt.get(path + "Load.z", 0.)};
        OptionalVector3 fixity = {pt.get_optional<double>(path + "Fixity.x"), pt.get_optional<double>(path + "Fixity.y"), pt.get_optional<double>(path + "Fixity.z")};

        addNode(position, fixity, load);
    }

    for (const auto& element : pt.get_child("elements"))
        addElement(pt.get<unsigned int>("elements." + element.first + ".node_1"), pt.get<unsigned int>("elements." + element.first + ".node_2"), Element::Type::Frame);

}
