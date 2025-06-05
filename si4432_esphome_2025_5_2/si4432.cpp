#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up Si4432...");
  // TODO: Initialize the SI4432 device via SPI
}

void Si4432Component::loop() {
  // TODO: Read data or handle interrupts
}

void Si4432Component::set_cs_pin(GPIOPin *pin) {
  this->cs_pin_ = pin;
}

void Si4432Component::set_irq_pin(GPIOPin *pin) {
  this->irq_pin_ = pin;
}

}  // namespace si4432
}  // namespace esphome