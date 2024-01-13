#include "pow.t.hh"
#include <cmath>

namespace utilities { namespace math 
{
namespace negExp 
{
   constexpr std::size_t nGridPoints=5e+03;
   constexpr double epsilion=1e-16;     

   template<typename Size_t, typename Value_t>
   Value_t negExpN(Size_t N, Value_t X ) 
   {  // The d^n/dx^n(Exp(-x))
         return math::pow(-1.0,N)*std::exp(-X);
   }
}
} // End of namespace math;
} // End of namespace utilities;