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

 protected:
  GPIOPin *cs_pin_;
};

}  // namespace si4432
}  // namespace esphome

