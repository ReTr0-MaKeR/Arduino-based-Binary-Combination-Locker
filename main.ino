/*
Author: Md. Tanvir Hassan
Department of EEE
Daffodil International University
Date of development: 13th May 2024
*/

const int masterSwitchPins[] = {6, 7, 8, 9};
const int numMasterSwitches = 4;

const int keySwitchPins[] = {2, 3, 4, 5};
const int numKeySwitches = 4;

const int entrySwitchPin = 11;
const int greenLedPin = 12;
const int redLedPin = 13;

int masterCombination[numMasterSwitches];

void setup() {
  Serial.begin(9600);
  while (!Serial);

  for (int i = 0; i < numMasterSwitches; ++i) {
    pinMode(masterSwitchPins[i], INPUT_PULLUP);
  }

  for (int i = 0; i < numKeySwitches; ++i) {
    pinMode(keySwitchPins[i], INPUT_PULLUP);
  }

  pinMode(entrySwitchPin, INPUT_PULLUP);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  for (int i = 0; i < numMasterSwitches; ++i) {
    masterCombination[i] = 0;
  }
}

void loop() {
  int entrySwitchState = digitalRead(entrySwitchPin);

  Serial.print("Master Key: ");
  for (int i = 0; i < numMasterSwitches; ++i) {
    Serial.print(digitalRead(masterSwitchPins[i]));
  }
  Serial.print("    ");

  Serial.print("Input Key: ");
  for (int i = 0; i < numKeySwitches; ++i) {
    Serial.print(digitalRead(keySwitchPins[i]));
  }
  Serial.println();

  if (entrySwitchState == LOW) {
    if (checkCombination()) {
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      Serial.println("Access Granted");
    } else {
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, HIGH);
      Serial.println("Access Denied");
    }
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(redLedPin, LOW);
  }

  for (int i = 0; i < numMasterSwitches; ++i) {
    masterCombination[i] = digitalRead(masterSwitchPins[i]);
  }

  delay(100);
}

bool checkCombination() {
  for (int i = 0; i < numMasterSwitches; ++i) {
    if (digitalRead(keySwitchPins[i]) != masterCombination[i]) {
      return false;
    }
  }
  return true;
}
