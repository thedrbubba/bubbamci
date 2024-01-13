#include <catch2/catch.hpp>

#include "ModifiedChebyshevInterpolation.t.hh"
#include "ExpN.t.hh"

TEST_CASE("negExpAt0", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion);

    const double x = 0.0;
    CHECK_THAT(exp(x), WithinAbs(negExp::negExpN(0,x), 1e-15));
} 
TEST_CASE("negExp_small", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion);

    const double x = 1.0e-04;

    CHECK_THAT(exp(x), WithinAbs(negExp::negExpN(0,x), 1e-15));
}
TEST_CASE("negExp_1.5", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion);

    const double x = 1.5;
    CHECK_THAT(exp(x), WithinAbs(negExp::negExpN(0,x), 1e-15));
}
TEST_CASE("negExp_2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion);

    const double x = 2.0;
    CHECK_THAT(exp(x), WithinAbs(negExp::negExpN(0,x), 1e-15));
}
TEST_CASE("negExp_0to2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion);

 
    for(double x=0.0; x<2.0; x += 0.00001) {
       CHECK_THAT(exp(x), WithinAbs(negExp::negExpN(0,x), 1.0e-15));
    }
}
TEST_CASE("negExp_x_>_Xmax", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;

    using float_t = double;
    using int_t   = std::size_t;

    std::function<float_t(int_t, float_t)> funcNDer=negExp::negExpN<int_t, float_t>;    

    specialfunction::ModifiedChebyshevInterpolation<int_t,float_t,negExp::nGridPoints> exp(funcNDer,negExp::epsilion,true);

#if defined(BOOST_ENABLE_ASSERT_HANDLER)
    CHECK_THROWS(exp(2.6)); 
#endif
    CHECK(true);
}