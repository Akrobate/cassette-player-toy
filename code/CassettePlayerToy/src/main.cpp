#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>
#include <Toggle.h>

#include <FastLED.h>

#include "./configuration.h"
#include <LightAnimation.h>
#include <Cny70.h>


LightAnimation lightAnimation();

// Pixel led (ws2812b)

CRGB leds[1];

void printDetail(uint8_t type, int value);

SoftwareSerial softSerial(RX_PIN, TX_PIN);
#define FPSerial softSerial

Toggle buttonVolumeUp(BUTTON_VOLUME_UP);
Toggle buttonVolumeDown(BUTTON_VOLUME_DOWN);
Toggle buttonPlay(BUTTON_PLAY);
Toggle buttonNext(BUTTON_NEXT);
Toggle buttonPrevious(BUTTON_PREVIOUS);

DFRobotDFPlayerMini myDFPlayer;

boolean is_playing = 0;

unsigned int volume = 10;

int cny70_0 = 0;
int cny70_1 = 0;
int cny70_2 = 0;
int cny70_3 = 0;


Cny70 cny_1(CNY70_INPUT_0, CNY70_LED_0);
Cny70 cny_2(CNY70_INPUT_0, CNY70_LED_0);
Cny70 cny_3(CNY70_INPUT_0, CNY70_LED_0);



void setup() {

    FPSerial.begin(9600);
    Serial.begin(9600);

    Serial.println();
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));



    if (!myDFPlayer.begin(FPSerial, true, false)) {
        Serial.println(F("Unable to begin"));
        while(true) {
            delay(0);
        }
    }


    myDFPlayer.volume(0);

    // myDFPlayer.play(1);

    Serial.println(F("DFPlayer on the air !!! "));

    //delay(5000);


    //myDFPlayer.reset();


    // CNY70
    pinMode(CNY70_INPUT_0, INPUT);
    pinMode(CNY70_LED_0, OUTPUT);

    pinMode(CNY70_INPUT_1, INPUT);
    pinMode(CNY70_LED_1, OUTPUT);

    pinMode(CNY70_INPUT_2, INPUT);
    pinMode(CNY70_LED_2, OUTPUT);

    pinMode(CNY70_INPUT_3, INPUT);
    pinMode(CNY70_LED_3, OUTPUT);


    pinMode(PIXEL_LED_PIN, OUTPUT);
    digitalWrite(PIXEL_LED_PIN, LOW);
    FastLED.addLeds<NEOPIXEL, PIXEL_LED_PIN>(leds, 1);

    
}



void loop() {

    // static unsigned long timer = millis();


    buttonVolumeUp.poll();
    buttonVolumeDown.poll();
    buttonPlay.poll();
    buttonNext.poll();
    buttonPrevious.poll();

    if (buttonVolumeUp.onPress()) {
        volume += 1;
        if (volume > 30) {
            volume = 30;
        }
        myDFPlayer.volume(volume);

        Serial.print(F("Volume: "));
        Serial.println(volume);
    }

    if (buttonVolumeDown.onPress()) {
        if (volume > 0) {
            volume -= 1;
            Serial.print(F("Volume: "));
            Serial.println(volume);
            myDFPlayer.volume(volume);
        }
    }



    if (buttonPlay.onPress()) {
        Serial.println(F("Play"));
    }

    if (buttonNext.onPress()) {
        Serial.println(F("Next file:"));
    }

    if (buttonPrevious.onPress()) {
        Serial.println(F("Previous file:"));
    }




    /*

    digitalWrite(CNY70_LED_0, HIGH);
    delay(100);
    cny70_0 = analogRead(CNY70_INPUT_0);
    digitalWrite(CNY70_LED_0, LOW);

    digitalWrite(CNY70_LED_1, HIGH);
    delay(100);
    cny70_1 = analogRead(CNY70_INPUT_1);
    digitalWrite(CNY70_LED_1, LOW);

    digitalWrite(CNY70_LED_2, HIGH);
    delay(100);
    cny70_2 = analogRead(CNY70_INPUT_2);
    digitalWrite(CNY70_LED_2, LOW);

    digitalWrite(CNY70_LED_3, HIGH);
    delay(100);
    cny70_3 = analogRead(CNY70_INPUT_3);
    digitalWrite(CNY70_LED_3, LOW);

    Serial.print("CNY Values: ");
    Serial.print("CNY0: ");
    Serial.print(cny70_0);
    Serial.print(", CNY1: ");
    Serial.print(cny70_1);
    Serial.print(", CNY2: ");
    Serial.print(cny70_2);
    Serial.print(", CNY3: ");
    Serial.println(cny70_3);

    */

// delay(1000);

    leds[0] = CRGB::Red;
    //FastLED.show();


    //delay(100);


    // leds[0] = CRGB::Green;
    // FastLED.show();


    //if (myDFPlayer.available()) {
    //    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    //}

}


