#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class SI4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;

  void set_cs_pin(GPIOPin *cs) { this->cs_pin_ = cs; }
  void set_irq_pin(GPIOPin *irq) { this->irq_pin_ = irq; }

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome