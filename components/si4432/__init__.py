import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import spi

DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
SI4432Component = si4432_ns.class_("SI4432Component", cg.Component, spi.SPIDevice)

CONF_CS_PIN = "cs_pin"
CONF_IRQ_PIN = "irq_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SI4432Component),
    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_IRQ_PIN): pins.gpio_input_pin_schema,
}).extend(spi.spi_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    irq = await cg.gpio_pin_expression(config[CONF_IRQ_PIN])
    cg.add(var.set_cs_pin(cs))
    cg.add(var.set_irq_pin(irq))