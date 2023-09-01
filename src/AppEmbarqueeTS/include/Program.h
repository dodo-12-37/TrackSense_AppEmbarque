#pragma once
#include <Arduino.h>
#include "Interfaces/ILTE.h"



class Program
{
private:
    ILTE *lte;

public:
    Program();
    ~Program();

    void execute();
};
