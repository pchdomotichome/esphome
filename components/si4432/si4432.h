#pragma once
#include "esphome.h"

class SI4432 : public Component, public spi::SPIDevice {
public:
    void setup() override;
    void loop() override;
    void set_cs_pin(GPIOPin *pin);

private:
    GPIOPin *cs_pin_{nullptr};
    void write_register(uint8_t reg, uint8_t value);
    uint8_t read_register(uint8_t reg);
};
