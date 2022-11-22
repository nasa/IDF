/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/ThrustMasterJoystickHotas.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/ThrustMasterJoystickHotas.cpp}
 */

#ifndef THRUSTMASTER_JOYSTICK_HOTAS_HH
#define THRUSTMASTER_JOYSTICK_HOTAS_HH

#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %ThrustMaster Joystick Hotas
 *
 * @author Philip Kunz
 */
class ThrustMasterJoystickHotas : public virtual InputLayout {

    public:

    /** constructor */
    ThrustMasterJoystickHotas();

    /** destructor */
    virtual ~ThrustMasterJoystickHotas() {};

    /** forward-backward pivoting */
    SingleInput forwardBackwardPivot;

    /** left-right pivoting */
    SingleInput leftRightPivot;

    /** trigger */
    SingleInput trigger;

    /** trigger */
    SingleInput triggerStage2;

    /** buttons */
    SingleInput button2;
    SingleInput button3;
    SingleInput button4;
    SingleInput button5;
    SingleInput button19;


    /** hat1 directions */
    SingleInput hat1UpDownPivot;
    SingleInput hat1LeftRightPivot;
    SingleInput hat1North;
    SingleInput hat1NorthEast;
    SingleInput hat1East;
    SingleInput hat1SouthEast;
    SingleInput hat1South;
    SingleInput hat1SouthWest;
    SingleInput hat1West;
    SingleInput hat1NorthWest;

    /** hat2 directions */
    SingleInput hat2UpDownPivot;
    SingleInput hat2LeftRightPivot;
    SingleInput hat2North;
    SingleInput hat2NorthEast;
    SingleInput hat2East;
    SingleInput hat2SouthEast;
    SingleInput hat2South;
    SingleInput hat2SouthWest;
    SingleInput hat2West;
    SingleInput hat2NorthWest;

    /** hat3 directions */
    SingleInput hat3UpDownPivot;
    SingleInput hat3LeftRightPivot;
    SingleInput hat3North;
    SingleInput hat3NorthEast;
    SingleInput hat3East;
    SingleInput hat3SouthEast;
    SingleInput hat3South;
    SingleInput hat3SouthWest;
    SingleInput hat3West;
    SingleInput hat3NorthWest;

    /** hat4 directions */
    SingleInput hat4UpDownPivot;
    SingleInput hat4LeftRightPivot;
    SingleInput hat4North;
    SingleInput hat4East;
    SingleInput hat4South;
    SingleInput hat4West;

    protected:

    virtual const std::vector<Configurable>& getConfigurables();

};

}

#endif
