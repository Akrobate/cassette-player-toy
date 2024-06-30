#ifndef CassetteReader_h
#define CassetteReader_h

#include "../Cny70/Cny70.h"
#include "configuration.h"

#include <Arduino.h>

/**
 * About CassetteReader class
 */

class CassetteReader {
    
    public:

        CassetteReader();

        void update();


    private:

        Cny70 * cny_1;
        Cny70 * cny_2;
        Cny70 * cny_3;
        Cny70 * cny_4;

        int cny_value_list[4];
        int cny_threshold[4];
        int value = 0;

        int last_time = 0;
        int period_duration = 2000;

};

#endif