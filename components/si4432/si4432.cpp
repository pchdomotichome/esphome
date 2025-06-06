#include "si4432.h"
#include "esphome/core/log.h"
#include "esphome/core/helpers.h"
#include "driver/gpio.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting");

  // Configurar CS como salida y ponerlo en HIGH
  gpio_pad_select_gpio((gpio_num_t) this->cs_pin_);
  gpio_set_direction((gpio_num_t) this->cs_pin_, GPIO_MODE_OUTPUT);
  gpio_set_level((gpio_num_t) this->cs_pin_, 1);

  delay(10);
  ESP_LOGI(TAG, "Si4432 setup done");
}

void Si4432Component::loop() {
  static uint32_t last_time = 0;
  if (millis() - last_time > 5000) {
    last_time = millis();

    uint8_t reg07 = read_register(0x07);  // Operating & Function Control 1
    uint8_t reg0C = read_register(0x0C);  // Device Type
    uint8_t reg0D = read_register(0x0D);  // Device Version
    uint8_t reg02 = read_register(0x02);  // Interrupt Status 1

    ESP_LOGI(TAG, "Reg 0x07 = 0x%02X | 0x0C = 0x%02X | 0x0D = 0x%02X | 0x02 = 0x%02X",
             reg07, reg0C, reg0D, reg02);
  }
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  gpio_set_level((gpio_num_t) this->cs_pin_, 0);  // CS LOW
  delayMicroseconds(1);

  this->spi_->transfer_byte(reg & 0x7F);  // MSB=0 → Read
  uint8_t value = this->spi_->transfer_byte(0x00);  // Dummy write to receive

  gpio_set_level((gpio_num_t) this->cs_pin_, 1);  // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome


