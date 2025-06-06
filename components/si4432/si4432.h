#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"  // ✅ este es el include correcto en 2025.5.2

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice<Si4432Component> {
 public:
  void setup() override;
  void loop() override;

 protected:
  uint8_t read_register(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome

