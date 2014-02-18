#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <Algebra.hpp>
#include <Node.hpp>
#include <Element.hpp>
#include <Mesh.hpp>
#include <iostream>


BOOST_AUTO_TEST_CASE(Matrix_Tests)
{
    Matrix matrix(2,3, arma::fill::zeros);

    BOOST_CHECK(matrix(1,1)==0);
}

BOOST_AUTO_TEST_CASE(Factor)
{
    Matrix matrix_1(2,3);

    matrix_1(0,1) = 2;

    Matrix matrix_2(3,5);

    matrix_2(1,1) = 2;

    BOOST_CHECK(matrix_1(0,1)==matrix_2(1,1));

    Matrix product = matrix_1 * matrix_2;
    BOOST_CHECK(product(0,1)==4);

    //std::cout << matrix_1 << std::endl << matrix_2 << std::endl << product;

}

BOOST_AUTO_TEST_CASE(Element_tests)
{
//    Node node_1{0., 0.};
//    Node node_2{0., 3.};

//    Element element(node_1, node_2, 2E8, 0.01, 3E-4);

//    Matrix matrix;

//    std::initializer_list<std::initializer_list<double>> matrix_lists = {
//    {0.2667E+05, 0.0000E+00, -0.4000E+05, -0.2667E+05, -0.0000E+00, -0.4000E+05},
//    {0.0000E+00, 0.6667E+06, 0.0000E+00, -0.0000E+00, -0.6667E+06, 0.0000E+00},
//    {-0.4000E+05, 0.0000E+00, 0.8000E+05, 0.4000E+05, -0.0000E+00, 0.4000E+05},
//    {-0.2667E+05, -0.0000E+00, 0.4000E+05, 0.2667E+05, 0.0000E+00, 0.4000E+05},
//    {-0.0000E+00, -0.6667E+06, -0.0000E+00, 0.0000E+00, 0.6667E+06, -0.0000E+00},
//    {-0.4000E+05, 0.0000E+00, 0.4000E+05, 0.4000E+05, -0.0000E+00, 0.8000E+05}
//};

    //std::cout << element.getStiffnessMatrix() << std::endl << matrix << std::endl;

    //BOOST_CHECK(element.getStiffnessMatrix() == matrix);

}


BOOST_AUTO_TEST_CASE(Mesh_tests)
{
    Mesh mesh;

    mesh.addNode({0., 0., 0.}, {0., 0., 0.}, {});
    mesh.addNode({0., 3., 0.}, {0., 0., 0.}, {});
    mesh.addNode({2., 3., 0.}, {0., 0., 0.}, {});
    mesh.addNode({4., 3., 0.}, {0., 0., 0.}, {});
    mesh.addNode({4., 0., 0.}, {0., 0., 0.}, {});

    mesh.addElement(0, 1, Element::Type::Frame);
    mesh.addElement(1, 2, Element::Type::Frame);
    mesh.addElement(2, 3, Element::Type::Frame);
    mesh.addElement(3, 4, Element::Type::Frame);

    auto matrix = mesh.getStiffnessMatrix();

    std::cout << matrix << std::endl;
}

BOOST_AUTO_TEST_CASE(Ptree_tests)
{
    Mesh mesh;

    mesh.load("example.info");
}

BOOST_AUTO_TEST_CASE(Gauss_tests)
{

    Matrix matrix = {
        9., 4., 1.,
        3., 3., 1.,
        4., 4., 1.
    };

    matrix.reshape(3,3);

    //std::cout << matrix << std::endl;

    Vector vector = {7, 8, 3};
    auto result = arma::solve(matrix, vector);

    std::cout << result << std::endl;

    //BOOST_CHECK(result == Vector({-0.2, 4., -0.8}));
}
