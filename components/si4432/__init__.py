import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import spi, sensor
from esphome.const import CONF_ID, CONF_CS_PIN
from esphome import pins

DEPENDENCIES = ['spi']

si4432_ns = cg.esphome_ns.namespace('si4432')
Si4432Component = si4432_ns.class_('Si4432Component', cg.Component, spi.SPIDevice)

CONF_STATUS_SENSOR = "status_sensor"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Si4432Component),
        cv.Required(CONF_CS_PIN): pins.gpio_output_pin_schema,
        cv.Optional("status_sensor"): cv.declare_id(sensor.Sensor),
    }
).extend(spi.spi_device_schema())
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_CS_PIN])
    cg.add(var.set_cs_pin(pin))

    if CONF_STATUS_SENSOR in config:
        sens = await cg.get_variable(config[CONF_STATUS_SENSOR])
        cg.add(var.set_status_sensor(sens))
