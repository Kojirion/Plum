#ifndef NODE_HPP
#define NODE_HPP
#include "Algebra.hpp"
#include <boost/optional.hpp>
#include <array>

struct OptionalVector3 {
    std::array<boost::optional<double>, 3> coords;
};

struct Node
{
    Node(Vector3 position, OptionalVector3 fixity, Vector3 load);

    Vector3 position;
    OptionalVector3 fixity;
    Vector3 load;


};

//static_assert(std::is_pod<Node>::value, "Node is pod");

#endif // NODE_HPP
