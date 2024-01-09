#ifndef MATH_FACTORIAL_HH_
#define MATH_FACTORIAL_HH_

namespace utilities { namespace math 
{ 
    template<typename Type_t, typename Size_t>
    Type_t factorial(Size_t n) 
    {   // Simple factorial function
    if (0 == n || 1 == n) return static_cast<Type_t>(1);
        return static_cast<Type_t>(n * factorial<Type_t,Size_t>(n - 1));
    }

} // End of namespace math
} // End of namespace utilities

#endif /* MATH_FACTORIAL_HH_ */