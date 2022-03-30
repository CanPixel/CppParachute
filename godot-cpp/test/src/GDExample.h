#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Sprite.hpp>
#include <Timer.hpp>
#include <PackedScene.hpp>
#include <RandomNumberGenerator.hpp>
#include "HUD.h"

namespace godot {

class GDExample : public Sprite {
	GODOT_CLASS(GDExample, Sprite)
	
	int lives;
	HUD *_hud;
	Timer *_mob_timer;
	Timer *_start_timer;
	Ref<RandomNumberGenerator> _random;
	
public:
	Vector2 _screen_size;
	Ref<PackedScene> mob_scene;
	inline static bool _endgame = false;
	inline static int score = 0;
	
	static void _register_methods();

	void _init() {}
	void _ready();
	void _hit();
	void _miss();
	
	void _on_MobTimer_timeout();
	void _on_StartTimer_timeout();
};
}
#endif