
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

  void set_cs_pin(int pin) { cs_pin_ = pin; }

 protected:
  int cs_pin_{-1};
};

}  // namespace si4432
}  // namespace esphome
