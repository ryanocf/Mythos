#pragma once

class Visuals
{
public:
	auto draw() -> void;

private:
	auto box_2D(v2 v2_head, v2 v2_foot) -> void;
	auto health(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void;
	auto armor(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void;
	auto name(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void;
	auto distance(v2 v2_head, v2 v2_foot, v3 v3_foot, DWORD_PTR dw_local_player, DWORD_PTR dw_entity) -> void;
	auto weapon(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void;
};

extern Visuals* visuals;