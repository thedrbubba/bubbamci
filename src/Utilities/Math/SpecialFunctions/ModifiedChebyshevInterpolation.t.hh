#ifndef MATH_MCI_HH_
#define MATH_MCI_HH_

#include "factorial.t.hh"
#include "pow.t.hh"

#include <iostream>
#include <functional>
#include <array>
#include <cmath>

#include <boost/assert.hpp>

/* Basic Outline of this file and the class ModifiedChebyshevInterpolation.

   o  template<,> 
      class ModifiedChebyshevInterpolation
         public: ctor() and operator()
         private: 
            maxFunctionNDer()
            a()
            createTables()
            function()
   
   Function Pointer: FunctionNDerivate, user set by Ctor.
   Data Structures: F is an array of arrays size ( nGridPoints*(nChebyshev+1) ).

   Reference:  Gill, P.M.W., Johnson, B.G. and Pople, J.A. (1991), Two-Electron Repulsion Integrals Over Gaussian s Functions. 
               Int. J. Quantum Chem., 40: 745-752. https://doi.org/10.1002/qua.560400604
               Section: Modified Chebyshev Interpolation
*/

namespace utilities {
namespace math { namespace specialfunction
{

template<typename Int=std::size_t, typename Float=double, Int nGridPoint=Int(5e+03)>
class ModifiedChebyshevInterpolation {
   private:
      using Int_t   = Int;
      using Float_t = Float;
      static constexpr Int_t nChebyshev = 3;
      using Array2D_t      = std::array<std::array<Float_t, nGridPoint>, (nChebyshev+1)>;
      using functionNDer_t = std::function<Float_t(Int_t, Float_t)>;

   public: // Interface
      ModifiedChebyshevInterpolation(functionNDer_t funcNDer, Float_t Epsilon, bool MCIinfo=false) 
                : FunctionNDerivate(funcNDer), epsilon(Epsilon) {createTables(MCIinfo);}
      Float_t operator()(Float_t x) { return function(x); }

   private:
      functionNDer_t FunctionNDerivate = nullptr;
      Float_t epsilon = 0.0;

      static constexpr Int_t Mt = 4; // Trunicate summation of m = 0 to infinity. Mt=4 is more than enough. (3+2*Mt) is max number derivatives needed.
      Float_t Xmax = 0.0;
      Float_t inv2delta = 0.0;
      Array2D_t F;

   private: // member functions
      Float_t maxFunctionNDer(void)
      {
         return 4.40470'27160'06556;    // TODO: TRA - max|f(n+1)(X)| assumes n=3, f=erf
      }
      Float_t a(Int_t k, Float_t Xi, const Float_t& delta_inv2)
      {  // Eq(37) - a_k Coefficient generation.
         BOOST_ASSERT(FunctionNDerivate);

         Float_t sum = 0.0; 
         for( Int_t m=0; m<(Mt+1); ++m ) {
            sum += std::pow(delta_inv2,2*m) * FunctionNDerivate((k+2*m), Xi) 
                   / ( math::factorial<Float_t,Int_t>(m)*math::factorial<Float_t,Int_t>(k+m) );
         }
         return ((k!=0) ? 2 : 1) * math::pow(delta_inv2, k)*sum;
      }
      void createTables(bool MCI_Info) 
      {  // For 3rd order Chebyshev Polynomials only.... index of 0-3.
         const Float_t deltaNum = math::pow(2.0, nChebyshev) * math::factorial<Float_t,Int_t>(nChebyshev+1) * epsilon;
         const Float_t delta    = std::pow(deltaNum/maxFunctionNDer(), 1.0/(nChebyshev+1));
         const auto invdelta    = 1.0/delta;
         const auto delta_inv2  = delta*0.5;
         inv2delta              = 0.5*invdelta;

         for(Int_t j=0; j<nGridPoint; ++j) {
           auto Xj        = (2.0*j+1.0)*delta;
           Xmax           = Xj;
           const auto A0j = a(0,Xj, delta_inv2);
           const auto A1j = a(1,Xj, delta_inv2);
           const auto A2j = a(2,Xj, delta_inv2);
           const auto A3j = a(3,Xj, delta_inv2);                  
           Xj  *= invdelta;
           // These Fs are specific to 3rd-order Chebyshev. If you want to change the order then you have to rederive the Fs!
           F[0][j] = (A0j-A2j)+ (A1j-3*A3j)*(-Xj)+ 2*A2j*math::pow(-Xj, 2)+ 4*A3j*math::pow(-Xj, 3);
           F[1][j] = 2*(A1j-3*A3j)+ 8*A2j*(-Xj)+ 24*A3j*math::pow(-Xj, 2);
           F[2][j] = 8*A2j+ 48*A3j*(-Xj);
           F[3][j] = 32*A3j;                  
         }     

         if(MCI_Info) std::cout << "Grid Points Info: N = "   << nGridPoint 
                                << " , Xmax  ~= "             << Xmax 
                                << " , Delta ~= "             << delta
                                << " , epsilon = "            << epsilon
                                << " , Mt = "                 << Mt
                                << " , Memory ~= "            << sizeof(F)
                                << " : *this = "              << sizeof(*this)                        
                                << std::endl;      
      }
      Float_t function(Float_t x)
      { // Eq.(42) - f(x)
         BOOST_ASSERT(!F.empty());
         BOOST_ASSERT(0 <= x);
         BOOST_ASSERT(x < Xmax);       

         const auto xs=x*inv2delta;
         const Int_t i=std::floor(xs);   // Eq.(41)    
           // This equation is specific to order 3 Chebyshev. If the order of Chebyshev Polynomials is changed this needs to changed.
         return ( F[0][i]+ xs*(F[1][i]+ xs*(F[2][i]+ xs*F[3][i] )) );
      }     
}; //End of Class ModifiedChebyshevInterpolation

} // End of namespace specialfunction
} // End of namespace math
} // End of namescape utilities


#endif /* MATH_MCI_HH_ */
