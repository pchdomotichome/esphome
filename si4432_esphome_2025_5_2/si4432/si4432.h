#pragma once

#include "esphome/components/spi/spi.h"
#include "esphome/core/component.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public PollingComponent, public spi::SPIDevice {
 public:
  void update() override;
  void setup() override;
  void dump_config() override;

  void set_cs_pin(GPIOPin *pin);
  void set_irq_pin(GPIOPin *pin);

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome