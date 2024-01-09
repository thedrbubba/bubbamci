#include <catch2/catch.hpp>

#include "ModifiedChebyshevInterpolation.t.hh"
#include "ErfN.t.hh"

TEST_CASE("ErfClass0", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

    const double x = 0.0;
    CHECK_THAT(erf(x), WithinAbs(ErfN(0,x), 1e-15));
} 
TEST_CASE("ErfClass1", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

    const double x = 1.0e-04;

    CHECK_THAT(erf(x), WithinAbs(ErfN(0,x), 1e-15));
}
TEST_CASE("ErfClass2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

    const double x = 1.5;
    CHECK_THAT(erf(x), WithinAbs(ErfN(0,x), 1e-15));
}
TEST_CASE("ErfClass3", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

    const double x = 2.0;
    CHECK_THAT(erf(x), WithinAbs(ErfN(0,x), 1e-15));
}
TEST_CASE("erf_0to2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

 
    for(double x=0.0; x<2.0; x += 0.00001) {
       CHECK_THAT(erf(x), WithinAbs(ErfN(0,x), 1.0e-15));
    }
}
TEST_CASE("x_>_Xmax", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=ErfN<size_t,double>;    
    
    specialfunction::ModifiedChebyshevInterpolation<> erf(funcNDer,false);

    CHECK_THROWS(erf(2.6)); 
}