#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432...");
  this->spi_setup();
}

void Si4432Component::loop() {
  // Placeholder loop
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();
  this->transfer(reg | 0x80);
  this->transfer(value);
  this->disable();
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer(reg & 0x7F);
  uint8_t value = this->transfer(0);
  this->disable();
  return value;
}

}  // namespace si4432
}  // namespace esphome
