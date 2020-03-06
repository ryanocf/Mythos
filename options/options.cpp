#include "../include.h"

namespace Options
{
	// aimbot
	bool b_aimbot_active		= false;
	bool b_aimbot_attack_team	= false;
	int i_aimbot_key			= 0x01;
	int i_aimbot_mode			= 0;
	float f_aimbot_fov			= 690;

	// triggerbot
	bool b_triggerbot_active		= false;
	bool b_triggerbot_attack_team	= false;
	int i_triggerbot_key			= 0x02;
	int i_triggerbot_delay			= 0;

	// esp
	bool b_esp_active			= false;
	bool b_esp_active_team		= false;
	int i_esp_box_type			= 0; // 0: Box | 1: Filled Box | 2: Cornered Box | 3: Filled Cornered Box
	ImVec4 v4_esp_enemy_color	= ImVec4(255, 0, 0, 255);
	ImVec4 v4_esp_team_color	= ImVec4(0, 0, 255, 255);

	bool b_esp_health		= false;
	int i_esp_health_style	= 2; // 0: Text | 1: Bar | 2: Text + Bar
	int i_esp_health_pos	= 0; // 0: left | 1: top | 2: bottom

	bool b_esp_armor		= false;
	int i_esp_armor_style	= 2; // 0: Text | 1: Bar | 2: Text + Bar
	int i_esp_armor_pos		= 0; // 0: left | 1: top | 2: bottom

	bool b_esp_name = false;

	bool b_esp_distance = false;

	bool b_esp_weapon		= false;
	int i_esp_weapon_style	= 0; // 0: Text | 1: Icon

	// misc
	bool b_misc_unlimted_health = false;

	bool b_misc_unlimited_ammo	= false;
	int i_misc_weapon_damage	= 0;
	bool b_misc_no_recoil		= false;
	bool b_misc_rapidfire		= false;

	// menu
	bool b_menu_open		= true;
	ImVec4 v4_menu_color	= ImColor(232, 70, 33, 255);
}