#include "../../include.h"

auto Aimbot::start() -> void
{
	while (GetAsyncKeyState(Options::i_aimbot_key) && Options::b_aimbot_active && !Options::b_menu_open)
	{
		DWORD_PTR dw_local_player = offsets->get_local_player();
		if (!dw_local_player)
			return;

		DWORD_PTR dw_entity = get_closest_target_to_crosshair(dw_local_player);
		if (!dw_entity)
			return;

		//process->write<BYTE>(dw_local_player + p_entity->b_attack, 1);
		v3 v3_player_head = offsets->get_entity_head(dw_local_player);
		v3 v3_player_view = offsets->get_entity_view(dw_local_player);
		v3 v3_enemy_head = offsets->get_entity_head(dw_entity);

		v3 v3_delta = v3_enemy_head - v3_player_head;
		v3_delta.normalize();

		float f_yaw = -atan2(v3_delta.x, v3_delta.y) / 3.14159265358979323846f * 180 + 180;
		float f_pitch = atan2(v3_delta.z, sqrt(v3_delta.x * v3_delta.x + v3_delta.y * v3_delta.y)) / 3.14159265358979323846f * 180;

		process->write<float>(dw_local_player + p_entity->v3_view_pos, f_yaw);
		process->write<float>(dw_local_player + p_entity->v3_view_pos + 0x4, f_pitch);

		std::this_thread::sleep_for(std::chrono::microseconds(5));
		//process->write<BYTE>(dw_local_player + p_entity->b_attack, 0);
	}
}

auto Aimbot::get_closest_target_to_crosshair(DWORD_PTR dw_local_player) -> DWORD_PTR
{
	DWORD_PTR dw_best_entity = NULL;
	float f_lowest_distance = Options::f_aimbot_fov;

	int player_count = offsets->get_player_count();
	for (auto i = 1; i < player_count; i++)
	{
		DWORD_PTR dw_entity = process->read<DWORD_PTR>(offsets->get_entity_list() + 0x4 * i);
		if (!dw_entity)
			continue;

		if (offsets->is_entity_dead(dw_entity))
			continue;

		if (offsets->get_entity_team(dw_local_player) == offsets->get_entity_team(dw_entity) && !Options::b_aimbot_attack_team)
			continue;

		v3 v3_entity_head = offsets->get_entity_head(dw_entity);
		v2 v2_entity_screen = offsets->get_entity_screen(v3_entity_head);

		float f_distance = sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - v2_entity_screen.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - v2_entity_screen.y, 2));

		if (f_distance < f_lowest_distance)
		{
			f_lowest_distance = f_distance;
			dw_best_entity = dw_entity;
		}
	}
	return dw_best_entity;
}

auto Aimbot::get_closest_target_to_position(DWORD_PTR dw_local_player) -> DWORD_PTR
{
	DWORD_PTR lol = 1;
	return lol;
}

Aimbot* aimbot = new Aimbot();