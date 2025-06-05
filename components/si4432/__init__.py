from esphome.components import spi, gpio
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins

CODEOWNERS = ["@pchdomotichome"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.PollingComponent, spi.SPIDevice)

CONF_SPI_ID = "spi_id"
CONF_CS_PIN = "cs_pin"
CONF_IRQ_PIN = "irq_pin"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIDevice),
    cv.Required(CONF_CS_PIN): gpio.output_pin_schema,
    cv.Required(CONF_IRQ_PIN): gpio.input_pin_schema,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])

    # Registrar como dispositivo SPI
    spi_dev = await spi.register_spi_device(config[CONF_SPI_ID], config[CONF_CS_PIN])
    cg.add(var.set_spi_device(spi_dev))

    # Configurar IRQ
    irq_pin = await cg.gpio_pin_expression(config[CONF_IRQ_PIN])
    cg.add(var.set_irq_pin(irq_pin))

    # Registrar componente
    await cg.register_component(var, config)
