import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN
from esphome import automation
from esphome.components.spi import SPIComponent
from esphome.core import CORE
from esphome.cpp_helpers import setup_component

CODEOWNERS = ["@pchdomotichome"]
DEPENDENCIES = ["spi"]

CONF_SI4432_ID = "si4432_id"

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_CS_PIN): cv.spi_cs_pin,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
