from esphome.components import spi
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins

CODEOWNERS = ["@pchdomotichome"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.PollingComponent, spi.SPIDevice)

CONF_CS_PIN = "cs_pin"
CONF_IRQ_PIN = "irq_pin"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
        cv.Required(CONF_IRQ_PIN): pins.gpio_input_pin_schema,
        cv.GenerateID(spi.CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    }
).extend(cv.polling_component_schema("1s"))

async def to_code(config):
    spi_id = await cg.get_variable(config[spi.CONF_SPI_ID])

    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    irq = await cg.gpio_pin_expression(config[CONF_IRQ_PIN])

    var = cg.new_Pvariable(config[cv.CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, spi_id, cs)
    cg.add(var.set_irq_pin(irq))

