#include "si4432.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup complete");
}

void Si4432Component::loop() {
  const uint32_t now = millis();
  if (now - this->last_log_time_ >= 5000) {
    this->last_log_time_ = now;

    uint8_t reg_type = this->read_register(0x00);   // Device Type
    uint8_t reg_ver  = this->read_register(0x01);   // Version
    uint8_t reg_stat = this->read_register(0x02);   // Status
    uint8_t reg_int1 = this->read_register(0x03);   // Interrupt Status 1
    uint8_t reg_int2 = this->read_register(0x04);   // Interrupt Status 2
    uint8_t reg_mode = this->read_register(0x07);   // Operating Mode

    ESP_LOGI(TAG, "[Loop] Type=0x%02X Ver=0x%02X Stat=0x%02X INT1=0x%02X INT2=0x%02X MODE=0x%02X",
             reg_type, reg_ver, reg_stat, reg_int1, reg_int2, reg_mode);
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->enable();  // CS LOW
  spi::spi_transfer_byte(this, reg & 0x7F);  // Clear MSB for read
  uint8_t value = spi::spi_transfer_byte(this, 0x00);  // Dummy write to receive
  this->disable();  // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome







