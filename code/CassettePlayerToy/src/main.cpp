#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>
#include <Toggle.h>


#define LED 8

#define RX_PIN 10  // plugged on TX of the DFPlayer
#define TX_PIN 9  // plugged on RX of the DFPlayer

#define BUTTON_PREVIOUS  14
#define BUTTON_NEXT      15

#define BUTTON_PLAY 16

#define BUTTON_VOLUME_DOWN  17
#define BUTTON_VOLUME_UP    18


SoftwareSerial softSerial(RX_PIN, TX_PIN);
#define FPSerial softSerial

Toggle buttonVolumeUp(BUTTON_VOLUME_UP);
Toggle buttonVolumeDown(BUTTON_VOLUME_DOWN);
Toggle buttonPlay(BUTTON_PLAY);
Toggle buttonNext(BUTTON_NEXT);
Toggle buttonPrevious(BUTTON_PREVIOUS);

DFRobotDFPlayerMini myDFPlayer;

void setup() {

    pinMode(LED, OUTPUT);

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
    Serial.println(F("DFPlayer Mini online."));

}


unsigned int volume = 0;

void loop() {
    buttonVolumeUp.poll();
    buttonVolumeDown.poll();
    buttonPlay.poll();
    buttonNext.poll();
    buttonPrevious.poll();

    myDFPlayer.volume(volume);


    if (buttonVolumeUp.onPress()) {
        volume += 1;
        if (volume > 30) {
            volume = 30;
        }
        Serial.print(F("Volume: "));
        Serial.println(volume);
    }

    if (buttonVolumeDown.onPress()) {
        if (volume > 0) {
            volume -= 1;
            Serial.print(F("Volume: "));
            Serial.println(volume);
        }
    }

    if (buttonPlay.onPress()) {
        Serial.println(F("button was pressed"));
        myDFPlayer.play(1);
    }

    if (buttonNext.onPress()) {
        Serial.println(F("button was pressed"));
        myDFPlayer.next();
    }

    if (buttonPrevious.onPress()) {
        Serial.println(F("button was pressed"));
        myDFPlayer.previous();
    }

    // digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    // delay(100);                      // wait for a second
    // digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
    // delay(100);                      // wait for a second
}

