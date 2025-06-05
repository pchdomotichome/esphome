#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class SI4432Component : public Component, public spi::SPIDevice {
 public:
  void set_cs_pin(GPIOPin *pin) { this->cs_ = pin; }

  void setup() override {
    // Inicialización del chip Si4432 (placeholder)
    ESP_LOGI("si4432", "Inicializando Si4432...");
  }

  void loop() override {
    // Lógica de recepción/transmisión (placeholder)
  }

 protected:
  GPIOPin *cs_;
};

}  // namespace si4432
}  // namespace esphome

