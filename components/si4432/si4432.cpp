
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void SI4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432Component...");
  // Inicialización básica
}

void SI4432Component::loop() {
  // Aquí iría el código de recepción/transmisión si4432
}

}  // namespace si4432
}  // namespace esphome
