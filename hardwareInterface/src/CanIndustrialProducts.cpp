#include "CanIndustrialProducts.hh"

using namespace idf;

CanIndustrialProducts::CanIndustrialProducts(int networkID, int baudRate) :
    CanDevice(networkID, baudRate) {}

void CanIndustrialProducts::update() {
    CanDevice::update();
}

void CanIndustrialProducts::printState() {
}
