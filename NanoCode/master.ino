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

void setup() {
  Serial.begin(115200);
  SPI.begin();
  esp.begin();
}

void loop() {
  delay(1000);
  send(rand() % (65 + 1 - 0) + 0);
}