#include "Parser.h"
#include <Arduino.h>

// #define DEBUG

Parser::Parser() { reset(); }

void Parser::update() {
  while (Serial.available()) {
    char input = static_cast<char>(Serial.read());
    if (input == '#') {
      setStarted();
      continue;
    }
    if (not isStarted()) continue;
    if (input == '\n') {
      setEnded();
      break;
    }
    addChar(input);
  }
  if (isEnded()) parse();
}

void Parser::parse() {
  msg.ps = strtoul(buffer_, nullptr, 10);
  msg.users = 0;
  char *name = strtok(buffer_ + 2, ",");
  while (name != nullptr) {
    strcpy(msg.names[msg.users], name);
    ++msg.users;
    name = strtok(nullptr, ",");
  }
  msg.stamp = millis();
#ifdef DEBUG
  Serial.println("==Message==");
  Serial.print("Process: ");
  Serial.println(msg.ps);
  Serial.print("Users: ");
  Serial.println(static_cast<int>(msg.users));
  Serial.print("Names: ");
  for (uint8_t i = 0; i < msg.users; ++i) {
    Serial.print(msg.names[i]);
    if (i < msg.users - 1) Serial.print(", ");
  }
  Serial.println("\n");
#endif
  reset();
}

void Parser::reset() {
  memset(&buffer_, 0, sizeof(buffer_));
  size_ = 0;
  started_ = false;
  ended_ = false;
}

void Parser::addChar(char c) {
#ifdef DEBUG
  Serial.print(static_cast<byte>(c));
  Serial.print(" ");
#endif
  buffer_[size_++] = c;
}

bool Parser::isStarted() { return started_; }

bool Parser::isEnded() { return ended_; }

void Parser::setStarted() {
#ifdef DEBUG
  Serial.println("setStarted");
#endif
  if (isStarted()) reset();
  started_ = true;
}

void Parser::setEnded() {
#ifdef DEBUG
  Serial.println("\nsetEnded");
#endif
  started_ = false;
  ended_ = true;
}
