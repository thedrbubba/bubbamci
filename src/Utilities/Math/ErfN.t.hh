#include "Hermite.t.hh"
#include <cmath>

namespace utilities { namespace math 
{
  template<typename Size_t, typename Value_t>
  Value_t ErfN(Size_t N, Value_t X ) 
  {  // The d^n/dx^n(Erf(x)) using Hermite Polynomials.
     if (0==N) {
        return std::erf(X);
     } else {
        const Value_t xPi=2.0/std::sqrt(3.14159'26535'89793'23846);
        return xPi*std::exp(-X*X)*std::pow(-1.0,N-1)*math::Hermite(N-1,X);
     }
  }
} // End of namespace math;
} // End of namespace utilities;