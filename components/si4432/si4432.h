#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component {
 public:
  void setup() override;
  void loop() override;

  void set_spi_device(spi::SPIDevice *device) { this->spi_dev_ = device; }

 protected:
  spi::SPIDevice *spi_dev_{nullptr};

  void read_status();
};

}  // namespace si4432
}  // namespace esphome