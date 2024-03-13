/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/Keyboard.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/Keyboard.cpp}
 */

#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include <map>
#include "idf/InputLayout.hh"
#include "idf/SingleInput.hh"

namespace idf {

/**
 * %Keyboard input layout
 *
 * See https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf,
 * "Section 10 Keyboard/Keypad Page" for byte to key mapping.
 */
class Keyboard : public virtual InputLayout {

    public:

    /** constructor */
    Keyboard();

    /** left Ctrl */
    SingleInput leftCtrl;

    /** left Shift */
    SingleInput leftShift;

    /** left Alt */
    SingleInput leftAlt;

    /** left Gui (Windows key) */
    SingleInput leftGui;

    /** right Ctrl */
    SingleInput rightCtrl;

    /** right Shift */
    SingleInput rightShift;

    /** right Alt */
    SingleInput rightAlt;

    /** right Gui (Windows key) */
    SingleInput rightGui;

    /** a and A */
    SingleInput a;

    /** b and B */
    SingleInput b;

    /** c and C */
    SingleInput c;

    /** d and D */
    SingleInput d;

    /** e and E */
    SingleInput e;

    /** f and F */
    SingleInput f;

    /** g and G */
    SingleInput g;

    /** h and H */
    SingleInput h;

    /** i and I */
    SingleInput i;

    /** j and J */
    SingleInput j;

    /** k and K */
    SingleInput k;

    /** l and L */
    SingleInput l;

    /** m and M */
    SingleInput m;

    /** n and N */
    SingleInput n;

    /** o and O */
    SingleInput o;

    /** p and P */
    SingleInput p;

    /** q and Q */
    SingleInput q;

    /** r and R */
    SingleInput r;

    /** s and S */
    SingleInput s;

    /** t and T */
    SingleInput t;

    /** u and U */
    SingleInput u;

    /** v and V */
    SingleInput v;

    /** w and W */
    SingleInput w;

    /** x and X */
    SingleInput x;

    /** y and Y */
    SingleInput y;

    /** z and Z */
    SingleInput z;

    /** 1 and ! */
    SingleInput one;

    /** 2 and @ */
    SingleInput two;

    /** 3 and # */
    SingleInput three;

    /** 4 and $ */
    SingleInput four;

    /** 5 and % */
    SingleInput five;

    /** 6 and ^ */
    SingleInput six;

    /** 7 and & */
    SingleInput seven;

    /** 8 and * */
    SingleInput eight;

    /** 9 and ( */
    SingleInput nine;

    /** 0 and ) */
    SingleInput zero;

    /** return (enter) */
    SingleInput enter;

    /** escape */
    SingleInput escape;

    /** delete (backspace - backs up the cursor one position, deleting a character as it goes)  */
    SingleInput backspace;

    /** tab */
    SingleInput tab;

    /** spacebar */
    SingleInput spacebar;

    /** - and _ */
    SingleInput hyphen;

    /** = and + */
    SingleInput equals;

    /** [ and { */
    SingleInput openBracket;

    /** ] and } */
    SingleInput closeBracket;

    /** \ and | */
    SingleInput backslash;

    /** non-US # and ~ */
    SingleInput nonUsNumberSign;

    /** ; and : */
    SingleInput colon;

    /** ' and " */
    SingleInput quote;

    /** ` and ~ */
    SingleInput grave;

    /** , and < */
    SingleInput comma;

    /** \. and > */
    SingleInput period;

    /** / and ? */
    SingleInput forwardSlash;

    /** caps lock */
    SingleInput capsLock;

    /** F1 */
    SingleInput f1;

    /** F2 */
    SingleInput f2;

    /** F3 */
    SingleInput f3;

    /** F4 */
    SingleInput f4;

    /** F5 */
    SingleInput f5;

    /** F6 */
    SingleInput f6;

    /** F7 */
    SingleInput f7;

    /** F8 */
    SingleInput f8;

    /** F9 */
    SingleInput f9;

    /** F10 */
    SingleInput f10;

    /** F11 */
    SingleInput f11;

    /** F12 */
    SingleInput f12;

    /** print screen  */
    SingleInput printScreen;

    /** scroll lock */
    SingleInput scrollLock;

    /** pause */
    SingleInput pause;

    /** insert */
    SingleInput insert;

    /** home */
    SingleInput home;

    /** page up */
    SingleInput pageUp;

    /** delete forward (deletes one character without changing position) */
    SingleInput deleteForward;

    /** end */
    SingleInput end;

    /** page down */
    SingleInput pageDown;

    /** right arrow */
    SingleInput rightArrow;

    /** left arrow */
    SingleInput leftArrow;

    /** down arrow */
    SingleInput downArrow;

    /** up arrow */
    SingleInput upArrow;

    /** keypad num lock and clear */
    SingleInput keypadNumLock;

    /** keypad divide */
    SingleInput keypadDivide;

    /** keypad multiply */
    SingleInput keypadMultiply;

    /** keypad subtract */
    SingleInput keypadSubtract;

    /** keypad add */
    SingleInput keypadAdd;

    /** keypad enter */
    SingleInput keypadEnter;

    /** keypad 1 and end */
    SingleInput keypad1;

    /** keypad 2 and down arrow */
    SingleInput keypad2;

    /** keypad 3 and page down */
    SingleInput keypad3;

    /** keypad 4 and left arrow */
    SingleInput keypad4;

    /** keypad 5 */
    SingleInput keypad5;

    /** keypad 6 and right arrow */
    SingleInput keypad6;

    /** keypad 7 and home */
    SingleInput keypad7;

    /** keypad 8 and up arrow */
    SingleInput keypad8;

    /** keypad 9 and page up */
    SingleInput keypad9;

    /** keypad 0 and insert */
    SingleInput keypad0;

    /** keypad . and delete */
    SingleInput keypadDecimalPoint;

    /** non-US \ and | */
    SingleInput nonUsBackslash;

    /** application (Windows key for Windows 95 and "Compose") */
    SingleInput application;

    /** power */
    SingleInput power;

    /** keypad = */
    SingleInput keypadEquals;

    /** F13 */
    SingleInput f13;

    /** F14 */
    SingleInput f14;

    /** F15 */
    SingleInput f15;

    /** F16 */
    SingleInput f16;

    /** F17 */
    SingleInput f17;

    /** F18 */
    SingleInput f18;

    /** F19 */
    SingleInput f19;

    /** F20 */
    SingleInput f20;

    /** F21 */
    SingleInput f21;

    /** F22 */
    SingleInput f22;

    /** F23 */
    SingleInput f23;

    /** F24 */
    SingleInput f24;

    /** execute */
    SingleInput execute;

    /** help */
    SingleInput help;

    /** menu */
    SingleInput menu;

    /** select */
    SingleInput select;

    /** stop */
    SingleInput stop;

    /** again */
    SingleInput again;

    /** undo */
    SingleInput undo;

    /** cut */
    SingleInput cut;

    /** copy */
    SingleInput copy;

    /** paste */
    SingleInput paste;

    /** find */
    SingleInput find;

    /** mute */
    SingleInput mute;

    /** volume up */
    SingleInput volumeUp;

    /** volume down */
    SingleInput volumeDown;

    /** locking caps lock */
    SingleInput lockingCapsLock;

    /** locking num lock */
    SingleInput lockingNumLock;

    /** locking scroll lock */
    SingleInput lockingScrollLock;

    /** keypad comma */
    SingleInput keypadComma;

    /** keypad equal sign (used on AS/400 keyboards) */
    SingleInput keypadEqualSign;

    /** international 1 */
    SingleInput international1;

    /** international 2 */
    SingleInput international2;

    /** international 3 */
    SingleInput international3;

    /** international 4 */
    SingleInput international4;

    /** international 5 */
    SingleInput international5;

    /** international 6 */
    SingleInput international6;

    /** international 7 */
    SingleInput international7;

    /** international 8 */
    SingleInput international8;

    /** international 9 */
    SingleInput international9;

    /** lang 1 */
    SingleInput lang1;

    /** lang 2 */
    SingleInput lang2;

    /** lang 3 */
    SingleInput lang3;

    /** lang 4 */
    SingleInput lang4;

    /** lang 5 */
    SingleInput lang5;

    /** lang 6 */
    SingleInput lang6;

    /** lang 7 */
    SingleInput lang7;

    /** lang 8 */
    SingleInput lang8;

    /** lang 9 */
    SingleInput lang9;

    /** alternate erase (example: Erase-Eaze key) */
    SingleInput alternateErase;

    /** SysReq/Attention */
    SingleInput sysReqAttention;

    /** cancel */
    SingleInput cancel;

    /** clear */
    SingleInput clear;

    /** prior */
    SingleInput prior;

    /** return */
    SingleInput returnKey;

    /** separator */
    SingleInput separator;

    /** out */
    SingleInput out;

    /** oper */
    SingleInput oper;

    /** clear/again */
    SingleInput clearAgain;

    /** CrSel/Props */
    SingleInput crSelProps;

    /** ExSel */
    SingleInput exSel;

    /** keypad 00 */
    SingleInput keypad00;

    /** keypad 000 */
    SingleInput keypad000;

    /** thousands separator */
    SingleInput keypadThousandsSeparator;

    /** decimal separator */
    SingleInput keypadDecimalSeparator;

    /** currency unit */
    SingleInput keypadCurrencyUnit;

    /** currency sub-unit */
    SingleInput keypadCurrencySubunit;

    /** keypad ( */
    SingleInput keypadOpenParenthesis;

    /** keypad ) */
    SingleInput keypadCloseParenthesis;

    /** keypad { */
    SingleInput keypadOpenBracket;

    /** keypad } */
    SingleInput keypadCloseBracket;

    /** keypad tab */
    SingleInput keypadTab;

    /** keypad backspace */
    SingleInput keypadBackspace;

    /** keypad A */
    SingleInput keypadA;

    /** keypad B */
    SingleInput keypadB;

    /** keypad C */
    SingleInput keypadC;

    /** keypad D */
    SingleInput keypadD;

    /** keypad E */
    SingleInput keypadE;

    /** keypad F */
    SingleInput keypadF;

    /** keypad XOR */
    SingleInput keypadXOR;

    /** keypad ^ */
    SingleInput keypadCaret;

    /** keypad % */
    SingleInput keypadPercent;

    /** keypad < */
    SingleInput keypadLessThan;

    /** keypad > */
    SingleInput keypadGreaterThan;

    /** keypad & */
    SingleInput keypadAnd;

    /** keypad && */
    SingleInput keypadDoubleAnd;

    /** keypad | */
    SingleInput keypadOr;

    /** keypad || */
    SingleInput keypadDoubleOr;

    /** keypad : */
    SingleInput keypadColon;

    /** keypad # */
    SingleInput keypadNumberSign;

    /** keypad space */
    SingleInput keypadSpace;

    /** keypad @ */
    SingleInput keypadAt;

    /** keypad ! */
    SingleInput keypadBang;

    /** keypad memory store */
    SingleInput keypadMemoryStore;

    /** keypad memory recall */
    SingleInput keypadMemoryRecall;

    /** keypad memory clear */
    SingleInput keypadMemoryClear;

    /** keypad memory add */
    SingleInput keypadMemoryAdd;

    /** keypad memory subtract */
    SingleInput keypadMemorySubtract;

    /** keypad memory multiply */
    SingleInput keypadMemoryMultiply;

    /** keypad memory divide */
    SingleInput keypadMemoryDivide;

    /** keypad +/- */
    SingleInput keypadPlusMinus;

    /** keypad clear */
    SingleInput keypadClear;

    /** keypad clear entry */
    SingleInput keypadClearEntry;

    /** keypad binary */
    SingleInput keypadBinary;

    /** keypad octal */
    SingleInput keypadOctal;

    /** keypad decimal */
    SingleInput keypadDecimal;

    /** keypad hexadecimal */
    SingleInput keypadHexadecimal;

    /** keypad left control */
    SingleInput keypadLeftControl;

    /** keypad left shift */
    SingleInput keypadLeftShift;

    /** keypad left alt */
    SingleInput keypadLeftAlt;

    /** keypad left gui */
    SingleInput keypadLeftGui;

    /** keypad right control */
    SingleInput keypadRightControl;

    /** keypad right shift */
    SingleInput keypadRightShift;

    /** keypad right alt */
    SingleInput keypadRightAlt;

    /** keypad right gui */
    SingleInput keypadRightGui;

    /**
     * gets a description of the active inputs for debugging purposes
     *
     * @return a textual representation of the active inputs
     */
    std::string getActiveDescription();

    protected:

    /** maps byte values to keys */
    std::map<unsigned char, SingleInput*> map;

    /** active keys */
    std::vector<SingleInput*> active;

    /** maps inputs to textual descriptions */
    std::map<SingleInput*, std::string> descriptions;

};

}

#endif
