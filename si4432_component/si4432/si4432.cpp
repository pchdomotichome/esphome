#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432...");
  this->cs_pin_->setup();
  this->cs_pin_->digital_write(true);
}

void Si4432Component::dump_config() {
  ESP_LOGCONFIG(TAG, "Si4432:");
}

void Si4432Component::update() {
  ESP_LOGD(TAG, "Polling Si4432...");
}

void Si4432Component::set_cs_pin(GPIOPin *pin) {
  this->cs_pin_ = pin;
}
void Si4432Component::set_irq_pin(GPIOPin *pin) {
  this->irq_pin_ = pin;
}

}  // namespace si4432
}  // namespace esphome