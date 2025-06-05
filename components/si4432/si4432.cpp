#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup completo");
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop ejecutándose...");
}

}  // namespace si4432
}  // namespace esphome

