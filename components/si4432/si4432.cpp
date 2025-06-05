#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup");

  // Asegurarse que el pin CS está configurado
  if (this->cs_pin_ != nullptr) {
    this->cs_pin_->setup();
    this->cs_pin_->digital_write(true);  // CS high (desactivado)
  }

  // Prueba: leer un registro conocido (por ejemplo, 0x01: Device Type)
  uint8_t device_type = read_register(0x01);
  ESP_LOGI(TAG, "Device Type register: 0x%02X", device_type);
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop...");
  // Ejemplo: podés hacer lecturas periódicas aquí
}

void Si4432Component::write_register(uint8_t address, uint8_t value) {
  this->cs_pin_->digital_write(false);  // CS low

  this->write_byte(address | 0x80);  // MSB=1 para escritura
  this->write_byte(value);

  this->cs_pin_->digital_write(true);  // CS high
}

uint8_t Si4432Component::read_register(uint8_t address) {
  this->cs_pin_->digital_write(false);  // CS low

  this->write_byte(address & 0x7F);  // MSB=0 para lectura
  uint8_t value = this->read_byte();

  this->cs_pin_->digital_write(true);  // CS high
  return value;
}

}  // namespace si4432
}  // namespace esphome

