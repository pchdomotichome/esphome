#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");

  // Inicializa el SPI
  this->spi_setup();

  ESP_LOGI(TAG, "Si4432 setup: CS pin is GPIO%d", this->cs_pin_);
}

void Si4432Component::loop() {
  static uint32_t last_read = 0;
  if (millis() - last_read > 5000) {
    last_read = millis();

    // Leer algunos registros clave del chip Si4432
    uint8_t reg07 = this->read_register(0x07);  // Operating mode and function control 1
    uint8_t reg08 = this->read_register(0x08);  // Operating mode and function control 2
    uint8_t reg0C = this->read_register(0x0C);  // Device status

    ESP_LOGI(TAG, "Reg 0x07 = 0x%02X | Reg 0x08 = 0x%02X | Reg 0x0C = 0x%02X", reg07, reg08, reg0C);
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->transfer(reg & 0x7F);  // Clear MSB to indicate read
  uint8_t value = this->transfer(0x00);  // Dummy byte to read response
  this->disable();  // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome



