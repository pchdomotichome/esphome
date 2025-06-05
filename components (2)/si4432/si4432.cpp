
#include "esphome.h"
#include "esphome/core/log.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

class SI4432Component : public Component, public spi::SPIDevice<spi::BIT_ORDER_MSB_FIRST, spi::CLOCK_POLARITY_LOW, spi::CLOCK_PHASE_LEADING, spi::DATA_RATE_1MHZ> {
 public:
  void setup() override {
    ESP_LOGI(TAG, "Setting up SI4432...");
    this->spi_setup();

    uint8_t part_num = this->read_register(0x01);  // Device Type
    ESP_LOGI(TAG, "SI4432 Device ID: 0x%02X", part_num);

    // Modo receptor (simplificado)
    this->write_register(0x07, 0x01);  // Operating Mode: Ready
  }

  void loop() override {
    uint8_t status = this->read_register(0x03);  // Interrupt Status 1
    if (status & 0x02) {  // Packet Received
      ESP_LOGI(TAG, "Packet received");

      uint8_t len = this->read_register(0x4B);  // Received packet length
      std::vector<uint8_t> buffer;
      for (int i = 0; i < len; i++) {
        buffer.push_back(this->read_register(0x7F));  // FIFO
      }

      ESP_LOGI(TAG, "Data:");
      for (auto byte : buffer) {
        ESP_LOGI(TAG, "0x%02X ", byte);
      }
    }
  }

 protected:
  void write_register(uint8_t reg, uint8_t value) {
    this->enable();
    this->spi_write_byte(reg | 0x80);  // Write operation
    this->spi_write_byte(value);
    this->disable();
  }

  uint8_t read_register(uint8_t reg) {
    this->enable();
    this->spi_write_byte(reg & 0x7F);  // Read operation
    uint8_t value = this->spi_read_byte();
    this->disable();
    return value;
  }
};

}  // namespace si4432
}  // namespace esphome
