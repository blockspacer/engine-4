#include "stdafx.h"
#include <enl/cmdline.h>
#include "entsys.h"
#include "renderer.h"
#include "event_handler.h"
#include "memstat.h"
#include <chrono>

void thread_logic();
void thread_rendering();
void thread_sound();

int main(int argc, char** argv)
{
	memstat_init();
	memstat_enabled = true;
	CMDLINE_INIT();

	//PRINT_DBG(gpCmdline->GetExecName());
	// init globals
	ASSERT(gpGlobals);

	gpGlobals->pEntSys = new entsys();
	gpGlobals->pRenderer = new renderer();
	gpGlobals->pEventHandler = new event_handler();
	
	// Start main threads

	std::thread thread_logic_(thread_logic);
	PRINT_DBG("Logic thread started");
	std::thread thread_rendering_(thread_rendering);
	PRINT_DBG("Rendering thread started");
	std::thread thread_sound_(thread_sound);
	PRINT_DBG("Sound thread started");

	thread_rendering_.join();
	thread_logic_.join();
	thread_sound_.join();

	// deinit globals
	delete gpGlobals->pEventHandler;
	delete gpGlobals->pRenderer;
	delete gpGlobals->pEntSys;

	memstat_enabled = false;
	memstat_print();

#if defined(PLAT_DEBUG)

#endif

#if defined(PLAT_DEBUG) // wait for key
	PRINT("Press a key to exit...");
	std::string a;
	std::cin >> a;
#endif

	//CMDLINE_SHUTDOWN(); // CRASH HERE

	return 0;
}

void thread_logic()
{
	gpGlobals->iThreadLogic = std::this_thread::get_id();

	gpGlobals->pRenderer->begin_load();
	auto a = gpGlobals->pRenderer->load_model("data/models/cowboy_hat.smd");
	auto b = gpGlobals->pRenderer->load_model("data/models/cowboy_hat.smd");
	ASSERT(a == b);
	gpGlobals->pRenderer->load_shader("data/shaders/model_dynamic.qc");
	gpGlobals->pRenderer->end_load();

	std::chrono::high_resolution_clock::time_point m_start, m_end;

	while (gpGlobals->bRunning)
	{
		m_start = std::chrono::high_resolution_clock::now();
		gpGlobals->pEntSys->update_entities();
		m_end = std::chrono::high_resolution_clock::now();
		float flElapsed = std::chrono::duration_cast<std::chrono::duration<float>>(m_end - m_start).count();
		if (flElapsed < 0.015625f)
		{
			//std::this_thread::sleep_for(std::chrono::duration<float>(0.015625f - flElapsed));
		}
		gpGlobals->flDeltaTime = flElapsed;
		gpGlobals->curtime += gpGlobals->flDeltaTime;

		gpGlobals->pEventHandler->update();
	}
}

void thread_rendering()
{
	gpGlobals->iThreadRendering = std::this_thread::get_id();
	gpGlobals->pRenderer->open_window("engine", 1280, 720, false);
	gpGlobals->pRenderer->init_gl();

	gpGlobals->pRenderer->load_loop();

	std::chrono::high_resolution_clock::time_point m_start, m_end;

	while (gpGlobals->bRunning)
	{
		gpGlobals->pRenderer->render();
	}

	gpGlobals->pRenderer->shutdown_gl();
	gpGlobals->pRenderer->close_window();
}

void thread_sound()
{
	gpGlobals->iThreadSound = std::this_thread::get_id();
}
