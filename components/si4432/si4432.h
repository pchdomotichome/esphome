#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(uint8_t pin) { cs_pin_ = pin; }

 protected:
  uint8_t cs_pin_;
  uint32_t last_read_time_{0};

  uint8_t read_register(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome

