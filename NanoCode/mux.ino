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
  Serial.begin(9600);
  DDRD = B11110000; // set D4-D7 to Output and D3-D2 to input
  DDRB = B00000011; // set D8-D9 to Ouput and D10-D13 to input
}

void setInputPinToMuxPin(int muxPin) {
  PORTD = controlPins[muxPin];
}

void selectMux(int mux) {
  switch(mux) {
    case 0:
      PORTB = B00000010;
      break;
    case 1:
      PORTB = B00000001;
      break;
    case 2:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      break;
    case 3:
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
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
      // write to i2c to be sent to d2 mini
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