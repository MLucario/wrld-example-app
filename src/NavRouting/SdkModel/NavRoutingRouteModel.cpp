// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingRouteModel::NavRoutingRouteModel()
            : m_duration(0)
            , m_distance(0)
            {

            }

            NavRoutingRouteModel::NavRoutingRouteModel(const double duration,
                                                       const double distance,
                                                       const std::vector<NavRoutingDirectionModel>& directions)
            : m_duration(duration)
            , m_distance(distance)
            , m_directions(directions)
            {

            }

            const double NavRoutingRouteModel::GetDuration() const
            {
                return m_duration;
            }

            const double NavRoutingRouteModel::GetDistance() const
            {
                return m_distance;
            }

            const std::vector<NavRoutingDirectionModel>& NavRoutingRouteModel::GetDirections() const
            {
                return m_directions;
            }
        }
    }
}
