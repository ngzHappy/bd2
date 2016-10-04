#include "../to_plain_text.hpp"


namespace text {

ToPlainTextAns to_plain_text(const char *argBegin,const char *argEnd){
    auto varLength=argEnd-argBegin;

    if(varLength<3){
        return{argBegin,argEnd};
    }

}

}/**/








