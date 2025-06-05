from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CS_PIN
from esphome import pins
from esphome.core import CORE
from esphome.cpp_generator import Pvariable
from esphome.cpp_helpers import setup_component
from esphome.cpp_types import App, Component

DEPENDENCIES = ['spi']

CONF_SI4432_ID = "si4432_id"

si4432_ns = esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = Pvariable(config[CONF_ID], Si4432Component.new())
    yield spi.setup_spi_device(var, config[CONF_CS_PIN])
    yield setup_component(var, config)
