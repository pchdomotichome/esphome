import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID

CODEOWNERS = ["@tu_usuario"]
DEPENDENCIES = ["spi"]

CONF_SI4432_ID = "si4432_id"
si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.Required("spi_id"): cv.use_id(spi.SPIComponent),
        cv.Required("cs_pin"): cv.spi_device_cs_pin,  # ✅ Válido en ESPHome 2025.5.2
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

