#include "si4432.h"

void SI4432::set_cs_pin(GPIOPin *pin) {
    this->cs_pin_ = pin;
}

void SI4432::write_register(uint8_t reg, uint8_t value) {
    this->enable();
    this->write_byte(reg | 0x80); // Bit 7 alto para escritura
    this->write_byte(value);
    this->disable();
}

uint8_t SI4432::read_register(uint8_t reg) {
    this->enable();
    this->write_byte(reg & 0x7F); // Bit 7 bajo para lectura
    uint8_t value = this->read_byte();
    this->disable();
    return value;
}

void SI4432::setup() {
    if (this->cs_pin_ != nullptr) {
        this->cs_pin_->digital_write(true);
    }
    // Configuración inicial del SI4432 (ejemplo: 433MHz)
    write_register(0x75, 0x53); // Frecuencia base
    write_register(0x76, 0x64); // Paso de frecuencia
    ESP_LOGI("SI4432", "Inicializado a 433MHz");
}

void SI4432::loop() {
    // Lógica de recepción/transmisión (opcional)
}
