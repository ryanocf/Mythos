#pragma once

namespace Options
{
	// aimbot
	extern bool b_aimbot_active;
	extern bool b_aimbot_attack_team;
	extern int i_aimbot_key;
	extern int i_aimbot_mode;
	extern float f_aimbot_fov;

	// triggerbot
	extern bool b_triggerbot_active;
	extern bool b_triggerbot_attack_team;
	extern int i_triggerbot_key;
	extern int i_triggerbot_delay;

	// esp
	extern bool b_esp_active;
	extern bool b_esp_active_team;
	extern int i_esp_box_type;
	extern ImVec4 v4_esp_enemy_color;
	extern ImVec4 v4_esp_team_color;

	extern bool b_esp_health;
	extern int i_esp_health_style;
	extern int i_esp_health_pos;

	extern bool b_esp_armor;
	extern int i_esp_armor_style;
	extern int i_esp_armor_pos;

	extern bool b_esp_name;

	extern bool b_esp_distance;

	extern bool b_esp_weapon;
	extern int i_esp_weapon_style;

	// misc
	extern bool b_misc_unlimted_health;

	extern bool b_misc_unlimited_ammo;
	extern int i_misc_weapon_damage;
	extern bool b_misc_no_recoil;
	extern bool b_misc_rapidfire;

	// menu
	extern bool b_menu_open;
	extern ImVec4 v4_menu_color;
}