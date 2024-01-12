#include <catch2/catch.hpp>

#include "ErfN.t.hh"
#include <cmath>
#include <iostream>

namespace Test
{
using type=double;
type ERFN(type X, std::size_t n);
}

TEST_CASE("Erfn<0>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    const size_t n=0;
    const double X=2.0;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-14));
}
TEST_CASE("ErfN<1>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;    
    const size_t n=1;
    const double X=2.0;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-14));
}
TEST_CASE("ErfN<2>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    const size_t n=2;
    const double X=2.0;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-14));
}
TEST_CASE("ErfN<3>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;    
    const size_t n=3;
    const double X=2.0;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-14));
}
TEST_CASE("ErfN<10>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;    
    const size_t n=10;
    const double X=2.0;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-14));
}
TEST_CASE("ErfN<11>(2)", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;    
    const size_t n=11;
    const double X=2.00;

    CHECK_THAT(Erf::ErfN(n,X), WithinAbs(Test::ERFN(X,n), 1e-12));
}


namespace Test
{
// Checks the Erfn implementation.
type ERFN(type X, std::size_t n)
{
   constexpr type Pi=3.14159'26535'89793'23846; // 20 decimal places, more than enough.
   const type invsqrtPi=1.0/sqrt(Pi);

   switch (n)
   {
      case 0:
        return std::erf(X);
        break;
      case 1:
        return (2.0*exp(-X*X))*invsqrtPi;          
        break;
      case 2:
        return -(4.0*exp(-X*X)*X)*invsqrtPi;
        break;
      case 3:
        return (4*exp(-X*X)*(2*X*X - 1))*invsqrtPi;
        break;
      case 4:
        return -(8*exp(-X*X)*X*(2*X*X - 3))*invsqrtPi;
        break;
      case 5:
        return (8*exp(-X*X)*(4*X*X*X*X - 12*X*X + 3))*invsqrtPi;
        break;
      case 6:
        return -(16*exp(-X*X)*X*(4*X*X*X*X - 20*X*X + 15))*invsqrtPi;
        break;
      case 7:
        return (16*exp(-X*X)*(8*X*X*X*X*X*X - 60*X*X*X*X + 90*X*X - 15))*invsqrtPi;
        break;
      case 8:
        return -(32*exp(-X*X)*X*(8*X*X*X*X*X*X - 84*X*X*X*X + 210*X*X - 105))*invsqrtPi;
        break;
      case 9:
        return (32*exp(-X*X)*(16*X*X*X*X*X*X*X*X - 224*X*X*X*X*X*X + 840*X*X*X*X - 840*X*X + 105))*invsqrtPi;
        break;
      case 10:
        return -(64*exp(-X*X)*X*(16*X*X*X*X*X*X*X*X - 288*X*X*X*X*X*X + 1512*X*X*X*X - 2520*X*X + 945))*invsqrtPi;
        break;
      case 11:
        return (64*exp(-X*X)*(32*X*X*X*X*X*X*X*X*X*X - 720*X*X*X*X*X*X*X*X + 5040*X*X*X*X*X*X - 12600*X*X*X*X + 9450*X*X - 945))*invsqrtPi;
        break;
      default:
        std::cout << "Case is greater than 11 ! Check the (k+2m) being handed into this function\n";
        return -999999;
        break;
   }
}
}
