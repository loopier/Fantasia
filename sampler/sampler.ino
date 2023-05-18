// use: https://github.com/dgduncan/SevenSegment
#include <SegmentDisplay.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Encoder.h>

// Audio Declarations
// AudioSynthWaveform       waveform1;      //xy=684,318
// AudioOutputI2S           i2s1;           //xy=913,314
// AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
// AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=1125,313

// GUItool: begin automatically generated code
AudioSynthWavetable      wavetable1;     //xy=823,575
AudioOutputI2S           i2s1;           //xy=1294,566
AudioConnection          patchCord1(wavetable1, 0, i2s1, 0);
AudioConnection          patchCord2(wavetable1, 0, i2s1, 1);
// GUItool: end automatically generated code


//Display LEDs Declaration
// SegmentDisplay segmentDisplay(30, 32, 33, 28, 31, 26, 29, 9);
//                             E   D   C  DP  B   A   G   F
//                             1   2   4  5   6   7   9  10
SegmentDisplay segmentDisplay(31, 28, 33, 9, 32, 30, 26, 29);


//Teensy audio initialization Code

//SD CARD PINS
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  11
#define SDCARD_SCK_PIN   13

int maxSdReadAttempts = 10;
int numSdReadAttempts = 0;
File root;

// select the input pins for the potentiometers
int potPin1 = A0; 
int potPin2 = A1;
int potPin3 = A2;
int potPin4 = A3;
Encoder enc(0,1);

// pushbutton connected to digital pinS
int btnPin1 = 2;    
int btnPin2 = 5; 
int btnPin3 = 25; 
int btnPin4 = 27; 
int gatePin1 = 3; 
int gatePin2 =6; 
int encBtnPin =4;

 // Variables to store port values 
float pot1 = 0; 
float pot2 = 0;
float pot3 = 0;
float pot4 = 0;
int btn1 = 0;   
int btn2 = 0;
int btn3 = 0;
int btn4 = 0;
int gate1 = 0;
int gate2 = 0;
long oldEncPos = -999;
long newEncPos = -999;
bool encFlag = 0; // is display decimal flag displayed
int encPressed = 0; // is encoder button pressed
char displayValue = 0;

int mywaveform = 0;

void setup() {  
  // open the serial port at 9600 bps:
  Serial.begin(9600); 

  Serial.println("Booting Sampler");
  
  //Audio setup
  Serial.println("Setting up audio...");
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  sgtl5000_1.inputSelect(AUDIO_INPUT_LINEIN);
  sgtl5000_1.micGain(36); //NEEDED?
  
  Serial.println("Audio ready");

  // SD setup
  Serial.println("Setting up SD card...");
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (numSdReadAttempts < maxSdReadAttempts) {
      Serial.println("Unable to access the SD card");
      numSdReadAttempts++;
      delay(500);
    }
    Serial.println("ERROR: Failed to read SD card.");
  } else {
    Serial.println("Reading root...");
    root = SD.open("/");
    printDirectory( root, 0 );
    root.close();
    Serial.println("done");
  }
  
  numSdReadAttempts = 0;

  // sets the digital pins as inputs and set pullups
  Serial.println("Setting digital pins...");
  pinMode(btnPin1, INPUT_PULLUP);   
  pinMode(btnPin2, INPUT_PULLUP); 
  pinMode(btnPin3, INPUT_PULLUP); 
  pinMode(btnPin4, INPUT_PULLUP); 
  pinMode(gatePin1, INPUT_PULLUP); 
  pinMode(gatePin2, INPUT_PULLUP); 
  pinMode(encBtnPin, INPUT_PULLUP); 
  Serial.println("done");

  //Set Display LEDs ports as Outputs 
  Serial.println("Setting display...");
  pinMode(30, OUTPUT);    
  pinMode(32, OUTPUT); 
  pinMode(33, OUTPUT); 
  pinMode(28, OUTPUT); 
  pinMode(31, OUTPUT); 
  pinMode(26, OUTPUT); 
  pinMode(29, OUTPUT); 
  pinMode(9, OUTPUT);
  Serial.println("done");
  
}


void loop() {
  pot1 = max(analogRead(potPin1), 20);
  pot2 = analogRead(potPin2);
  pot3 = max(analogRead(potPin3), 1);
  pot4 = analogRead(potPin4);
  btn1 = !digitalRead(btnPin1);
  btn2 = !digitalRead(btnPin2);
  btn3 = !digitalRead(btnPin3);
  btn4 = !digitalRead(btnPin4);
  encPressed = !digitalRead(encBtnPin);
  newEncPos = enc.read() / 4;

  if (encPressed) { 
    encFlag = !encFlag;
    segmentDisplay.displayHex(displayValue, encFlag);
  }
  
  if (newEncPos != oldEncPos) {
    displayValue = abs(newEncPos % 16);
    oldEncPos = newEncPos;
    segmentDisplay.displayHex(displayValue, encFlag);
  }

//  Serial.println(btn4);
}

void printDirectory(File dir, int numTabs) {
  while( true ) {
    File entry = dir.openNextFile();
    
    if (!entry) { break; }

    for(uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    
    Serial.print(entry.name());
    
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    
    entry.close();
  }
}
