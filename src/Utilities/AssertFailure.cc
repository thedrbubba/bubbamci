#include <boost/assert.hpp>
#include <sstream>
#include <stdexcept>

namespace boost {
	void
	assertion_failed( char const* expr, char const * function, char const* file, long line ) {
		std::ostringstream ss;
		ss <<file<<"["<<line<<"]:"<<function<<" Assert failed for "<<expr;
		throw std::runtime_error( ss.str() );
	}
}
