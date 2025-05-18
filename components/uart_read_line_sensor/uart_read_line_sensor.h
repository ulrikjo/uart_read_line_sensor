#pragma once

#include "esphome/components/uart/uart.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/core/component.h"

namespace esphome {
namespace uart_read_line_sensor {

class UartReadLineSensor : public Component, public UARTDevice, public text_sensor::TextSensor {
 public:
  UartReadLineSensor(UARTComponent *parent) : UARTDevice(parent) {}

  void setup() override {}
  void loop() override {
    while (this->available()) {
      char c = this->read();
      if (c == '\n' || buffer_index_ >= sizeof(buffer_) - 1) {
        buffer_[buffer_index_] = '\0';
        this->publish_state(buffer_);
        buffer_index_ = 0;
      } else {
        buffer_[buffer_index_++] = c;
      }
    }
  }

 protected:
  char buffer_[256];
  size_t buffer_index_{0};
};

}  // namespace uart_read_line_sensor
}  // namespace esphome
