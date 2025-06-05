
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/spi/spi.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public spi::SPIDevice, public Component {
 public:
  void setup() override;
  void loop() override;
};

}  // namespace si4432
}  // namespace esphome
