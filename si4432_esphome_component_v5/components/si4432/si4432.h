#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(GPIOPin *pin) { this->cs_pin_ = pin; }
  void set_irq_pin(GPIOPin *pin) { this->irq_pin_ = pin; }

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;

  void write_register(uint8_t reg, uint8_t value);
  uint8_t read_register(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome
