#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <Matrix.hpp>
#include <Node.hpp>
#include <Element.hpp>

BOOST_AUTO_TEST_CASE(Matrix_Tests)
{
    Matrix matrix(2,3);

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

}

BOOST_AUTO_TEST_CASE(Element_tests)
{
    Node node_1{0., 0.};
    Node node_2{0., 3.};

    Element element(node_1, node_2, 2E8, 0.01, 3E-4);

    Matrix matrix = {
        {0.2667E+05, 0.0000E+00, -0.4000E+05, -0.2667E+05, -0.0000E+00, -0.4000E+05},
        {0.0000E+00, 0.6667E+06, 0.0000E+00, -0.0000E+00, -0.6667E+06, 0.0000E+00},
        {-0.4000E+05, 0.0000E+00, 0.8000E+05, 0.4000E+05, -0.0000E+00, 0.4000E+05},
        {-0.2667E+05, -0.0000E+00, 0.4000E+05, 0.2667E+05, 0.0000E+00, 0.4000E+05},
        {-0.0000E+00, -0.6667E+06, -0.0000E+00, 0.0000E+00, 0.6667E+06, -0.0000E+00},
        {-0.4000E+05, 0.0000E+00, 0.4000E+05, 0.4000E+05, -0.0000E+00, 0.8000E+05}
    };

    std::cout << element.getStiffnessMatrix() << std::endl << matrix << std::endl;

    BOOST_CHECK(element.getStiffnessMatrix() == matrix);

}
