#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Iniciando Si4432...");

  pinMode(cs_pin_, OUTPUT);
  digitalWrite(cs_pin_, HIGH);
  delay(10);

  this->spi_setup();

  write_register(0x07, 0x80);
  delay(10);

  write_register(0x07, 0x01);
  write_register(0x06, 0x00);
  write_register(0x75, 0x63);
  write_register(0x76, 0x60);
  write_register(0x77, 0x00);

  write_register(0x71, 0x63);
  write_register(0x1C, 0x1D);
  write_register(0x30, 0x8C);

  write_register(0x07, 0x05);
}

void Si4432Component::loop() {
  uint8_t status = read_register(0x03);
  if (status & 0x04) {
    uint8_t length = read_register(0x4B);
    ESP_LOGI(TAG, "Paquete recibido, longitud: %d", length);
    for (uint8_t i = 0; i < length; i++) {
      uint8_t byte = read_register(0x7F);
      ESP_LOGI(TAG, "Byte[%d] = 0x%02X", i, byte);
    }
  }
}

void Si4432Component::write_register(uint8_t reg, uint8_t value) {
  this->enable();
  this->transfer(reg | 0x80);
  this->transfer(value);
  this->disable();
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();
  this->transfer(reg & 0x7F);
  uint8_t value = this->transfer(0);
  this->disable();
  return value;
}

}  // namespace si4432
}  // namespace esphome
