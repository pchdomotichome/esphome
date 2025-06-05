
#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Setting up SI4432 component...");
  this->spi_setup();
  if (this->irq_pin_ != nullptr) {
    this->irq_pin_->setup();
  }
}

void Si4432Component::loop() {
  // Aquí podrías implementar recepción o debug
}

}  // namespace si4432
}  // namespace esphome
