
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  spi_setup();
}

void Si4432Component::loop() {
  static uint32_t last_check = 0;
  uint32_t now = millis();
  if (now - last_check < 5000) return;  // Cada 5 segundos
  last_check = now;

  uint8_t reg = read_register(0x07);  // Operating Mode and Function Control 1
  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X", reg);

  if (this->status_sensor_ != nullptr) {
    bool ok = reg != 0x00 && reg != 0xFF;
    this->status_sensor_->publish_state(ok);
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  enable();
  transfer_byte(reg & 0x7F);
  uint8_t val = transfer_byte(0x00);
  disable();
  return val;
}

}  // namespace si4432
}  // namespace esphome
