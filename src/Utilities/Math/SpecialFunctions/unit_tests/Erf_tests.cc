#include <catch2/catch.hpp>

#include "ModifiedChebyshevInterpolation.t.hh"
#include "ErfN.t.hh"

TEST_CASE("ErfClass0", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

    const double x = 0.0;
    CHECK_THAT(erf(x), WithinAbs(Erf::ErfN(0,x), 1e-15));
} 
TEST_CASE("ErfClass1", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

    const double x = 1.0e-04;

    CHECK_THAT(erf(x), WithinAbs(Erf::ErfN(0,x), 1e-15));
}
TEST_CASE("ErfClass2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

    const double x = 1.5;
    CHECK_THAT(erf(x), WithinAbs(Erf::ErfN(0,x), 1e-15));
}
TEST_CASE("ErfClass3", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

    const double x = 2.0;
    CHECK_THAT(erf(x), WithinAbs(Erf::ErfN(0,x), 1e-15));
}
TEST_CASE("erf_0to2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

 
    for(double x=0.0; x<2.0; x += 0.00001) {
       CHECK_THAT(erf(x), WithinAbs(Erf::ErfN(0,x), 1.0e-15));
    }
}
TEST_CASE("x_>_Xmax", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=Erf::ErfN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,Erf::nGridPoints> erf(funcNDer,Erf::epsilion, false);

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
    CHECK_THROWS(erf(2.6)); 
#endif
    CHECK(true);
}