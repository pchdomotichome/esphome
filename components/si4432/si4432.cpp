#include "si4432.h"

namespace esphome {
namespace si4432 {

void Si4432Component::setup() {
  this->spi_setup();  // 🔧 Inicializa el dispositivo SPI
  ESP_LOGI("si4432", "Setup completo.");
  ESP_LOGI(TAG, "Si4432 setup starting");
  // Leer registros clave
  const uint8_t regs_to_read[] = {
    0x01, 0x02, 0x06, 0x07, 0x08,
    0x0F, 0x10, 0x11,
    0x75, 0x76, 0x77
  };

  for (uint8_t reg : regs_to_read) {
    uint8_t val = read_register(reg);
    ESP_LOGI(TAG, "Reg 0x%02X = 0x%02X", reg, val);
  }  
}

void Si4432Component::loop() {
  uint8_t reg_val = this->read_register(0x07);
  ESP_LOGI("si4432", "Reg 0x07 = 0x%02X", reg_val);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->write_byte(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->read_byte();  // Read response
  this->disable();  // CS HIGH
  return val;
}

}  // namespace si4432
}  // namespace esphome

