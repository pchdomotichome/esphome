#include "si4432.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: CS pin configured");
  this->cs_pin_->setup();  // Configurar CS como salida
  this->cs_pin_->digital_write(true);  // CS HIGH
}

void Si4432Component::loop() {
  uint32_t now = millis();
  if (now - this->last_read_time_ < 5000) {
    return;
  }
  this->last_read_time_ = now;

  uint8_t status = this->read_register(0x07);      // Operating Mode
  uint8_t device_type = this->read_register(0x00); // Device Type
  uint8_t version = this->read_register(0x01);     // Version
  uint8_t status2 = this->read_register(0x02);     // Status

  ESP_LOGI(TAG, "SI4432 Registers:");
  ESP_LOGI(TAG, "  Reg 0x00 (Device Type)   = 0x%02X", device_type);
  ESP_LOGI(TAG, "  Reg 0x01 (Version)       = 0x%02X", version);
  ESP_LOGI(TAG, "  Reg 0x02 (Status)        = 0x%02X", status2);
  ESP_LOGI(TAG, "  Reg 0x07 (Operating Mode)= 0x%02X", status);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->cs_pin_->digital_write(false);  // CS LOW
  delayMicroseconds(1);

  spi::transfer_byte(this->spi_, reg & 0x7F);  // Clear MSB for read
  uint8_t value = spi::transfer_byte(this->spi_, 0x00);  // Dummy byte to receive data

  this->cs_pin_->digital_write(true);  // CS HIGH
  delayMicroseconds(1);
  return value;
}

}  // namespace si4432
}  // namespace esphome


