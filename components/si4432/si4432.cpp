#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup");
  this->spi_setup();  // Importante para inicializar SPIDevice
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - this->last_log_time_ < 5000) return;
  this->last_log_time_ = now;

  // Registros útiles para diagnóstico
  uint8_t reg00 = read_register(0x00);  // Device Type
  ESP_LOGI(TAG, "[Loop] Reg 0x00 (Device Type) = 0x%02X", reg00);

  uint8_t reg06 = read_register(0x06);  // Interrupt Enable 2
  ESP_LOGI(TAG, "[Loop] Reg 0x06 (Interrupt Enable 2) = 0x%02X", reg06);

  uint8_t reg07 = read_register(0x07);  // Operating Mode & Function Control 1
  ESP_LOGI(TAG, "[Loop] Reg 0x07 = 0x%02X", reg07);

  uint8_t reg09 = read_register(0x09);  // Data Access Control
  ESP_LOGI(TAG, "[Loop] Reg 0x09 (Data Access Control) = 0x%02X", reg09);

  uint8_t reg0C = read_register(0x0C);  // FIFO Control 1
  ESP_LOGI(TAG, "[Loop] Reg 0x0C = 0x%02X", reg0C);

  uint8_t reg0D = read_register(0x0D);  // FIFO Control 2
  ESP_LOGI(TAG, "[Loop] Reg 0x0D = 0x%02X", reg0D);

  uint8_t reg0E = read_register(0x0E);  // FIFO Data
  ESP_LOGI(TAG, "[Loop] Reg 0x0E = 0x%02X", reg0E);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();                      // CS LOW
  this->write_byte(reg & 0x7F);        // MSB=0 para lectura
  uint8_t value = this->read_byte();   // Dummy para recibir
  this->disable();                     // CS HIGH
  return value;
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();                      // CS LOW
  this->write_byte(reg | 0x80);        // MSB=1 para escritura
  this->write_byte(value);
  this->disable();                     // CS HIGH
}

}  // namespace si4432
}  // namespace esphome






