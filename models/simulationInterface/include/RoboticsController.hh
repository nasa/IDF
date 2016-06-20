/**
 * @trick_parse{everything}
 */

#ifndef _ROBOTICS_CONTROLLER_FEATURE_HH_
#define _ROBOTICS_CONTROLLER_FEATURE_HH_

#include <functional>
#include "simulationInterface/include/Controller.hh"
#include "simulationInterface/include/Feature.hh"

namespace idf {

class RoboticsController;

class RoboticsBase {

    protected:

    template<typename T>
    class Feature : public idf::Feature<T, RoboticsController> {

        public:

        Feature(const std::function<T (const RoboticsController&)>& function) :
            idf::Feature<T, RoboticsController>(function) {}

    };

};

template<>
struct ControllerTraits<RoboticsController> {
    template<class T>
    using Feature = RoboticsBase::Feature<T>;
};

class RoboticsController : public RoboticsBase, public Controller<RoboticsController> {

    public:

    static const Feature<bool> RATE_MODE;

    private:

    /** the rate mode returned by getRateMode() when inactive */
    bool inactiveRateMode;

};

}

#endif
