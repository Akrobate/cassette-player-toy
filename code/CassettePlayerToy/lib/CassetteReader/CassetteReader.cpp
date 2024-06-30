#include "CassetteReader.h"

CassetteReader::CassetteReader() {

    this->cny_1 = new Cny70(CNY70_INPUT_0, CNY70_LED_0);
    this->cny_2 = new Cny70(CNY70_INPUT_0, CNY70_LED_0);
    this->cny_3 = new Cny70(CNY70_INPUT_0, CNY70_LED_0);
    this->cny_4 = new Cny70(CNY70_INPUT_0, CNY70_LED_0);

}


void CassetteReader::update() {

    if (millis() > this->last_time + this->period_duration) {

        this->cny_1->update();
        this->cny_2->update();
        this->cny_3->update();
        this->cny_4->update();


        if (!this->cny_1->valueAvailable()) {
            this->cny_1->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && !this->cny_2->valueAvailable()
        ) {
            this->cny_2->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && this->cny_2->valueAvailable()
            && !this->cny_3->valueAvailable()
        ) {
            this->cny_3->processMesure();
        }

        if (
            this->cny_1->valueAvailable()
            && this->cny_2->valueAvailable()
            && this->cny_3->valueAvailable()
            && !this->cny_4->valueAvailable()
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
        }

    }

}