#include "si4432.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void Si4432Component::setup() {
  ESP_LOGI(TAG, "Si4432 setup starting...");
  this->spi_setup();  // Inicializa SPI (del SPIDevice)
}

void Si4432Component::loop() {
  // Leer algunos registros clave del Si4432 cada ciclo (podés usar un delay si querés limitarlo)
  uint8_t reg_07 = this->read_register(0x07);
  uint8_t reg_02 = this->read_register(0x02);
  uint8_t reg_03 = this->read_register(0x03);
  ESP_LOGI(TAG, "Reg 0x07 = 0x%02X | Reg 0x02 = 0x%02X | Reg 0x03 = 0x%02X", reg_07, reg_02, reg_03);
}

uint8_t Si4432Component::read_register(uint8_t reg) {
  this->cs_->digital_write(false);                       // CS LOW
  spi::spi_transfer_byte(this, reg & 0x7F);              // Dirección de lectura (MSB=0)
  uint8_t value = spi::spi_transfer_byte(this, 0x00);    // Dummy → leer valor
  this->cs_->digital_write(true);                        // CS HIGH
  return value;
}

}  // namespace si4432
}  // namespace esphome





