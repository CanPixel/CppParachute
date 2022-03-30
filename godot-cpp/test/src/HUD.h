#ifndef HUD_H
#define HUD_H

#include <Godot.hpp>
#include <string>
#include <CanvasLayer.hpp>
#include <Label.hpp>
#include <Timer.hpp>
#include <CanvasItem.hpp>

namespace godot {
	class HUD : public CanvasLayer {
		GODOT_CLASS(HUD, CanvasLayer)

	private:
		Label *_score_label;
		Label *_time_label;
		Label *_end_label;
		Label *_end_score;
		Timer *_game_timer;
		CanvasItem *_life_1;
		CanvasItem *_life_2;
		CanvasItem *_life_3;
		CanvasItem *_end_screen;
		float game_time = 0.0;
		
	public:
		real_t game_duration = 60.0;
	
		void _init() {} 
		void _ready();
		void show_end_screen(String txt);
		void show_get_ready();
		void show_game_over();
		void update_lives(int lives);
		void update_score(int score);
		void _game_timer_tick();
		
		static void _register_methods();
	};
}
#endif