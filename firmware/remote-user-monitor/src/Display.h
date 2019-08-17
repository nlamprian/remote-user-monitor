#ifndef __DISPLAY__
#define __DISPLAY__

#include <SSD1306Wire.h>

#include "Types.h"

class Display {
 public:
  Display(uint8_t sda_pin, uint8_t scl_pin, uint8_t font_size);
  void init(const uint8_t *font_data);
  void initIntro(int16_t width, int16_t height, const uint8_t *bits);
  void showIntro();
  void update(const Message &msg);

 private:
  void updateOffset(const Message &msg);
  void drawImage(int16_t width, int16_t height, const uint8_t *bits);
  void drawUsers(const Message &msg);

  SSD1306Wire display_;
  const uint8_t font_size_;
  const uint8_t max_names_;

  uint8_t offset_;
  unsigned long offset_period_;
  unsigned long last_offset_time_;

  int16_t intro_width_;
  int16_t intro_height_;
  const uint8_t *intro_bits_;
};

#endif  // __DISPLAY__
