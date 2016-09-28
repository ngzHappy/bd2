﻿// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2011-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP

#include <deque>

#include <Qt/boost/range.hpp>
#include <Qt/boost/geometry/core/point_type.hpp>
#include <Qt/boost/geometry/algorithms/detail/overlay/turn_info.hpp>
#include <Qt/boost/geometry/algorithms/detail/overlay/get_turns.hpp>
#include <Qt/boost/geometry/algorithms/detail/overlay/self_turn_points.hpp>

#include <Qt/boost/geometry/policies/disjoint_interrupt_policy.hpp>
#include <Qt/boost/geometry/policies/robustness/robust_point_type.hpp>
#include <Qt/boost/geometry/policies/robustness/segment_ratio_type.hpp>
#include <Qt/boost/geometry/policies/robustness/get_rescale_policy.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
#  include <Qt/boost/geometry/algorithms/detail/overlay/debug_turn_info.hpp>
#  include <Qt/boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{


#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)

/*!
\brief Overlay Invalid Input Exception
\ingroup overlay
\details The overlay_invalid_input_exception is thrown at invalid input
 */
class overlay_invalid_input_exception : public geometry::exception
{
public:

    inline overlay_invalid_input_exception() {}

    virtual char const* what() const throw()
    {
        return "Boost.Geometry Overlay invalid input exception";
    }
};

#endif


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{


template <typename Geometry, typename RobustPolicy>
inline bool has_self_intersections(Geometry const& geometry,
        RobustPolicy const& robust_policy,
        bool throw_on_self_intersection = true)
{
    typedef typename point_type<Geometry>::type point_type;
    typedef turn_info
    <
        point_type,
        typename segment_ratio_type<point_type, RobustPolicy>::type
    > turn_info;
    std::deque<turn_info> turns;
    detail::disjoint::disjoint_interrupt_policy policy;

    geometry::self_turns<detail::overlay::assign_null_policy>(geometry, robust_policy, turns, policy);

#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
    bool first = true;
#endif
    for(typename std::deque<turn_info>::const_iterator it = boost::begin(turns);
        it != boost::end(turns); ++it)
    {
        turn_info const& info = *it;
        bool const both_union_turn =
            info.operations[0].operation == detail::overlay::operation_union
            && info.operations[1].operation == detail::overlay::operation_union;
        bool const both_intersection_turn =
            info.operations[0].operation == detail::overlay::operation_intersection
            && info.operations[1].operation == detail::overlay::operation_intersection;

        bool const valid = (both_union_turn || both_intersection_turn)
            && (info.method == detail::overlay::method_touch
                || info.method == detail::overlay::method_touch_interior);

        if (! valid)
        {
#ifdef BOOST_GEOMETRY_DEBUG_HAS_SELF_INTERSECTIONS
            if (first)
            {
                std::cout << "turn points: " << std::endl;
                first = false;
            }
            std::cout << method_char(info.method);
            for (int i = 0; i < 2; i++)
            {
                std::cout << " " << operation_char(info.operations[i].operation);
                std::cout << " " << info.operations[i].seg_id;
            }
            std::cout << " " << geometry::dsv(info.point) << std::endl;
#endif

#if ! defined(BOOST_GEOMETRY_OVERLAY_NO_THROW)
            if (throw_on_self_intersection)
            {
                throw overlay_invalid_input_exception();
            }
#endif
            return true;
        }

    }
    return false;
}

// For backward compatibility
template <typename Geometry>
inline bool has_self_intersections(Geometry const& geometry,
                    bool throw_on_self_intersection = true)
{
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename geometry::rescale_policy_type<point_type>::type
        rescale_policy_type;

    rescale_policy_type robust_policy
            = geometry::get_rescale_policy<rescale_policy_type>(geometry);

    return has_self_intersections(geometry, robust_policy,
                throw_on_self_intersection);
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_HAS_SELF_INTERSECTIONS_HPP
