#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432 component...");
  this->cs_pin_->setup();
  this->irq_pin_->setup();
}

void Si4432Component::update() {
  ESP_LOGD(TAG, "Polling Si4432...");
}

}  // namespace si4432
}  // namespace esphome