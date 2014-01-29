#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include <Matrix.hpp>

BOOST_AUTO_TEST_CASE(Factor)
{
    Matrix matrix(2,3);

    BOOST_CHECK(matrix(1,1)==0);
}
