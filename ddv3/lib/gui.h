#pragma once
#include <d3d9.h>
#include <imgui.h>
#include <imgui_impl_dx9.h>
#include <imgui_impl_win32.h>

namespace gui {
	       int WIDTH = 525;
		   int HEIGHT = 410;
		   bool exit = true;
		   HWND window = nullptr;
		   WNDCLASSEXA windowClass = {};
		   POINTS position = {};
		   PDIRECT3D9 d3d = nullptr;
		   LPDIRECT3DDEVICE9 device = nullptr;
		   D3DPRESENT_PARAMETERS presentParameters = {};

		  void CreateHWindow (const char* windowName,const char* className)noexcept;
		  void DestroyHWindow () noexcept;
		  bool CreateDevice () noexcept;
		  void ResetDevice () noexcept;
		  void DestroyDevice () noexcept;
		  void CreateImGui () noexcept;
		  void DestroyImGui () noexcept;
		  void BeginRender () noexcept;
		  void EndRender () noexcept;
		  void Render () noexcept;

		  void DestroyHWindow() noexcept {
			  DestroyWindow(window);
			  UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
		  }

		  bool CreateDevice() noexcept {
			  d3d = Direct3DCreate9(D3D_SDK_VERSION);
			  if (!d3d)return false;
			  ZeroMemory(&presentParameters, sizeof(presentParameters));
			  presentParameters.Windowed = TRUE;
			  presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
			  presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
			  presentParameters.EnableAutoDepthStencil = TRUE;
			  presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
			  presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
			  if (d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window, D3DCREATE_HARDWARE_VERTEXPROCESSING, &presentParameters, &device) < 0) return false;
			  return true;
		  }

		  void ResetDevice() noexcept {
			  ImGui_ImplDX9_InvalidateDeviceObjects();
			  auto result = device->Reset(&presentParameters);
			  if (result == D3DERR_INVALIDCALL) IM_ASSERT(0);
			  ImGui_ImplDX9_CreateDeviceObjects();
		  }

		  void DestroyDevice() noexcept {
			  if (device) {
				  device->Release();
				  device = nullptr;
			  }
			  if (d3d) {
				  d3d->Release();
				  d3d = nullptr;
			  }
		  }

		  void CreateImGui() noexcept {
			  IMGUI_CHECKVERSION();
			  ImGui::CreateContext();
			  ImGuiIO& io = ::ImGui::GetIO();
			  (void)io;
			  // io.IniFilename = NULL;
			  auto config = ImFontConfig();
			  config.FontDataOwnedByAtlas = false;
			  ImGui::GetIO().Fonts->AddFontFromMemoryTTF(myfont, sizeof(myfont), 20, &config, io.Fonts->GetGlyphRangesCyrillic());
			  ImGui::StyleColorsDark();
			  ImGui_ImplWin32_Init(window);
			  ImGui_ImplDX9_Init(device);
		  }

		  void DestroyImGui() noexcept {
			  ImGui_ImplDX9_Shutdown();
			  ImGui_ImplWin32_Shutdown();
			  ImGui::DestroyContext();
		  }

		  void BeginRender() noexcept {
			  MSG message;
			  while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
				  TranslateMessage(&message);
				  DispatchMessage(&message);
			  }
			  ImGui_ImplDX9_NewFrame();
			  ImGui_ImplWin32_NewFrame();
			  ImGui::NewFrame();
		  }

		  void EndRender() noexcept {
			  ImGui::EndFrame();
			  device->SetRenderState(D3DRS_ZENABLE, FALSE);
			  device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			  device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
			  device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
			  if (device->BeginScene() >= 0) {
				  ImGui::Render();
				  ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
				  device->EndScene();
			  }
			  auto result = device->Present(0, 0, 0, 0);
			  if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) ResetDevice();
		  }
}

ColorRGBA floatToRGBA(float col[]) {
	float r = (int)(col[0] * 255);
	float g = (int)(col[1] * 255);
	float b = (int)(col[2] * 255);
	float a = (int)(col[3] * 255);
	return { r,g,b,a };
}

void Bild() {
	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();
	while (gui::exit) {
		gui::BeginRender();
		gui::Render();
		gui::EndRender();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();
}
