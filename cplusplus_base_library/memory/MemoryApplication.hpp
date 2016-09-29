#ifndef _m_MEMORY_APPLICATION_1_
#define _m_MEMORY_APPLICATION_1_

#include "../private_cplusplus_base_library/cplusplus_base_library_global.hpp"

#ifndef IS_PLUGIN_FIRE
#define IS_PLUGIN_FIRE false
#endif

namespace memory {
class CPLUSPLUS_BASE_LIBRARYSHARED_EXPORT Application {
    static void _p_setMainConstruct();
    static void _p_clearMainConstruct();
    static void _p_setMainQuit();
    static void _p_clearMainQuit();
public:
    Application() { _p_setMainConstruct(); }
    ~Application() { _p_setMainQuit(); }

    static bool isMainConstruct();
    static bool isMainQuit();
};
}

#endif

