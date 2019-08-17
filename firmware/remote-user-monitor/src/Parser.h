#ifndef __PARSER__
#define __PARSER__

#include "Types.h"

class Parser {
 public:
  Parser();
  /**
   * \brief Reads messages from the serial
   * \details Messages have the following format:
   * #<PS_FLAG> <NAME_0>,<NAME_1>,...,<NAME_N>\n
   */
  void update();

  Message msg;

 private:
  void reset();
  void addChar(char c);
  void parse();
  bool isStarted();
  bool isEnded();
  void setStarted();
  void setEnded();

  bool started_, ended_;
  char buffer_[256];
  uint8_t size_;
};

#endif  // __PARSER__
