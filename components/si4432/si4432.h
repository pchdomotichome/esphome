#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component {
 public:
  void setup() override;
  void loop() override;

  void set_spi(spi::SPIComponent *spi) { this->spi_ = spi; }
  void set_cs_pin(GPIOPin *cs) { this->cs_pin_ = cs; }

 protected:
  spi::SPIComponent *spi_;
  GPIOPin *cs_pin_;
  uint32_t last_read_time_{0};

  uint8_t read_register(uint8_t reg);
};

}  // namespace si4432
}  // namespace esphome

