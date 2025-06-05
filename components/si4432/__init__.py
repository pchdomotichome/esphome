import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_SPI_ID

DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
SI4432 = si4432_ns.class_("SI4432", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(SI4432),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): cv.int_,  # Aceptamos un número de pin directamente
})

async def to_code(config):
    spi_comp = await cg.get_variable(config[CONF_SPI_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    # ✅ Este helper funciona con enteros simples
    cs = cg.digital_pin_to_gpio_expression(config[CONF_CS_PIN])

    cg.add(var.set_spi(spi_comp))
    cg.add(var.set_cs_pin(cs))

