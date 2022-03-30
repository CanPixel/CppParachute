#include "GDExample.h"
#include "Player.h"
#include "Money.h"
#include <SceneTree.hpp>
#include <NodePath.hpp>
#include <Viewport.hpp>
#include <string>

using namespace godot;

void GDExample::_ready() {
	lives = 3;
	score = 0;
	_hud = get_node<HUD>("HUD");
	_mob_timer = get_node<Timer>("MobTimer");
	_start_timer = get_node<Timer>("StartTimer");
	_start_timer->start();
	
	_random = (Ref<RandomNumberGenerator>)RandomNumberGenerator::_new();
	_random->randomize();
	
	_screen_size = get_viewport_rect().size;
	GDExample::_endgame = false;
}

void GDExample::_on_MobTimer_timeout() {	
	if(GDExample::_endgame) return;
	
	godot::Node *mob = mob_scene->instance();
	add_child(mob);
	
	Vector2 v = Vector2(_random->randf_range((double)0.0, (double)_screen_size.x - (double)10.0), -((double)_screen_size.y / (double)2.0));
	mob->set("position", v);
}

void GDExample::_hit() {
	if(GDExample::_endgame) return;
	score++;
	_hud->update_score(score);
}

void GDExample::_miss() {
	if(GDExample::_endgame) return;
	lives--;
	
	//Endgame
	if(lives <= 0) {
		_hud->show_end_screen("You Lost");
		return;
	}
	
	_hud->update_lives(lives);
}

void GDExample::_on_StartTimer_timeout() {
	_mob_timer->set_wait_time(_random->randf_range(1.1, 2.0));
	_mob_timer->start();
}

void GDExample::_register_methods() {
	register_property("mob_scene", &GDExample::mob_scene, (Ref<PackedScene>)nullptr);

	register_method("_ready", &GDExample::_ready);
	register_method("_miss", &GDExample::_miss);
	register_method("_hit", &GDExample::_hit);
	register_method("_on_MobTimer_timeout", &GDExample::_on_MobTimer_timeout);
	register_method("_on_StartTimer_timeout", &GDExample::_on_StartTimer_timeout);
}


/** GDNative Initialize **/
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	Godot::gdnative_init(o);
}

/** GDNative Terminate **/
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	Godot::gdnative_terminate(o);
}

/** NativeScript Initialize **/
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	Godot::nativescript_init(handle);
	register_class<GDExample>();
	register_class<Player>();
	register_class<Money>();
	register_class<HUD>();
}