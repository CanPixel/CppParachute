#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <Input.hpp>
#include <Sprite.hpp>
#include <Area2D.hpp>
#include <CollisionShape2D.hpp>
#include <string>

namespace godot {
	class Player : public Area2D {
		GODOT_CLASS(Player, Area2D)

	private:
		Input *_input;
		Sprite *_sprite;
		Vector2 _screen_size;
		
		float _speed;
		float _max_speed = 600;
		float _acceleration = 800;
		float _deceleration = 1500;
		real_t _direction = 0;
		real_t _last_dir = 0;
		
	public:
		void _init() {} 
		void _ready();
		void _on_Player_body_entered(Node2D *_body);
		void _process(float delta);
		
		static void _register_methods();
	};
}
#endif