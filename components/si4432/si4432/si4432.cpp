#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432...");
  this->spi_setup();
}

void Si4432Component::loop() {
  read_status();
}

void Si4432Component::read_status() {
  uint8_t status = this->read_byte(0x02);  // Registro de estado hipotético
  ESP_LOGD(TAG, "SI4432 Status: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome