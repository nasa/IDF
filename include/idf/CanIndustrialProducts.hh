/*
PURPOSE:
LIBRARY DEPENDENCIES: (
(idf/CanIndustrialProducts.cpp)
)
*/

/**
 * @trick_parse{everything}
 * @trick_link_dependency{idf/CanIndustrialProducts.cpp}
 */

#ifndef CAN_INDUSTRIAL_PRODUCTS_HH
#define CAN_INDUSTRIAL_PRODUCTS_HH

#include "idf/CanDevice.hh"
#include "idf/IndustrialProducts.hh"

namespace idf {

/**
 * CAN IndustrialProducts hand controller
 *
 * @author Derek Bankieris
 */
class CanIndustrialProducts : public CanDevice, public IndustrialProducts {

    public:

    /* the CAN-ID of this device */
    static const int canId;

    /**
     * constructs a new instance
     *
     * @param networkId the network number
     * @param flags @copydoc flags
     * @param transmitQueueSize @copydoc transmitQueueSize
     * @param receiveQueueSize @copydoc receiveQueueSize
     * @param transmitTimeout @copydoc transmitTimeout
     * @param receiveTimeout @copydoc receiveTimeout
     */
    CanIndustrialProducts(int networkId = 0, uint32_t flags = NTCAN_MODE_OBJECT,
      int32_t transmitQueueSize = 0, int32_t receiveQueueSize = 1,
      int32_t transmitTimeout = 0, int32_t receiveTimeout = 0);

    void open();
    std::vector<std::vector<unsigned char> > read();
    void decode(const std::vector<unsigned char>& data);

};

}

#endif
