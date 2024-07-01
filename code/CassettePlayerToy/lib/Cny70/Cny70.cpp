#include "Cny70.h"


Cny70::Cny70(int input_analog_pin, int led_pin) {
    this->input_analog_pin = input_analog_pin;
    this->led_pin = led_pin;
    pinMode(input_analog_pin, INPUT);
    pinMode(led_pin, OUTPUT);
}



void Cny70::update() {
    if (this->processing_mesure) {
        if (this->led_state == false) {
            digitalWrite(this->led_pin, HIGH);
            this->led_state = true;
        }
        
        if (millis() > this->last_time + this->mesure_time) {
            this->value = analogRead(this->input_analog_pin);
            digitalWrite(this->led_pin, LOW);
            this->led_state = false;
            this->processing_mesure = false;
            this->value_available = true;
        }
    }
}


void Cny70::processMesure() {
    this->processing_mesure = true;
    this->last_time = millis();
}



int Cny70::getValue() {
    if (this->processing_mesure) {
        return 0;
    }

    if (!this->value_available) {
        return 0;
    }

    this->value_available = false;
    return this->value;
}


bool Cny70::valueAvailable() {
    return this->value_available;
}


bool Cny70::isProcessingMesure() {
    return this->processing_mesure;
}
