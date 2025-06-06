#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - last_read_time_ < 5000)
    return;

  last_read_time_ = now;

  uint8_t reg_07 = read_register(0x07);  // Operating Mode
  uint8_t reg_02 = read_register(0x02);  // Device Status
  uint8_t reg_03 = read_register(0x03);  // Interrupt Status 1
  uint8_t reg_04 = read_register(0x04);  // Interrupt Status 2

  ESP_LOGI(TAG, "Reg 0x07 (OpMode1):  0x%02X", reg_07);
  ESP_LOGI(TAG, "Reg 0x02 (DevStat):  0x%02X", reg_02);
  ESP_LOGI(TAG, "Reg 0x03 (IntStat1): 0x%02X", reg_03);
  ESP_LOGI(TAG, "Reg 0x04 (IntStat2): 0x%02X", reg_04);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->cs_->digital_write(false);  // CS LOW
  this->spi_->transfer(reg & 0x7F);  // MSB=0 → read
  uint8_t value = this->spi_->transfer(0x00);  // Dummy write to read
  this->cs_->digital_write(true);   // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome





