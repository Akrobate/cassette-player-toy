#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>
#include <Toggle.h>

#include <LightAnimation.h>


LightAnimation lightAnimation();

#define LED 8

#define RX_PIN 10  // plugged on TX of the DFPlayer
#define TX_PIN 9  // plugged on RX of the DFPlayer

#define BUTTON_PREVIOUS  14
#define BUTTON_NEXT      15

#define BUTTON_PLAY 16

#define BUTTON_VOLUME_DOWN  17
#define BUTTON_VOLUME_UP    18



void printDetail(uint8_t type, int value);


// SoftwareSerial softSerial(RX_PIN, TX_PIN);
// #define FPSerial softSerial

Toggle buttonVolumeUp(BUTTON_VOLUME_UP);
Toggle buttonVolumeDown(BUTTON_VOLUME_DOWN);
Toggle buttonPlay(BUTTON_PLAY);
Toggle buttonNext(BUTTON_NEXT);
Toggle buttonPrevious(BUTTON_PREVIOUS);

DFRobotDFPlayerMini myDFPlayer;


boolean is_playing = 0;

unsigned int volume = 10;

int cny70_0 = 0;


#define CNY70_INPUT_0  A2
#define CNY70_LED_0  12



void setup() {

    pinMode(LED, OUTPUT);

    // FPSerial.begin(9600);
    Serial.begin(9600);

    Serial.println();
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    // CNY70

    //pinMode(CNY70_0, INPUT_PULLUP);
    pinMode(CNY70_INPUT_0, INPUT);
    pinMode(CNY70_LED_0, OUTPUT);

    
}



void loop() {

    static unsigned long timer = millis();


    Serial.print(F("CNY ON LED"));
    digitalWrite(CNY70_LED_0, HIGH);

    delay(2000);

    cny70_0 = analogRead(CNY70_INPUT_0);
    Serial.print(F("CNY Value : "));
    Serial.println(cny70_0);

    Serial.print(F("CNY OFF LED"));
    digitalWrite(CNY70_LED_0, LOW);

    delay(2000);

    cny70_0 = analogRead(CNY70_INPUT_0);
    Serial.print(F("CNY Value (led off): "));
    Serial.println(cny70_0);

}


