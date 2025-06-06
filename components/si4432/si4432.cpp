
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  this->spi_setup();
  uint8_t val = this->read_register(0x07);
  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X", val);
}

void Si4432Component::loop() {
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer(reg & 0x7F);
  uint8_t val = this->transfer(0x00);
  this->disable();
  return val;
}

}  // namespace si4432
}  // namespace esphome
