#include "Money.h"
#include <string>

using namespace godot;

void Money::_init() {	
	_random = (Ref<godot::RandomNumberGenerator>)RandomNumberGenerator::_new();
	_random->randomize();
	_sway = _random->randf_range(0.0, 2.2);
	_sway_speed = _random->randf_range(1.5, 5.0);
	_acceleration = _random->randf_range(40.0, 100.0);
	_speed = 0.5;
	time_passed = 0.0;
}

void Money::_ready() {
	_main = get_node<GDExample>("../");
}

void Money::_process(float delta) {	
	time_passed += delta;
	Vector2 velocity(0, 0);
	Vector2 position = get_position();
	
	_speed += delta * _acceleration;
	_speed = Math::clamp(_speed, (float)0.0, _max_speed);
	
	position.y += _speed * (real_t)delta;
	position.x += sin(time_passed * _sway_speed) * _sway;
	set_position(position);
	
	//Out of screen bounds aka MISSED
	if(position.y > 515) _kill();
}

void Money::_kill() {
	_main->_miss();
	queue_free();
}

void Money::_register_methods() {
	register_method("_process", &Money::_process);
	register_method("_ready", &Money::_ready);
	register_property("_max_speed", &Money::_max_speed, (float)350.0);
	register_method("_kill", &Money::_kill);
}