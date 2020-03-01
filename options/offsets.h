#pragma once

/*
0 = knife
1 = pistol
2 = carbine
3 = shotgun
4 = SMG
5 = sniper
6 = AR
8 = granade
9 = duals
*/

class Offsets
{
public:
	class Game // wrapper for pointers
	{
	public:
		int view_matrix			= 0x101AE8;
		int local_player		= 0x10F4F4;
		int entity_list			= 0x10F4F8;
		int player_count		= 0x10F500;
		int player_in_crosshair = 0x101C38;
	};

	class Entity // dw_module
	{
	public:
		int v3_head_pos = 0x4;
		int v3_velocity = 0x10;
		int v3_foot_pos = 0x34;
		int v3_view_pos = 0x40;
		int f_max_speed = 0x50;
		int f_object_distance = 0x58;
		int f_height = 0x5C;
		int f_max_height = 0x60;
		int f_height_above_head = 0x64;
		int i_health = 0xF8;
		int i_armor = 0xFC;
		int i_granades = 0x158;
		int i_kills = 0x1FC;
		int i_flag_score = 0x200;
		int i_deaths = 0x204;
		int i_score = 0x208;
		int i_team_kills = 0x20C;
		int b_attack = 0x224;
		int str_name = 0x225; // char[260]
		int i_team = 0x32C;
		int i_dead = 0x338;
		int weapon_class = 0x374;
		int byte_norecoil = 0x63786;

		class Weapon // local_player + 0x374
		{
		public:
			int i_id = 0x4;
			int owner_class = 0x8;
			int info_class = 0xC;
			int clip_class = 0x10;
			int magazine_class = 0x14;
			int rapidfire_class = 0x18;

			// local_player + 0x374 + 0x8
			int entity_class = 0x0;

			// local_player + 0x374 + 0xC
			int str_weapon_name = 0x0; // char[260]
			int sh_damage = 0x10C;

			// local_player + 0x374 + 0x10
			int i_current_clip = 0x0;

			// local_player + 0x374 + 0x14
			int i_current_mag = 0x0;

			// local_player + 0x374 + 0x18
			int i_rapidfire = 0x0;
		};
	};

	enum Weapons
	{
		WEAPON_KNIFE,
		WEAPON_PISTOL,
		WEAPON_CARBINE,
		WEAPON_SHOTGUN,
		WEAPON_SMG,
		WEAPON_SNIPER,
		WEAPON_Rifle,
		WEAPON_GRANADE = 8,
		WEAPON_DUALS
	};

	std::array<std::string, 10> arr_weapon_names = {
		"Knife",
		"Pistol",
		"Carbine",
		"Shotgun",
		"SMG",
		"Sniper",
		"Rifle",
		"cpistol", // ignore
		"Granade",
		"Dual Pistols"
	};

	std::array<std::string, 10> arr_weapon_icons = {
		"5",
		"E",
		"a",
		"c",
		"L",
		"Z",
		"W",
		"j",
		"cpistol",
		"B"
	};

public:
	auto get_local_player() -> DWORD_PTR;
	auto get_entity_list() -> DWORD_PTR;
	auto is_entity_dead(DWORD_PTR dw_entity) -> bool;
	auto get_entity_team(DWORD_PTR dw_entity) -> bool;
	auto get_entity_head(DWORD_PTR dw_entity) -> v3;
	auto get_entity_foot(DWORD_PTR dw_entity)-> v3;
	auto get_entity_view(DWORD_PTR dw_entity) -> v3;
	auto get_view_matrix() -> float;
	auto get_entity_screen(v3 v3_world) -> v2;
	auto get_entity_name(DWORD_PTR dw_entity) -> std::string;
	auto get_player_count() -> int;
	auto get_entity_in_crosshair() -> std::string;
	auto get_entity_weapon(DWORD_PTR dw_entity) -> int;

public:
	const BYTE* NOP = (BYTE*)"\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90";
	const BYTE* NoRecoil = (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2";

	bool b_no_recoil = false;
};

extern Offsets* offsets;
extern Offsets::Game* p_game;
extern Offsets::Entity* p_entity;
extern Offsets::Entity::Weapon* p_weapon;