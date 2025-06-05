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
  // Lógica de lectura o escucha del transceptor
  this->read_status();
}

void Si4432Component::read_status() {
  // Ejemplo de lectura de estado del Si4432
  uint8_t status = this->read_byte(0x02);  // Supongamos que 0x02 es un registro de estado
  ESP_LOGD(TAG, "Status register: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome
