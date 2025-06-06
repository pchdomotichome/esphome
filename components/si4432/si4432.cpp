#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup iniciado");
  this->spi_setup();  // Inicializa SPI como SPIDevice
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - this->last_log_time_ >= 5000) {
    this->last_log_time_ = now;

    uint8_t reg_07 = read_register(0x07);  // Operating Mode & Function Control 1
    uint8_t reg_0C = read_register(0x0C);  // Device Status
    uint8_t reg_0D = read_register(0x0D);  // Interrupt Status 1
    uint8_t reg_0E = read_register(0x0E);  // Interrupt Status 2

    ESP_LOGI(TAG, "[Loop] Reg 0x07 = 0x%02X", reg_07);
    ESP_LOGI(TAG, "[Loop] Reg 0x0C = 0x%02X", reg_0C);
    ESP_LOGI(TAG, "[Loop] Reg 0x0D = 0x%02X", reg_0D);
    ESP_LOGI(TAG, "[Loop] Reg 0x0E = 0x%02X", reg_0E);
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






