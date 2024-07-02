#include "CassetteReader.h"

CassetteReader::CassetteReader() {

    this->cny_1 = new Cny70(CNY70_INPUT_0, CNY70_LED_0);
    this->cny_2 = new Cny70(CNY70_INPUT_1, CNY70_LED_1);
    this->cny_3 = new Cny70(CNY70_INPUT_2, CNY70_LED_2);
    this->cny_4 = new Cny70(CNY70_INPUT_3, CNY70_LED_3);

    this->cny_threshold[0] = 40;
    this->cny_threshold[1] = 40;
    this->cny_threshold[2] = 40;
    this->cny_threshold[3] = 40;

    for (int i = 0; i < 4; i++) {
        this->cny_value_list[i] = 1000;
    }

}


void CassetteReader::update() {

    if (millis() > this->last_time + this->period_duration) {

        this->cny_1->update();
        this->cny_2->update();
        this->cny_3->update();
        this->cny_4->update();


        if (
            !this->cny_1->valueAvailable()
            && !this->cny_1->isProcessingMesure()
        ) {
            this->cny_1->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && !this->cny_2->valueAvailable()
            && !this->cny_2->isProcessingMesure()
        ) {
            this->cny_2->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && this->cny_2->valueAvailable()
            && !this->cny_3->valueAvailable()
            && !this->cny_3->isProcessingMesure()
        ) {
            this->cny_3->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && this->cny_2->valueAvailable()
            && this->cny_3->valueAvailable()
            && !this->cny_4->valueAvailable()
            && !this->cny_4->isProcessingMesure()
        ) {
            this->cny_4->processMesure();
        }


        if (
            this->cny_1->valueAvailable()
            && this->cny_2->valueAvailable()
            && this->cny_3->valueAvailable()
            && this->cny_4->valueAvailable()
        ) {
        
            this->cny_value_list[0] = this->cny_1->getValue();
            this->cny_value_list[1] = this->cny_2->getValue();
            this->cny_value_list[2] = this->cny_3->getValue();
            this->cny_value_list[3] = this->cny_4->getValue();
            
            this->last_time = millis();

            if (this->serial_debug_activate) {
                for (int i = 0; i < 4; i++) {
                    Serial.print("CNY Value ");
                    Serial.print(i + 1);
                    Serial.print(": ");
                    Serial.print(this->cny_value_list[i]);
                    Serial.print(" ");
                    
                }
                Serial.print(" - ");
                Serial.print(this->getIntegerValue());
                Serial.print(" ");
                Serial.println();
            }
        }

    }

}



int CassetteReader::calculateIntegerValue() {
    int integerValue = 0;
    for (int i = 0; i < 4; i++) {
        if (cny_value_list[i] < this->cny_threshold[i]) {
            integerValue |= (1 << i);
        }
    }
    return integerValue;
}


int CassetteReader::getIntegerValue() {
    return this->value;
}


// Debt is valueChanged is not checked then getIntegerValue is not changing
bool CassetteReader::valueChanged() {
    if (this->calculateIntegerValue() != this->value) {
        this->value = this->calculateIntegerValue();
        return true;
    }
    return false;
}