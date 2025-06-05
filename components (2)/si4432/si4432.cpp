#include "si4432.h"
#include "esphome/core/log.h"

namespace esphome {
namespace si4432 {

static const char *const TAG = "si4432";

void SI4432Component::setup() {
  ESP_LOGCONFIG(TAG, "Setting up SI4432...");
  // setup code here
}

void SI4432Component::loop() {
  // loop code here
}

void SI4432Component::dump_config() {
  ESP_LOGCONFIG(TAG, "SI4432 Component");
}

}  // namespace si4432
}  // namespace esphome