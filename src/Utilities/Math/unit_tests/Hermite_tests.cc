#include <catch2/catch.hpp>
#include "Hermite.t.hh"
#include <cmath>

TEST_CASE("Hermite<0>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=0;
    const double X=2.0;
    CHECK_THAT(Hermite(n,X), WithinAbs(1, 1e-14));
}
TEST_CASE("Hermite<1>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=1;
    const double X=2.0;
    CHECK_THAT(Hermite(n,X), WithinAbs(2*X, 1e-14));
}
TEST_CASE("Hermite<2>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=2;
    const double X=2.0;
    CHECK_THAT(Hermite(n,X), WithinAbs(4*X*X-2, 1e-14));
}
TEST_CASE("Hermite<3>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=3;
    const double X=2.0;
    CHECK_THAT(Hermite(n,X), WithinAbs(8*X*X*X-12*X, 1e-14));
}
TEST_CASE("Hermite<4>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=4;
    const double X=2.0;
    CHECK_THAT(Hermite(n,X), WithinAbs(16*X*X*X*X-48*X*X+12, 1e-14));
}
TEST_CASE("Hermite<10>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=10;
    const double X=2.0;
    const double expected = 
      1024*std::pow(X,10)  -23040*std::pow(X,8) +161280*std::pow(X,6) 
   -403200*std::pow(X, 4) +302400*std::pow(X,2) -30240;

    CHECK_THAT(Hermite(n,X), WithinAbs(expected, 1e-14));
}
TEST_CASE("Hermite<11>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    const size_t n=11;
    const double X=2.0;

    CHECK_THAT(Hermite(n,X), WithinAbs(-121216, 1e-14));
}