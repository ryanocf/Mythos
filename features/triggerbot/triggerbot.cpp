#include "../../include.h"

auto Triggerbot::start() -> void
{	
	while (GetAsyncKeyState(Options::i_triggerbot_key) && Options::b_triggerbot_active && !Options::b_menu_open)
	{
		clear_name();

		std::this_thread::sleep_for(std::chrono::milliseconds(18));

		str_player = offsets->get_entity_in_crosshair();

		int player_count = offsets->get_player_count();
		for (auto i = 0; i < player_count; i++)
		{
			DWORD_PTR dw_local_player = offsets->get_local_player();
			if (!dw_local_player)
				continue;

			DWORD_PTR dw_entity = process->read<DWORD_PTR>(offsets->get_entity_list() + 0x4 * i);
			if (!dw_entity)
				continue;

			int i_weapon_id = offsets->get_entity_weapon(dw_local_player);
			if (i_weapon_id == offsets->WEAPON_KNIFE || i_weapon_id == offsets->WEAPON_GRANADE)
				continue;

			std::string str_entity = offsets->get_entity_name(dw_entity);
			if (str_entity.compare(str_player) != 0)
				continue;

			if (offsets->is_entity_dead(dw_entity))
				continue;

			if (offsets->get_entity_team(dw_local_player) == offsets->get_entity_team(dw_entity) && !Options::b_triggerbot_attack_team)
				continue;

			if (Options::b_triggerbot_active && !str_player.empty()) {
				shoot(dw_local_player);
				break;
			}
		}
	}
}

auto Triggerbot::shoot(DWORD_PTR dw_local_player) -> void
{
	if (Options::i_triggerbot_delay > 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(Options::i_triggerbot_delay));

	process->write<BYTE>(dw_local_player + p_entity->b_attack, 1);
	std::this_thread::sleep_for(std::chrono::milliseconds(18));
	process->write<BYTE>(dw_local_player + p_entity->b_attack, 0);
	return;
}

auto Triggerbot::clear_name() -> void
{
	BYTE* pattern = (BYTE*)"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";
	process->write_protected(process->dw_module + p_game->player_in_crosshair, pattern, 15);
	str_player.clear();
	return;
}

Triggerbot* triggerbot = new Triggerbot();