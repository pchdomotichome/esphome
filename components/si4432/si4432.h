
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi_device.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::DATA; }

 protected:
  void read_status();
};

}  // namespace si4432
}  // namespace esphome
