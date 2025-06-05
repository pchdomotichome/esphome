from esphome.components.spi import SPIComponent
from esphome.components.spi import spi_device_schema
from esphome.const import CONF_ID
from esphome.components import spi
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components.spi import SpiDevice
from esphome.const import CONF_CS_PIN

from esphome.components.output import gpio

DEPENDENCIES = ["spi"]
AUTO_LOAD = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
#    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
    cv.Required(CONF_CS_PIN): gpio.gpio_output_pin_schema,

}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cs_pin = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(cs_pin))

