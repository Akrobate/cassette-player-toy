#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>
#include <Toggle.h>

#include <LightAnimation.h>


LightAnimation lightAnimation();


// Verified
#define RX_PIN 2  // plugged on TX of the DFPlayer
#define TX_PIN 3  // plugged on RX of the DFPlayer


// Pixel led (ws2812b)
#define PIXEL_LED_PIN 4




#define BUTTON_PREVIOUS  14
#define BUTTON_NEXT      15

#define BUTTON_PLAY 16

#define BUTTON_VOLUME_DOWN  17
#define BUTTON_VOLUME_UP    18



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


#define CNY70_INPUT_0  A2
#define CNY70_LED_0  12

#define CNY70_INPUT_1  A3
#define CNY70_LED_1  13

#define CNY70_INPUT_2  A4
#define CNY70_LED_2  14

#define CNY70_INPUT_3  A5
#define CNY70_LED_3  15

void setup() {

    FPSerial.begin(9600);
    Serial.begin(9600);

    Serial.println();
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

    if (!myDFPlayer.begin(FPSerial, true, true)) {
        Serial.println(F("Unable to begin"));
        while(true) {
            delay(0);
        }
    }
    Serial.println(F("DFPlayer on the air !!! "));



    // CNY70
    pinMode(CNY70_INPUT_0, INPUT);
    pinMode(CNY70_LED_0, OUTPUT);

    pinMode(CNY70_INPUT_1, INPUT);
    pinMode(CNY70_LED_1, OUTPUT);

    pinMode(CNY70_INPUT_2, INPUT);
    pinMode(CNY70_LED_2, OUTPUT);

    pinMode(CNY70_INPUT_3, INPUT);
    pinMode(CNY70_LED_3, OUTPUT);

    
}



void loop() {

    static unsigned long timer = millis();

/*
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
*/


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


    delay(1000);




    //if (myDFPlayer.available()) {
    //    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    //}

}


