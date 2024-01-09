#include <catch2/catch.hpp>

#include "ModifiedChebyshevInterpolation.t.hh"


namespace Testing {
double functionNDer(std::size_t N, double X );
}

TEST_CASE("MCIClass_0", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;
    
    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);
// TODO: TRA - Need to fix!
    const double x = 0.1;
    CHECK_THAT(broadening(x), WithinAbs(Testing::functionNDer(0,x), 1.0e-10));
} 
TEST_CASE("MCIClass_1", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;
    
    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);

// TODO: TRA - Need to fix!

    const double x = 1.0e-04;
//    CHECK_THAT(broadening(x), WithinAbs(Testing::functionNDer(0,x), 1e-15));
}
TEST_CASE("MCIClass_2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;
    
    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);

    const double x = 1.5;
    CHECK_THAT(broadening(x), WithinAbs(Testing::functionNDer(0,x), 1e-15));
}
TEST_CASE("MCIClass_3", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;

    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);

    const double x = 2.0;
    CHECK_THAT(broadening(x), WithinAbs(Testing::functionNDer(0,x), 1e-15));
}
TEST_CASE("MCIClass_0to2", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;

    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);

    for(double x=0.5; x<2.0; x += 0.00001) {
       CHECK_THAT(broadening(x), WithinAbs(Testing::functionNDer(0,x), 3.0e-14));
    }
}
TEST_CASE("MCIClass_x_>_Xmax", "[Simple]") 
{
    using Catch::Matchers::WithinAbs;
    using namespace utilities::math;
    std::function<double(std::size_t, double)> funcNDer=Testing::functionNDer;

    specialfunction::ModifiedChebyshevInterpolation<> broadening(funcNDer);

    CHECK_THROWS(broadening(3.00)); 
}

namespace Testing {
  double 
  functionNDer(std::size_t N, double X ) 
  {
   using std::pow;
   constexpr double Pi=3.14159'26535'89793'23846; // 20 decimal places, more than enough.
   const double sqrtPi=sqrt(Pi);
   const double invsqrtPi=1.0/sqrtPi;

   switch (N)
   {    
      case 0:
        //0th  (1+1/(2*x*x))erf(x)                + Exp(-x*x)/(x*sqrt(Pi))
        return (1+0.5*std::pow(X,-2))*std::erf(X) + std::exp(-X*X)*invsqrtPi*std::pow(X,-1);
        break;
      case 1:
        //1st -erf(x)/(x*x*x)
        return -std::erf(X)/(pow(X,3));          
        break;
      case 2:
        //2nd  ((-2 x)/(E^x^2 Sqrt[Pi])       + 3 Erf[x])/x^4
        return ((-2*X)/(std::exp(X*X)*sqrtPi) + 3*std::erf(X))/(pow(X,4));
        break;
      case 3:
        //3rd  (4 (3 x + x^3      - 3 E^x^2 Sqrt[Pi]       Erf[x])) / (E^x^2 Sqrt[Pi] x^5)
        return (4*(3*X + pow(X,3) - 3*std::exp(X*X)*sqrtPi*std::erf(X)))*invsqrtPi*std::exp(-X*X)/pow(X,5);
        break;
      case 4:
        //d^3/dX^3(-erf(X)/(X X X)) = 
        //     (60 erf(X))/X^6           - (72 e^(-X^2))/(sqrt(π) X^5)            - ((8 e^(-X^2) X^2)/sqrt(π)              - (4 e^(-X^2))/sqrt(π))/X^3              - (36 e^(-X^2))/(sqrt(π) X^3)  
        return (60*std::erf(X))/pow(X,6) - (72*std::exp(-X*X))*invsqrtPi/pow(X,5) - ((8*std::exp(-X*X)*pow(X,2))*invsqrtPi - (4*std::exp(-X*X))*invsqrtPi)/pow(X,3) - (36*std::exp(-X*X))*invsqrtPi/(pow(X,3));
        break;
      case 5:
        //d^4/dX^4(-erf(X)/(X X X)) = 
        //     (8 e^(-X^2)       (-45 sqrt(π) e^(X^2) erf(X)           + 2 X^7      + 9 X^5      + 30 X^3      + 60 X)) /(sqrt(π) X^7)
        return (8*std::exp(-X*X)*(-45*sqrtPi*std::exp(X*X)*std::erf(X) + 2*pow(X,7) + 9*pow(X,5) + 30*pow(X,3) + 60*X))*invsqrtPi/(pow(X,7));
        break;
      case 6:
        //d^5/dX^5(-erf(X)/(X X X)) = 
        //     -(8 e^(-X^2)       (-315 sqrt(π) e^(X^2) erf(X)           + 4 X^9      + 18 X^7      + 78 X^5      + 240 X^3      + 450 X))/(sqrt(π) X^8)
        return -(8*std::exp(-X*X)*(-315*sqrtPi*std::exp(X*X)*std::erf(X) + 4*pow(X,9) + 18*pow(X,7) + 78*pow(X,5) + 240*pow(X,3) + 450*X))*invsqrtPi/(pow(X,8));
        break;
      case 7:
        //d^6/dX^6(-erf(X)/(X X X)) = 
        //     (16 e^(-X^2)       (-1260 sqrt(π) e^(X^2) erf(X)             + 4 X^11      + 16 X^9      + 87 X^7      + 357 X^5      + 1050 X^3      + 1890 X))          /(sqrt(π) X^9)
        return (16*std::exp(-X*X)*(-1260*sqrt(Pi)*std::exp(X*X)*std::erf(X) + 4*pow(X,11) + 16*pow(X,9) + 87*pow(X,7) + 357*pow(X,5) + 1050*pow(X,3) + 1890*X))*invsqrtPi/(pow(X,9));
        break;
      case 8:
        //d^7/dX^7(-erf(X)/(X X X)) = 
        //     (181440 erf(X))/X^10           - (282240 e^(-X^2))/(sqrt(π) X^9)              - (12600 ((8 e^(-X^2) X^2)/sqrt(π)              - (4 e^(-X^2))/sqrt(π)))/X^7              - (211680 e^(-X^2))/(sqrt(π) X^7)              + (2100 ((24 e^(-X^2) X)/sqrt(π)         - (16 e^(-X^2) X^3)/sqrt(π)))/X^6                   - (252 (-(96 e^(-X^2) X^2)/sqrt(π)              + (24 e^(-X^2))/sqrt(π)         + (32 e^(-X^2) X^4)/sqrt(π)))/X^5                   - ((1440 e^(-X^2) X^2)/sqrt(π)              - (240 e^(-X^2))/sqrt(π)         + (128 e^(-X^2) X^6)/sqrt(π)              - (960 e^(-X^2) X^4)/sqrt(π))/X^3                   + (21 (-(240 e^(-X^2) X)/sqrt(π)         - (64 e^(-X^2) X^5)/sqrt(π)              + (320 e^(-X^2) X^3)/sqrt(π)))/X^4
        return (181440*std::erf(X))/pow(X,10) - (282240*std::exp(-X*X))*invsqrtPi/(pow(X,9)) - (12600*((8*std::exp(-X*X)*pow(X,2))*invsqrtPi - (4*std::exp(-X*X))*invsqrtPi))/pow(X,7) - (211680*std::exp(-X*X))*invsqrtPi/(pow(X,7)) + (2100*((24*std::exp(-X*X)*X)*invsqrtPi - (16*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,6) - (252*(-(96*std::exp(-X*X)*pow(X,2))*invsqrtPi + (24*std::exp(-X*X))*invsqrtPi + (32*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,5) - ((1440*std::exp(-X*X)*pow(X,2))*invsqrtPi - (240*std::exp(-X*X))*invsqrtPi + (128*std::exp(-X*X)*pow(X,6))*invsqrtPi - (960*std::exp(-X*X)*pow(X,4))*invsqrtPi)/pow(X,3) + (21*(-(240*std::exp(-X*X)*X)*invsqrtPi - (64*std::exp(-X*X)*pow(X,5))*invsqrtPi + (320*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,4);
        break;
      case 9:
        //d^8/dX^8(-erf(X)/(X X X)) = 
        //     (32 e^(-X^2)       (-56700 sqrt(π) e^(X^2) erf(X)           + 8 X^15      + 12 X^13      + 162 X^11      + 975 X^9      + 4860 X^7      + 18900 X^5      + 52920 X^3      + 90720 X))/(sqrt(π) X^11)
        return (32*std::exp(-X*X)*(-56700*sqrtPi*std::exp(X*X)*std::erf(X) + 8*pow(X,15) + 12*pow(X,13) + 162*pow(X,11) + 975*pow(X,9) + 4860*pow(X,7) + 18900*pow(X,5) + 52920*pow(X,3) + 90720*X))*invsqrtPi/(pow(X,11));
        break;
      case 10:
      //d^9/dX^9(-erf(X)/(X X X)) = 
      //       (19958400 erf(X))/X^12           - (32659200 e^(-X^2))/(sqrt(π) X^11)              - (1693440 ((8 e^(-X^2) X^2)/sqrt(π)              - (4 e^(-X^2))/sqrt(π)))/X^9              - (26127360 e^(-X^2))/(sqrt(π) X^9)              + (317520 ((24 e^(-X^2) X)/sqrt(π)         - (16 e^(-X^2) X^3)/sqrt(π)))/X^8                   - (45360 (-(96 e^(-X^2) X^2)/sqrt(π)              + (24 e^(-X^2))/sqrt(π)         + (32 e^(-X^2) X^4)/sqrt(π)))/X^7                   - (432 ((1440 e^(-X^2) X^2)/sqrt(π)              - (240 e^(-X^2))/sqrt(π)         + (128 e^(-X^2) X^6)/sqrt(π)              - (960 e^(-X^2) X^4)/sqrt(π)))/X^5                   + (5040 (-(240 e^(-X^2) X)/sqrt(π)         - (64 e^(-X^2) X^5)/sqrt(π)              + (320 e^(-X^2) X^3)/sqrt(π)))/X^6                   - (-(26880 e^(-X^2) X^2)/sqrt(π)              + (3360 e^(-X^2))/sqrt(π)         + (512 e^(-X^2) X^8)/sqrt(π)              - (7168 e^(-X^2) X^6)/sqrt(π)              + (26880 e^(-X^2) X^4)/sqrt(π))/X^3                   + (27 ((3360 e^(-X^2) X)/sqrt(π)         - (256 e^(-X^2) X^7)/sqrt(π)              + (2688 e^(-X^2) X^5)/sqrt(π)              - (6720 e^(-X^2) X^3)/sqrt(π)))/X^4
        return (19958400*std::erf(X))/pow(X,12) - (32659200*std::exp(-X*X))*invsqrtPi/(pow(X,11)) - (1693440*((8*std::exp(-X*X)*pow(X,2))*invsqrtPi - (4*std::exp(-X*X))*invsqrtPi))/pow(X,9) - (26127360*std::exp(-X*X))*invsqrtPi/(pow(X,9)) + (317520*((24*std::exp(-X*X)*X)*invsqrtPi - (16*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,8) - (45360*(-(96*std::exp(-X*X)*pow(X,2))*invsqrtPi + (24*std::exp(-X*X))*invsqrtPi + (32*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,7) - (432*((1440*std::exp(-X*X)*pow(X,2))*invsqrtPi - (240*std::exp(-X*X))*invsqrtPi + (128*std::exp(-X*X)*pow(X,6))*invsqrtPi - (960*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,5) + (5040*(-(240*std::exp(-X*X)*X)*invsqrtPi - (64*std::exp(-X*X)*pow(X,5))*invsqrtPi + (320*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,6) - (-(26880*std::exp(-X*X)*pow(X,2))*invsqrtPi + (3360*std::exp(-X*X))*invsqrtPi + (512*std::exp(-X*X)*pow(X,8))*invsqrtPi - (7168*std::exp(-X*X)*pow(X,6))*invsqrtPi + (26880*std::exp(-X*X)*pow(X,4))*invsqrtPi)/pow(X,3) + (27*((3360*std::exp(-X*X)*X)*invsqrtPi - (256*std::exp(-X*X)*pow(X,7))*invsqrtPi + (2688*std::exp(-X*X)*pow(X,5))*invsqrtPi - (6720*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,4);
        break;
      case 11:
      //d^10/dX^10(-erf(X)/(X X X)) = 
      //       -(239500800 erf(X))/X^13           + (399168000 e^(-X^2))/(sqrt(π) X^12)              + (21772800 ((8 e^(-X^2) X^2)/sqrt(π)              - (4 e^(-X^2))/sqrt(π)))/X^10              + (326592000 e^(-X^2))/(sqrt(π) X^10)              - (4233600 ((24 e^(-X^2) X)/sqrt(π)         - (16 e^(-X^2) X^3)/sqrt(π)))/X^9                   + (635040 (-(96 e^(-X^2) X^2)/sqrt(π)              + (24 e^(-X^2))/sqrt(π)         + (32 e^(-X^2) X^4)/sqrt(π)))/X^8                   + (7200 ((1440 e^(-X^2) X^2)/sqrt(π)              - (240 e^(-X^2))/sqrt(π)         + (128 e^(-X^2) X^6)/sqrt(π)              - (960 e^(-X^2) X^4)/sqrt(π)))/X^6                   + (64 e^(-X^2)       (16 X^8      - 288 X^6      + 1512 X^4      - 2520 X^2      + 945))/(sqrt(π) X^2)        + (30 (-(26880 e^(-X^2) X^2)/sqrt(π)              + (3360 e^(-X^2))/sqrt(π)         + (512 e^(-X^2) X^8)/sqrt(π)              - (7168 e^(-X^2) X^6)/sqrt(π)              + (26880 e^(-X^2) X^4)/sqrt(π)))/X^4                   - (75600 (-(240 e^(-X^2) X)/sqrt(π)         - (64 e^(-X^2) X^5)/sqrt(π)              + (320 e^(-X^2) X^3)/sqrt(π)))/X^7                   - (540 ((3360 e^(-X^2) X)/sqrt(π)         - (256 e^(-X^2) X^7)/sqrt(π)              + (2688 e^(-X^2) X^5)/sqrt(π)              - (6720 e^(-X^2) X^3)/sqrt(π)))/X^5
        return -(239500800*std::erf(X))/pow(X,13) + (399168000*std::exp(-X*X))*invsqrtPi/(pow(X,12)) + (21772800*((8*std::exp(-X*X)*pow(X,2))*invsqrtPi - (4*std::exp(-X*X))*invsqrtPi))/pow(X,10) + (326592000*std::exp(-X*X))*invsqrtPi/(pow(X,10)) - (4233600*((24*std::exp(-X*X)*X)*invsqrtPi - (16*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,9) + (635040*(-(96*std::exp(-X*X)*pow(X,2))*invsqrtPi + (24*std::exp(-X*X))*invsqrtPi + (32*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,8) + (7200*((1440*std::exp(-X*X)*pow(X,2))*invsqrtPi - (240*std::exp(-X*X))*invsqrtPi + (128*std::exp(-X*X)*pow(X,6))*invsqrtPi - (960*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,6) + (64*std::exp(-X*X)*(16*pow(X,8) - 288*pow(X,6) + 1512*pow(X,4) - 2520*pow(X,2) + 945))*invsqrtPi/(pow(X,2)) + (30*(-(26880*std::exp(-X*X)*pow(X,2))*invsqrtPi + (3360*std::exp(-X*X))*invsqrtPi + (512*std::exp(-X*X)*pow(X,8))*invsqrtPi - (7168*std::exp(-X*X)*pow(X,6))*invsqrtPi + (26880*std::exp(-X*X)*pow(X,4))*invsqrtPi))/pow(X,4) - (75600*(-(240*std::exp(-X*X)*X)*invsqrtPi - (64*std::exp(-X*X)*pow(X,5))*invsqrtPi + (320*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,7) - (540*((3360*std::exp(-X*X)*X)*invsqrtPi - (256*std::exp(-X*X)*pow(X,7))*invsqrtPi + (2688*std::exp(-X*X)*pow(X,5))*invsqrtPi - (6720*std::exp(-X*X)*pow(X,3))*invsqrtPi))/pow(X,5);
        break;
      default:
        std::cout << "Case is greater than 11 ! Check the (k+2m) being handed into this function\n";
        abort();
        return -999999;
        break;
   }
 }
}