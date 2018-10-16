#include <Wiegand.h>
WIEGAND wg;

const int weigandD0 = 2;
const int weigandD1 = 3;
const int weigandLED = 0;
const int weigandBuzzer = 1;
const int approvedDelay = 1500;
const int defaultFlashDelay = 100;

int flashingCount = 5;
int flashingBuzzerCount = 5;
bool ledState = true;
bool buzzerState = true;
long lastFlashChange = 0;
int flashDelay = defaultFlashDelay;

void setup() {
  Serial.begin(9600);
  wg.begin(weigandD0, weigandD1);
  pinMode(weigandLED, OUTPUT);
  pinMode(weigandBuzzer, OUTPUT);
  digitalWrite(weigandLED, ledState);
  digitalWrite(weigandBuzzer, buzzerState);
}

void loop() {  
  if (millis() > lastFlashChange + flashDelay) {
    lastFlashChange = millis();
    if (flashingCount) {
      digitalWrite(weigandLED, ledState);
      ledState = !ledState;
      flashingCount--;
    } else {
      digitalWrite(weigandLED, HIGH);
    }
    if (flashingBuzzerCount) {
      digitalWrite(weigandBuzzer, buzzerState);
      buzzerState = !buzzerState;
      flashingBuzzerCount--;
    } else {
      digitalWrite(weigandBuzzer, HIGH);
    }
  }

  if (wg.available())
  {
    Serial.println(wg.getCode());
  }
  if (Serial.available()) {
    String message = Serial.readString();

    if (message == "flash") {
      flashDelay = 150;
      flashingCount = 200;
    } 
    
    else if (message == "approved") {
      flashingCount = 0;
      flashingBuzzerCount = 0;
      digitalWrite(weigandLED, LOW);
      digitalWrite(weigandBuzzer, LOW);
      delay(approvedDelay);
      digitalWrite(weigandLED, HIGH);
      digitalWrite(weigandBuzzer, HIGH);
    } 
    
    else if (message == "denied") {
      flashingCount = 5;
      flashingBuzzerCount = 5;
    }

    else if (message == "stop") {
      flashingCount = 0;
      flashingBuzzerCount = 0;
      digitalWrite(weigandLED, HIGH);
      digitalWrite(weigandBuzzer, HIGH);
    }

    else if (message == "slowflash") {
      flashDelay = 500;
    }

    else if (message == "fastflash") {
      flashDelay = 150;
    }
  }
}
