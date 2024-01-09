#ifndef MATH_POW_HH_
#define MATH_POW_HH_

namespace utilities { namespace math 
{ 
	template<typename Type_t, typename Size_t>
	Type_t pow(Type_t x, Size_t N) 
	{   // Simple pow integer function replacement.
	    Type_t product=1.0;
	    for(Size_t n=0; n<N; ++n){
	        product *=x;
    	}
    	return product;
	}
	
} // End of namespace math
} // End of namespace utilities

#endif /* MATH_POW_HH_ */