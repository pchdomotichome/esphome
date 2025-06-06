#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  this->spi_setup();
  ESP_LOGI(TAG, "Si4432 setup completed. CS pin: GPIO%d", cs_pin_);
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - last_read_time_ < 5000)
    return;

  last_read_time_ = now;

  // Leer registros clave
  uint8_t status = read_register(0x07);
  uint8_t device_type = read_register(0x00);
  uint8_t version = read_register(0x01);

  ESP_LOGI(TAG, "Reg 0x07: 0x%02X | Device Type: 0x%02X | Version: 0x%02X",
           status, device_type, version);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->transfer(reg & 0x7F);  // MSB=0 for read
  uint8_t value = this->transfer(0x00);  // Dummy write to read
  this->disable();  // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome



