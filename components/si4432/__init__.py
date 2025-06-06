import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi, gpio  # ✅ usamos gpio para validar el pin
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

CODEOWNERS = ["@tucmundo"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
        cv.Required(CONF_CS_PIN): gpio.gpio_output_pin_schema,  # ✅ ESTE FUNCIONA en 2025.5.2
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])       # ✅ correcto para GPIO output pin
    parent = await cg.get_variable(config[CONF_SPI_ID])          # ✅ SPI parent
    await spi.register_spi_device(var, parent, cs)               # ✅ registro válido

