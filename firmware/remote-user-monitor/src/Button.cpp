#include "Button.h"

Button::Button() : last_input_(true) {}

void Button::init(uint8_t pin) {
  pinMode(pin, INPUT_PULLUP);
  debouncer_.attach(pin);
  debouncer_.interval(10);
}

void Button::update() {
  debouncer_.update();
  int input = debouncer_.read();
  if (not input and last_input_) Serial.println("GTFO");
  last_input_ = input;
}
