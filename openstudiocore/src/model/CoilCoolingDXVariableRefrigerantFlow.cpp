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

#include "Model.hpp"
#include "Model_Impl.hpp"
#include "CurveBiquadratic.hpp"
#include "CurveBiquadratic_Impl.hpp"
#include "CurveQuadratic.hpp"
#include "CurveQuadratic_Impl.hpp"
#include "CoilCoolingDXVariableRefrigerantFlow.hpp"
#include "CoilCoolingDXVariableRefrigerantFlow_Impl.hpp"
#include "Schedule.hpp"
#include "Schedule_Impl.hpp"
#include "Curve.hpp"
#include "Curve_Impl.hpp"
#include "Connection.hpp"
#include "Connection_Impl.hpp"
#include "ScheduleTypeLimits.hpp"
#include "ScheduleTypeRegistry.hpp"
#include <utilities/idd/OS_Coil_Cooling_DX_VariableRefrigerantFlow_FieldEnums.hxx>
#include <utilities/idd/IddEnums.hxx>
#include "../utilities/units/Unit.hpp"
#include "../utilities/core/Assert.hpp"

namespace openstudio {

namespace model {

namespace detail {

  CoilCoolingDXVariableRefrigerantFlow_Impl::CoilCoolingDXVariableRefrigerantFlow_Impl(const IdfObject& idfObject,
                                                                                       Model_Impl* model,
                                                                                       bool keepHandle)
    : HVACComponent_Impl(idfObject,model,keepHandle)
  {
    OS_ASSERT(idfObject.iddObject().type() == CoilCoolingDXVariableRefrigerantFlow::iddObjectType());
  }

  CoilCoolingDXVariableRefrigerantFlow_Impl::CoilCoolingDXVariableRefrigerantFlow_Impl(const openstudio::detail::WorkspaceObject_Impl& other,
                                                                                       Model_Impl* model,
                                                                                       bool keepHandle)
    : HVACComponent_Impl(other,model,keepHandle)
  {
    OS_ASSERT(other.iddObject().type() == CoilCoolingDXVariableRefrigerantFlow::iddObjectType());
  }

  CoilCoolingDXVariableRefrigerantFlow_Impl::CoilCoolingDXVariableRefrigerantFlow_Impl(const CoilCoolingDXVariableRefrigerantFlow_Impl& other,
                                                                                       Model_Impl* model,
                                                                                       bool keepHandle)
    : HVACComponent_Impl(other,model,keepHandle)
  {}

  const std::vector<std::string>& CoilCoolingDXVariableRefrigerantFlow_Impl::outputVariableNames() const
  {
    static std::vector<std::string> result;
    if (result.empty()){
    }
    return result;
  }

  IddObjectType CoilCoolingDXVariableRefrigerantFlow_Impl::iddObjectType() const {
    return CoilCoolingDXVariableRefrigerantFlow::iddObjectType();
  }

  std::vector<ScheduleTypeKey> CoilCoolingDXVariableRefrigerantFlow_Impl::getScheduleTypeKeys(const Schedule& schedule) const
  {
    std::vector<ScheduleTypeKey> result;
    UnsignedVector fieldIndices = getSourceIndices(schedule.handle());
    UnsignedVector::const_iterator b(fieldIndices.begin()), e(fieldIndices.end());
    if (std::find(b,e,OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::AvailabilitySchedule) != e)
    {
      result.push_back(ScheduleTypeKey("CoilCoolingDXVariableRefrigerantFlow","Availability Schedule"));
    }
    return result;
  }

  Schedule CoilCoolingDXVariableRefrigerantFlow_Impl::availabilitySchedule() const {
    boost::optional<Schedule> value = optionalAvailabilitySchedule();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Availability Schedule attached.");
    }
    return value.get();
  }

  boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedTotalCoolingCapacity() const {
    return getDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedTotalCoolingCapacity,true);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedTotalCoolingCapacityAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedTotalCoolingCapacity, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedSensibleHeatRatio() const {
    return getDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedSensibleHeatRatio,true);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedSensibleHeatRatioAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedSensibleHeatRatio, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  boost::optional<double> CoilCoolingDXVariableRefrigerantFlow_Impl::ratedAirFlowRate() const {
    return getDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate,true);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::isRatedAirFlowRateAutosized() const {
    bool result = false;
    boost::optional<std::string> value = getString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, true);
    if (value) {
      result = openstudio::istringEqual(value.get(), "autosize");
    }
    return result;
  }

  Curve CoilCoolingDXVariableRefrigerantFlow_Impl::coolingCapacityRatioModifierFunctionofTemperatureCurve() const {
    boost::optional<Curve> value = optionalCoolingCapacityRatioModifierFunctionofTemperatureCurve();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Cooling Capacity Ratio Modifier Functionof Temperature Curve attached.");
    }
    return value.get();
  }

  Curve CoilCoolingDXVariableRefrigerantFlow_Impl::coolingCapacityModifierCurveFunctionofFlowFraction() const {
    boost::optional<Curve> value = optionalCoolingCapacityModifierCurveFunctionofFlowFraction();
    if (!value) {
      LOG_AND_THROW(briefDescription() << " does not have an Cooling Capacity Modifier Curve Functionof Flow Fraction attached.");
    }
    return value.get();
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setAvailabilitySchedule(Schedule& schedule) {
    bool result = setSchedule(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::AvailabilitySchedule,
                              "CoilCoolingDXVariableRefrigerantFlow",
                              "Availability Schedule",
                              schedule);
    return result;
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedTotalCoolingCapacity(boost::optional<double> ratedTotalCoolingCapacity) {
    bool result(false);
    if (ratedTotalCoolingCapacity) {
      result = setDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedTotalCoolingCapacity, ratedTotalCoolingCapacity.get());
    }
    return result;
  }

  void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedTotalCoolingCapacity() {
    bool result = setString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedTotalCoolingCapacity, "autosize");
    OS_ASSERT(result);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedSensibleHeatRatio(boost::optional<double> ratedSensibleHeatRatio) {
    bool result(false);
    if (ratedSensibleHeatRatio) {
      result = setDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedSensibleHeatRatio, ratedSensibleHeatRatio.get());
    }
    return result;
  }

  void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedSensibleHeatRatio() {
    bool result = setString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedSensibleHeatRatio, "autosize");
    OS_ASSERT(result);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setRatedAirFlowRate(boost::optional<double> ratedAirFlowRate) {
    bool result(false);
    if (ratedAirFlowRate) {
      result = setDouble(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, ratedAirFlowRate.get());
    }
    return result;
  }

  void CoilCoolingDXVariableRefrigerantFlow_Impl::autosizeRatedAirFlowRate() {
    bool result = setString(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::RatedAirFlowRate, "autosize");
    OS_ASSERT(result);
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
    bool result = setPointer(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofTemperatureCurve, curve.handle());
    return result;
  }

  bool CoilCoolingDXVariableRefrigerantFlow_Impl::setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve) {
    bool result = setPointer(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityModifierCurveFunctionofFlowFraction, curve.handle());
    return result;
  }

  boost::optional<Schedule> CoilCoolingDXVariableRefrigerantFlow_Impl::optionalAvailabilitySchedule() const {
    return getObject<ModelObject>().getModelObjectTarget<Schedule>(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::AvailabilitySchedule);
  }

  boost::optional<Curve> CoilCoolingDXVariableRefrigerantFlow_Impl::optionalCoolingCapacityRatioModifierFunctionofTemperatureCurve() const {
    return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityRatioModifierFunctionofTemperatureCurve);
  }

  boost::optional<Curve> CoilCoolingDXVariableRefrigerantFlow_Impl::optionalCoolingCapacityModifierCurveFunctionofFlowFraction() const {
    return getObject<ModelObject>().getModelObjectTarget<Curve>(OS_Coil_Cooling_DX_VariableRefrigerantFlowFields::CoolingCapacityModifierCurveFunctionofFlowFraction);
  }
    
  ModelObject CoilCoolingDXVariableRefrigerantFlow_Impl::clone(Model model) const
  {
    CoilCoolingDXVariableRefrigerantFlow objectClone = HVACComponent_Impl::clone(model).cast<CoilCoolingDXVariableRefrigerantFlow>();

    Curve curveClone = coolingCapacityRatioModifierFunctionofTemperatureCurve().clone(model).cast<Curve>();
    objectClone.setCoolingCapacityRatioModifierFunctionofTemperatureCurve(curveClone);

    curveClone = coolingCapacityModifierCurveFunctionofFlowFraction().clone(model).cast<Curve>();
    objectClone.setCoolingCapacityModifierCurveFunctionofFlowFraction(curveClone);

    return objectClone;
  }

  std::vector<ModelObject> CoilCoolingDXVariableRefrigerantFlow_Impl::children() const
  {
    std::vector<ModelObject> result;

    result.push_back(coolingCapacityRatioModifierFunctionofTemperatureCurve());
    result.push_back(coolingCapacityModifierCurveFunctionofFlowFraction());

    return result;
  }

} // detail

CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(const Model& model)
  : HVACComponent(CoilCoolingDXVariableRefrigerantFlow::iddObjectType(),model)
{
  OS_ASSERT(getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>());

  Schedule schedule = model.alwaysOnDiscreteSchedule();
  setAvailabilitySchedule(schedule);

  autosizeRatedTotalCoolingCapacity();

  autosizeRatedSensibleHeatRatio();

  autosizeRatedAirFlowRate();

  CurveBiquadratic vrfTUCoolCapFT(model);
  vrfTUCoolCapFT.setName("VRFTUCoolCapFT");
  vrfTUCoolCapFT.setCoefficient1Constant(5.85884077803259E-02);
  vrfTUCoolCapFT.setCoefficient2x(5.87396532718384E-02);
  vrfTUCoolCapFT.setCoefficient3xPOW2(-2.10274979759697E-04);
  vrfTUCoolCapFT.setCoefficient4y(1.09370473889647E-02);
  vrfTUCoolCapFT.setCoefficient5yPOW2(-0.0001219549);
  vrfTUCoolCapFT.setCoefficient6xTIMESY(-0.0005246615);
  vrfTUCoolCapFT.setMinimumValueofx(15);
  vrfTUCoolCapFT.setMaximumValueofx(23.89);
  vrfTUCoolCapFT.setMinimumValueofy(20);
  vrfTUCoolCapFT.setMaximumValueofy(43.33);
  vrfTUCoolCapFT.setMinimumCurveOutput(0.8083);
  vrfTUCoolCapFT.setMaximumCurveOutput(1.2583);
  setCoolingCapacityRatioModifierFunctionofTemperatureCurve(vrfTUCoolCapFT);

  CurveQuadratic vrfACCoolCapFFF(model);
  vrfACCoolCapFFF.setName("VRFACCoolCapFFF");
  vrfACCoolCapFFF.setCoefficient1Constant(0.8);
  vrfACCoolCapFFF.setCoefficient2x(0.2);
  vrfACCoolCapFFF.setCoefficient3xPOW2(0.0);
  vrfACCoolCapFFF.setMinimumValueofx(0.5);
  vrfACCoolCapFFF.setMaximumValueofx(1.5);
  setCoolingCapacityModifierCurveFunctionofFlowFraction(vrfACCoolCapFFF);
}

IddObjectType CoilCoolingDXVariableRefrigerantFlow::iddObjectType() {
  return IddObjectType(IddObjectType::OS_Coil_Cooling_DX_VariableRefrigerantFlow);
}

Schedule CoilCoolingDXVariableRefrigerantFlow::availabilitySchedule() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->availabilitySchedule();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedTotalCoolingCapacity() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedTotalCoolingCapacity();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedTotalCoolingCapacityAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedTotalCoolingCapacityAutosized();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedSensibleHeatRatio() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedSensibleHeatRatio();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedSensibleHeatRatioAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedSensibleHeatRatioAutosized();
}

boost::optional<double> CoilCoolingDXVariableRefrigerantFlow::ratedAirFlowRate() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->ratedAirFlowRate();
}

bool CoilCoolingDXVariableRefrigerantFlow::isRatedAirFlowRateAutosized() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->isRatedAirFlowRateAutosized();
}

Curve CoilCoolingDXVariableRefrigerantFlow::coolingCapacityRatioModifierFunctionofTemperatureCurve() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->coolingCapacityRatioModifierFunctionofTemperatureCurve();
}

Curve CoilCoolingDXVariableRefrigerantFlow::coolingCapacityModifierCurveFunctionofFlowFraction() const {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->coolingCapacityModifierCurveFunctionofFlowFraction();
}

bool CoilCoolingDXVariableRefrigerantFlow::setAvailabilitySchedule(Schedule& schedule) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setAvailabilitySchedule(schedule);
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedTotalCoolingCapacity(double ratedTotalCoolingCapacity) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedTotalCoolingCapacity(ratedTotalCoolingCapacity);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedTotalCoolingCapacity() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedTotalCoolingCapacity();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedSensibleHeatRatio(double ratedSensibleHeatRatio) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedSensibleHeatRatio(ratedSensibleHeatRatio);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedSensibleHeatRatio() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedSensibleHeatRatio();
}

bool CoilCoolingDXVariableRefrigerantFlow::setRatedAirFlowRate(double ratedAirFlowRate) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setRatedAirFlowRate(ratedAirFlowRate);
}

void CoilCoolingDXVariableRefrigerantFlow::autosizeRatedAirFlowRate() {
  getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->autosizeRatedAirFlowRate();
}

bool CoilCoolingDXVariableRefrigerantFlow::setCoolingCapacityRatioModifierFunctionofTemperatureCurve(const Curve& curve) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setCoolingCapacityRatioModifierFunctionofTemperatureCurve(curve);
}

bool CoilCoolingDXVariableRefrigerantFlow::setCoolingCapacityModifierCurveFunctionofFlowFraction(const Curve& curve) {
  return getImpl<detail::CoilCoolingDXVariableRefrigerantFlow_Impl>()->setCoolingCapacityModifierCurveFunctionofFlowFraction(curve);
}

/// @cond
CoilCoolingDXVariableRefrigerantFlow::CoilCoolingDXVariableRefrigerantFlow(std::shared_ptr<detail::CoilCoolingDXVariableRefrigerantFlow_Impl> impl)
  : HVACComponent(impl)
{}
/// @endcond

} // model
} // openstudio

