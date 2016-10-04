#include "BaiDuUserCache.hpp"
#include <QtCore/qfile.h>
#include <lua/lua.hpp>
#include <text/to_plain_text.hpp>
#include <memory/MemoryLibrary.hpp>

namespace baidu {

BaiDuUserCache::~BaiDuUserCache(){

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
                    lua::setglobal(L,"cache");
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


}/**/


/*endl of the file*/

