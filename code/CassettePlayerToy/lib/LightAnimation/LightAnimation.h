#ifndef LightAnimation_h
#define LightAnimation_h

#include "../../src/configuration.h"
#include <FastLED.h>

#include <Arduino.h>

/**
 * About LightAnimation class
 */

class LightAnimation {
    
    public:

        LightAnimation();

        
        static constexpr int ANIMATION_NO_ANIMATION = 0;
        static constexpr int ANIMATION_START_DEVICE = 1;
        static constexpr int ANIMATION_NO_CASSETTE = 2;
        static constexpr int ANIMATION_CASSETTE_DETECTED = 3;
        static constexpr int ANIMATION_PAUSED = 4;
        static constexpr int ANIMATION_UNKNOWN_CASSETTE = 5;

        unsigned int animation = 0; 

        void update();

        void resetAnimation();

        void triggerAnimationStartDevice();
        void triggerAnimationNoCassette();
        void triggerAnimationCassetteDetected();
        void triggerAnimationPaused();
        void triggerAnimationUnknownCassette();

    private:

        CRGB leds[1];

        unsigned long last_time = 0;
        unsigned int period_duration = 1000;
        boolean loop_animation = false;

        void animationStartDevice();
        void animationNoCassette();
        void animationCassetteDetected();
        void animationPaused();
        void animationUnknownCassette();




};

#endif