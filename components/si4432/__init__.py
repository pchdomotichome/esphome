
import esphome.config_validation as cv
from esphome import automation
from esphome.components import spi
from esphome.const import CONF_ID

from esphome.components.spi import spi_device_schema
from esphome.cpp_generator import Pvariable
from esphome.cpp_helpers import setup_component

CODEOWNERS = ["@pchdomotichome"]
AUTO_LOAD = ["spi"]
MULTI_CONF = True

si4432_ns = cv.new_namespace('si4432')
Si4432Component = si4432_ns.class_('Si4432Component', spi.SPIDevice, cv.Component)

CONFIG_SCHEMA = spi_device_schema(Si4432Component).extend({
    cv.GenerateID(): cv.declare_id(Si4432Component),
})

def to_code(config):
    var = yield spi.register_spi_device(config, Si4432Component.new)
    yield setup_component(var, config)
