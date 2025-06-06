#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: SPI device ready");
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->transfer(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->transfer(0x00);  // Dummy write to read
  this->disable();  // CS HIGH
  return val;
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop running...");
  uint8_t reg_val = read_register(0x07);
  ESP_LOGI(TAG, "Registro 0x07 (Device Status): 0x%02X", reg_val);
}

}  // namespace si4432
}  // namespace esphome

