#include <SPI.h>
#include <Pixy.h>

Pixy pixy;


void setup() {
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();
}

void loop() {
  float tarX = targetPosition(4);
  static float lastTarX;

  if (tarX != lastTarX) {
    //turn towards target
    lastTarX = tarX;
  }
  Serial.print("Target X: "); Serial.println(tarX);
}
float targetPosition(int refreshPerSec) {
  int refreshInterval = 50 / refreshPerSec;
  static int counter = 0;
  uint16_t blocks;
  char buf[32];
  static float avX;

  blocks = pixy.getBlocks();

  if (blocks) {
    counter++;
    if (counter % refreshInterval == 0) {
      avX = 0;
      //            sprintf(buf, "Detected %d:\n", blocks);
      //            Serial.print(buf);

      for (int j = 0; j < blocks; j++) {
        //                sprintf(buf, "  block %d: ", j);
        //                Serial.print(buf);
        //                pixy.blocks[j].print();

        avX += pixy.blocks[j].x;
      }
      avX /= blocks;
      //       Serial.print("Average X: "); Serial.println(avX);
    }
  }
  return avX;
}

