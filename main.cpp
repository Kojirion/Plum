#include <boost/program_options.hpp>
#include <iostream>
#include "Mesh.hpp"
#include <vector>
#include <string>
#include <armadillo>

int main(int ac, char* av[])
{
    namespace po = boost::program_options;

    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("msm", "print member stiffness matrices")
            ("gsm", "print global stiffness matrix")
            ("input-file", po::value<std::vector<std::string> >(), "input file")
            ;

    po::positional_options_description p;
    p.add("input-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(ac, av).options(desc).positional(p).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

//    if (!vm.count("input-file")) {
//        std::cout << "No input file" << std::endl;
//        return 1;
//    }

    Mesh mesh;
    mesh.load("example.info");

    Matrix matrix = mesh.getStiffnessMatrix();    
    Vector vector = mesh.getLoadsVector();

    std::cout << vector << std::endl;
    std::cout << matrix << std::endl;

    //auto result = arma::solve(matrix, vector);

    //std::cout << result << std::endl;


    //also usage, -o to specify output, version

    return 0;
}

