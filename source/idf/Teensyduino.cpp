#include "idf/Teensyduino.hh"

namespace idf {

Teensyduino::Teensyduino() : 
    button1(0, 1),
    button2(0, 1),
    button3(0, 1),
    button4(0, 1),
    button5(0, 1),
    button6(0, 1),
    button7(0, 1),
    button8(0, 1),
    button9(0, 1),
    button10(0, 1),
    button11(0, 1),
    button12(0, 1),
    button13(0, 1),
    button14(0, 1),
    button15(0, 1),
    button16(0, 1),
    button17(0, 1),
    button18(0, 1),
    button19(0, 1),
    button20(0, 1),
    button21(0, 1),
    button22(0, 1),
    button23(0, 1),
    button24(0, 1),
    button25(0, 1),
    button26(0, 1),
    button27(0, 1),
    button28(0, 1),
    button29(0, 1),
    button30(0, 1),
    button31(0, 1),
    button32(0, 1),
    x(0, 1023, 512),
    y(0, 1023, 512),
    z(0, 1023, 512),
    zRotate(0, 1023, 512),
    sliderLeft(0, 1023, 512),
    sliderRight(0, 1023, 512),
    hatNorth(0, 1),
    hatNorthEast(0, 1),
    hatEast(0, 1),
    hatSouthEast(0, 1),
    hatSouth(0, 1),
    hatSouthWest(0, 1),
    hatWest(0, 1),
    hatNorthWest(0, 1) {}

const std::vector<InputLayout::Configurable>& Teensyduino::getConfigurables() {
    static std::vector<Configurable> inputs;
    if (inputs.empty()) {
        append(InputLayout::getConfigurables(), inputs);
        inputs.push_back(Configurable(x, "X-Axis", "x"));
        inputs.push_back(Configurable(y, "Y-Axis", "y"));
        inputs.push_back(Configurable(z, "Z-Axis", "z"));
        inputs.push_back(Configurable(zRotate, "Z-Rotate Axis", "zRotate"));
        inputs.push_back(Configurable(sliderLeft, "Left Slider", "sliderLeft"));
        inputs.push_back(Configurable(sliderRight, "Right Slider", "sliderRight"));
    }
    return inputs;
}

}
