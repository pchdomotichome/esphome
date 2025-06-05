
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432 component (receive-only)...");
  // Aquí va la lógica de inicialización del receptor
}

void Si4432Component::loop() {
  // Aquí puede ir el procesamiento de datos del receptor
}

}  // namespace si4432
}  // namespace esphome
