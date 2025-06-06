#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component {
 public:
  void setup() override;
  void loop() override;

  void set_spi_parent(spi::SPIComponent *parent) { this->spi_ = parent; }
  void set_cs_pin(GPIOPin *cs) { this->cs_ = cs; }

 protected:
  uint8_t read_register(uint8_t reg);

  spi::SPIComponent *spi_;
  GPIOPin *cs_;
  uint32_t last_read_time_{0};
};

}  // namespace si4432
}  // namespace esphome

