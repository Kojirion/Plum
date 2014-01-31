#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <Matrix.hpp>

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
