#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  this->spi_setup();
}

void Si4432Component::loop() {
  static uint32_t last_read = 0;
  if (millis() - last_read > 5000) {
    last_read = millis();

    uint8_t reg07 = read_register(0x07);
    uint8_t reg0C = read_register(0x0C);
    uint8_t reg0D = read_register(0x0D);

    ESP_LOGI(TAG, "Reg 0x07 = 0x%02X | 0x0C = 0x%02X | 0x0D = 0x%02X", reg07, reg0C, reg0D);

    if (this->chip_ok_ != nullptr) {
      bool ok = (reg07 != 0x00) || (reg0C != 0x00) || (reg0D != 0x00);
      this->chip_ok_->publish_state(ok ? 1 : 0);
    }
  }
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