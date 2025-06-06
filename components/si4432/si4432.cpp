#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");
  this->spi_setup();  // Inicializa SPI desde SPIDevice
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - last_read_time_ < 5000)
    return;

  last_read_time_ = now;

  uint8_t status = read_register(0x07);  // Operating Mode & Function Control 1
  uint8_t interrupt_status1 = read_register(0x03);
  uint8_t interrupt_status2 = read_register(0x04);
  uint8_t device_status = read_register(0x02);

  ESP_LOGI(TAG, "Reg 0x07 (OpMode1):  0x%02X", status);
  ESP_LOGI(TAG, "Reg 0x03 (IntStat1): 0x%02X", interrupt_status1);
  ESP_LOGI(TAG, "Reg 0x04 (IntStat2): 0x%02X", interrupt_status2);
  ESP_LOGI(TAG, "Reg 0x02 (DevStat):  0x%02X", device_status);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  this->transfer_byte(reg & 0x7F);  // MSB=0 for read
  uint8_t value = this->transfer_byte(0x00);  // Dummy write
  this->disable();  // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome




