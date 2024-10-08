#include "api.hpp"

static float velocity = 0;
static float thrust = 0;
static float thrust_limit = 50;
static float thrust_delta = 0;
static float gravity_influence = 100;
static float smooth = 0.9;

SANDBOXED_PROPERTIES(6, {
	.name = "velocity",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return velocity; },
	.setter = [](Variant value) -> Variant { velocity = value; return Variant(velocity); },
	.default_value = Variant{0.f},
}, {
	.name = "thrust",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return thrust; },
	.setter = [](Variant value) -> Variant { thrust = value; return Variant(thrust); },
	.default_value = Variant{0.f},
}, {
	.name = "thrust_limit",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return thrust_limit; },
	.setter = [](Variant value) -> Variant { thrust_limit = value; return Variant(thrust_limit); },
	.default_value = Variant{50.f},
}, {
	.name = "thrust_delta",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return thrust_delta; },
	.setter = [](Variant value) -> Variant { thrust_delta = value; return Variant(thrust_delta); },
	.default_value = Variant{0.f},
}, {
	.name = "gravity_influence",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return gravity_influence; },
	.setter = [](Variant value) -> Variant { gravity_influence = value; return Variant(gravity_influence); },
	.default_value = Variant{100.f},
}, {
	.name = "smooth",
	.type = Variant::FLOAT,
	.getter = []() -> Variant { return smooth; },
	.setter = [](Variant value) -> Variant { smooth = value; return Variant(smooth); },
	.default_value = Variant{0.9f},
});

extern "C" Variant _physics_process_plane(double delta, Node3D plane) {
	if (is_editor()) {
		return Nil;
	}
	constexpr double Math_PI = 3.14159265358979;
	float y_ang = 0;
	Vector3 direction;
	Vector3 target_vector;
	Transform3D transform;
	float target_speed = 0;
	Basis basis = plane.get_transform().get_basis();
	
	direction = basis.get_column(2);

	y_ang = direction.angle_to(Vector3(0, 1, 0));
	if ((thrust <= thrust_limit && thrust_delta > 0) || (thrust >= 0 && thrust_delta < 0)) {
		thrust += thrust_delta;
	}
	target_speed = thrust + (y_ang / Math_PI - 0.5) * gravity_influence; // We subtract 0.5 from the angle over pi because gravity's influence should be zero at 90 degrees or when the angle over pi is 0.5
	velocity = (velocity * smooth + target_speed * (1 - smooth)) / 2;
	target_vector = Vector3(0, 0, velocity);
	transform = plane.get_transform();
	transform.translate(target_vector * delta);
	plane.set_transform(transform);
	// if (frame_counter == 0) {
	// 	print("thrust: %d\n", int(thrust * 1000));
	// 	print("y_ang: %d\n", int(y_ang * 1000));
	// 	print("velocity: %d\n", int(velocity * 1000));
	// }

	return Nil;
}
