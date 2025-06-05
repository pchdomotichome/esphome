#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGD(TAG, "Setting up SI4432 component...");
  this->spi_setup();
}

void Si4432Component::loop() {
  this->read_status();
}

void Si4432Component::read_status() {
  uint8_t status = this->read_byte(0x02);  // Suponiendo 0x02 como un registro de estado válido
  ESP_LOGD(TAG, "SI4432 status: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome