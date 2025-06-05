import esphome.config_validation as cv
from esphome import automation
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN

from esphome.cpp_generator import Pvariable
from esphome.cpp_helpers import gpio_pin_expression
from esphome import pins

CONF_SI4432_ID = "si4432_id"

CODEOWNERS = ["@tu_usuario"]
DEPENDENCIES = ["spi"]

si4432_ns = esphome.ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", esphome.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
}).extend(spi.spi_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(cs))
    await spi.register_spi_device(var, config)

