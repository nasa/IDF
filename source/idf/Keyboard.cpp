#include "idf/Keyboard.hh"

namespace idf {

Keyboard::Keyboard() :
    leftCtrl(0, 1),
    leftShift(0, 1),
    leftAlt(0, 1),
    leftGui(0, 1),
    rightCtrl(0, 1),
    rightShift(0, 1),
    rightAlt(0, 1),
    rightGui(0, 1),
    a(0, 1),
    b(0, 1),
    c(0, 1),
    d(0, 1),
    e(0, 1),
    f(0, 1),
    g(0, 1),
    h(0, 1),
    i(0, 1),
    j(0, 1),
    k(0, 1),
    l(0, 1),
    m(0, 1),
    n(0, 1),
    o(0, 1),
    p(0, 1),
    q(0, 1),
    r(0, 1),
    s(0, 1),
    t(0, 1),
    u(0, 1),
    v(0, 1),
    w(0, 1),
    x(0, 1),
    y(0, 1),
    z(0, 1),
    one(0, 1),
    two(0, 1),
    three(0, 1),
    four(0, 1),
    five(0, 1),
    six(0, 1),
    seven(0, 1),
    eight(0, 1),
    nine(0, 1),
    zero(0, 1),
    enter(0, 1),
    escape(0, 1),
    backspace(0, 1),
    tab(0, 1),
    spacebar(0, 1),
    hyphen(0, 1),
    equals(0, 1),
    openBracket(0, 1),
    closeBracket(0, 1),
    backslash(0, 1),
    nonUsNumberSign(0, 1),
    colon(0, 1),
    quote(0, 1),
    grave(0, 1),
    comma(0, 1),
    period(0, 1),
    forwardSlash(0, 1),
    capsLock(0, 1),
    f1(0, 1),
    f2(0, 1),
    f3(0, 1),
    f4(0, 1),
    f5(0, 1),
    f6(0, 1),
    f7(0, 1),
    f8(0, 1),
    f9(0, 1),
    f10(0, 1),
    f11(0, 1),
    f12(0, 1),
    printScreen(0, 1),
    scrollLock(0, 1),
    pause(0, 1),
    insert(0, 1),
    home(0, 1),
    pageUp(0, 1),
    deleteForward(0, 1),
    end(0, 1),
    pageDown(0, 1),
    rightArrow(0, 1),
    leftArrow(0, 1),
    downArrow(0, 1),
    upArrow(0, 1),
    keypadNumLock(0, 1),
    keypadDivide(0, 1),
    keypadMultiply(0, 1),
    keypadSubtract(0, 1),
    keypadAdd(0, 1),
    keypadEnter(0, 1),
    keypad1(0, 1),
    keypad2(0, 1),
    keypad3(0, 1),
    keypad4(0, 1),
    keypad5(0, 1),
    keypad6(0, 1),
    keypad7(0, 1),
    keypad8(0, 1),
    keypad9(0, 1),
    keypad0(0, 1),
    keypadDecimalPoint(0, 1),
    nonUsBackslash(0, 1),
    application(0, 1),
    power(0, 1),
    keypadEquals(0, 1),
    f13(0, 1),
    f14(0, 1),
    f15(0, 1),
    f16(0, 1),
    f17(0, 1),
    f18(0, 1),
    f19(0, 1),
    f20(0, 1),
    f21(0, 1),
    f22(0, 1),
    f23(0, 1),
    f24(0, 1),
    execute(0, 1),
    help(0, 1),
    menu(0, 1),
    select(0, 1),
    stop(0, 1),
    again(0, 1),
    undo(0, 1),
    cut(0, 1),
    copy(0, 1),
    paste(0, 1),
    find(0, 1),
    mute(0, 1),
    volumeUp(0, 1),
    volumeDown(0, 1),
    lockingCapsLock(0, 1),
    lockingNumLock(0, 1),
    lockingScrollLock(0, 1),
    keypadComma(0, 1),
    keypadEqualSign(0, 1),
    international1(0, 1),
    international2(0, 1),
    international3(0, 1),
    international4(0, 1),
    international5(0, 1),
    international6(0, 1),
    international7(0, 1),
    international8(0, 1),
    international9(0, 1),
    lang1(0, 1),
    lang2(0, 1),
    lang3(0, 1),
    lang4(0, 1),
    lang5(0, 1),
    lang6(0, 1),
    lang7(0, 1),
    lang8(0, 1),
    lang9(0, 1),
    alternateErase(0, 1),
    sysReqAttention(0, 1),
    cancel(0, 1),
    clear(0, 1),
    prior(0, 1),
    returnKey(0, 1),
    separator(0, 1),
    out(0, 1),
    oper(0, 1),
    clearAgain(0, 1),
    crSelProps(0, 1),
    exSel(0, 1),
    keypad00(0, 1),
    keypad000(0, 1),
    keypadThousandsSeparator(0, 1),
    keypadDecimalSeparator(0, 1),
    keypadCurrencyUnit(0, 1),
    keypadCurrencySubunit(0, 1),
    keypadOpenParenthesis(0, 1),
    keypadCloseParenthesis(0, 1),
    keypadOpenBracket(0, 1),
    keypadCloseBracket(0, 1),
    keypadTab(0, 1),
    keypadBackspace(0, 1),
    keypadA(0, 1),
    keypadB(0, 1),
    keypadC(0, 1),
    keypadD(0, 1),
    keypadE(0, 1),
    keypadF(0, 1),
    keypadXOR(0, 1),
    keypadCaret(0, 1),
    keypadPercent(0, 1),
    keypadLessThan(0, 1),
    keypadGreaterThan(0, 1),
    keypadAnd(0, 1),
    keypadDoubleAnd(0, 1),
    keypadOr(0, 1),
    keypadDoubleOr(0, 1),
    keypadColon(0, 1),
    keypadNumberSign(0, 1),
    keypadSpace(0, 1),
    keypadAt(0, 1),
    keypadBang(0, 1),
    keypadMemoryStore(0, 1),
    keypadMemoryRecall(0, 1),
    keypadMemoryClear(0, 1),
    keypadMemoryAdd(0, 1),
    keypadMemorySubtract(0, 1),
    keypadMemoryMultiply(0, 1),
    keypadMemoryDivide(0, 1),
    keypadPlusMinus(0, 1),
    keypadClear(0, 1),
    keypadClearEntry(0, 1),
    keypadBinary(0, 1),
    keypadOctal(0, 1),
    keypadDecimal(0, 1),
    keypadHexadecimal(0, 1),
    keypadLeftControl(0, 1),
    keypadLeftShift(0, 1),
    keypadLeftAlt(0, 1),
    keypadLeftGui(0, 1),
    keypadRightControl(0, 1),
    keypadRightShift(0, 1),
    keypadRightAlt(0, 1),
    keypadRightGui(0, 1),
    map(),
    active() {

    /**
     * SingleInput::value is initialized to the neutral value, which is 0.5 in this case. This is
     * inappropriate for binary inputs, so set all keys to zero.
     */
    leftCtrl.setValue(0);
    leftShift.setValue(0);
    leftAlt.setValue(0);
    leftGui.setValue(0);
    rightCtrl.setValue(0);
    rightShift.setValue(0);
    rightAlt.setValue(0);
    rightGui.setValue(0);
    a.setValue(0);
    b.setValue(0);
    c.setValue(0);
    d.setValue(0);
    e.setValue(0);
    f.setValue(0);
    g.setValue(0);
    h.setValue(0);
    i.setValue(0);
    j.setValue(0);
    k.setValue(0);
    l.setValue(0);
    m.setValue(0);
    n.setValue(0);
    o.setValue(0);
    p.setValue(0);
    q.setValue(0);
    r.setValue(0);
    s.setValue(0);
    t.setValue(0);
    u.setValue(0);
    v.setValue(0);
    w.setValue(0);
    x.setValue(0);
    y.setValue(0);
    z.setValue(0);
    one.setValue(0);
    two.setValue(0);
    three.setValue(0);
    four.setValue(0);
    five.setValue(0);
    six.setValue(0);
    seven.setValue(0);
    eight.setValue(0);
    nine.setValue(0);
    zero.setValue(0);
    enter.setValue(0);
    escape.setValue(0);
    backspace.setValue(0);
    tab.setValue(0);
    spacebar.setValue(0);
    hyphen.setValue(0);
    equals.setValue(0);
    openBracket.setValue(0);
    closeBracket.setValue(0);
    backslash.setValue(0);
    nonUsNumberSign.setValue(0);
    colon.setValue(0);
    quote.setValue(0);
    grave.setValue(0);
    comma.setValue(0);
    period.setValue(0);
    forwardSlash.setValue(0);
    capsLock.setValue(0);
    f1.setValue(0);
    f2.setValue(0);
    f3.setValue(0);
    f4.setValue(0);
    f5.setValue(0);
    f6.setValue(0);
    f7.setValue(0);
    f8.setValue(0);
    f9.setValue(0);
    f10.setValue(0);
    f11.setValue(0);
    f12.setValue(0);
    printScreen.setValue(0);
    scrollLock.setValue(0);
    pause.setValue(0);
    insert.setValue(0);
    home.setValue(0);
    pageUp.setValue(0);
    deleteForward.setValue(0);
    end.setValue(0);
    pageDown.setValue(0);
    rightArrow.setValue(0);
    leftArrow.setValue(0);
    downArrow.setValue(0);
    upArrow.setValue(0);
    keypadNumLock.setValue(0);
    keypadDivide.setValue(0);
    keypadMultiply.setValue(0);
    keypadSubtract.setValue(0);
    keypadAdd.setValue(0);
    keypadEnter.setValue(0);
    keypad1.setValue(0);
    keypad2.setValue(0);
    keypad3.setValue(0);
    keypad4.setValue(0);
    keypad5.setValue(0);
    keypad6.setValue(0);
    keypad7.setValue(0);
    keypad8.setValue(0);
    keypad9.setValue(0);
    keypad0.setValue(0);
    keypadDecimalPoint.setValue(0);
    nonUsBackslash.setValue(0);
    application.setValue(0);
    power.setValue(0);
    keypadEquals.setValue(0);
    f13.setValue(0);
    f14.setValue(0);
    f15.setValue(0);
    f16.setValue(0);
    f17.setValue(0);
    f18.setValue(0);
    f19.setValue(0);
    f20.setValue(0);
    f21.setValue(0);
    f22.setValue(0);
    f23.setValue(0);
    f24.setValue(0);
    execute.setValue(0);
    help.setValue(0);
    menu.setValue(0);
    select.setValue(0);
    stop.setValue(0);
    again.setValue(0);
    undo.setValue(0);
    cut.setValue(0);
    copy.setValue(0);
    paste.setValue(0);
    find.setValue(0);
    mute.setValue(0);
    volumeUp.setValue(0);
    volumeDown.setValue(0);
    lockingCapsLock.setValue(0);
    lockingNumLock.setValue(0);
    lockingScrollLock.setValue(0);
    keypadComma.setValue(0);
    keypadEqualSign.setValue(0);
    international1.setValue(0);
    international2.setValue(0);
    international3.setValue(0);
    international4.setValue(0);
    international5.setValue(0);
    international6.setValue(0);
    international7.setValue(0);
    international8.setValue(0);
    international9.setValue(0);
    lang1.setValue(0);
    lang2.setValue(0);
    lang3.setValue(0);
    lang4.setValue(0);
    lang5.setValue(0);
    lang6.setValue(0);
    lang7.setValue(0);
    lang8.setValue(0);
    lang9.setValue(0);
    alternateErase.setValue(0);
    sysReqAttention.setValue(0);
    cancel.setValue(0);
    clear.setValue(0);
    prior.setValue(0);
    returnKey.setValue(0);
    separator.setValue(0);
    out.setValue(0);
    oper.setValue(0);
    clearAgain.setValue(0);
    crSelProps.setValue(0);
    exSel.setValue(0);
    keypad00.setValue(0);
    keypad000.setValue(0);
    keypadThousandsSeparator.setValue(0);
    keypadDecimalSeparator.setValue(0);
    keypadCurrencyUnit.setValue(0);
    keypadCurrencySubunit.setValue(0);
    keypadOpenParenthesis.setValue(0);
    keypadCloseParenthesis.setValue(0);
    keypadOpenBracket.setValue(0);
    keypadCloseBracket.setValue(0);
    keypadTab.setValue(0);
    keypadBackspace.setValue(0);
    keypadA.setValue(0);
    keypadB.setValue(0);
    keypadC.setValue(0);
    keypadD.setValue(0);
    keypadE.setValue(0);
    keypadF.setValue(0);
    keypadXOR.setValue(0);
    keypadCaret.setValue(0);
    keypadPercent.setValue(0);
    keypadLessThan.setValue(0);
    keypadGreaterThan.setValue(0);
    keypadAnd.setValue(0);
    keypadDoubleAnd.setValue(0);
    keypadOr.setValue(0);
    keypadDoubleOr.setValue(0);
    keypadColon.setValue(0);
    keypadNumberSign.setValue(0);
    keypadSpace.setValue(0);
    keypadAt.setValue(0);
    keypadBang.setValue(0);
    keypadMemoryStore.setValue(0);
    keypadMemoryRecall.setValue(0);
    keypadMemoryClear.setValue(0);
    keypadMemoryAdd.setValue(0);
    keypadMemorySubtract.setValue(0);
    keypadMemoryMultiply.setValue(0);
    keypadMemoryDivide.setValue(0);
    keypadPlusMinus.setValue(0);
    keypadClear.setValue(0);
    keypadClearEntry.setValue(0);
    keypadBinary.setValue(0);
    keypadOctal.setValue(0);
    keypadDecimal.setValue(0);
    keypadHexadecimal.setValue(0);
    keypadLeftControl.setValue(0);
    keypadLeftShift.setValue(0);
    keypadLeftAlt.setValue(0);
    keypadLeftGui.setValue(0);
    keypadRightControl.setValue(0);
    keypadRightShift.setValue(0);
    keypadRightAlt.setValue(0);
    keypadRightGui.setValue(0);

    map[0x04] = &a;
    map[0x05] = &b;
    map[0x06] = &c;
    map[0x07] = &d;
    map[0x08] = &e;
    map[0x09] = &f;
    map[0x0A] = &g;
    map[0x0B] = &h;
    map[0x0C] = &i;
    map[0x0D] = &j;
    map[0x0E] = &k;
    map[0x0F] = &l;
    map[0x10] = &m;
    map[0x11] = &n;
    map[0x12] = &o;
    map[0x13] = &p;
    map[0x14] = &q;
    map[0x15] = &r;
    map[0x16] = &s;
    map[0x17] = &t;
    map[0x18] = &u;
    map[0x19] = &v;
    map[0x1A] = &w;
    map[0x1B] = &x;
    map[0x1C] = &y;
    map[0x1D] = &z;
    map[0x1E] = &one;
    map[0x1F] = &two;
    map[0x20] = &three;
    map[0x21] = &four;
    map[0x22] = &five;
    map[0x23] = &six;
    map[0x24] = &seven;
    map[0x25] = &eight;
    map[0x26] = &nine;
    map[0x27] = &zero;
    map[0x28] = &enter;
    map[0x29] = &escape;
    map[0x2A] = &backspace;
    map[0x2B] = &tab;
    map[0x2C] = &spacebar;
    map[0x2D] = &hyphen;
    map[0x2E] = &equals;
    map[0x2F] = &openBracket;
    map[0x30] = &closeBracket;
    map[0x31] = &backslash;
    map[0x32] = &nonUsNumberSign;
    map[0x33] = &colon;
    map[0x34] = &quote;
    map[0x35] = &grave;
    map[0x36] = &comma;
    map[0x37] = &period;
    map[0x38] = &forwardSlash;
    map[0x39] = &capsLock;
    map[0x3A] = &f1;
    map[0x3B] = &f2;
    map[0x3C] = &f3;
    map[0x3D] = &f4;
    map[0x3E] = &f5;
    map[0x3F] = &f6;
    map[0x40] = &f7;
    map[0x41] = &f8;
    map[0x42] = &f9;
    map[0x43] = &f10;
    map[0x44] = &f11;
    map[0x45] = &f12;
    map[0x46] = &printScreen;
    map[0x47] = &scrollLock;
    map[0x48] = &pause;
    map[0x49] = &insert;
    map[0x4A] = &home;
    map[0x4B] = &pageUp;
    map[0x4C] = &deleteForward;
    map[0x4D] = &end;
    map[0x4E] = &pageDown;
    map[0x4F] = &rightArrow;
    map[0x50] = &leftArrow;
    map[0x51] = &downArrow;
    map[0x52] = &upArrow;
    map[0x53] = &keypadNumLock;
    map[0x54] = &keypadDivide;
    map[0x55] = &keypadMultiply;
    map[0x56] = &keypadSubtract;
    map[0x57] = &keypadAdd;
    map[0x58] = &keypadEnter;
    map[0x59] = &keypad1;
    map[0x5A] = &keypad2;
    map[0x5B] = &keypad3;
    map[0x5C] = &keypad4;
    map[0x5D] = &keypad5;
    map[0x5E] = &keypad6;
    map[0x5F] = &keypad7;
    map[0x60] = &keypad8;
    map[0x61] = &keypad9;
    map[0x62] = &keypad0;
    map[0x63] = &keypadDecimalPoint;
    map[0x64] = &nonUsBackslash;
    map[0x65] = &application;
    map[0x66] = &power;
    map[0x67] = &keypadEquals;
    map[0x68] = &f13;
    map[0x69] = &f14;
    map[0x6A] = &f15;
    map[0x6B] = &f16;
    map[0x6C] = &f17;
    map[0x6D] = &f18;
    map[0x6E] = &f19;
    map[0x6F] = &f20;
    map[0x70] = &f21;
    map[0x71] = &f22;
    map[0x72] = &f23;
    map[0x73] = &f24;
    map[0x74] = &execute;
    map[0x75] = &help;
    map[0x76] = &menu;
    map[0x77] = &select;
    map[0x78] = &stop;
    map[0x79] = &again;
    map[0x7A] = &undo;
    map[0x7B] = &cut;
    map[0x7C] = &copy;
    map[0x7D] = &paste;
    map[0x7E] = &find;
    map[0x7F] = &mute;
    map[0x80] = &volumeUp;
    map[0x81] = &volumeDown;
    map[0x82] = &lockingCapsLock;
    map[0x83] = &lockingNumLock;
    map[0x84] = &lockingScrollLock;
    map[0x85] = &keypadComma;
    map[0x86] = &keypadEqualSign;
    map[0x87] = &international1;
    map[0x88] = &international2;
    map[0x89] = &international3;
    map[0x8A] = &international4;
    map[0x8B] = &international5;
    map[0x8C] = &international6;
    map[0x8D] = &international7;
    map[0x8E] = &international8;
    map[0x8F] = &international9;
    map[0x90] = &lang1;
    map[0x91] = &lang2;
    map[0x92] = &lang3;
    map[0x93] = &lang4;
    map[0x94] = &lang5;
    map[0x95] = &lang6;
    map[0x96] = &lang7;
    map[0x97] = &lang8;
    map[0x98] = &lang9;
    map[0x99] = &alternateErase;
    map[0x9A] = &sysReqAttention;
    map[0x9B] = &cancel;
    map[0x9C] = &clear;
    map[0x9D] = &prior;
    map[0x9E] = &returnKey;
    map[0x9F] = &separator;
    map[0xA0] = &out;
    map[0xA1] = &oper;
    map[0xA2] = &clearAgain;
    map[0xA3] = &crSelProps;
    map[0xA4] = &exSel;
    map[0xB0] = &keypad00;
    map[0xB1] = &keypad000;
    map[0xB2] = &keypadThousandsSeparator;
    map[0xB3] = &keypadDecimalSeparator;
    map[0xB4] = &keypadCurrencyUnit;
    map[0xB5] = &keypadCurrencySubunit;
    map[0xB6] = &keypadOpenParenthesis;
    map[0xB7] = &keypadCloseParenthesis;
    map[0xB8] = &keypadOpenBracket;
    map[0xB9] = &keypadCloseBracket;
    map[0xBA] = &keypadTab;
    map[0xBB] = &keypadBackspace;
    map[0xBC] = &keypadA;
    map[0xBD] = &keypadB;
    map[0xBE] = &keypadC;
    map[0xBF] = &keypadD;
    map[0xC0] = &keypadE;
    map[0xC1] = &keypadF;
    map[0xC2] = &keypadXOR;
    map[0xC3] = &keypadCaret;
    map[0xC4] = &keypadPercent;
    map[0xC5] = &keypadLessThan;
    map[0xC6] = &keypadGreaterThan;
    map[0xC7] = &keypadAnd;
    map[0xC8] = &keypadDoubleAnd;
    map[0xC9] = &keypadOr;
    map[0xCA] = &keypadDoubleOr;
    map[0xCB] = &keypadColon;
    map[0xCC] = &keypadNumberSign;
    map[0xCD] = &keypadSpace;
    map[0xCE] = &keypadAt;
    map[0xCF] = &keypadBang;
    map[0xD0] = &keypadMemoryStore;
    map[0xD1] = &keypadMemoryRecall;
    map[0xD2] = &keypadMemoryClear;
    map[0xD3] = &keypadMemoryAdd;
    map[0xD4] = &keypadMemorySubtract;
    map[0xD5] = &keypadMemoryMultiply;
    map[0xD6] = &keypadMemoryDivide;
    map[0xD7] = &keypadPlusMinus;
    map[0xD8] = &keypadClear;
    map[0xD9] = &keypadClearEntry;
    map[0xDA] = &keypadBinary;
    map[0xDB] = &keypadOctal;
    map[0xDC] = &keypadDecimal;
    map[0xDD] = &keypadHexadecimal;
    map[0xE0] = &keypadLeftControl;
    map[0xE1] = &keypadLeftShift;
    map[0xE2] = &keypadLeftAlt;
    map[0xE3] = &keypadLeftGui;
    map[0xE4] = &keypadRightControl;
    map[0xE5] = &keypadRightShift;
    map[0xE6] = &keypadRightAlt;
    map[0xE7] = &keypadRightGui;

    descriptions[&leftCtrl] = "Left Ctrl";
    descriptions[&leftShift] = "Left Shift";
    descriptions[&leftAlt] = "Left Alt";
    descriptions[&leftGui] = "Left GUI";
    descriptions[&rightCtrl] = "Right Ctrl";
    descriptions[&rightShift] = "Right Shift";
    descriptions[&rightAlt] = "Right Alt";
    descriptions[&rightGui] = "Right GUI";
    descriptions[&a] = "A";
    descriptions[&b] = "B";
    descriptions[&c] = "C";
    descriptions[&d] = "D";
    descriptions[&e] = "E";
    descriptions[&f] = "F";
    descriptions[&g] = "G";
    descriptions[&h] = "H";
    descriptions[&i] = "I";
    descriptions[&j] = "J";
    descriptions[&k] = "K";
    descriptions[&l] = "L";
    descriptions[&m] = "M";
    descriptions[&n] = "N";
    descriptions[&o] = "O";
    descriptions[&p] = "P";
    descriptions[&q] = "Q";
    descriptions[&r] = "R";
    descriptions[&s] = "S";
    descriptions[&t] = "T";
    descriptions[&u] = "U";
    descriptions[&v] = "V";
    descriptions[&w] = "W";
    descriptions[&x] = "X";
    descriptions[&y] = "Y";
    descriptions[&z] = "Z";
    descriptions[&one] = "1";
    descriptions[&two] = "2";
    descriptions[&three] = "3";
    descriptions[&four] = "4";
    descriptions[&five] = "5";
    descriptions[&six] = "6";
    descriptions[&seven] = "7";
    descriptions[&eight] = "8";
    descriptions[&nine] = "9";
    descriptions[&zero] = "0";
    descriptions[&enter] = "Enter";
    descriptions[&escape] = "Escape";
    descriptions[&backspace] = "Backspace";
    descriptions[&tab] = "Tab";
    descriptions[&spacebar] = "Spacebar";
    descriptions[&hyphen] = "-";
    descriptions[&equals] = "=";
    descriptions[&openBracket] = "[";
    descriptions[&closeBracket] = "]";
    descriptions[&backslash] = "\\";
    descriptions[&nonUsNumberSign] = "non-US #";
    descriptions[&colon] = ";";
    descriptions[&quote] = "'";
    descriptions[&grave] = "`";
    descriptions[&comma] = ",";
    descriptions[&period] = ".";
    descriptions[&forwardSlash] = "/";
    descriptions[&capsLock] = "Caps Lock";
    descriptions[&f1] = "F1";
    descriptions[&f2] = "F2";
    descriptions[&f3] = "F3";
    descriptions[&f4] = "F4";
    descriptions[&f5] = "F5";
    descriptions[&f6] = "F6";
    descriptions[&f7] = "F7";
    descriptions[&f8] = "F8";
    descriptions[&f9] = "F9";
    descriptions[&f10] = "F10";
    descriptions[&f11] = "F11";
    descriptions[&f12] = "F12";
    descriptions[&printScreen] = "Print Screen";
    descriptions[&scrollLock] = "Scroll Lock";
    descriptions[&pause] = "Pause";
    descriptions[&insert] = "Insert";
    descriptions[&home] = "Home";
    descriptions[&pageUp] = "Page Up";
    descriptions[&deleteForward] = "Delete";
    descriptions[&end] = "End";
    descriptions[&pageDown] = "Page Down";
    descriptions[&rightArrow] = "Right Arrow";
    descriptions[&leftArrow] = "Left Arrow";
    descriptions[&downArrow] = "Down Arrow";
    descriptions[&upArrow] = "Up Arrow";
    descriptions[&keypadNumLock] = "Keypad Num Lock";
    descriptions[&keypadDivide] = "Keypad /";
    descriptions[&keypadMultiply] = "Keypad *";
    descriptions[&keypadSubtract] = "Keypad -";
    descriptions[&keypadAdd] = "Keypad +";
    descriptions[&keypadEnter] = "Keypad Enter";
    descriptions[&keypad1] = "Keypad 1";
    descriptions[&keypad2] = "Keypad 2";
    descriptions[&keypad3] = "Keypad 3";
    descriptions[&keypad4] = "Keypad 4";
    descriptions[&keypad5] = "Keypad 5";
    descriptions[&keypad6] = "Keypad 6";
    descriptions[&keypad7] = "Keypad 7";
    descriptions[&keypad8] = "Keypad 8";
    descriptions[&keypad9] = "Keypad 9";
    descriptions[&keypad0] = "Keypad 0";
    descriptions[&keypadDecimalPoint] = "Keypad .";
    descriptions[&nonUsBackslash] = "non-US \\";
    descriptions[&application] = "Application";
    descriptions[&power] = "Power";
    descriptions[&keypadEquals] = "Keypad =";
    descriptions[&f13] = "F13";
    descriptions[&f14] = "F14";
    descriptions[&f15] = "F15";
    descriptions[&f16] = "F16";
    descriptions[&f17] = "F17";
    descriptions[&f18] = "F18";
    descriptions[&f19] = "F19";
    descriptions[&f20] = "F20";
    descriptions[&f21] = "F21";
    descriptions[&f22] = "F22";
    descriptions[&f23] = "F23";
    descriptions[&f24] = "F24";
    descriptions[&execute] = "Execute";
    descriptions[&help] = "Help";
    descriptions[&menu] = "Menu";
    descriptions[&select] = "Select";
    descriptions[&stop] = "Stop";
    descriptions[&again] = "Again";
    descriptions[&undo] = "Undo";
    descriptions[&cut] = "Cut";
    descriptions[&copy] = "Copy";
    descriptions[&paste] = "Paste";
    descriptions[&find] = "Find";
    descriptions[&mute] = "Mute";
    descriptions[&volumeUp] = "Volume Up";
    descriptions[&volumeDown] = "Volume Down";
    descriptions[&lockingCapsLock] = "Locking Caps Lock";
    descriptions[&lockingNumLock] = "Locking Num Lock";
    descriptions[&lockingScrollLock] = "Locking Scroll Lock";
    descriptions[&keypadComma] = "Keypad ,";
    descriptions[&keypadEqualSign] = "Keypad Equal Sign";
    descriptions[&international1] = "International 1";
    descriptions[&international2] = "International 2";
    descriptions[&international3] = "International 3";
    descriptions[&international4] = "International 4";
    descriptions[&international5] = "International 5";
    descriptions[&international6] = "International 6";
    descriptions[&international7] = "International 7";
    descriptions[&international8] = "International 8";
    descriptions[&international9] = "International 9";
    descriptions[&lang1] = "Lang 1";
    descriptions[&lang2] = "Lang 2";
    descriptions[&lang3] = "Lang 3";
    descriptions[&lang4] = "Lang 4";
    descriptions[&lang5] = "Lang 5";
    descriptions[&lang6] = "Lang 6";
    descriptions[&lang7] = "Lang 7";
    descriptions[&lang8] = "Lang 8";
    descriptions[&lang9] = "Lang 9";
    descriptions[&alternateErase] = "Alternate Erase";
    descriptions[&sysReqAttention] = "SysReq/Attention";
    descriptions[&cancel] = "Cancel";
    descriptions[&clear] = "Clear";
    descriptions[&prior] = "Prior";
    descriptions[&returnKey] = "Return Key";
    descriptions[&separator] = "Separator";
    descriptions[&out] = "Out";
    descriptions[&oper] = "Oper";
    descriptions[&clearAgain] = "Clear AGain";
    descriptions[&crSelProps] = "CrSel/Props";
    descriptions[&exSel] = "ExSel";
    descriptions[&keypad00] = "Keypad 00";
    descriptions[&keypad000] = "Keypad 000";
    descriptions[&keypadThousandsSeparator] = "Keypad Thousands Separator";
    descriptions[&keypadDecimalSeparator] = "Keypad Decimal Separator";
    descriptions[&keypadCurrencyUnit] = "Keypad Currency Unit";
    descriptions[&keypadCurrencySubunit] = "Keypad Currency Subunit";
    descriptions[&keypadOpenParenthesis] = "Keypad (";
    descriptions[&keypadCloseParenthesis] = "Keypad )";
    descriptions[&keypadOpenBracket] = "Keypad {";
    descriptions[&keypadCloseBracket] = "Keypad }";
    descriptions[&keypadTab] = "Keypad Tab";
    descriptions[&keypadBackspace] = "Keypad Backspace";
    descriptions[&keypadA] = "Keypad A";
    descriptions[&keypadB] = "Keypad B";
    descriptions[&keypadC] = "Keypad C";
    descriptions[&keypadD] = "Keypad D";
    descriptions[&keypadE] = "Keypad E";
    descriptions[&keypadF] = "Keypad F";
    descriptions[&keypadXOR] = "Keypad XOR";
    descriptions[&keypadCaret] = "Keypad ^";
    descriptions[&keypadPercent] = "Keypad %";
    descriptions[&keypadLessThan] = "Keypad <";
    descriptions[&keypadGreaterThan] = "Keypad >";
    descriptions[&keypadAnd] = "Keypad &";
    descriptions[&keypadDoubleAnd] = "Keypad &&";
    descriptions[&keypadOr] = "Keypad |";
    descriptions[&keypadDoubleOr] = "Keypad ||";
    descriptions[&keypadColon] = "Keypad :";
    descriptions[&keypadNumberSign] = "Keypad #";
    descriptions[&keypadSpace] = "Keypad Space";
    descriptions[&keypadAt] = "Keypad @";
    descriptions[&keypadBang] = "Keypad !";
    descriptions[&keypadMemoryStore] = "Keypad Memory Store";
    descriptions[&keypadMemoryRecall] = "Keypad Memory Recall";
    descriptions[&keypadMemoryClear] = "Keypad Memory Clear";
    descriptions[&keypadMemoryAdd] = "Keypad Memory Add";
    descriptions[&keypadMemorySubtract] = "Keypad Memory Subtract";
    descriptions[&keypadMemoryMultiply] = "Keypad Memory Multiply";
    descriptions[&keypadMemoryDivide] = "Keypad Memory Divide";
    descriptions[&keypadPlusMinus] = "Keypad +/-";
    descriptions[&keypadClear] = "Keypad Clear";
    descriptions[&keypadClearEntry] = "Keypad Clear Entry";
    descriptions[&keypadBinary] = "Keypad Binary";
    descriptions[&keypadOctal] = "Keypad Octal";
    descriptions[&keypadDecimal] = "Keypad Decimal";
    descriptions[&keypadHexadecimal] = "Keypad Hexadecimal";
    descriptions[&keypadLeftControl] = "Keypad Left Control";
    descriptions[&keypadLeftShift] = "Keypad Left Shift";
    descriptions[&keypadLeftAlt] = "Keypad Left Alt";
    descriptions[&keypadLeftGui] = "Keypad Left GUI";
    descriptions[&keypadRightControl] = "Keypad Right Control";
    descriptions[&keypadRightShift] = "Keypad Right Shift";
    descriptions[&keypadRightAlt] = "Keypad Right Alt";
    descriptions[&keypadRightGui] = "Keypad Right GUI";
}

std::string Keyboard::getActiveDescription() {
    std::string result;
    if (leftCtrl.getValue() > 0.9) {
        result += descriptions[&leftCtrl] + "\n";
    }
    if (leftShift.getValue() > 0.9) {
        result += descriptions[&leftShift] + "\n";
    }
    if (leftAlt.getValue() > 0.9) {
        result += descriptions[&leftAlt] + "\n";
    }
    if (leftGui.getValue() > 0.9) {
        result += descriptions[&leftGui] + "\n";
    }
    if (rightCtrl.getValue() > 0.9) {
        result += descriptions[&rightCtrl] + "\n";
    }
    if (rightShift.getValue() > 0.9) {
        result += descriptions[&rightShift] + "\n";
    }
    if (rightAlt.getValue() > 0.9) {
        result += descriptions[&rightAlt] + "\n";
    }
    if (rightGui.getValue() > 0.9) {
        result += descriptions[&rightGui] + "\n";
    }
    for (std::vector<SingleInput*>::iterator it = active.begin(); it != active.end(); ++it) {
        result += descriptions[*it] + "\n";
    }
    return result;
}

}
