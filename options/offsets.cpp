#include "../include.h"

auto Offsets::get_local_player() -> DWORD_PTR 
{
	return process->read<DWORD_PTR>(process->dw_module + p_game->local_player);
}

auto Offsets::get_entity_list() -> DWORD_PTR 
{
	return process->read<DWORD_PTR>(process->dw_module + p_game->entity_list);
}

auto Offsets::is_entity_dead(DWORD_PTR dw_entity) -> bool
{
	return process->read<int>(dw_entity + p_entity->i_dead);
}

auto Offsets::get_entity_team(DWORD_PTR dw_entity) -> bool
{
	return process->read<int>(dw_entity + p_entity->i_team);
}

auto Offsets::get_entity_head(DWORD_PTR dw_entity) -> v3
{
	v3 v3_head_pos;
	for (auto i = 0; i < 3; i++)
	{
		v3_head_pos[i] = process->read<float>(dw_entity + p_entity->v3_head_pos + 0x4 * i);
	}
	return v3_head_pos;
}

auto Offsets::get_entity_foot(DWORD_PTR dw_entity) -> v3
{
	v3 v3_entity_pos;
	for (auto i = 0; i < 3; i++)
	{
		v3_entity_pos[i] = process->read<float>(dw_entity + p_entity->v3_foot_pos + 0x4 * i);
	}
	return v3_entity_pos;
}

auto Offsets::get_entity_view(DWORD_PTR dw_entity) -> v3
{
	v3 v3_view_pos;
	for (auto i = 0; i < 3; i++)
	{
		v3_view_pos[i] = process->read<float>(dw_entity + p_entity->v3_view_pos + 0x4 * i);
	}
	return v3_view_pos;
}

auto Offsets::get_view_matrix() -> float
{
	return process->read<DWORD_PTR>(process->dw_module + p_game->view_matrix);
}

auto Offsets::get_entity_screen(v3 v3_world) -> v2
{
	float f_matrix[16];
	for (auto i = 0; i < 16; i++) // index is always 16 in 3D games
	{
		f_matrix[i] = process->read<float>(process->dw_module + p_game->view_matrix + 0x4 * i);
	}

	return math->world_to_screen(v3_world, f_matrix, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

auto Offsets::get_entity_name(DWORD_PTR dw_entity) -> std::string
{
	char name[32];
	process->read(dw_entity + p_entity->str_name, &name, 32);
	char c[32];
	sprintf(c, "%s", name);
	return std::string(c);
}

auto Offsets::get_player_count() -> int
{
	return process->read<int>(process->dw_module + p_game->player_count);
}

auto Offsets::get_entity_in_crosshair() -> std::string
{
	char name[32];
	process->read(process->dw_module + p_game->player_in_crosshair, &name, 32);
	char c[32];
	sprintf(c, "%s", name);
	return std::string(c);
}

auto Offsets::get_entity_weapon(DWORD_PTR dw_entity) -> int
{
	std::vector<int> v3_offsets = { p_entity->weapon_class, p_weapon->i_id };
	return process->read_multi<int>(dw_entity, v3_offsets);
}

Offsets* offsets					= new Offsets();
Offsets::Game* p_game				= new Offsets::Game();
Offsets::Entity* p_entity			= new Offsets::Entity();
Offsets::Entity::Weapon* p_weapon	= new Offsets::Entity::Weapon();