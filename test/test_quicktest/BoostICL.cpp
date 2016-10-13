#include "BoostICL.hpp"

#include <iostream>
#include <Qt/boost/icl/interval_set.hpp>

BoostICL::BoostICL() {
    using t=boost::icl::interval_set<double>;
    using tt=t::interval_type;
    t test;
    test.insert(tt::closed(1,2));
    test.insert(tt::closed(5,9));

    {
        auto x=test.equal_range(tt::closed(3,3.3));

        for (auto i=x.first; i!=x.second; ++i) {
            std::cout<<i->lower()<<" , "<<i->upper()<<std::endl;
        }
    }

    {
        auto x=test.equal_range(tt::closed(1.1,3.3));

        for (auto i=x.first; i!=x.second; ++i) {
            std::cout<<i->lower()<<" , "<<i->upper()<<std::endl;
        }
    }

}
