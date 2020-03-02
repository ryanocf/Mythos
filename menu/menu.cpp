#include "../include.h"

// fonts
#include "fonts/astriumwep.cpp"

const char* menu_tabs[] = {
	"s",
	"t",
	"u",
	"v"
};

enum {
	TAB_AIM,
	TAB_ESP,
	TAB_MISC,
	TAB_CONFIG
};

auto Menu::draw() -> void
{
	static int i_active = 0;

    ImGui::SetNextWindowSize(ImVec2(700, 500));
    ImGui::Begin("nll", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0));

		ImGui::PushFont(drawing->font3); // icon font
		render_tabs(menu_tabs, i_active, ImVec2(ImGui::GetWindowWidth() / std::size(menu_tabs) - 11.4f, 31), true);
		ImGui::PopFont();

		custom_imgui->CustomBorder(1);
		ImGui::PopStyleVar();

		ImGui::Dummy(ImVec2(0, 10));

		switch (i_active)
		{
		case TAB_AIM:
			render_aim();
			break;

		case TAB_ESP:
			render_esp();
			break;

		case TAB_MISC:
			render_misc();
			break;

		case TAB_CONFIG:
			render_config();
			break;
		}
	}

	//ImGui::ShowDemoWindow();

    ImGui::End();
}

// https://github.com/spirthack/CSGOSimple/tree/master/CSGOSimple#L64
template<size_t T>
auto Menu::render_tabs(const char* (&names)[T], int& i_active, ImVec2 v2_size, bool b_sameline) -> void
{
	bool values[T] = { false };

	values[i_active] = true;

	for (auto i = 0; i < T; i++)
	{
		if (values[i] == true)
			ImGui::PushStyleColor(ImGuiCol_Button, Options::v4_menu_color);
		else
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.05f, 0.05, 0.05f, 1.00f)); // not necessary in general but this way we can pop the style at the end

		if (custom_imgui->Button(names[i], v2_size))
			i_active = i;

		ImGui::PopStyleColor();

		if (b_sameline && i < T - 1)
			ImGui::SameLine();
	}
}

auto Menu::render_aim() -> void
{
	ImGui::Columns(2, NULL, false);
	{
		custom_imgui->Header("Aimbot", 1);
		ImGui::Checkbox("Active##Aimbot", &Options::b_aimbot_active);
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::Checkbox("Attack Team##Aimbot", &Options::b_aimbot_attack_team);
		if (custom_imgui->Keybind("Key##Aimbot", Options::i_aimbot_key, ImVec2(100, 39)))
			custom_imgui->CaptureInputEvent(Options::i_aimbot_key);

		ImGui::SetNextItemWidth(330.0f);
		ImGui::Combo("Mode", &Options::i_aimbot_mode, "FOV\0Distance\0");
		ImGui::SetNextItemWidth(160.0f);
		ImGui::SliderFloat("Smooth", &Options::f_aimbot_smooth, FLT_MIN, 20.0f, "%.1f");
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::SetNextItemWidth(160.0f);
		ImGui::SliderFloat("FOV", &Options::f_aimbot_fov, 15, 1103, "%1.0f");
		if (ImGui::IsItemHovered())
			aimbot->b_aim_fov_hovered = true;
		else
			aimbot->b_aim_fov_hovered = false;

	}
	ImGui::NextColumn();
	{
		custom_imgui->Header("Triggerbot", 2);
		ImGui::Checkbox("Active##Triggerbot", &Options::b_triggerbot_active);
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::Checkbox("Attack Team##Triggerbot", &Options::b_triggerbot_attack_team);
		if (custom_imgui->Keybind("Key##Triggerbot", Options::i_triggerbot_key, ImVec2(100, 39)))
			custom_imgui->CaptureInputEvent(Options::i_triggerbot_key);

		ImGui::SetNextItemWidth(330.0f);
		ImGui::SliderInt("Delay", &Options::i_triggerbot_delay, 0, 200, "%d");
	}
}

auto Menu::render_esp() -> void
{
	ImGui::Columns(2, NULL, false);
	{
		custom_imgui->Header("ESP", 1);
		ImGui::Checkbox("Active##ESP", &Options::b_esp_active);
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::Checkbox("Show Team", &Options::b_esp_active_team);
		ImGui::SetNextItemWidth(330.0f);
		ImGui::Combo("ESP Type", &Options::i_esp_box_type, "Box\0Filled Box\0Cornered Box\0Filled Cornered Box\0");

		ImGui::Checkbox("Health ESP", &Options::b_esp_health);
		ImGui::SetNextItemWidth(160.0f);
		ImGui::Combo("Style##health", &Options::i_esp_health_style, "Text\0Bar\0Text + Bar\0");
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::SetNextItemWidth(160.0f);
		ImGui::Combo("Position##health", &Options::i_esp_health_pos, "Left\0Top\0Bottom\0");

		ImGui::Checkbox("Armor ESP", &Options::b_esp_armor);
		ImGui::SetNextItemWidth(160.0f);
		ImGui::Combo("Style##armor", &Options::i_esp_armor_style, "Text\0Bar\0Text + Bar\0");
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::SetNextItemWidth(160.0f);
		ImGui::Combo("Position##armor", &Options::i_esp_armor_pos, "Left\0Top\0Bottom\0");

		ImGui::Checkbox("Name ESP", &Options::b_esp_name);
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::Checkbox("Distance ESP", &Options::b_esp_distance);
		ImGui::Checkbox("Weapon ESP", &Options::b_esp_weapon);
		ImGui::SetNextItemWidth(330.0f);
		ImGui::Combo("Style##weapon", &Options::i_esp_weapon_style, "Text\0Icon\0");
	}
	ImGui::NextColumn();
	{
		custom_imgui->Header("Colors", 2);
		ImGui::Text("Enemy Color");
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::ColorEdit4("Enemy Color", (float*)&Options::v4_esp_enemy_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoTooltip);
		ImGui::Text("Team Color");
		ImGui::SameLine(178.0f, 0.0f);
		ImGui::ColorEdit4("Team Color", (float*)&Options::v4_esp_team_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoTooltip);
	}
}

auto Menu::render_misc() -> void
{
	ImGui::Columns(2, NULL, false);
	{
		custom_imgui->Header("Player", 1);
		ImGui::Checkbox("Unlimited Health", &Options::b_misc_unlimted_health);
	}
	ImGui::NextColumn();
	{
		custom_imgui->Header("Weapon", 2);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 21)); // ghetto workaround so that I don't have to make more cancer custom imgui shit
		ImGui::Checkbox("Unlimited Ammo", &Options::b_misc_unlimited_ammo);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, -33));
		ImGui::Dummy(ImVec2(242.0f, 0.0f));
		ImGui::SameLine();

		if (ImGui::Button("Set Damage"))
			misc->set_weapon_damage();

		ImGui::PopStyleVar(2);
		ImGui::SetNextItemWidth(242.0f);
		ImGui::SliderInt("Weapon Damage", &Options::i_misc_weapon_damage, 0, 256, "%d");
		ImGui::Checkbox("No Recoil", &Options::b_misc_no_recoil);
		ImGui::Checkbox("Rapidfire", &Options::b_misc_rapidfire);
		ImGui::Checkbox("Force Dual Wield", &Options::b_misc_force_duals);
	}
}

auto Menu::render_config() -> void
{
	ImGui::Columns(2, NULL, false);
	{
		custom_imgui->Header("Config", 1);
		if (ImGui::Button("UNLOAD"))
			render->b_Shutdown = true;
	}
	ImGui::NextColumn();
}

auto Menu::init_style() -> void
{
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig config;
	config.OversampleH = 7;
	config.OversampleV = 7;
	config.RasterizerMultiply = 2.0f;
	drawing->font1 = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 16.0f);
	config.RasterizerMultiply = 1.0f;
	drawing->font2 = io.Fonts->AddFontDefault(&config);
	drawing->font3 = io.Fonts->AddFontFromMemoryCompressedTTF(astriumwep_compressed_data, astriumwep_compressed_size, 24.0f, &config);

	ImGuiStyle& style = ImGui::GetStyle();

	style.ItemSpacing		= ImVec2(10, 10);
	style.GrabRounding		= 0.f;
	style.WindowRounding	= 0.f;
	style.ScrollbarRounding	= 0.f;
	style.FrameRounding		= 0.f;
	style.FrameBorderSize	= 1.0f;
	style.ChildBorderSize	= 1.0f;
	style.PopupBorderSize	= 1.0f;
	style.WindowTitleAlign	= ImVec2(0.5f, 0.5f);
	style.AntiAliasedLines	= false;
	style.AntiAliasedFill	= true;

	style.Colors[ImGuiCol_Text]					= ImVec4(0.85f, 0.85f, 0.85f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled]			= ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_WindowBg]				= ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg]		= ImVec4(0.11f, 0.11f, 0.11f, 0.00f);
	style.Colors[ImGuiCol_PopupBg]				= ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_Border]				= ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow]			= ImVec4(0.60f, 0.60f, 0.60f, 0.30f);
	style.Colors[ImGuiCol_FrameBg]				= ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered]		= ImVec4(0.13f, 0.13f, 0.13f, 0.50f);
	style.Colors[ImGuiCol_FrameBgActive]		= ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_TitleBg]				= Options::v4_menu_color;
	style.Colors[ImGuiCol_TitleBgCollapsed]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_TitleBgActive]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_MenuBarBg]			= ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg]			= ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = Options::v4_menu_color;
	style.Colors[ImGuiCol_ScrollbarGrabActive]	= Options::v4_menu_color;
	style.Colors[ImGuiCol_CheckMark]			= Options::v4_menu_color;
	style.Colors[ImGuiCol_SliderGrab]			= Options::v4_menu_color;
	style.Colors[ImGuiCol_SliderGrabActive]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_Button]				= ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_ButtonActive]			= Options::v4_menu_color;
	style.Colors[ImGuiCol_Header]				= Options::v4_menu_color;
	style.Colors[ImGuiCol_HeaderHovered]		= Options::v4_menu_color;
	style.Colors[ImGuiCol_HeaderActive]			= Options::v4_menu_color;
	style.Colors[ImGuiCol_Separator]			= ImVec4(0.60f, 0.60f, 0.60f, 0.30f);
	style.Colors[ImGuiCol_SeparatorHovered]		= ImVec4(0.60f, 0.60f, 0.60f, 0.30f);
	style.Colors[ImGuiCol_SeparatorActive]		= ImVec4(0.60f, 0.60f, 0.60f, 0.30f);
	style.Colors[ImGuiCol_ResizeGrip]			= ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripHovered]	= ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive]		= ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_PlotLines]			= ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered]		= ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram]		= ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg]		= ImVec4(0.32f, 0.52f, 0.65f, 1.00f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
}

Menu* menu = new Menu();