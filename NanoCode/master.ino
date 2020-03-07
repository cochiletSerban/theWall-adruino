#include <SPI.h>

class ESPMaster {
  private:
    uint8_t _ss_pin;
  public:
    ESPMaster(uint8_t pin): _ss_pin(pin) {}
    void begin() {
      pinMode(_ss_pin, OUTPUT);
      digitalWrite(_ss_pin, HIGH);
    }
    void writeData(uint8_t * data, size_t len) {
      uint8_t i = 0;
      digitalWrite(_ss_pin, LOW);
      SPI.transfer(0x02);
      SPI.transfer(0x00);
      SPI.transfer((uint8_t)(rand() % (60 + 1 - 0) + 0));
      digitalWrite(_ss_pin, HIGH);
    }
    void writeData(const char * data) {
      writeData((uint8_t *)data, strlen(data));
    }
};

ESPMaster esp(SS);

void send(const char * message) {
  Serial.print("Master: ");
  Serial.println(message);
  esp.writeData(message);
  delay(10);
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  esp.begin();
}

void loop() {
  delay(1000);
  send("Are you alive?");
}