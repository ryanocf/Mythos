#include "../../include.h"

ImVec4 iv4_BoxColor;

auto Visuals::draw() -> void
{
	int player_count = offsets->get_player_count();
	for (auto i = 1; i < player_count; i++)
	{
		DWORD_PTR dw_local_player = offsets->get_local_player();
		if (!dw_local_player)
			continue;

		DWORD_PTR dw_entity = process->read<DWORD_PTR>(offsets->get_entity_list() + 0x4 * i);
		if (!dw_entity)
			continue;

		if (offsets->is_entity_dead(dw_entity))
			continue;

		int i_player_team = offsets->get_entity_team(dw_local_player);
		int i_entity_team = offsets->get_entity_team(dw_entity);

		if (i_player_team == i_entity_team && !Options::b_esp_active_team)
			continue;

		if (i_player_team == i_entity_team)
			iv4_BoxColor = Options::v4_esp_team_color;
		else
			iv4_BoxColor = Options::v4_esp_enemy_color;


		// ghetto code
		v3 v3_head = offsets->get_entity_head(dw_entity);
		v3 v3_foot = offsets->get_entity_foot(dw_entity);

		v3_head.z += 0.7f;

		v2 v2_head = offsets->get_entity_screen(v3_head);
		v2 v2_foot = offsets->get_entity_screen(v3_foot);

		if (Options::b_esp_aim_fov)
			aim_fov(dw_local_player, dw_entity);

		if (v2_head == v2(-1, -1) || v2_foot == v2(-1, -1))
			continue;

		if (Options::b_esp_active)
			box_2D(v2_head, v2_foot);

		if (Options::b_esp_health)
			health(v2_head, v2_foot, dw_entity);

		if (Options::b_esp_armor)
			armor(v2_head, v2_foot, dw_entity);

		if (Options::b_esp_name)
			name(v2_head, v2_foot, dw_entity);

		if (Options::b_esp_distance)
			distance(v2_head, v2_foot, v3_foot, dw_local_player, dw_entity);

		if (Options::b_esp_weapon)
			weapon(v2_head, v2_foot, dw_entity);
	}
}

auto Visuals::box_2D(v2 v2_head, v2 v2_foot) -> void
{
	float w, left, top, right, bottom;

	w = (v2_foot.y - v2_head.y) / 4; // player width

	left = v2_foot.x - w;
	top = v2_head.y;
	right = v2_foot.x + w;
	bottom = v2_foot.y;

	RECT box = { left, top, right, bottom };
	switch (Options::i_esp_box_type)
	{
		case 0:
			drawing->rect(box, iv4_BoxColor, 1.0f, true, true);
			break;

		case 1:
			iv4_BoxColor.w = 0.1f;
			drawing->filled_rect(box, iv4_BoxColor, false);
			iv4_BoxColor.w = 1.0f;
			drawing->rect(box, iv4_BoxColor, 1.0f, true, true);
			break;

		case 2:
			drawing->filled_rect({ (LONG)left - 1, (LONG)top - 1, (LONG)left + 6, (LONG)top + 2 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)left - 1, (LONG)top - 1, (LONG)left + 2, (LONG)top + 6 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)right - 6, (LONG)top - 1, (LONG)right, (LONG)top + 2 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)right - 2, (LONG)top - 1, (LONG)right + 1, (LONG)top + 6 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)left - 1, (LONG)bottom - 2, (LONG)left + 6, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)left - 1, (LONG)bottom - 6, (LONG)left + 2, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)right - 6, (LONG)bottom - 2, (LONG)right, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)right - 2, (LONG)bottom - 6, (LONG)right + 1, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);

			drawing->line({ (LONG)left, (LONG)top + 1, (LONG)left + 5, (LONG)top + 1 }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)left + 1, (LONG)top, (LONG)left + 1, (LONG)top + 5 }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)right - 5, (LONG)top + 1, (LONG)right, (LONG)top + 1 }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)right, (LONG)top, (LONG)right, (LONG)top + 5 }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)left, (LONG)bottom, (LONG)left + 5, (LONG)bottom }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)left + 1, (LONG)bottom - 5, (LONG)left + 1, (LONG)bottom }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)right - 5, (LONG)bottom, (LONG)right, (LONG)bottom }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)right, (LONG)bottom - 5, (LONG)right, (LONG)bottom }, iv4_BoxColor, 1.0f);
			break;

		case 3:
			iv4_BoxColor.w = 0.1f;
			drawing->filled_rect(box, iv4_BoxColor, false);
			iv4_BoxColor.w = 1.0f;

			drawing->filled_rect({ (LONG)left - 1, (LONG)top - 1, (LONG)left + 6, (LONG)top + 2 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)left - 1, (LONG)top - 1, (LONG)left + 2, (LONG)top + 6 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)right - 6, (LONG)top - 1, (LONG)right, (LONG)top + 2 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)right - 2, (LONG)top - 1, (LONG)right + 1, (LONG)top + 6 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)left - 1, (LONG)bottom - 2, (LONG)left + 6, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)left - 1, (LONG)bottom - 6, (LONG)left + 2, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);

			drawing->filled_rect({ (LONG)right - 6, (LONG)bottom - 2, (LONG)right, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect({ (LONG)right - 2, (LONG)bottom - 6, (LONG)right + 1, (LONG)bottom + 1 }, ImVec4(0, 0, 0, 1), false);

			drawing->line({ (LONG)left, (LONG)top + 1, (LONG)left + 5, (LONG)top + 1 }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)left + 1, (LONG)top, (LONG)left + 1, (LONG)top + 5 }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)right - 5, (LONG)top + 1, (LONG)right, (LONG)top + 1 }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)right, (LONG)top, (LONG)right, (LONG)top + 5 }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)left, (LONG)bottom, (LONG)left + 5, (LONG)bottom }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)left + 1, (LONG)bottom - 5, (LONG)left + 1, (LONG)bottom }, iv4_BoxColor, 1.0f);

			drawing->line({ (LONG)right - 5, (LONG)bottom, (LONG)right, (LONG)bottom }, iv4_BoxColor, 1.0f);
			drawing->line({ (LONG)right, (LONG)bottom - 5, (LONG)right, (LONG)bottom }, iv4_BoxColor, 1.0f);
			break;
	}
}

auto Visuals::health(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void
{
	int health = process->read<int>(dw_entity + p_entity->i_health);

	float dis = 3.0f;

	float bw = 2.0f; // Bar Width

	float htt = v2_foot.y - v2_head.y; // Head To Toe
	float w = (v2_foot.y - v2_head.y) / 4; // player width

	float dif, left, top, right, bottom;
	RECT bar_bg;
	ImVec2 text;

	switch (Options::i_esp_health_pos)
	{
		case 0:
			dif = htt;
			left = v2_foot.x - w - dis - bw;
			top = v2_head.y + htt - ((dif * health) / 100);
			right = v2_foot.x - w - dis;
			bottom = v2_foot.y;
			bar_bg = { (LONG)left - 1, (LONG)v2_head.y - 1, (LONG)right + 1, (LONG)bottom - 1 };
			break;

		case 1:
			dif = (v2_foot.x + w) - (v2_foot.x - w);
			left = v2_foot.x - w;
			top = v2_head.y - dis - bw;
			right = v2_foot.x - w + ((dif * health) / 100);
			bottom = v2_head.y - dis;
			bar_bg = { (LONG)left - 1, (LONG)top - 1, (LONG)v2_foot.x + (LONG)w + 1, (LONG)bottom + 1 };
			break;

		case 2:
			dif = (v2_foot.x + w) - (v2_foot.x - w);
			left = v2_foot.x - w;
			top = v2_foot.y + dis;
			right = v2_foot.x - w + ((dif * health) / 100);
			bottom = v2_foot.y + dis + bw;
			bar_bg = { (LONG)left - 1, (LONG)top - 1, (LONG)v2_foot.x + (LONG)w + 1, (LONG)bottom + 1 };
			break;
	}
	RECT bar_health = { left, top, right, bottom };
	text = ImVec2(v2_foot.x + w + dis, v2_head.y);

	switch (Options::i_esp_health_style)
	{
		case 0:
			drawing->text(text, "HP:" + std::to_string(health), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
			break;

		case 1:
			drawing->filled_rect(bar_bg, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect(bar_health, ImVec4(0, 1, 0, 1), false);
			break;

		case 2:
			drawing->filled_rect(bar_bg, ImVec4(0, 0, 0, 1), false);
			drawing->filled_rect(bar_health, ImVec4(0, 0.9f, 0, 1), false);
			drawing->text(text, "HP:" + std::to_string(health), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
			break;
	}
}

auto Visuals::armor(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void
{
	int armor = process->read<int>(dw_entity + p_entity->i_armor);

	float dis;
	if (!Options::b_esp_health || Options::i_esp_armor_pos != Options::i_esp_health_pos || Options::i_esp_health_style == 0)
		dis = 3.0f; // distance between box and bar
	else
		dis = 8.0f;

	float bw = 2.0f; // Bar Width

	float htt = v2_foot.y - v2_head.y; // Head To Toe
	float w = (v2_foot.y - v2_head.y) / 4; // player width

	float dif, left, top, right, bottom;
	RECT bar_bg;
	ImVec2 text;

	switch (Options::i_esp_armor_pos)
	{
	case 0:
		dif = htt;
		left = v2_foot.x - w - dis - bw;
		top = v2_head.y + htt - ((dif * armor) / 100);
		right = v2_foot.x - w - dis;
		bottom = v2_foot.y;
		bar_bg = { (LONG)left - 1, (LONG)v2_head.y - 1, (LONG)right + 1, (LONG)bottom - 1 };
		break;

	case 1:
		dif = (v2_foot.x + w) - (v2_foot.x - w);
		left = v2_foot.x - w;
		top = v2_head.y - dis - bw;
		right = v2_foot.x - w + ((dif * armor) / 100);
		bottom = v2_head.y - dis;
		bar_bg = { (LONG)left - 1, (LONG)top - 1, (LONG)v2_foot.x + (LONG)w + 1, (LONG)bottom + 1 };
		break;

	case 2:
		dif = (v2_foot.x + w) - (v2_foot.x - w);
		left = v2_foot.x - w;
		top = v2_foot.y + dis;
		right = v2_foot.x - w + ((dif * armor) / 100);
		bottom = v2_foot.y + dis + bw;
		bar_bg = { (LONG)left - 1, (LONG)top - 1, (LONG)v2_foot.x + (LONG)w + 1, (LONG)bottom + 1 };
		break;
	}
	RECT bar_armor = { left, top, right, bottom };
	int i_hdif;
	if (!Options::b_esp_health || Options::i_esp_health_style % 2 == 1)
		i_hdif = 0;
	else
		i_hdif = 13;

	dis = 3.0f;
	text = ImVec2(v2_foot.x + w + dis, v2_head.y + i_hdif);
	switch (Options::i_esp_armor_style)
	{
	case 0:
		drawing->text(text, "AP:" + std::to_string(armor), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
		break;

	case 1:
		drawing->filled_rect(bar_bg, ImVec4(0, 0, 0, 1), false);
		drawing->filled_rect(bar_armor, ImVec4(0, 1, 1, 1), false);
		break;

	case 2:
		drawing->filled_rect(bar_bg, ImVec4(0, 0, 0, 1), false);
		drawing->filled_rect(bar_armor, ImVec4(0, 0.9f, 0.9f, 1), false);
		drawing->text(text, "AP:" + std::to_string(armor), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
		break;
	}
}

auto Visuals::name(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void
{
	std::string name = offsets->get_entity_name(dw_entity);
	ImVec2 text_pos = ImGui::CalcTextSize(name.c_str());
	int i_hdif = 15;

	if (Options::b_esp_health && Options::i_esp_health_pos == 1 && Options::i_esp_health_style > 0)
		i_hdif = 20;

	if (Options::b_esp_armor && Options::i_esp_armor_pos == 1 && Options::i_esp_armor_style > 0)
		i_hdif = 20;

	if (Options::b_esp_health && Options::b_esp_armor && Options::i_esp_health_pos == 1 && Options::i_esp_armor_pos == 1 && Options::i_esp_health_style > 0 && Options::i_esp_armor_style > 0)
		i_hdif = 25;

	drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_head.y - i_hdif), name.c_str(), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
}

auto Visuals::weapon(v2 v2_head, v2 v2_foot, DWORD_PTR dw_entity) -> void
{
	int weaponid = offsets->get_entity_weapon(dw_entity);
	std::string weaponname = offsets->arr_weapon_names[weaponid];
	std::string weaponicon = offsets->arr_weapon_icons[weaponid];
	ImVec2 text_pos;
	int i_hdif = 1;

	switch (Options::i_esp_weapon_style)
	{
	case 0:
		text_pos = ImGui::CalcTextSize(weaponname.c_str());

		if (Options::b_esp_health && Options::i_esp_health_pos == 2 && Options::i_esp_health_style > 0)
			i_hdif = 6;

		if (Options::b_esp_armor && Options::i_esp_armor_pos == 2 && Options::i_esp_armor_style > 0)
			i_hdif = 6;

		if (Options::b_esp_health && Options::b_esp_armor && Options::i_esp_health_pos == 2 && Options::i_esp_armor_pos == 2 && Options::i_esp_health_style > 0 && Options::i_esp_armor_style > 0)
			i_hdif = 11;

		if (Options::b_esp_health + Options::b_esp_armor != 2 || Options::i_esp_health_pos != 3 || Options::i_esp_armor_pos != 3 || Options::i_esp_health_style == 0 || Options::i_esp_armor_style == 0)
			drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_foot.y + i_hdif), weaponname.c_str(), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
		else
			drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_foot.y + i_hdif), weaponname.c_str(), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);

		break;

	case 1:
		drawing->font3->Scale = 0.6f;
		ImGui::PushFont(drawing->font3);
		text_pos = ImGui::CalcTextSize(weaponicon.c_str());

		if (Options::b_esp_health && Options::i_esp_health_pos == 2 && Options::i_esp_health_style > 0)
			i_hdif = 6;

		if (Options::b_esp_armor && Options::i_esp_armor_pos == 2 && Options::i_esp_armor_style > 0)
			i_hdif = 6;

		if (Options::b_esp_health && Options::b_esp_armor && Options::i_esp_health_pos == 2 && Options::i_esp_armor_pos == 2 && Options::i_esp_health_style > 0 && Options::i_esp_armor_style > 0)
			i_hdif = 11;

		drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_foot.y + i_hdif), weaponicon.c_str(), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);

		ImGui::PopFont();
		drawing->font3->Scale = 1.0f;
		break;
	}
}

auto Visuals::distance(v2 v2_head, v2 v2_foot, v3 v3_foot, DWORD_PTR dw_local_player, DWORD_PTR dw_entity) -> void
{
	v3 v3_local_foot = offsets->get_entity_foot(dw_local_player);
	v3* dis = new v3(v3_local_foot.x, v3_local_foot.y, v3_local_foot.z);
	int dist = dis->dist_to_sqr(v3_foot) / 100;
	char c[32];
	sprintf(c, "%im", dist);

	ImVec2 text_pos = ImGui::CalcTextSize(c);
	int i_hdif = 0;

	int plush = 0;
	if (Options::b_esp_distance + Options::b_esp_weapon == 2)
		plush = 13;

	if (Options::b_esp_health && Options::i_esp_health_pos == 2 && Options::i_esp_health_style > 0)
		i_hdif = 5;

	if (Options::b_esp_armor && Options::i_esp_armor_pos == 2 && Options::i_esp_armor_style > 0)
		i_hdif = 5;

	if (Options::b_esp_health && Options::b_esp_armor && Options::i_esp_health_pos == 2 && Options::i_esp_armor_pos == 2 && Options::i_esp_health_style > 0 && Options::i_esp_armor_style > 0)
		i_hdif = 10;
	
	if (Options::b_esp_health + Options::b_esp_armor != 2 || Options::i_esp_health_pos != 2 || Options::i_esp_armor_pos != 2 || Options::i_esp_health_style == 0 || Options::i_esp_armor_style == 0)
		drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_foot.y + i_hdif + plush), std::string(c), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
	else
		drawing->text(ImVec2(v2_foot.x - (text_pos.x / 2), v2_foot.y + i_hdif + plush), std::string(c), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
}

auto Visuals::aim_fov(DWORD_PTR dw_local_player, DWORD_PTR dw_entity) -> void
{
	v2 cam;
	cam.x = GetSystemMetrics(SM_CXSCREEN) / 2;
	cam.y = GetSystemMetrics(SM_CYSCREEN) / 2;

	drawing->circle(ImVec2(cam.x, cam.y), Options::f_aimbot_fov, ImVec4(0.9f, 0.9f, 0.9f, 1.0f), 2.0f, true, true);

	v3 v3_head = offsets->get_entity_head(dw_entity);
	v2 v2_head = offsets->get_entity_screen(v3_head);
	float f_distance = sqrt(pow(cam.x - v2_head.x, 2) + pow(cam.y - v2_head.y, 2));
	if (f_distance <= Options::f_aimbot_fov && Options::f_aimbot_fov < 1103) {
		RECT line = { cam.x, cam.y, v2_head.x, v2_head.y };
		drawing->line(line, ImVec4(0.9f, 0.9f, 0.9f, 0.9f), 1.0f);

		RECT rect = { v2_head.x - 2, v2_head.y - 2, v2_head.x + 2, v2_head.y + 2 };
		if (dw_entity == aimbot->get_closest_target_to_crosshair(dw_local_player))
			drawing->filled_rect(rect, Options::v4_esp_aim_fov_focused_color, true);
		else
			drawing->filled_rect(rect, Options::v4_esp_aim_fov_color, true);

		ImVec2 v2_text_size = ImGui::CalcTextSize(std::to_string((int)f_distance).c_str());

		ImVec2 v2_text_pos;
		v2_text_pos.x = cam.x > v2_head.x ? cam.x - (cam.x - v2_head.x) / 2 - v2_text_size.x / 2 : cam.x + (v2_head.x - cam.x) / 2 - v2_text_size.x / 2;
		v2_text_pos.y = cam.y > v2_head.y ? cam.y - (cam.y - v2_head.y) / 2 - v2_text_size.y / 2 : cam.y + (v2_head.y - cam.y) / 2 - v2_text_size.y / 2;

		drawing->text(v2_text_pos, std::to_string((int)f_distance), ImVec4(0.9f, 0.9f, 0.9f, 1.0f), true);
	}
}

Visuals* visuals = new Visuals();