from esphome.components import spi, gpio
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_CS_PIN, CONF_IRQ_PIN, CONF_SPI_ID
import esphome.codegen as cg

DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.PollingComponent, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_SPI_ID): cv.use_id(spi.SPIComponent),
    cv.Required(CONF_CS_PIN): gpio.output_pin_schema,
    cv.Required(CONF_IRQ_PIN): gpio.input_pin_schema,
}).extend(cv.polling_component_schema("60s"))

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
    cs = await gpio.build_output_pin(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(cs))
    irq = await gpio.build_input_pin(config[CONF_IRQ_PIN])
    cg.add(var.set_irq_pin(irq))