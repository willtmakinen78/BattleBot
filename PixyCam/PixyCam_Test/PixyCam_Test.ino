#include <SPI.h>  
#include <Pixy.h>

Pixy pixy;

int refreshPerSec = 4;
int refreshInterval;

void setup() {
  Serial.begin(9600);
  Serial.print("Starting...\n");

  pixy.init();

  refreshInterval = 50/refreshPerSec;
}

void loop() {
  static int counter = 0;
  uint16_t blocks;
  char buf[32]; 
  blocks = pixy.getBlocks();

  if (blocks) {
    counter++;
    if (counter % refreshInterval == 0) {
      sprintf(buf, "Detected %d:\n", blocks);
      Serial.print(buf);

      float avX;
      for (int j = 0; j < blocks; j++) {
        sprintf(buf, "  block %d: ", j);
        Serial.print(buf); 
        pixy.blocks[j].print();

        avX += pixy.blocks[j].x;
      }
      avX /= blocks;
      Serial.print("Average X: "); Serial.println(avX);
    }
  }

}
