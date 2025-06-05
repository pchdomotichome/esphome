
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class SI4432Component : public Component, public spi::SPIDevice {
 public:
  void set_cs_pin(GPIOPin *pin) { cs_pin_ = pin; }
  void set_irq_pin(GPIOPin *pin) { irq_pin_ = pin; }

  void setup() override {
    // Inicialización del transceptor aquí si se desea
  }

  void loop() override {
    // Bucle principal
  }

 protected:
  GPIOPin *cs_pin_;
  GPIOPin *irq_pin_;
};

}  // namespace si4432
}  // namespace esphome
