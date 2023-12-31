#pragma once
#include <d3d9.h>
#include <tgmath.h>
#include <iostream>
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui_impl_dx9.h"
#include <Windows.h>
#include <string>
#include <iostream>

namespace gui
{
	constexpr int WIDTH = 800;
	constexpr int HEIGHT = 400;
	inline bool isRunning = true;
	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = { };
	inline POINTS position = { };
	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };
	void CreateHWindow(const char* windowName) noexcept;
	void DestroyHWindow() noexcept;
	bool CreateDevice() noexcept;
	void ResetDevice() noexcept;
	void DestroyDevice() noexcept;

	void CreateImGui() noexcept;
	void DestroyImGui() noexcept;

	void BeginRender() noexcept;
	void EndRender() noexcept;
}