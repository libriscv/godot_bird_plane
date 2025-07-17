extends Node3D

@export var smooth_follow: Sandbox_BirdPlaneCoreSmoothFollowSmoothFollow
@export var thrust: CPPScript_BirdPlaneCoreThrustThrust
@export var turning: CPPScript_BirdPlaneCoreTurningTurning

var sensitivity: float
var mouse_speed: Vector2

func simple_method_filter(_sandbox, _obj, method: String) -> bool:
	# TODO: Record the actual methods needed, dump them on exit and add them here
	return method != "free" && method != "queue_free"

func _ready() -> void:
	# Enable restrictions, but make exceptions for most methods on objects
	smooth_follow.set_method_allowed_callback(simple_method_filter)
	thrust.set_method_allowed_callback(simple_method_filter)
	turning.set_method_allowed_callback(simple_method_filter)
	if smooth_follow.is_jit():
		print("SmoothFollow program is JIT-compiled")
	if thrust.is_jit():
		print("Thrust program is JIT-compiled")
	if turning.is_jit():
		print("Turning program is JIT-compiled")

func _process(delta: float):
	var plane: Node3D = get_node("Plane")
	var camera: Node3D = get_node("Camera")
	smooth_follow._process_parent_child(delta, plane, camera)
	thrust._physics_process_plane(delta, plane)

func _physics_process(_delta) -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED
	#$Turning._physics_process_plane(delta, plane)

func _input(event: InputEvent):
	var plane: Node3D = get_node("Plane")

	if event is InputEventMouseMotion:
		turning._input_plane(event, plane, mouse_speed)
