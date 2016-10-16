#ifndef __8302__MODULE_HPP__
#define __8302__MODULE_HPP__

#include <type_traits>

namespace module {

/*noexcept*/
class lua :public std::false_type {};
/*noexcept*/
class cplusplus :public std::true_type {};

}/*namespace module*/

#endif


