
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432 component...");
  this->spi_setup();  // Inicializa el dispositivo SPI
}

void Si4432Component::loop() {
  this->read_status();
}

void Si4432Component::read_status() {
  // Suponiendo que 0x02 sea un registro de estado para ejemplo
  uint8_t status = this->read_byte(0x02);
  ESP_LOGD(TAG, "Status register: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome
