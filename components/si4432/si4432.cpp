#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");

  if (!this->spi_setup()) {
    ESP_LOGE(TAG, "SPI setup failed");
    if (this->chip_ok_ != nullptr)
      this->chip_ok_->publish_state(0.0f);
    return;
  }

  // Leer algunos registros clave
  uint8_t reg_07 = this->read_register(0x07);
  uint8_t reg_08 = this->read_register(0x08);
  uint8_t reg_0C = this->read_register(0x0C);

  ESP_LOGI(TAG, "Reg 0x07 (Device Status) = 0x%02X", reg_07);
  ESP_LOGI(TAG, "Reg 0x08 (Interrupt Status 1) = 0x%02X", reg_08);
  ESP_LOGI(TAG, "Reg 0x0C (Device Type) = 0x%02X", reg_0C);

  if (this->chip_ok_ != nullptr)
    this->chip_ok_->publish_state(1.0f);
}

void Si4432Component::loop() {
  static uint32_t last_check = 0;
  const uint32_t now = millis();
  if (now - last_check < 5000)
    return;
  last_check = now;

  uint8_t reg_07 = this->read_register(0x07);
  uint8_t reg_08 = this->read_register(0x08);
  uint8_t reg_0C = this->read_register(0x0C);

  ESP_LOGD(TAG, "[Loop] Reg 0x07 = 0x%02X | 0x08 = 0x%02X | 0x0C = 0x%02X", reg_07, reg_08, reg_0C);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW

  spi::write_byte(this->spi_bus_, reg & 0x7F);
  uint8_t val = spi::read_byte(this->spi_bus_);

  this->disable();  // CS HIGH
  return val;
}

uint8_t Si4432Component::transfer(uint8_t data) {
  return spi::transfer_byte(this->spi_bus_, data);
}

}  // namespace si4432
}  // namespace esphome

