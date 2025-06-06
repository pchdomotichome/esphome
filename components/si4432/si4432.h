
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component, public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1MHZ> {
 public:
  void setup() override;
  void loop() override;

  void set_status_sensor(sensor::Sensor *sensor) { status_sensor_ = sensor; }

 protected:
  uint8_t read_register(uint8_t reg);
  sensor::Sensor *status_sensor_{nullptr};
};

}  // namespace si4432
}  // namespace esphome
