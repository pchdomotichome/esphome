import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID
from esphome.components import spi

DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
        cv.Optional(CONF_CS_PIN): cv.templatable(cv.GPIOPin),  # ✅ esto sí funciona
    }
).extend(cv.COMPONENT_SCHEMA)

@cg.coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    spi_parent = await cg.get_variable(config[CONF_SPI_ID])
    await spi.register_spi_device(var, spi_parent)

    if CONF_CS_PIN in config:
        cs_pin = await cg.gpio_pin_expression(config[CONF_CS_PIN])
        cg.add(var.set_cs_pin(cs_pin))

