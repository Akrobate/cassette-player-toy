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
    myDFPlayer.volume(volume);

    
}



void loop() {

    static unsigned long timer = millis();


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

        if (is_playing) {
            myDFPlayer.pause();
            is_playing = false;
        } else {
            myDFPlayer.start();
            is_playing = true;
        }

        Serial.println(myDFPlayer.readCurrentFileNumber());
        myDFPlayer.play(1);
        myDFPlayer.enableLoopAll();

        delay(100);
        Serial.println(myDFPlayer.readCurrentFileNumber());
    }

    if (buttonNext.onPress()) {
        Serial.println(F("Next file:"));
        Serial.println(myDFPlayer.readCurrentFileNumber());
        myDFPlayer.next();
        // delay(3000);
        Serial.println(myDFPlayer.readCurrentFileNumber());
        Serial.println(myDFPlayer.readCurrentFileNumber());
    }

    if (buttonPrevious.onPress()) {
        Serial.println(F("Previous file:"));
        Serial.println(myDFPlayer.readCurrentFileNumber());
        myDFPlayer.previous();
        // delay(3000);
        Serial.println(myDFPlayer.readCurrentFileNumber());
        Serial.println(myDFPlayer.readCurrentFileNumber());
    }

    if (millis() - timer > 3000) {
        timer = millis();

        Serial.print(F("Playing now: "));
        Serial.println(myDFPlayer.readCurrentFileNumber());

        Serial.print(F("State now: "));
        Serial.println(myDFPlayer.readState());
        Serial.print(F("readFileCounts now: "));
        Serial.println(myDFPlayer.readFileCounts());
        Serial.println(F("---------------------------"));


    }

    if (myDFPlayer.available()) {
        printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
    }
    

    // digitalWrite(LED, HIGH);  // turn the LED on (HIGH is the voltage level)
    // delay(100);                      // wait for a second
    // digitalWrite(LED, LOW);   // turn the LED off by making the voltage LOW
    // delay(100);                      // wait for a second
}





void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
