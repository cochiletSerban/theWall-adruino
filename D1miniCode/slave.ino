#include "SPISlave.h"

void setup() {
  Serial.begin(115200);
  SPISlave.onData([](uint8_t * data, size_t len) {
    Serial.printf("songId: %d\n", data[0]);
  });
  SPISlave.begin();
}

void loop() {}