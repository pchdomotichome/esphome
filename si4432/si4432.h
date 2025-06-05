#pragma once
#include "esphome/core/component.h"

namespace esphome {
namespace si4432 {

class Si4432Component : public Component {
 public:
  void setup() override;
  void loop() override;
};

}  // namespace si4432
}  // namespace esphome

