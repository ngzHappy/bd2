#include "BaiDuUserCache.hpp"
#include <QtCore/qfile.h>
#include <lua/lua.hpp>
#include <text/to_plain_text.hpp>
#include <memory/MemoryLibrary.hpp>

namespace baidu {

BaiDuUserCache::~BaiDuUserCache(){

}

void BaiDuUserCache::open() {
       
    if (_m_L) { return; }

    if(_m_FileName.isEmpty()){
        _m_L.reset();
        return;
    }

    /*try read*/
    read();

    if (_m_L) { return; }

    {
        QFile varFile(_m_FileName);
        if(varFile.open(QIODevice::WriteOnly)==false){
            _m_L.reset();
            return;
        }
        varFile.write(u8R"_(
return {username="",password=""}
)_");
    }

    /*try read again*/
    read();

}

void BaiDuUserCache::setUserName(const QString&arg) {
    auto L=_m_L.get();
    if (L) {
        luaL::StateLock _lock_{ L };
        if (lua::TTABLE==lua::rawgetp(L,LUA_REGISTRYINDEX,this)) {
            lua::pushlstring(L,"username");
            const auto var=arg.toUtf8();
            lua::pushlstring(L,var.data(),var.size());
            lua::rawset(L,-3);
        }
    }
}

void BaiDuUserCache::setPassWord(const QString&arg) {
    auto L=_m_L.get();
    if (L) {
        luaL::StateLock _lock_{ L };
        if (lua::TTABLE==lua::rawgetp(L,LUA_REGISTRYINDEX,this)) {
            lua::pushlstring(L,"password");
            const auto var=arg.toUtf8();
            lua::pushlstring(L,var.data(),var.size());
            lua::rawset(L,-3);
        }
    }
}


void BaiDuUserCache::read(){

    if(_m_FileName.isEmpty()){
        _m_L.reset();
        return;
    }

    QByteArray varFileData;
    text::ToPlainTextAns varFileDataWithOutBom;

    {

        {
            QFile varFile(_m_FileName);
            if(varFile.open(QIODevice::ReadOnly)==false){
                _m_L.reset();
                return;
            }
            varFileData=varFile.readAll();
        }

        if(varFileData.isEmpty()){
            _m_L.reset();
            return;
        }

        varFileDataWithOutBom=text::to_plain_text(
                    varFileData.cbegin(),
                    varFileData.cend());

        if(bool(varFileDataWithOutBom)==false){
            _m_L.reset();
            return;
        }

    }

    _m_L=_instance_lua();
    auto L=_m_L.get();

    if (L) {
        
        const char * varData=varFileDataWithOutBom.data();
        auto varSize=varFileDataWithOutBom.size();
        const auto varU8FileName=_m_FileName.toUtf8();

        if (lua::OK==luaL::loadbuffer(
            L,varData,varSize,
            varU8FileName.data())) {

            if(lua::OK==lua::pcall(L,0,lua::MULTRET,0)){
                if (lua::istable(L,-1)) {
                    lua::pushvalue(L,-1);
                    lua::setglobal(L,"cache");
                    lua::rawsetp(L,LUA_REGISTRYINDEX,this);
                }
                else {
                    lua::pushlstring(L,"there must be a table");
                    luaL::default_lua_error_function(L);
                    _m_L.reset();
                }
            }
            else {
                luaL::default_lua_error_function(L);
                _m_L.reset();
            }
        }
        else {
            luaL::default_lua_error_function(L);
            _m_L.reset();
        }

    }

}

std::shared_ptr<lua::State> BaiDuUserCache::_instance_lua(){
    auto L=luaL::newstate();
    if (L) {
        lua::openlibs(L);
        return std::shared_ptr<lua::State>(L,
            [](lua::State*_L) {lua::close(_L);},
            memory::Allocator<int>{});
    }

    return{};
}

void BaiDuUserCache::write(){

    auto L=_m_L.get();

    if (L) {

        if (lua::TTABLE==lua::getglobal(L,"cache")) {
            luaL::function_table_tostring(L);
            if (lua::isstring(L,-1)) {
                std::size_t varLen;
                auto varStr=lua::tolstring(L,-1,&varLen);

                QFile file_(_m_FileName);

                if (file_.open(QIODevice::WriteOnly)==false) {
                    lua::pop(L,1);
                    return;
                }

                constexpr const static char varUtf8Bom[]{
                    char(0x00EF),char(0x00BB),char(0x00BF)
                };

                file_.write(varUtf8Bom,3);
                file_.write(varStr,varLen);
                lua::pop(L,1);

            }
            else {
                lua::pop(L,1);
            }
        }
        else {
            lua::pop(L,1);
        }

    }


}

QString BaiDuUserCache::getUserName()const {
    auto L=_m_L.get();
    if (L) {
        luaL::StateLock _lock_{ L };
        if (lua::TTABLE==lua::rawgetp(L,LUA_REGISTRYINDEX,this)) {
            lua::pushlstring(L,"username");
            if (lua::TSTRING==lua::rawget(L,-2)) {
                std::size_t varLen;
                auto varAns=lua::tolstring(L,-1,&varLen);
                if (varLen>0) {
                    return QString::fromUtf8(varAns,static_cast<int>(varLen));
                }
            }
        }
    }
    return{};
}

QString BaiDuUserCache::getPassWord()const {
    auto L=_m_L.get();
    if (L) {
        luaL::StateLock _lock_{ L };
        if (lua::TTABLE==lua::rawgetp(L,LUA_REGISTRYINDEX,this)) {
            lua::pushlstring(L,"password");
            if (lua::TSTRING==lua::rawget(L,-2)) {
                std::size_t varLen;
                auto varAns=lua::tolstring(L,-1,&varLen);
                if (varLen>0) {
                    return QString::fromUtf8(varAns,static_cast<int>(varLen));
                }
            }
        }
    }
    return{};
}

}/**/


/*endl of the file*/

