#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public PollingComponent, public spi::SPIDevice {
 public:
  void set_cs_pin(GPIOPin *cs) { this->cs_pin_ = cs; }
  void set_irq_pin(GPIOPin *irq) { this->irq_pin_ = irq; }

  void setup() override;
  void update() override;

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome