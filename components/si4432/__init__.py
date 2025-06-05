import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi, pins
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

CODEOWNERS = ["@tu_usuario"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component)

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.GenerateID(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
        cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
    })
    .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    spi_dev = await spi.register_spi_device(var, config)
    cg.add(var.set_cs_pin(spi_dev.cs_pin))

