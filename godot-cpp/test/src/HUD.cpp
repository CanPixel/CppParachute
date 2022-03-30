#include "HUD.h"
#include "GDExample.h"

using namespace godot;

void HUD::_ready() {
	_score_label = get_node<Label>("ScoreLabel");
	_time_label = get_node<Label>("TimeLabel");
	_game_timer = get_node<Timer>("GameTimer");
	_life_1 = get_node<CanvasItem>("Lives/life1");
	_life_2 = get_node<CanvasItem>("Lives/life2");
	_life_3 = get_node<CanvasItem>("Lives/life3");
	_end_score = get_node<Label>("EndScreen/BG/Label/ScoreLabel");
	_end_label = get_node<Label>("EndScreen/BG/Label");
	_end_screen = get_node<CanvasItem>("EndScreen");
	_end_screen->hide();
}

void HUD::_game_timer_tick() {
	if(GDExample::_endgame) return;
	
	game_time++;
	
	auto time_left = game_duration - game_time;
	String remaining_time = "0:";
	remaining_time += String::num_int64(time_left);
	_time_label->set_text(remaining_time);
	
	if(time_left <= 0) {
		show_end_screen("You Won!");
		return;
	}
	
	_game_timer->start();
}

void HUD::show_end_screen(String txt) {
	GDExample::_endgame = true;
	_game_timer->stop();
	_end_label->set_text(txt);
	
	String ends = "Score: ";
	ends += String::num_int64(GDExample::score);
	_end_score->set_text(ends);
	
	_end_screen->show();
}

void HUD::update_lives(int lives) {
	auto _all_lives = {_life_1, _life_2, _life_3};
	
	int remaining = _all_lives.size() - lives;
	if(remaining <= 0) return;
	
	for(int i = 0; i < remaining; i++) (*(_all_lives.begin() + i))->hide();
}

void HUD::update_score(int p_score) {
	String text = "Score: ";
	text += String::num_int64(p_score);
	_score_label->set_text(text);
}

void HUD::_register_methods() {
	register_method("_ready", &HUD::_ready);
	register_method("_game_timer_tick", &HUD::_game_timer_tick);
	register_method("update_score", &HUD::update_score);
	register_method("update_lives", &HUD::update_lives);
	register_method("show_end_screen", &HUD::show_end_screen);
	register_property("game_duration", &HUD::game_duration, (real_t)60.0);
}