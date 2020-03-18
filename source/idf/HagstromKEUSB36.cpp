#include "idf/HagstromKEUSB36.hh"

namespace idf {

HagstromKEUSB36::HagstromKEUSB36() :
    input1(0, 1),
    input2(0, 1),
    input3(0, 1),
    input4(0, 1),
    input5(0, 1),
    input6(0, 1),
    input7(0, 1),
    input8(0, 1),
    input9(0, 1),
    input10(0, 1),
    input11(0, 1),
    input12(0, 1),
    input13(0, 1),
    input14(0, 1),
    input15(0, 1),
    input16(0, 1),
    input17(0, 1),
    input18(0, 1),
    input19(0, 1),
    input20(0, 1),
    input21(0, 1),
    input22(0, 1),
    input23(0, 1),
    input24(0, 1),
    input25(0, 1),
    input26(0, 1),
    input27(0, 1),
    input28(0, 1),
    input29(0, 1),
    input30(0, 1),
    input31(0, 1),
    input32(0, 1),
    input33(0, 1),
    input34(0, 1),
    input35(0, 1),
    input36(0, 1) {
    map[4]  = &input1;
    map[5]  = &input2;
    map[6]  = &input3;
    map[7]  = &input4;
    map[8]  = &input5;
    map[9]  = &input6;
    map[10] = &input7;
    map[11] = &input8;
    map[12] = &input9;
    map[13] = &input10;
    map[14] = &input11;
    map[15] = &input12;
    map[16] = &input13;
    map[17] = &input14;
    map[18] = &input15;
    map[19] = &input16;
    map[20] = &input17;
    map[21] = &input18;
    map[22] = &input19;
    map[23] = &input20;
    map[24] = &input21;
    map[25] = &input22;
    map[26] = &input23;
    map[27] = &input24;
    map[28] = &input25;
    map[29] = &input26;
    map[30] = &input27;
    map[31] = &input28;
    map[32] = &input29;
    map[33] = &input30;
    map[34] = &input31;
    map[35] = &input32;
    map[36] = &input33;
    map[37] = &input34;
    map[38] = &input35;
    map[39] = &input36;

    inputs.push_back(&input1);
    inputs.push_back(&input2);
    inputs.push_back(&input3);
    inputs.push_back(&input4);
    inputs.push_back(&input5);
    inputs.push_back(&input6);
    inputs.push_back(&input7);
    inputs.push_back(&input8);
    inputs.push_back(&input9);
    inputs.push_back(&input10);
    inputs.push_back(&input11);
    inputs.push_back(&input12);
    inputs.push_back(&input13);
    inputs.push_back(&input14);
    inputs.push_back(&input15);
    inputs.push_back(&input16);
    inputs.push_back(&input17);
    inputs.push_back(&input18);
    inputs.push_back(&input19);
    inputs.push_back(&input20);
    inputs.push_back(&input21);
    inputs.push_back(&input22);
    inputs.push_back(&input23);
    inputs.push_back(&input24);
    inputs.push_back(&input25);
    inputs.push_back(&input26);
    inputs.push_back(&input27);
    inputs.push_back(&input28);
    inputs.push_back(&input29);
    inputs.push_back(&input30);
    inputs.push_back(&input31);
    inputs.push_back(&input32);
    inputs.push_back(&input33);
    inputs.push_back(&input34);
    inputs.push_back(&input35);
    inputs.push_back(&input36);
}

const std::vector<SingleInput*>& HagstromKEUSB36::getInputs() const {
    return inputs;
}

}
