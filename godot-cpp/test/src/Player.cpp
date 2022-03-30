#include "Player.h"
#include "GDExample.h"

using namespace godot;

void Player::_ready() {
	_input = Input::get_singleton();
	_sprite = get_node<Sprite>("Sprite");
	_screen_size = get_viewport_rect().size;
	_speed = 0.0;
}

void Player::_process(float delta) {
	if(GDExample::_endgame) return;
	
	Vector2 velocity(0, 0);
	float input = 0.0;
	if(_input->is_action_pressed("ui_left")) input = _direction = -1.0;
	else if(_input->is_action_pressed("ui_right")) input = _direction = 1.0;
	
	if(input == 0.0) {
		if(_speed > 0) {
			_speed -= delta * _deceleration;
			if(_speed < 0) _speed = 0;
		}
		else {
			_speed += delta * _deceleration;
			if(_speed > 0) _speed = 0;
		}
	} else _speed += delta * input * _acceleration;
	
	if(_direction != _last_dir) _speed /= 2.0;
	_last_dir = _direction;

	_speed = Math::clamp(_speed, -_max_speed, _max_speed);
	velocity.x = _speed;
	
	if(_direction > 0) _sprite->set_flip_h(false);
	else if(_direction < 0) _sprite->set_flip_h(true);
	
	Vector2 position = get_position();
	position += velocity * delta;
	position.x = Math::clamp(position.x, (real_t)-50.0, _screen_size.x);
	set_position(position);
}

void Player::_on_Player_body_entered(godot::Node2D *_body) {
	_body->queue_free();
	emit_signal("hit");
}

void Player::_register_methods() {
	register_method("_on_Player_body_entered", &Player::_on_Player_body_entered);
	register_method("_ready", &Player::_ready);
	register_method("_process", &Player::_process);
	register_property<Player, real_t>("_max_speed", &Player::_max_speed, 600.0);
	register_property<Player, real_t>("_acceleration", &Player::_acceleration, 800.0);
	register_property<Player, real_t>("_deceleration", &Player::_deceleration, 1500.0);
	register_signal<Player>("hit", Dictionary());
}