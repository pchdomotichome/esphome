#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component,
                        public spi::SPIDevice<
                            spi::BIT_ORDER_MSB_FIRST,
                            spi::CLOCK_POLARITY_LOW,
                            spi::CLOCK_PHASE_LEADING,
                            spi::DATA_RATE_125KHZ> {
 public:
  void setup() override;
  void loop() override;

 protected:
  uint8_t read_register(uint8_t reg);
  void write_register(uint8_t reg, uint8_t value);
  uint32_t last_log_time_{0};
};

}  // namespace si4432
}  // namespace esphome

