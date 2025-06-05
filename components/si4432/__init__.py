from esphome import pins
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

from esphome.cpp_generator import Pvariable
from esphome.cpp_helpers import gpio_output_pin_expression, setup_component
from esphome.cpp_types import App, Component

CODEOWNERS = ["@pchdomotichome"]
DEPENDENCIES = ["spi"]

CONF_SI4432_ID = "si4432_id"

si4432_ns = App.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.GenerateID(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)


def to_code(config):
    rhs = si4432_ns.Si4432Component.new()
    si4432 = Pvariable(config[CONF_ID], rhs)
    yield spi.register_spi_device(si4432, config)
    yield gpio_output_pin_expression(config[CONF_CS_PIN])
    yield setup_component(si4432, config)