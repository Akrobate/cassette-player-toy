#include "LightAnimation.h"


LightAnimation::LightAnimation() {

    pinMode(PIXEL_LED_PIN, OUTPUT);
    digitalWrite(PIXEL_LED_PIN, LOW);
    FastLED.addLeds<NEOPIXEL, PIXEL_LED_PIN>(leds, 1);
}



void LightAnimation::update() {
    switch (this->animation) {
        case ANIMATION_START_DEVICE:
            this->animationStartDevice();
            break;
        case ANIMATION_NO_CASSETTE:
            this->animationNoCassette();
            break;
        case ANIMATION_CASSETTE_DETECTED:
            this->animationCassetteDetected();
            break;
        case ANIMATION_PAUSED:
            this->animationPaused();
            break;
        case ANIMATION_UNKNOWN_CASSETTE:
            this->animationUnknownCassette();
            break;
        default:
            break;
    }
}




void LightAnimation::animationStartDevice() {
    if (millis() < this->last_time + this->period_duration) {
        leds[0] = CHSV(
            160 + map(millis() - this->last_time, 0, this->period_duration, 0, 255),
            255,
            255
        );
        FastLED.show();
    }
}




void LightAnimation::animationNoCassette() {
    unsigned long _millis = millis();
    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            leds[0] = CHSV(
                160,
                255,
                map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255)
            );
        } else {
            leds[0] = CHSV(
                160,
                255,
                255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)
            );

        }

        FastLED.show();
    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->animation = ANIMATION_NO_ANIMATION;
        }
    }
}




void LightAnimation::animationCassetteDetected() {


    unsigned long _millis = millis();

    // Serial.println(_millis - this->last_time);

    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            leds[0] = CHSV(
                96,
                255,
                map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255)
            );
        } else {
            leds[0] = CHSV(
                96,
                255,
                255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)
            );
        }

        FastLED.show();
    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->animation = ANIMATION_NO_ANIMATION;
        }
    }
}





void LightAnimation::animationPaused() {


    unsigned long _millis = millis();

    // Serial.println(_millis - this->last_time);

    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            leds[0] = CHSV(
                32,
                255,
                map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255)
            );
        } else {
            leds[0] = CHSV(
                32,
                255,
                255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)
            );
        }

        FastLED.show();
    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->animation = ANIMATION_NO_ANIMATION;
        }
    }
}







void LightAnimation::animationUnknownCassette() {


    unsigned long _millis = millis();

    // Serial.println(_millis - this->last_time);

    if (_millis < this->last_time + this->period_duration) {

        if (_millis < this->last_time + this->period_duration / 2) {
            leds[0] = CHSV(
                0,
                255,
                map(_millis - (this->last_time), 0, this->period_duration / 2, 0, 255)
            );
        } else {
            leds[0] = CHSV(
                0,
                255,
                255 - map(_millis - this->last_time - this->period_duration / 2, 0, this->period_duration / 2, 0, 255)
            );
        }

        FastLED.show();
    } else {
        if (this->loop_animation) {
            this->last_time = _millis;
        } else {
            this->animation = ANIMATION_NO_ANIMATION;
        }
    }
}





void LightAnimation::triggerAnimationStartDevice() {
    this->last_time = millis();
    this->period_duration = 1000;
    this->animation = ANIMATION_START_DEVICE;
}


void LightAnimation::triggerAnimationNoCassette() {
    this->last_time = millis();
    this->period_duration = 3000;
    this->animation = ANIMATION_NO_CASSETTE;
    this->loop_animation = true;
}

void LightAnimation::triggerAnimationCassetteDetected() {
    this->last_time = millis();
    this->period_duration = 10000;
    this->animation = ANIMATION_CASSETTE_DETECTED;
    this->loop_animation = true;
}

void LightAnimation::triggerAnimationPaused() {
    this->last_time = millis();
    this->period_duration = 1000;
    this->animation = ANIMATION_PAUSED;
    this->loop_animation = true;
}

void LightAnimation::triggerAnimationUnknownCassette() {
    this->last_time = millis();
    this->period_duration = 500;
    this->animation = ANIMATION_UNKNOWN_CASSETTE;
    this->loop_animation = true;
}


void LightAnimation::resetAnimation() {
    this->animation = ANIMATION_NO_ANIMATION;
}