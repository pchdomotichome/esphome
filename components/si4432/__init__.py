import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

CODEOWNERS = ["@pch"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): cv.int_,
})

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    var.set_cs_pin(config[CONF_CS_PIN])  # ✅ usamos int directamente
    parent = await cg.get_variable(config[CONF_SPI_ID])  # ✅ extraer correctamente el SPIComponent
    await spi.register_spi_device(var, parent)  # ✅ pasar SPIComponent

