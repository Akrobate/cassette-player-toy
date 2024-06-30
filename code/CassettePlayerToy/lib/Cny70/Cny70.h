#ifndef Cny70_h
#define Cny70_h

#include <Arduino.h>

/**
 * About Cny70 class
 */

class Cny70 {
    
    public:

        Cny70(int input_analog_pin, int led_pin);

        void update();
        bool valueAvailable();
        int getValue();
        void processMesure();

    private:


        int input_analog_pin = 0;
        int led_pin = 0;

        bool led_state = false;
        
        const unsigned int mesure_time = 100;
        unsigned int last_time = 0;

        bool value_available = false;
        bool processing_mesure = false;

        int value = 0;

};

#endif