#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432...");
  this->spi_setup();
}

void Si4432Component::loop() {
  // Example read register loop
  uint8_t reg_val = this->read_register(0x01);
  ESP_LOGD(TAG, "Reg 0x01: 0x%02X", reg_val);
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();
  this->write_byte(reg | 0x80);
  this->write_byte(value);
  this->disable();
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->write_byte(reg & 0x7F);
  uint8_t value = this->read_byte();
  this->disable();
  return value;
}

}  // namespace si4432
}  // namespace esphome