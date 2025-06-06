import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID


CODEOWNERS = ["@pchom"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Si4432Component),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True))
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)  

