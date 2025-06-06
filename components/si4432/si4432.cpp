#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  this->spi_setup();  // Inicializa SPI (heredado de SPIDevice)
  ESP_LOGI(TAG, "Si4432 setup completo");
}

void Si4432Component::loop() {
  static uint32_t last_read = 0;
  uint32_t now = millis();
  if (now - last_read < 5000)
    return;
  last_read = now;

  uint8_t val = read_register(0x07);  // Registro de estado
  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X", val);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->cs_->digital_write(false);         // CS LOW
  this->transfer(reg & 0x7F);              // Enviar dirección (MSB=0 → read)
  uint8_t value = this->transfer(0x00);    // Dummy para recibir dato
  this->cs_->digital_write(true);          // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome




