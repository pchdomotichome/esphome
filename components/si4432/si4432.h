#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi_device.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public esphome::Component, public esphome::spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

 protected:
  void read_status();
  uint8_t read_byte(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome
