#include "si4432.h"

namespace esphome {
namespace si4432 {

void Si4432Component::setup() {
  ESP_LOGI("si4432", "Setup completo.");
}

void Si4432Component::loop() {
  uint8_t reg_val = this->read_register(0x07);
  ESP_LOGI("si4432", "Reg 0x07 = 0x%02X", reg_val);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->write_byte(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->read_byte();  // Read response
  this->disable();  // CS HIGH
  return val;
}

}  // namespace si4432
}  // namespace esphome

