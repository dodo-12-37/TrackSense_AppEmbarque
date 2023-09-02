#include "Modules/BLE.h"



BLE::BLE(TrackSenseProperties* trackSenseProperties) : _trackSenseProperties(trackSenseProperties)
{
}

BLE::~BLE()
{
}

void BLE::tick() const
{            
    // if (_trackSenseProperties->isBLEConnected)
    // {
    //     _trackSenseProperties->ble->poll();
    // }
}