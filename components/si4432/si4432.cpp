#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  if (this->spi_dev_ != nullptr)
    this->spi_dev_->setup();
}

void Si4432Component::loop() {
  this->read_status();
}

void Si4432Component::read_status() {
  if (!this->spi_dev_)
    return;

  uint8_t status = 0;
  this->spi_dev_->read_byte(0x02, &status);  // Suponiendo que 0x02 es un registro válido
  ESP_LOGD(TAG, "Status: 0x%02X", status);
}

}  // namespace si4432
}  // namespace esphome