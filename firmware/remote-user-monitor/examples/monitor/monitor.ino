#include <SPI.h>

#include <Button.h>
#include <Display.h>
#include <Led.h>
#include <Parser.h>

#include "intro.h"

Parser parser;
Display display(5, 4, 16);
Led led(12, 14, 2000);
Button button;

void setup() {
  display.init(ArialMT_Plain_16);
  display.initIntro(intro_width, intro_height, intro_bits);
  display.showIntro();
  delay(2000);

  Serial.begin(115200);
  Serial.setTimeout(1);

  led.init();
  button.init(16);
}

void loop() {
  parser.update();
  display.update(parser.msg);
  led.update(parser.msg);
  button.update();
}
