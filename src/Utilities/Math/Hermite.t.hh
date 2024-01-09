#ifndef UMERF_HH_
#define UMERF_HH_

namespace utilities { namespace math 
{
  template<typename Size_t, typename Value_t>
  Value_t Hermite(Size_t N, Value_t x)
  { // Simple Hermite Recursion Relation.
     Value_t H_n=0;
     if(N<2) {
       if (0==N) {H_n = 1.0;}
       if (1==N) {H_n = 2*x;}
     } else {
        Value_t H_n_2 = 1;
        Value_t H_n_1 = 2*x;
        for(Size_t n=2; n<(N+1); ++n) {
           H_n = 2.0*(x*H_n_1 - (n-1)*H_n_2);
           H_n_2=H_n_1; H_n_1=H_n;
        }
     }
     return H_n;
  }

} // End of namespace math;
} // End of namespace utilities;

#endif