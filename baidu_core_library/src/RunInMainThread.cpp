#include "../RunInMainThread.hpp"
#include <QtCore/qobject.h>
#include <QtGui/qevent.h>
#include <QtCore/qcoreapplication.h>
#include <memory/MemoryLibrary.hpp>
#include <cassert>

namespace baidu {

namespace {

constexpr auto event_id=QEvent::MaxUser;

class FunctionEvent :public QEvent{
public:
    virtual void run()=0;
    virtual ~FunctionEvent()=default;
    FunctionEvent() :QEvent(event_id){}
private:
    MEMORY_CLASS_NEW_DELETE
};

class PlainFunctionEvent :public FunctionEvent{
    const __private::PlainFunctionType _m_Data;
public:
    PlainFunctionEvent(__private::PlainFunctionType arg):_m_Data(arg) {}
    void run() { 
        try { _m_Data(); }
        catch (...) {}
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

class StdFunctionEvent :public FunctionEvent{
    const std::function<void(void)> _m_Data;
public:
    StdFunctionEvent(std::function<void(void)>&&arg):_m_Data(std::move(arg)) {}
    void run() { 
        try { _m_Data(); }
        catch (...) {}
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

class DoEvent :public QObject {
public:
    static DoEvent *instance() {
        static auto *ans=new DoEvent/*never delete*/;
        return ans;
    }
protected:
    virtual bool event(QEvent *arg) override{
        {
            auto var=dynamic_cast<PlainFunctionEvent *>(arg);
            if (var) {
                var->run();
                return true;
            }
        }
        return QObject::event(arg);
    }
private:
    MEMORY_CLASS_NEW_DELETE
};

static void _on_qt_start_() {
    DoEvent::instance();
}
Q_COREAPP_STARTUP_FUNCTION(_on_qt_start_)

}

namespace __private {

void _plain_runInMainThread(const PlainFunctionType arg) {
    assert( memory::Application::isMainConstruct() );
    if (arg==nullptr) { return; }
    if (memory::Application::isMainQuit()) { return; }
    QCoreApplication::postEvent(DoEvent::instance(),new PlainFunctionEvent(arg));
}

void _function_runInMainThread(std::function<void(void)>arg) {
    assert( memory::Application::isMainConstruct() );
    if (bool(arg)==false) { return; }
    if (memory::Application::isMainQuit()) { return; }
    QCoreApplication::postEvent(DoEvent::instance(),new StdFunctionEvent(std::move(arg)));
}

}/**/

}/**/

