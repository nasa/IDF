/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/HagstromKEUSB36.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/HagstromKEUSB36.cpp}
 */

#ifndef HAGSTROM_KEUSB36_HH
#define HAGSTROM_KEUSB36_HH

#include <map>
#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

// %HagstromKEUSB36 input layout
class HagstromKEUSB36 : public virtual InputLayout {

    public:

    /** constructor */
    HagstromKEUSB36();

    /** header pin 1 */
    SingleInput input1;

    /** header pin 2 */
    SingleInput input2;

    /** header pin 3 */
    SingleInput input3;

    /** header pin 4 */
    SingleInput input4;

    /** header pin 5 */
    SingleInput input5;

    /** header pin 6 */
    SingleInput input6;

    /** header pin 7 */
    SingleInput input7;

    /** header pin 8 */
    SingleInput input8;

    /** header pin 9 */
    SingleInput input9;

    /** header pin 10 */
    SingleInput input10;

    /** header pin 11 */
    SingleInput input11;

    /** header pin 12 */
    SingleInput input12;

    /** header pin 13 */
    SingleInput input13;

    /** header pin 14 */
    SingleInput input14;

    /** header pin 15 */
    SingleInput input15;

    /** header pin 16 */
    SingleInput input16;

    /** header pin 17 */
    SingleInput input17;

    /** header pin 18 */
    SingleInput input18;

    /** header pin 19 */
    SingleInput input19;

    /** header pin 20 */
    SingleInput input20;

    /** header pin 21 */
    SingleInput input21;

    /** header pin 22 */
    SingleInput input22;

    /** header pin 23 */
    SingleInput input23;

    /** header pin 24 */
    SingleInput input24;

    /** header pin 25 */
    SingleInput input25;

    /** header pin 26 */
    SingleInput input26;

    /** header pin 27 */
    SingleInput input27;

    /** header pin 28 */
    SingleInput input28;

    /** header pin 29 */
    SingleInput input29;

    /** header pin 30 */
    SingleInput input30;

    /** header pin 31 */
    SingleInput input31;

    /** header pin 32 */
    SingleInput input32;

    /** header pin 33 */
    SingleInput input33;

    /** header pin 34 */
    SingleInput input34;

    /** header pin 35 */
    SingleInput input35;

    /** header pin 36 */
    SingleInput input36;

    /**
     * gets a vector of all inputs in order
     *
     * @return a vector of the inputs
     */
    const std::vector<SingleInput*>& getInputs() const;

    protected:

    /** maps byte values to header pins */
    std::map<int, SingleInput*> map;

    /** all inputs together for ease of iteration */
    std::vector<SingleInput*> inputs;

};

}

#endif
