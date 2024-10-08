#include "api.hpp"

int dummy = 0;

// extern "C" void _physics_process_plane(Variant event, Node3D plane, Vector2 input_mouse_speed) {
// 	if (is_editor()) {
// 		return;
// 	}
// 	mouse_speed = input_mouse_speed.call("linear_interpolate", mouse_motion.call("get_relative") / Vector2(1000, 1000), sensitivity);
// 	plane.call("rotate_object_local", Vector3(1, 0, 0), mouse_speed.y);
// 	plane.call("rotate_object_local", Vector3(0, 0, 1), mouse_speed.x);
// }
