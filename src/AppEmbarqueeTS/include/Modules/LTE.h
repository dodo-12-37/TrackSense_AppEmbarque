#pragma once
#include <Arduino.h>
#include "Interfaces/ILTE.h"
#include "Configurations.h"
#include "TrackSenseProperties.h"



class LTE : ILTE
{
private:
    const TrackSenseProperties* _trackSenseProperties;

public:
    LTE(TrackSenseProperties* trackSenseProperties);
    ~LTE();

    void tick() const override;
};