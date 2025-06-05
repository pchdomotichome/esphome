
#pragma once
#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"
#include "esphome/core/gpio.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void set_cs_pin(GPIOPin *cs) { cs_pin_ = cs; }
  void set_irq_pin(GPIOPin *irq) { irq_pin_ = irq; }

  void setup() override;
  void loop() override;

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome
