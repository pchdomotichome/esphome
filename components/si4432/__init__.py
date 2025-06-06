
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import spi, sensor
from esphome.const import CONF_ID

AUTO_LOAD = ["sensor"]
DEPENDENCIES = ["spi"]

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component, spi.SPIDevice)

CONF_STATUS_SENSOR = "status_sensor"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
    cv.Required("cs_pin"): spi.cs_pin,
    cv.Optional(CONF_STATUS_SENSOR): sensor.sensor_schema(),
}).extend(spi.spi_device_schema())

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    if CONF_STATUS_SENSOR in config:
        sens = await sensor.new_sensor(config[CONF_STATUS_SENSOR])
        var.set_status_sensor(sens)
