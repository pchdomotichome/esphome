#pragma once
#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void set_cs_pin(uint8_t cs) { this->cs_pin_ = cs; }

  void setup() override;
  void loop() override;

 protected:
  uint8_t cs_pin_;
  void write_register(uint8_t reg, uint8_t value);
  uint8_t read_register(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome
