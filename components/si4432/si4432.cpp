#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup: CS pin is %p", this->cs_pin_);
  // Podés controlar el pin manualmente si querés:
  // this->cs_pin_->digital_write(false);
}

void Si4432Component::loop() {
  ESP_LOGD(TAG, "Si4432 loop running...");
}

}  // namespace si4432
}  // namespace esphome

