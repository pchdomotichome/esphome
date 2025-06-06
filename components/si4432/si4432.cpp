#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  this->spi_setup();
  ESP_LOGI(TAG, "Si4432 setup done");
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->transfer(0x00);  // Dummy write to read
  this->disable();
  return val;
}

void Si4432Component::loop() {
  static uint32_t last_log = 0;
  uint32_t now = millis();
  if (now - last_log < 5000) return;
  last_log = now;

  uint8_t reg_07 = read_register(0x07);  // Device status
  uint8_t reg_02 = read_register(0x02);  // Device type
  uint8_t reg_03 = read_register(0x03);  // Version

  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X", reg_07);
  ESP_LOGI(TAG, "Reg 0x02 (Device Type) = 0x%02X", reg_02);
  ESP_LOGI(TAG, "Reg 0x03 (Version) = 0x%02X", reg_03);

  if (this->chip_ok_ != nullptr) {
    this->chip_ok_->publish_state((reg_02 == 0x08) && (reg_03 != 0x00));
  }
}

}  // namespace si4432
}  // namespace esphome


