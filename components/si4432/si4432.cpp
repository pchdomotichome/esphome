#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  this->spi_setup();
  ESP_LOGI(TAG, "Si4432 setup complete");
}

void Si4432Component::loop() {
  // Opcional: lógica de recepción
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();
  this->transfer_byte(reg | 0x80);
  this->transfer_byte(value);
  this->disable();
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer_byte(reg & 0x7F);
  uint8_t value = this->transfer_byte(0);
  this->disable();
  return value;
}

}  // namespace si4432
}  // namespace esphome
