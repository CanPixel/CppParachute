#ifndef MONEY_H
#define MONEY_H

#include <Godot.hpp>
#include <Input.hpp>
#include <Sprite.hpp>
#include <RigidBody2D.hpp>
#include <RandomNumberGenerator.hpp>
#include "GDExample.h"

namespace godot {
	class Money : public RigidBody2D {
		GODOT_CLASS(Money, RigidBody2D)
		
		float _max_speed = 350;
		real_t _acceleration = 200;
		float _speed = 1.0;
		real_t _sway;
		real_t _sway_speed;
		float time_passed;
		GDExample *_main;
		
		Ref<RandomNumberGenerator> _random;
		
	public:
		Vector2 direction = Vector2(0, 1);
	
		void _init();
		void _ready();
		void _process(float delta);
		void _kill();
		
		static void _register_methods();
	};
}
#endif