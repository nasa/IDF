#include "Utils.hh"

double idf::bound(double value) {
    return value > 1 ? 1 : (value < -1 ? -1 : value);
}
