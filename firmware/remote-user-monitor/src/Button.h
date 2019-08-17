#ifndef __BUTTON__
#define __BUTTON__

#include <Bounce2.h>

class Button {
 public:
  Button();
  void init(uint8_t pin);
  void update();

 private:
  Bounce debouncer_;
  bool last_input_;
};

#endif  // __BUTTON__
