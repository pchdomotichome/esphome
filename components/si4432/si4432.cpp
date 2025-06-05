#include "esphome/core/log.h"
#include "si4432.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432 receiver...");
  // Aquí irá la inicialización real del chip Si4432
}

void Si4432Component::loop() {
  // Aquí iría la lógica para recibir datos
}

}  // namespace si4432
}  // namespace esphome