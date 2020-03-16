#include <SPI.h>

class ESPMaster {
  private:
    uint8_t _ss_pin;
    void _pulseSS() {
      digitalWrite(_ss_pin, HIGH);
      delayMicroseconds(5);
      digitalWrite(_ss_pin, LOW);
    }
  public:
    ESPMaster(uint8_t pin): _ss_pin(pin) {}
    void begin() {
      pinMode(_ss_pin, OUTPUT);
      _pulseSS();
    }
    void writeData(uint8_t data) {
      _pulseSS();
      SPI.transfer(0x02);
      SPI.transfer(0x00);
      SPI.transfer(data);
      _pulseSS();
    }
};

ESPMaster esp(SS);

void send(uint8_t message) {
  Serial.println(message);
  esp.writeData(message);
  delay(10);
}

byte controlPins[] = {
  B00000000,
  B10000000,
  B01000000,
  B11000000,
  B00100000,
  B10100000,
  B01100000,
  B11100000,
  B00010000,
  B10010000,
  B01010000,
  B11010000,
  B00110000,
  B10110000,
  B01110000,
  B11110000
};

void setup() {
  Serial.begin(115200);
  SPI.begin();
  esp.begin();
  // DDRD = B11110000; // set D4-D7 to Output and D3-D2 to input
  for (int i = 4; i < 10; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(3, INPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  // DDRB = B00000011; // set D8-D9 to Ouput and D10-D13 to input
}

void setInputPinToMuxPin(int muxPin) {
  PORTD = controlPins[muxPin];
}

void selectMux(int mux) {
  switch(mux) {
    case 0:
      digitalWrite(8, LOW);
      digitalWrite(9, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A4, HIGH);
      break;
    case 1:
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(A5, HIGH);
      digitalWrite(A4, HIGH);
      break;
    case 2:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(A5, LOW);
      digitalWrite(A4, HIGH);
      break;
    case 3:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(A5, HIGH);
      digitalWrite(A4, LOW);
      break;
  }
}

void getActiveAlbum() {
  selectMux(0);
  for (int i = 0; i < 64; i++) {
    if ( i == 16 || i == 32 || i == 48) {
      selectMux(i/16);
    }
    setInputPinToMuxPin(i % 16);
    if ( digitalRead(3) == 1 ) {
      Serial.println(i);
      // write to SPI to be sent to d2 mini
      if (i == 0) send(100);
      send(i);
    };
  }
}

void dumpMuxArr(byte* muxArr) {
  for (int i = 0; i<16; i++) {
    Serial.print(muxArr[i]);
    Serial.print(" ");
  }
  Serial.println("");
}



void loop()
{
  getActiveAlbum();
  delay(200);
}