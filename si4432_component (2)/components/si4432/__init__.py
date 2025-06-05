
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi
from esphome.const import CONF_ID, CONF_CS_PIN

CONF_IRQ_PIN = "irq_pin"

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required(CONF_CS_PIN): spi.validate_spi_cs_pin,
    cv.Required(CONF_IRQ_PIN): cv.int_,
}).extend(cv.COMPONENT_SCHEMA).extend(spi.spi_device_schema())

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    yield spi.register_spi_device(var, config)
    cg.add(var.set_irq_pin(config[CONF_IRQ_PIN]))
