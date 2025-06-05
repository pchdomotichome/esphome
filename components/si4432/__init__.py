import esphome.config_validation as cv
from esphome.components import spi, gpio
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID
import esphome.codegen as cg

CODEOWNERS = ["@tu_usuario"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component)

CONF_SI4432_ID = "si4432"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): gpio.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    spi_dev = await spi.register_spi_device(var, config)
    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(cs))

