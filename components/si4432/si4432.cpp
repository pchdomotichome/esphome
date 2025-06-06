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
  const unsigned long now = millis();
  if (now - this->last_read_time_ >= 5000) {
    this->last_read_time_ = now;
    this->read_diagnostics();
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->transfer(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->transfer(0x00);  // Dummy write to read
  this->disable();  // CS HIGH
  return val;
}

void Si4432Component::read_diagnostics() {
  ESP_LOGD(TAG, "Reading Si4432 diagnostics...");

  uint8_t dev_type = this->read_register(0x00);
  uint8_t version  = this->read_register(0x01);
  uint8_t status   = this->read_register(0x02);
  uint8_t op_mode  = this->read_register(0x07);
  uint8_t rssi     = this->read_register(0x26);

  ESP_LOGI(TAG, "Device Type: 0x%02X", dev_type);
  ESP_LOGI(TAG, "Version    : 0x%02X", version);
  ESP_LOGI(TAG, "Status     : 0x%02X", status);
  ESP_LOGI(TAG, "Op Mode    : 0x%02X", op_mode);
  ESP_LOGI(TAG, "RSSI       : 0x%02X", rssi);
}

}  // namespace si4432
}  // namespace esphome

