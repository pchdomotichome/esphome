#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432Component...");
  this->spi_setup();
}

void Si4432Component::loop() {
  // Polling or interrupt-based handling here
  this->read_status();
}

void Si4432Component::read_status() {
  uint8_t status = this->read_byte(0x02);
  ESP_LOGD(TAG, "Read status byte: 0x%02X", status);
}

uint8_t Si4432Component::read_byte(uint8_t reg) {
  this->enable();
  this->write_byte(reg & 0x7F);  // Read operation
  uint8_t val = this->read_byte();
  this->disable();
  return val;
}

}  // namespace si4432
}  // namespace esphome