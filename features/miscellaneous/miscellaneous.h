#pragma once

class Miscellaneous
{
public:
	auto unlimited_health() -> void;
	auto unlimited_ammo() -> void;
	auto set_weapon_damage() -> void;
	auto no_recoil(bool b_state) -> void;
	auto rapidfire() -> void;
	auto force_duals() -> void;
};

extern Miscellaneous* misc;