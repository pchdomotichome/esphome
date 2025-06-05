import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import spi, gpio
from esphome.const import CONF_ID

from . import si4432_ns

Si4432Component = si4432_ns.class_("Si4432Component", cg.Component)

CONF_SPI_ID = "spi_id"
CONF_CS_PIN = "cs_pin"
CONF_IRQ_PIN = "irq_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIDevice),
    cv.Required(CONF_CS_PIN): gpio.output_pin_schema,
    cv.Required(CONF_IRQ_PIN): gpio.input_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

