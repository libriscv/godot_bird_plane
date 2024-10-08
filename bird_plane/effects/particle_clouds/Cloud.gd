@tool
extends GPUParticles3D

var velocity = Vector3.ZERO
var alpha = 1: set = set_alpha

func set_alpha(value):
	alpha = clamp(value,0,1)
	process_material.set_shader_parameter("alpha",alpha)
