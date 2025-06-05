
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome import pins
from esphome.const import CONF_ID, CONF_IRQ_PIN, CONF_CS_PIN

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@pchdomotichome"]

CONF_SI4432_ID = "si4432"

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_CS_PIN): cv.uint8_t,
    cv.Required(CONF_IRQ_PIN): pins.gpio_input_pin
}).extend(spi.spi_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await spi.register_spi_device(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_cs_pin(config[CONF_CS_PIN]))
    cg.add(var.set_irq_pin(config[CONF_IRQ_PIN]))
