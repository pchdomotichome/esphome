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

    // Leer registros clave de estado
    uint8_t reg_07 = read_register(0x07);
    uint8_t reg_0C = read_register(0x0C);
    uint8_t reg_0D = read_register(0x0D);
    uint8_t reg_0E = read_register(0x0E);
    ESP_LOGI(TAG, "[Loop] Reg 0x07 = 0x%02X", reg_07);
    ESP_LOGI(TAG, "[Loop] Reg 0x0C = 0x%02X", reg_0C);
    ESP_LOGI(TAG, "[Loop] Reg 0x0D = 0x%02X", reg_0D);
    ESP_LOGI(TAG, "[Loop] Reg 0x0E = 0x%02X", reg_0E);

    // 🔧 Escribir un valor a un registro RW y leerlo de vuelta
    write_register(0x09, 0x62);  // Set Data Access Control (por ejemplo)
    uint8_t reg_09 = read_register(0x09);
    ESP_LOGI(TAG, "[Loop] Reg 0x09 (Data Access Control) = 0x%02X", reg_09);
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






