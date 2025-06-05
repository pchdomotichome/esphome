#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 SPI setup...");
  this->spi_setup();  // inicializa SPI con los parámetros del SPIDevice
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop running...");

  // Ejemplo: leer un registro (reg 0x07 = Operating Mode and Function Control 1)
  this->enable();  // baja CS
  this->transfer(0x07 & 0x7F);  // operación de lectura
  uint8_t reg_val = this->transfer(0x00);
  this->disable();  // sube CS

  ESP_LOGD(TAG, "Register 0x07 = 0x%02X", reg_val);
}

}  // namespace si4432
}  // namespace esphome

