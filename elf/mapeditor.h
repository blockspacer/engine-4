#pragma once
#include <ifsys/ifsys.h>
#include <elf/imapeditor.h>
#include <gfx/gfx.h>
#include <thread>
#include <map>
#include <array>

class mapeditor : public imapeditor {
public:
	virtual ~mapeditor() {}
	virtual const char * name() const override {
		return "EngineLevelEditor0001";
	}
	virtual void init() override;
	virtual bool shutdown() override;

	void set_ifsys(ifsys* pIfSys) { m_pIfSys = pIfSys; }

	void handle_events();
	void draw_gui();

	void new_world();

	enum tool {
		E_LED_TOOL_MIN = 0,
		E_LED_TOOL_SELECT = 0,
		E_LED_TOOL_TERRAIN_RAISE,
		E_LED_TOOL_TERRAIN_LOWER,
		E_LED_TOOL_MAX
	};

	void load_icon(mapeditor::tool id, const std::string& filename);

private:
	ifsys* m_pIfSys;
	std::thread m_thread;
	bool m_bShutdown;

	bool m_bFreeCamera;
	float m_flGameViewX, m_flGameViewY;
	std::map<mapeditor::tool, void*> m_icons;

	// Editor world state

	// GUI State
	bool m_bGUILevelSelectorOpen = false;
	std::array<char, 64> m_szGUILevelSelectorMap;
};