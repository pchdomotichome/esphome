
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(uint8_t pin) { this->cs_pin_ = pin; }
  void set_irq_pin(GPIOPin *pin) { this->irq_pin_ = pin; }

 protected:
  uint8_t cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome
