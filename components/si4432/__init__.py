import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import component
from esphome.const import CONF_ID

CODEOWNERS = ["@tuusuario"]
DEPENDENCIES = []

si4432_ns = cg.esphome_ns.namespace("si4432")
Si4432Component = si4432_ns.class_("Si4432Component", cg.Component)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(Si4432Component),
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

