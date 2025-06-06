#include "si4432.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: CS pin is ready");
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  spi::spi_transfer_byte(this->parent_, reg & 0x7F);  // Clear bit 7 for read
  uint8_t value = spi::spi_transfer_byte(this->parent_, 0x00);  // Dummy write to receive data
  this->disable();  // CS HIGH
  return value;
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop running...");

  uint8_t status = read_register(0x07);  // Device Status register
  ESP_LOGI(TAG, "Registro 0x07 (Device Status): 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome

