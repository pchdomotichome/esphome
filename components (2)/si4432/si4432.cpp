#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432 component...");
  this->spi_setup();  // Inicializa SPI
}

void Si4432Component::loop() {
  this->read_status();  // Aquí puede ir la lógica de lectura continua
}

void Si4432Component::read_status() {
  uint8_t status = this->read_byte(0x02);  // Ejemplo: leer registro de estado
  ESP_LOGD(TAG, "Status: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome