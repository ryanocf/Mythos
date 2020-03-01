#include "../../include.h"

auto Miscellaneous::unlimited_health() -> void
{
	DWORD_PTR dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;

	process->write<int>(dw_local_player + p_entity->i_health, 9999);
	process->write<int>(dw_local_player + p_entity->i_armor, 9999);
}

auto Miscellaneous::unlimited_ammo() -> void
{
	DWORD_PTR dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;

	// local_player + 0x374 = x1
	// x1 + 0x14 = x2
	// x2 + 0x0 = ammo
	
	std::vector<int> offsets;
	offsets = { p_entity->weapon_class, p_weapon->clip_class };
	DWORD_PTR i_WeaponCurPtr = process->read_multi<DWORD_PTR>(dw_local_player, offsets);
	offsets = { p_entity->weapon_class, p_weapon->magazine_class };
	DWORD_PTR i_WeaponMagPtr = process->read_multi<DWORD_PTR>(dw_local_player, offsets);

	process->write<int>(i_WeaponCurPtr + p_weapon->i_current_clip, 9999);
	process->write<int>(i_WeaponMagPtr + p_weapon->i_current_mag, 9999);
	process->write<int>(dw_local_player + p_entity->i_granades, 9999);

}

auto Miscellaneous::set_weapon_damage() -> void
{
	DWORD_PTR dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;

	std::vector<int> v3_offsets = { p_entity->weapon_class, p_weapon->info_class };
	DWORD_PTR dw_weapon_damage_ptr = process->read_multi<DWORD_PTR>(dw_local_player, v3_offsets);

	process->write<int>(dw_weapon_damage_ptr + p_weapon->sh_damage, Options::i_misc_weapon_damage);
}

auto Miscellaneous::no_recoil(bool b_state) -> void
{
	DWORD_PTR dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;

	if (b_state)
		process->write_protected(process->dw_module + p_entity->byte_norecoil, offsets->NOP, 10);
	else
		process->write_protected(process->dw_module + p_entity->byte_norecoil, offsets->NoRecoil, 10);
}

auto Miscellaneous::rapidfire() -> void
{
	DWORD_PTR dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;

	std::vector<int> v3_offsets = { p_entity->weapon_class, p_weapon->rapidfire_class };
	DWORD_PTR dw_rapidfire_ptr = process->read_multi<DWORD_PTR>(dw_local_player, v3_offsets);

	process->write<int>(dw_rapidfire_ptr + p_weapon->i_rapidfire, 0);
}

auto Miscellaneous::force_duals() -> void
{
	int dw_local_player = offsets->get_local_player();
	if (!dw_local_player)
		return;
}

Miscellaneous* misc = new Miscellaneous();