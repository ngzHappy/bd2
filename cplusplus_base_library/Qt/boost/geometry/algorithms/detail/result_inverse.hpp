// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_RESULT_INVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_RESULT_INVERSE_HPP


#include <Qt/boost/math/constants/constants.hpp>

#include <Qt/boost/geometry/core/radius.hpp>
#include <Qt/boost/geometry/core/srs.hpp>

#include <Qt/boost/geometry/util/math.hpp>

#include <Qt/boost/geometry/algorithms/detail/flattening.hpp>


namespace boost { namespace geometry { namespace detail
{

template <typename T>
struct result_inverse
{
    void set(T const& d, T const& a)
    {
        distance = d;
        azimuth = a;
    }

    T distance;
    T azimuth;
};

}}} // namespace boost::geometry::detail


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_RESULT_INVERSE_HPP
