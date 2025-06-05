#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(GPIOPin *pin);
  void set_irq_pin(GPIOPin *pin);

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome