#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component {
 public:
  void setup() override;
  void loop() override;

  void set_spi(esphome::spi::SPIComponent *spi) { this->spi_ = spi; }
  void set_cs_pin(int cs_pin) { this->cs_pin_ = cs_pin; }

 protected:
  uint8_t read_register(uint8_t reg);

  esphome::spi::SPIComponent *spi_{nullptr};
  int cs_pin_{-1};
};

}  // namespace si4432
}  // namespace esphome

