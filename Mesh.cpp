#include "Mesh.hpp"
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>

static const std::map<Element::Type, int> ldofn = {
    {Element::Type::Frame, 3},
    {Element::Type::Truss, 2},
    {Element::Type::ContactBeam_1, 1},
    {Element::Type::ContactBeam_2, 2}
};

Mesh::Mesh()
{
}

Matrix Mesh::getStiffnessMatrix()
{

    /*
     *
     * size of stiff ness matrix = 3 * nr_nodes
     for each element
        for i in 0 to 2 (node's degrees of freedom
        for j in 0 to 2
        get node index 1 = ni_1
        gst(ni_1*3 + i, ni_1*3 + j) = est(i, j);
        gst(ni_2*3 + i, ni_2*3 + j) = est(i+3, j+3);


     */




    //no const due to the map.at() ....
    int ndf = 3;
    Matrix toReturn(m_nodes.size() * ndf, m_nodes.size() * ndf, arma::fill::zeros);

    for (auto& element : m_elements) {
        Matrix est = element->getStiffnessMatrix();
        int offset_1 = ndf * indices_1.at(element.get());
        int offset_2 = ndf * indices_2.at(element.get());
        for (int i=0; i<ndf; ++i) {
            for (int j=0; j<ndf; ++j) {
                toReturn(offset_1 + i, offset_1 + j) = est(i, j);
                toReturn(offset_2 + i, offset_2 + j) = est(ndf + i, ndf+ j);
            }
        }
    }
//    std::cout << ndf << std::endl;
//    m_dofn = m_nodes.size();

//    for (auto& element : m_elements){
//        //no const due to taking address...
//        Matrix est = element->getStiffnessMatrix();



//    }

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
