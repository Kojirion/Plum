#include <boost/program_options.hpp>
#include <iostream>
#include "Mesh.hpp"

int main(int ac, char* av[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("msm", "print member stiffness matrices")
            ("gsm", "print global stiffness matrix")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
             << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }

    Mesh mesh;

    mesh.addNode({0., 0.});
    mesh.addNode({0., 3.});
    mesh.addNode({2., 3.});
    mesh.addNode({4., 3.});
    mesh.addNode({4., 0.});

    mesh.addElement(0, 1, Element::Type::Frame);
    mesh.addElement(1, 2, Element::Type::Frame);
    mesh.addElement(2, 3, Element::Type::Frame);
    mesh.addElement(3, 4, Element::Type::Frame);

    auto matrix = mesh.getStiffnessMatrix();

    //also usage, -o to specify output

    return 0;
}

