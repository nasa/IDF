/**
 * PURPOSE:
 * ()
 *
 * LIBRARY DEPENDENCIES:
 * ((hardwareInterface/src/CanIndustrialProducts.cpp))
 */

#ifndef _CAN_INDUSTRIAL_PRODUCTS_HH_
#define _CAN_INDUSTRIAL_PRODUCTS_HH_

#include "hardwareInterface/include/CanDevice.hh"
#include "inputAbstraction/include/IndustrialProducts.hh"

namespace idf {

/**
 * represents a CAN IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class CanIndustrialProducts : public CanDevice, public IndustrialProducts {

    public:

    static const int canId;

    /**
     * constructs a new instance
     *
     * @param networkId the network number
     * @param flags a bitwise OR of the following options:
     * NTCAN_MODE_OVERLAPPED - overlapped I/O only
     * NTCAN_MODE_OBJECT - reception is in object mode instead of FIFO mode
     * NTCAN_MODE_NO_RTR - remote message requests are ignored
     * NTCAN_MODE_NO_DATA - data frames are ignored
     * NTCAN_MODE_NO_INTERACTION - messages received via interaction mechanisms
     * are ignored
     * NTCAN_MODE_MARK_INTERACTION - messages received via interaction
     * mechanisms will be marked as such in the length field
     * @param transmitQueueSize maximum number of messages the Tx queue can hold
     * @param receiveQueueSize maximum number of messages the Rx queue can hold
     * @param transmitTimeout transmit timeout in ms
     * @param receiveTimeout receive timeout in ms
     */
    CanIndustrialProducts(int networkId = 0, uint32_t flags = NTCAN_MODE_OBJECT,
      int32_t transmitQueueSize = 0, int32_t receiveQueueSize = 1,
      int32_t transmitTimeout = 0, int32_t receiveTimeout = 0);

    void open();

    void update();

};

}

#endif
