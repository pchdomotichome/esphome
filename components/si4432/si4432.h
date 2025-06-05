#pragma once

#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void set_irq_pin(GPIOPin *pin) { irq_pin_ = pin; }

  void setup() override;
  void loop() override;

 protected:
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome
