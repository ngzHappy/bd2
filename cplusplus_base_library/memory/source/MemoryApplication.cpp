#include "../MemoryApplication.hpp"
#include <atomic>

namespace memory {

namespace {
std::atomic<bool> _msp_is_main_quit/*false*/;
std::atomic<bool> _msp_is_main_construct/*false*/;
}

void Application::_p_setMainConstruct() { _msp_is_main_construct.store(true); }
void Application::_p_clearMainConstruct() { _msp_is_main_construct.store(false); }
void Application::_p_setMainQuit() { _msp_is_main_quit.store(true); }
void Application::_p_clearMainQuit() { _msp_is_main_quit.store(false); }

bool Application::isMainConstruct() { return _msp_is_main_construct.load(); }
bool Application::isMainQuit() { return _msp_is_main_quit.load(); }

}/*memory*/



