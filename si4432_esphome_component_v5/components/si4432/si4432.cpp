#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  this->spi_setup();
  ESP_LOGI(TAG, "SI4432 setup completed.");
}

void Si4432Component::loop() {
  // Placeholder: read status or receive packets
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
  uint8_t val = this->transfer_byte(0x00);
  this->disable();
  return val;
}

}  // namespace si4432
}  // namespace esphome
