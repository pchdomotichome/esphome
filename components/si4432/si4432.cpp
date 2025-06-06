#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: calling spi_setup()");
  this->spi_setup();  // ← ¡Importante!
}

void Si4432Component::loop() {
  static uint32_t last_time = 0;
  if (millis() - last_time < 5000) return;
  last_time = millis();

  uint8_t reg07 = read_register(0x07);  // Operating & Function Control 1
  uint8_t reg0C = read_register(0x0C);  // Device Type
  uint8_t reg0D = read_register(0x0D);  // Device Version
  uint8_t reg02 = read_register(0x02);  // Interrupt Status 1

  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X | 0x0C = 0x%02X | 0x0D = 0x%02X | 0x02 = 0x%02X",
           reg07, reg0C, reg0D, reg02);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  delayMicroseconds(1);

  this->transfer(reg & 0x7F);  // Clear MSB for read
  uint8_t val = this->transfer(0x00);  // Dummy write to receive

  this->disable();  // CS HIGH
  return val;
}

}  // namespace si4432
}  // namespace esphome


