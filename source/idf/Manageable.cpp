#include "idf/Manageable.hh"

namespace idf {

Manageable::Manageable() :
    mOpen(false) {}

void Manageable::open() {
    mOpen = true;
}

void Manageable::update() {
    if (!isOpen()) {
        open();
    }
}

void Manageable::close() {
    mOpen = false;
}

bool Manageable::isOpen() const {
    return mOpen;
}

}
