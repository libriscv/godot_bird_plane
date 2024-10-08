extends Node3D

@onready var plane: Node3D = $"Plane"
@onready var camera: Node3D = $"Camera"

@export var smooth_follow: Sandbox
@export var thrust: Sandbox

var sensitivity: float
var mouse_speed: Vector2

func _process(delta: float):
	smooth_follow._process_parent_child(delta, plane, camera)
	thrust._physics_process_plane(delta, plane)

func _physics_process(_delta) -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
	#$Turning._physics_process_plane(delta, plane)
	
func _input(event: InputEvent):
	if event is InputEventMouseMotion:
		mouse_speed = mouse_speed.lerp(event.get_relative() / 1000, sensitivity);
