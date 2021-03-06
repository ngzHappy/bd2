﻿// Boost.Geometry

// Copyright (c) 2015-2016 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ANDOYER_INVERSE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ANDOYER_INVERSE_HPP


#include <Qt/boost/math/constants/constants.hpp>

#include <Qt/boost/geometry/core/radius.hpp>
#include <Qt/boost/geometry/core/srs.hpp>

#include <Qt/boost/geometry/util/condition.hpp>
#include <Qt/boost/geometry/util/math.hpp>

#include <Qt/boost/geometry/algorithms/detail/flattening.hpp>
#include <Qt/boost/geometry/algorithms/detail/result_inverse.hpp>


namespace boost { namespace geometry { namespace detail
{

/*!
\brief The solution of the inverse problem of geodesics on latlong coordinates,
       Forsyth-Andoyer-Lambert type approximation with first order terms.
\author See
    - Technical Report: PAUL D. THOMAS, MATHEMATICAL MODELS FOR NAVIGATION SYSTEMS, 1965
      http://www.dtic.mil/docs/citations/AD0627893
    - Technical Report: PAUL D. THOMAS, SPHEROIDAL GEODESICS, REFERENCE SYSTEMS, AND LOCAL GEOMETRY, 1970
      http://www.dtic.mil/docs/citations/AD703541
*/

template <typename CT, bool EnableDistance, bool EnableAzimuth>
struct andoyer_inverse
{
    typedef result_inverse<CT> result_type;

    template <typename T1, typename T2, typename Spheroid>
    static inline result_type apply(T1 const& lon1,
                                    T1 const& lat1,
                                    T2 const& lon2,
                                    T2 const& lat2,
                                    Spheroid const& spheroid)
    {
        CT const c0 = CT(0);
        CT const c1 = CT(1);
        CT const pi = math::pi<CT>();

        result_type result;

        // coordinates in radians

        if ( math::equals(lon1, lon2) && math::equals(lat1, lat2) )
        {
            result.set(c0, c0);
            return result;
        }

        CT const dlon = lon2 - lon1;
        CT const sin_dlon = sin(dlon);
        CT const cos_dlon = cos(dlon);
        CT const sin_lat1 = sin(lat1);
        CT const cos_lat1 = cos(lat1);
        CT const sin_lat2 = sin(lat2);
        CT const cos_lat2 = cos(lat2);

        // H,G,T = infinity if cos_d = 1 or cos_d = -1
        // lat1 == +-90 && lat2 == +-90
        // lat1 == lat2 && lon1 == lon2
        CT cos_d = sin_lat1*sin_lat2 + cos_lat1*cos_lat2*cos_dlon;
        // on some platforms cos_d may be outside valid range
        if (cos_d < -c1)
            cos_d = -c1;
        else if (cos_d > c1)
            cos_d = c1;

        CT const d = acos(cos_d); // [0, pi]
        CT const sin_d = sin(d);  // [-1, 1]
        
        CT const f = detail::flattening<CT>(spheroid);

        if ( BOOST_GEOMETRY_CONDITION(EnableDistance) )
        {
            CT const K = math::sqr(sin_lat1-sin_lat2);
            CT const L = math::sqr(sin_lat1+sin_lat2);
            CT const three_sin_d = CT(3) * sin_d;

            CT const one_minus_cos_d = c1 - cos_d;
            CT const one_plus_cos_d = c1 + cos_d;
            // cos_d = 1 or cos_d = -1 means that the points are antipodal

            CT const H = math::equals(one_minus_cos_d, c0) ?
                            c0 :
                            (d + three_sin_d) / one_minus_cos_d;
            CT const G = math::equals(one_plus_cos_d, c0) ?
                            c0 :
                            (d - three_sin_d) / one_plus_cos_d;

            CT const dd = -(f/CT(4))*(H*K+G*L);

            CT const a = get_radius<0>(spheroid);

            result.distance = a * (d + dd);
        }
        else
        {
            result.distance = c0;
        }

        if ( BOOST_GEOMETRY_CONDITION(EnableAzimuth) )
        {
            // sin_d = 0 <=> antipodal points
            if (math::equals(sin_d, c0))
            {
                // T = inf
                // dA = inf
                // azimuth = -inf
                if (lat1 <= lat2)
                    result.azimuth = c0;
                else
                    result.azimuth = pi;
            }
            else
            {
                CT const c2 = CT(2);

                CT A = c0;
                CT U = c0;
                if ( ! math::equals(cos_lat2, c0) )
                {
                    CT const tan_lat2 = sin_lat2/cos_lat2;
                    CT const M = cos_lat1*tan_lat2-sin_lat1*cos_dlon;
                    A = atan2(sin_dlon, M);
                    CT const sin_2A = sin(c2*A);
                    U = (f/ c2)*math::sqr(cos_lat1)*sin_2A;
                }

                CT V = c0;
                if ( ! math::equals(cos_lat1, c0) )
                {
                    CT const tan_lat1 = sin_lat1/cos_lat1;
                    CT const N = cos_lat2*tan_lat1-sin_lat2*cos_dlon;
                    CT const B = atan2(sin_dlon, N);
                    CT const sin_2B = sin(c2*B);
                    V = (f/ c2)*math::sqr(cos_lat2)*sin_2B;
                }

                CT const T = d / sin_d;
                CT const dA = V*T-U;

                result.azimuth = A - dA;

                // even with sin_d == 0 checked above if the second point
                // is somewhere in the antipodal area T may still be great
                // therefore dA may be great and the resulting azimuth
                // may be some more or less arbitrary angle
                if (A >= c0) // A indicates Eastern hemisphere
                {
                    if (dA >= c0) // A altered towards 0
                    {
                        if ((result.azimuth) < c0)
                            result.azimuth = c0;
                    }
                    else // dA < 0, A altered towards pi
                    {
                        if (result.azimuth > pi)
                            result.azimuth = pi;
                    }
                }
                else // A indicates Western hemisphere
                {
                    if (dA <= c0) // A altered towards 0
                    {
                        if (result.azimuth > c0)
                            result.azimuth = c0;
                    }
                    else // dA > 0, A altered towards -pi
                    {
                        CT const minus_pi = -pi;
                        if ((result.azimuth) < minus_pi)
                            result.azimuth = minus_pi;
                    }
                }
            }
        }
        else
        {
            result.azimuth = c0;
        }

        return result;
    }
};

}}} // namespace boost::geometry::detail


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ANDOYER_INVERSE_HPP
