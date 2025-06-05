#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"  // Ya incluye SPIDevice en 2025.5.2

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice {
 public:
  void setup() override;
  void loop() override;

 protected:
  void read_status();
};

}  // namespace si4432
}  // namespace esphome

