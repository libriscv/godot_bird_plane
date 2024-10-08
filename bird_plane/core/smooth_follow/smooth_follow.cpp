#include "api.hpp"

static float smoothness = 1.0f;

SANDBOXED_PROPERTIES(1, {
	.name = "smoothness",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return smoothness; },
	.setter = [](Variant value) -> Variant { smoothness = value; return Variant(smoothness); },
	.default_value = Variant{1.0f},
});

extern "C" void _process_parent_child(double delta, Node3D parent, Node3D child) {
	if (is_editor()) {
		return;
	}
	Variant parent_transform = parent.call("get_transform");
	Variant last_transform = parent_transform.call("interpolate_with", last_transform, smoothness);
	last_transform.call("set_basis", parent_transform.call("get_basis").call("slerp", last_transform.call("get_basis"), smoothness / 2));
	child.call("set_transform", last_transform);
}
