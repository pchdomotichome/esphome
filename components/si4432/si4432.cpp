#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  spi_setup();
  ESP_LOGI(TAG, "Si4432 setup complete");
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - last_read_time_ < 5000) return;
  last_read_time_ = now;

  uint8_t type = read_register(0x00);
  uint8_t version = read_register(0x01);
  uint8_t status = read_register(0x02);

  chip_ok_ = (type == 0x08) && (version == 0x06 || version == 0x04);

  if (status_sensor_ != nullptr)
    status_sensor_->publish_state(chip_ok_);

  if (chip_ok_) {
    ESP_LOGI(TAG, "Si4432 OK — Tipo: 0x%02X, Versión: 0x%02X", type, version);
  } else {
    ESP_LOGW(TAG, "Si4432 no responde correctamente — Tipo: 0x%02X, Versión: 0x%02X", type, version);
  }

  ESP_LOGD(TAG, "Reg 0x02 (Status) = 0x%02X", status);
  ESP_LOGD(TAG, "Reg 0x03 (Int Status 1) = 0x%02X", read_register(0x03));
  ESP_LOGD(TAG, "Reg 0x04 (Int Status 2) = 0x%02X", read_register(0x04));
  ESP_LOGD(TAG, "Reg 0x07 (Operating Mode) = 0x%02X", read_register(0x07));
  ESP_LOGD(TAG, "Reg 0x08 (Function Control) = 0x%02X", read_register(0x08));
  ESP_LOGD(TAG, "Reg 0x75 (Band Select) = 0x%02X", read_register(0x75));
  ESP_LOGD(TAG, "Reg 0x76 = 0x%02X", read_register(0x76));
  ESP_LOGD(TAG, "Reg 0x77 = 0x%02X", read_register(0x77));
  ESP_LOGD(TAG, "Reg 0x78 = 0x%02X", read_register(0x78));
  ESP_LOGD(TAG, "Reg 0x26 (RSSI) = 0x%02X", read_register(0x26));
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer_byte(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->transfer_byte(0x00);  // Dummy write
  this->disable();
  return val;
}

}  // namespace si4432
}  // namespace esphome


