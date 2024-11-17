extends Node

@export var sandy : Sandbox_BirdPlaneCoreThrustThrust

func _ready() -> void:
	sandy.vmcall("test", "test")
	sandy.vmcall("test", "test")

	sandy.vmcall("test")
