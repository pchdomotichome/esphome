#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  this->spi_setup();  // Inicializa el dispositivo SPI

  // Leer algunos registros clave para verificar comunicación
  uint8_t reg_07 = this->read_register(0x07);
  ESP_LOGI(TAG, "Reg 0x07 (Device Status) = 0x%02X", reg_07);

  uint8_t reg_02 = this->read_register(0x02);
  ESP_LOGI(TAG, "Reg 0x02 (Interrupt Enable 1) = 0x%02X", reg_02);

  uint8_t reg_03 = this->read_register(0x03);
  ESP_LOGI(TAG, "Reg 0x03 (Interrupt Enable 2) = 0x%02X", reg_03);
}

void Si4432Component::loop() {
  static uint32_t last_read = 0;
  const uint32_t interval_ms = 5000;
  uint32_t now = millis();

  if (now - last_read >= interval_ms) {
    last_read = now;

    uint8_t device_status = this->read_register(0x07);
    ESP_LOGI(TAG, "[Loop] Reg 0x07 = 0x%02X", device_status);
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();                              // CS LOW
  this->write_byte(reg & 0x7F);                // Dirección de lectura (MSB=0)
  uint8_t value = this->read_byte();           // Dummy → leer valor
  this->disable();                             // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome






