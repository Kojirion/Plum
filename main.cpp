#include <boost/program_options.hpp>
#include <iostream>

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

    //also usage, -o to specify output, or echo it to the screen

    return 0;
}

