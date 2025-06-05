
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432 component...");
  this->spi_setup();
  // Agregá aquí tu inicialización del SI4432
}

void Si4432Component::loop() {
  // Acá iría la lógica de lectura de IRQ o recepción de datos
}

}  // namespace si4432
}  // namespace esphome
