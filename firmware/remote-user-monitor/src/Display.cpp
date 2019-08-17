#include "Display.h"

Display::Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t font_size)
    : display_(0x3C, sda_pin, scl_pin),
      font_size_(font_size),
      max_names_(3),
      offset_(0),
      offset_period_(1500),
      last_offset_time_(0),
      intro_width_(0),
      intro_height_(0),
      intro_bits_(nullptr) {}

void Display::init(const uint8_t *font_data) {
  display_.init();
  display_.setTextAlignment(TEXT_ALIGN_LEFT);
  display_.setFont(font_data);
  display_.display();
}

void Display::initIntro(int16_t width, int16_t height, const uint8_t *bits) {
  intro_width_ = width;
  intro_height_ = height;
  intro_bits_ = bits;
}

void Display::showIntro() {
  display_.clear();
  drawImage(intro_width_, intro_height_, intro_bits_);
  display_.display();
}

void Display::update(const Message &msg) {
  updateOffset(msg);
  display_.clear();

  if (msg.isStale())
    drawImage(intro_width_, intro_height_, intro_bits_);
  else
    drawUsers(msg);

  display_.display();
}

void Display::updateOffset(const Message &msg) {
  if (msg.users > max_names_) {
    unsigned long current_time = millis();
    if ((unsigned long)(current_time - last_offset_time_) >= offset_period_) {
      offset_ = (offset_ + 1) % msg.users;
      last_offset_time_ = current_time;
    }
  } else {
    offset_ = 0;
    last_offset_time_ = millis();
  }
}

void Display::drawImage(int16_t width, int16_t height, const uint8_t *bits) {
  if (bits == nullptr) return;
  int16_t x = (display_.getWidth() - width) / 2;
  int16_t y = (display_.getHeight() - height) / 2;
  display_.drawXbm(x, y, width, height, bits);
}

void Display::drawUsers(const Message &msg) {
  // Set number of users
  display_.drawString(0, 0, "#users: ");
  display_.drawString(60, 0, String(msg.users));

  // Set user names
  uint8_t num_users = min(msg.users, max_names_);
  for (uint8_t i = 0; i < num_users; ++i) {
    uint8_t j = (i + offset_) % msg.users;
    display_.drawString(0, (i + 1) * font_size_, msg.names[j]);
  }
}