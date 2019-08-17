#include "Led.h"

Led::Led(int data_pin, int clock_pin, unsigned long flash_period)
    : colors_{0x070000, 0x050700, 0x000700},
      led_(1, data_pin, clock_pin, DOTSTAR_BRG),
      mode_(LedMode::STEADY),
      color_(colors_[0]),
      flash_half_period_(flash_period / 2),
      last_flash_time_(0),
      flash_state_(false) {}

void Led::init() {
  led_.begin();
  led_.show();
}

void Led::update(const Message &msg) {
  setMode(msg);
  setColor();
}

void Led::setMode(const Message &msg) {
  if (msg.isStale()) {
    mode_ = LedMode::STEADY;
    color_ = 0;
  } else if (msg.ps) {
    if (msg.users > 0) {
      mode_ = LedMode::STEADY;
      color_ = colors_[2];
    } else {
      mode_ = LedMode::FLASH;
      color_ = colors_[2];
    }
  } else {
    if (msg.users > 0) {
      mode_ = LedMode::STEADY;
      color_ = colors_[1];
    } else {
      mode_ = LedMode::STEADY;
      color_ = colors_[0];
    }
  }
}

void Led::setColor() {
  if (mode_ == LedMode::FLASH) {
    unsigned long current_time = millis();
    if ((unsigned long)(current_time - last_flash_time_) >=
        flash_half_period_) {
      flash_state_ = !flash_state_;
      last_flash_time_ = current_time;
    }
    led_.setPixelColor(0, flash_state_ ? color_ : 0);
  } else {
    led_.setPixelColor(0, color_);
  }
  led_.show();
}