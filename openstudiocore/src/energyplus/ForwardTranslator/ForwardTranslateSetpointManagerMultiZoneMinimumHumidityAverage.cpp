/**********************************************************************
 *  Copyright (c) 2008-2014, Alliance for Sustainable Energy.
 *  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 **********************************************************************/

#include "../ForwardTranslator.hpp"
#include "../../model/SetpointManagerMultiZoneMinimumHumidityAverage.hpp"
#include "../../model/Node.hpp"
#include "../../model/Node_Impl.hpp"
#include <utilities/idd/SetpointManager_MultiZone_MinimumHumidity_Average_FieldEnums.hxx>
#include "../../utilities/idd/IddEnums.hpp"
#include <utilities/idd/IddEnums.hxx>

using namespace openstudio::model;

namespace openstudio {

namespace energyplus {

boost::optional<IdfObject> ForwardTranslator::translateSetpointManagerMultiZoneMinimumHumidityAverage( SetpointManagerMultiZoneMinimumHumidityAverage & modelObject )
{
  boost::optional<double> d;

  // Name
  IdfObject idfObject = createRegisterAndNameIdfObject(openstudio::IddObjectType::SetpointManager_MultiZone_MinimumHumidity_Average, modelObject);

  // HVACAirLoopName
  if( boost::optional<AirLoopHVAC> airloop = modelObject.airLoopHVAC() )
  {
    idfObject.setString(SetpointManager_MultiZone_MinimumHumidity_AverageFields::HVACAirLoopName,airloop->name().get());
  }

  // Minimum Setpoint Humidity Ratio
  d = modelObject.minimumSetpointHumidityRatio();
  if( d )
  {
    idfObject.setDouble(SetpointManager_MultiZone_MinimumHumidity_AverageFields::MinimumSetpointHumidityRatio,d.get());
  }

  // Maximum Setpoint Humidity Ratio
  d = modelObject.maximumSetpointHumidityRatio();
  if( d )
  {
    idfObject.setDouble(SetpointManager_MultiZone_MinimumHumidity_AverageFields::MaximumSetpointHumidityRatio,d.get());
  }

  // Setpoint Node or NodeList Name
  if( boost::optional<Node> node = modelObject.setpointNode() )
  {
    idfObject.setString(SetpointManager_MultiZone_MinimumHumidity_AverageFields::SetpointNodeorNodeListName,node->name().get());
  }

  return idfObject;
}

} // energyplus

} // openstudio
