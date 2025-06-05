import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID
from esphome.components import spi
from esphome.core import CORE

from . import si4432_ns

SI4432Component = si4432_ns.class_("SI4432Component", spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SI4432Component),
    cv.GenerateID(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): cv.templatable(cv.OutputPin),
})

