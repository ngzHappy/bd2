#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){

    std::ofstream ofs("cat_to_url.txt");
    for(int i=1;i<72;++i){
        ofs<<"template<\n";

        ofs<<"typename _t_0_0,typename _t_0_1";
        for(int j=1;j<i;++j){
            ofs<<",\ntypename _t_"<<j<<"_0,typename _t_"<<j<<"_1";
        }

        ofs<<"\n>\n";
        ofs <<"string __cat_to_url(";

        ofs<<"const _t_0_0&_v_0_0,const _t_0_1&_v_0_1";
        for(int j=1;j<i;++j){
            ofs<<",\nconst _t_"<<j<<"_0&_v_"<<j<<"_0,const _t_"<<j<<"_1&_v_"<<j<<"_1";
        }

        ofs<<"){\n";

        ofs<<"constexpr int _n="<<i<<"*(2/*&=*/)+4;\n";
        ofs<<"const int _size=_n";

        for(int j=0;j<i;++j){
            ofs<<"\n+_v_"<<j<<"_0.size()+_v_"<<j<<"_1.size()";
        }
        ofs<<";\n";

        ofs<<"string _ans;\n_ans.reserve(_size);\n";

        for(int j=0;j<i;++j){
            ofs<<u8R"(_ans.append("&",1);)";
            ofs<<"_ans.append(_v_"<<j<<"_0.data(),_v_"<<j<<"_0.size());";
            ofs<<u8R"(_ans.append("=",1);)";
            ofs<<"_ans.append(_v_"<<j<<"_1.data(),_v_"<<j<<"_1.size());"<<std::endl;
        }

        ofs<<"return std::move(_ans);\n}\n";
    }


    (void)argc;
    (void)argv;
}








