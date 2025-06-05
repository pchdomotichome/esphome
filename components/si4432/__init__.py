import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
import esphome.components.gpio as gpio
from esphome.const import CONF_ID, CONF_CS_PIN

CONF_IRQ_PIN = "irq_pin"

DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(Si4432Component),
            cv.Required(spi.CONF_SPI_ID): cv.use_id(spi.SPIComponent),
            cv.Required(CONF_CS_PIN): gpio.output_pin_schema,
            cv.Required(CONF_IRQ_PIN): gpio.input_pin_schema,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema())
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
    cs = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    irq = await cg.gpio_pin_expression(config[CONF_IRQ_PIN])
    cg.add(var.set_cs_pin(cs))
    cg.add(var.set_irq_pin(irq))