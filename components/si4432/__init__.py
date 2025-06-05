
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

CODEOWNERS = ["@pchdomotichome"]
DEPENDENCIES = ["spi"]
AUTO_LOAD = ["logger"]

CONF_SI4432_ID = "si4432"

si4432_ns = cg.esphome_ns.namespace("si4432")
SI4432Component = si4432_ns.class_("SI4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SI4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): cv.cs_pin,  # CS pin gestionado automáticamente
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
