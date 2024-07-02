#include <Arduino.h>
#include <SoftwareSerial.h>

#include <DFRobotDFPlayerMini.h>
#include <Toggle.h>

#include "./configuration.h"
#include <LightAnimation.h>
#include <CassetteReader.h>

void printDetail(uint8_t type, int value);
void nextTrackInFolder();
void previousTrackInFolder();


SoftwareSerial softSerial(RX_PIN, TX_PIN);
#define FPSerial softSerial

Toggle buttonVolumeUp(BUTTON_VOLUME_UP);
Toggle buttonVolumeDown(BUTTON_VOLUME_DOWN);
Toggle buttonPlay(BUTTON_PLAY);
Toggle buttonNext(BUTTON_NEXT);
Toggle buttonPrevious(BUTTON_PREVIOUS);

DFRobotDFPlayerMini myDFPlayer;
bool is_playing = false;
unsigned int volume = 10;


int current_folder = 0;
int files_in_folder_count = 0;
int current_file = 0;

const unsigned int max_volume = 20;

CassetteReader * cassette_reader = new CassetteReader();
LightAnimation * light_animation = new LightAnimation();

void setup() {

    cassette_reader->serial_debug_activate = true;

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

    myDFPlayer.volume(volume);

    Serial.println(F("DFPlayer on the air !!! "));
    light_animation->triggerAnimationStartDevice();
}



void loop() {

    cassette_reader->update();
    light_animation->update();

    if (cassette_reader->valueChanged()) {
        Serial.print("Cassette reader value changed: ");
        Serial.println(cassette_reader->getIntegerValue());
        current_folder = cassette_reader->getIntegerValue();

        if (current_folder > 0) {
            files_in_folder_count = myDFPlayer.readFileCountsInFolder(current_folder);
            light_animation->triggerAnimationCassetteDetected();
            current_file = 1;
            myDFPlayer.playFolder(current_folder, current_file);
            is_playing = true;
        } else {
            light_animation->triggerAnimationNoCassette();
            myDFPlayer.pause();
            is_playing = false;
        }
    }

    buttonVolumeUp.poll();
    buttonVolumeDown.poll();
    buttonPlay.poll();
    buttonNext.poll();
    buttonPrevious.poll();

    if (buttonVolumeUp.onPress()) {
        volume += 1;
        if (volume > max_volume) {
            volume = max_volume;
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
            light_animation->triggerAnimationPaused();
            myDFPlayer.pause();
            is_playing = false;
        } else {
            light_animation->triggerAnimationCassetteDetected();
            myDFPlayer.start();
            is_playing = true;
        }
    }

    if (buttonNext.onPress()) {
        Serial.println(F("Next file:"));
        nextTrackInFolder();
    }

    if (buttonPrevious.onPress()) {
        Serial.println(F("Previous file:"));
        previousTrackInFolder();
    }


    if (myDFPlayer.available()) {
        printDetail(myDFPlayer.readType(), myDFPlayer.read());

        if (DFPlayerPlayFinished == myDFPlayer.readType()) {
            is_playing = false;
            nextTrackInFolder();
        }

        if (FileMismatch == myDFPlayer.readType()) {
            is_playing = false;
            light_animation->triggerAnimationUnknownCassette();
        }
    }

}


void nextTrackInFolder() {

    if (current_file < files_in_folder_count) {
        current_file += 1;
    } else {
        current_file = 1;
    }

    myDFPlayer.playFolder(current_folder, current_file);
    is_playing = true;

}


void previousTrackInFolder() {

    if (current_file > 1) {
        current_file -= 1;
    } else {
        current_file = files_in_folder_count;
    }

    myDFPlayer.playFolder(current_folder, current_file);
    is_playing = true;

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
