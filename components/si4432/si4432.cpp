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
  static uint32_t last_read = 0;
  const uint32_t interval_ms = 5000;
  uint32_t now = millis();

  if (now - last_read >= interval_ms) {
    last_read = now;

    // 1. Intentar poner el chip en modo standby (bit 0 en 1)
    write_register(0x07, 0b00000001);
    delay(1);

    // 2. Escribir configuración en registro 0x09 (Data Access Control)
    write_register(0x09, 0x62);
    delay(1);

    // 3. Leer registros clave
    ESP_LOGI(TAG, "[Loop] Reg 0x07 = 0x%02X", read_register(0x07));
    ESP_LOGI(TAG, "[Loop] Reg 0x0C = 0x%02X", read_register(0x0C));
    ESP_LOGI(TAG, "[Loop] Reg 0x0D = 0x%02X", read_register(0x0D));
    ESP_LOGI(TAG, "[Loop] Reg 0x0E = 0x%02X", read_register(0x0E));
    ESP_LOGI(TAG, "[Loop] Reg 0x09 (Data Access Control) = 0x%02X", read_register(0x09));
    
    
  }
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();                            // CS LOW
  this->write_byte(reg | 0x80);              // MSB=1 para escritura
  this->write_byte(value);
  this->disable();                           // CS HIGH
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();                            // CS LOW
  this->write_byte(reg & 0x7F);              // MSB=0 para lectura
  uint8_t value = this->read_byte();         // Dummy para recibir
  this->disable();                           // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome






