
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: CS pin is %d", this->cs_pin_);
  // Inicialización básica del receptor (dummy por ahora)
}

void Si4432Component::loop() {
  // Bucle receptor simplificado
  ESP_LOGD(TAG, "Si4432 loop running...");
}

}  // namespace si4432
}  // namespace esphome
