#ifndef MATHCONSTANTS_HH_
#define MATHCONSTANTS_HH_

namespace Constants 
{
  constexpr double epsilon    = 1e-09;
  constexpr long double nudge = 1.0e-08;

  namespace Math 
  {
     constexpr double PI         = 3.14159'26535'89793'23846'26433; ///< \f$ \pi \f$ to 25 decimal places.
     constexpr double ToRads     = PI/180.0;                        ///< From Degrees To Rads.
     constexpr double ToDegrees  = 1.0/ToRads;                      ///< From Rads To Degrees.
  }
}
#endif /* MATHCONSTANTS_HH_ */
