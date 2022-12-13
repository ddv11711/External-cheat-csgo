#include "Includer.h"

#define PROCESS_NAME "csgo.exe"


using namespace std;
using namespace chrono;
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;
using namespace nlohmann;

Memory memory;

Memory::Module clientDll;
Memory::Module engineDll;

Client client;
Engine engine;

//rgba
float timat[] = {0.f,1.f,0.f,1.f}; 
float wrag1[] = {1.f,1.f,0.f,1.f}; 
float wrag2[] = {1.f,0.f,0.f,1.f};
float wrag3[] = {0.f,0.f,1.f,1.f};
float wrag4[] = {1.f,1.f,1.f,1.f};
float colorC4[] = { 0.5803921818733215f,0.f,0.8274509906768799f,1.f};
float brightness = 5.f;

unsigned int start_btn = 0;
unsigned int start_triger=0;
unsigned int start_timeFlash = 0;
unsigned int start_timeLKM = 0;
unsigned int start_timeTriger = 0;
unsigned int end_time = 0;

unsigned int test_start_time = 0;
unsigned int test_end_time = 0;

bool timer_btn = true;
bool timer_LKM = false;
bool wh_Working = true;
bool flash_Working = true;
bool radarHack = true;
bool load = true;
bool triggerBot = true;
bool aimBot = false;
bool pauseFag = false;
bool pauseFlash = true;
bool RCS = true;
bool skin = false;
bool bunnyhop = true;
bool colorWH = false;
bool teamsot = false;
bool vidin3 = false;
bool fovloc = false;
bool fovbtn = true;
bool aimfriendlyfire = false;

int tabb = 0;
int bon = 8;
int trigerDelay = 25;
int bloc_brightness = 0;
int fov = 90;

void floatload(float* f1, json& f2);
void resetconfig();
bool saveconfig();
bool loadconfig();

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM windeParameter, LPARAM longParameter);

long __stdcall WindowProcess(HWND window, UINT message, WPARAM wideParameter, LPARAM longParameter) {
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter)) return true;
	switch (message) {
	case WM_SIZE: if (gui::device != NULL && wideParameter != SIZE_MINIMIZED){
		    gui::WIDTH = gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
		    gui::HEIGHT = gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND: if ((wideParameter & 0xfff0) == SC_KEYMENU) return 0;
	  break;
	case WM_DESTROY: PostQuitMessage(0);
	  return 0;
	case WM_LBUTTONDOWN: gui::position = MAKEPOINTS(longParameter);
	  return 0;
	case WM_MOUSEMOVE: if (wideParameter == MK_LBUTTON) {
						  auto points = MAKEPOINTS(longParameter);
						  auto rect = ::RECT{};
						  GetWindowRect(window, &rect);
						  rect.left += points.x - gui::position.x;
						  rect.top += points.y - gui::position.y;
						  if (gui::position.x >= 0 && gui::position.x < gui::WIDTH && gui::position.y >= 0 && gui::position.y <= 19) SetWindowPos(window, HWND_TOPMOST, rect.left, rect.top, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
					   }
	
	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}

void gui::CreateHWindow(const char* windowName, const char* className)noexcept {
	windowClass.cbSize = sizeof(WNDCLASSEXA);
	windowClass.style = CS_CLASSDC;
	windowClass.lpfnWndProc = WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = className;
	windowClass.hIconSm = 0;
	RegisterClassExA(&windowClass);
	window = CreateWindowA(className, windowName, WS_THICKFRAME | WS_POPUP | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_OVERLAPPED, 100, 100, WIDTH + 15, HEIGHT, 0, 0, windowClass.hInstance, 0);
	// SetWindowRgn(window, CreateRoundRectRgn(0, 0, WIDTH, HEIGHT, 16, 16), true);
	// SetWindowLongPtr(window, GWL_STYLE, WS_POPUP | WS_VISIBLE | WS_THICKFRAME| WM_GETMINMAXINFO);
	SetClassLong(window, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(15, 15, 15)));
	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::Render() noexcept {
	ImGui::SetNextWindowPos({ 0.f,0.f });
	ImGui::SetNextWindowSize(ImVec2(WIDTH, HEIGHT));
	ImGui::Begin("ddv3", &exit, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);
	if (tabb == 0) {
		 //ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(255, 255, 255, 255));
		// ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));
	}
	if (ImGui::Button("Wh", ImVec2(100.f, 25.f))) tabb = 0;
	//if(tabb==0)ImGui::PopStyleColor();
	ImGui::SameLine(0.f, 2.f);
	if (ImGui::Button("Trigger Bot", ImVec2(100.f, 25.f))) tabb = 1;
	ImGui::SameLine(0.f, 2.f);
	if (ImGui::Button("Aim Bot", ImVec2(100.f, 25.f))) tabb = 2;
	ImGui::SameLine(0.f, 2.f);
	if (ImGui::Button("Skin Changer", ImVec2(100.f, 25.f))) tabb = 3;
	ImGui::SameLine(0.f, 2.f);
	if (ImGui::Button(u8"Разное", ImVec2(100.f, 25.f))) tabb = 4;

	if (tabb == 0) {
		ImGui::Text(u8"Настройки WH");
		ImGui::Checkbox(u8"Вкл/Вык", &wh_Working);
		ImGui::ColorEdit3(u8"Цвет Напарника", timat);;
		ImGui::ColorEdit3(u8"Цвет Врага 1", wrag1);
		ImGui::ColorEdit3(u8"Цвет Врага 2", wrag2);
		ImGui::ColorEdit3(u8"Цвет Врага 3", wrag3);
		ImGui::ColorEdit3(u8"Цвет Врага 4", wrag4);
		ImGui::ColorEdit3(u8"Цвет C4", colorC4);
		if (ImGui::Checkbox(u8"Заливка тела Вкл/Вык", &colorWH) && !colorWH)  bloc_brightness = 1;
		if (ImGui::SliderFloat(u8"Яркости", &brightness, 0.f, 40.f) && brightness == 0) colorWH = false;
	}
	else if (tabb == 1) {
		ImGui::Text(u8"Настройки Trigger Bot");
		ImGui::Checkbox(u8"Вкл/Вык", &triggerBot);
		if (ImGui::InputInt(u8"Задержка (мс)", &trigerDelay)) {
			if (trigerDelay > 0 && !triggerBot)triggerBot = true;
			if (trigerDelay < 0) {
				trigerDelay = 0;
				if (triggerBot) triggerBot = false;
			}
			else if (trigerDelay == 0)triggerBot = false;
		}
		ImGui::Checkbox(u8"Огонь по своим Вкл/Вык", &teamsot);
	}
	else if (tabb == 2) {
		int comboBon=0;
		if (bon == 8)comboBon = 0;
		else if (bon == 6)comboBon = 1;
		else if (bon == 4)comboBon = 2;
		ImGui::Text(u8"Настройки Aim Bot");
		ImGui::Checkbox(u8"Вкл/Вык", &aimBot);
		ImGui::Checkbox(u8"Огонь по своим Вкл/Вык", &aimfriendlyfire);
		if (ImGui::Combo(u8"Куда наводиться", &comboBon, u8"Голова\0Грудь\0Живот\0")) {
			if (comboBon == 0)bon = 8;
			else if (comboBon == 1)bon = 6;
			else if (comboBon == 2) bon = 4;
		}
	}
	else if (tabb == 3) {
		ImGui::Text(u8"Настройки Skin Changer");
		ImGui::Checkbox(u8"Вкл/Вык", &skin);
	}
	else if (tabb == 4) {
		ImGui::Text(u8"Настройки Разное");
		ImGui::Checkbox(u8"Bunnyhop Вкл/Вык", &bunnyhop);
		ImGui::Checkbox(u8"Радар Хак Вкл/Вык", &radarHack);
		ImGui::Checkbox(u8"Контроль Отдачи Вкл/Вык", &RCS);
		ImGui::Checkbox(u8"Антифлеш Вкл/Вык", &flash_Working);
		ImGui::Checkbox(u8"Вид от 3 лица Вкл/Вык", &vidin3);
		if (ImGui::SliderInt(u8"Значение FOV", &fov, -175, 175)) { fovloc = true; fovbtn = false; }
		if (ImGui::Checkbox(u8"значение FOV по умолчанию", &fovbtn) && fovbtn) { fov = 90; fovloc = true; }
	}
	ImGui::SetCursorPosY(360);
	//ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 255, 255));
	if (ImGui::Button(u8"Загрузить", ImVec2(100.f, 25.f)))loadconfig();
	//ImGui::PopStyleColor();
	ImGui::SameLine(0.f, 100);
	if (ImGui::Button(u8"Сбросить", ImVec2(100.f, 25.f)))resetconfig();
	ImGui::SameLine(0.f,100);
	if (ImGui::Button(u8"Сохранить", ImVec2(100.f, 25.f)))saveconfig();
	ImGui::End();
}

void timersWorks() {
	end_time = clock();
	if (timer_LKM&&end_time - start_timeLKM > 2000) timer_LKM = false;
	if (!timer_btn&&end_time - timer_btn > 1000) timer_btn = true;
}

int main() {
	SetConsoleTitle("ddv");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	thread tr(Bild);
	tr.detach();
		if (!loadconfig()) { 
			cout << "Ошибка при загруки настроек! Настройки сброшены по умолчанию" << endl; 
			saveconfig();
		}
	
	cout << "Никита лох" << endl;
	cout << "Поиск процесса " << PROCESS_NAME << "......." << endl;

	auto ProcessId = memory.FindProcess(PROCESS_NAME);

	while (!ProcessId) {
		  Sleep(1000);
		  ProcessId = memory.FindProcess(PROCESS_NAME);
	}

	cout << "Процесс " << PROCESS_NAME << " найден" << endl;
	cout << "Запуск" << endl;

	memory.Attach(ProcessId, PROCESS_ALL_ACCESS);
	clientDll = memory.GetModule("client.dll");
	engineDll = memory.GetModule("engine.dll");

	while (clientDll.base <= NULL || engineDll.base <= NULL) {
		Sleep(1000);
		clientDll = memory.GetModule("client.dll");
		engineDll = memory.GetModule("engine.dll");
	}

	cout << "Модуль найден " << clientDll.base << ", размер " << clientDll.size << endl;
	
	//FreeConsole();
	
	Vec3 bestAngle;
	Vec3 viewAngles;
	Vec2 oldPunch;
	bool vidin3int=0;
	bool  test = false;
	float brightness_last = 0;

	while (true) {
		timersWorks();

		if (GetAsyncKeyState(VK_NUMPAD0) & 1) pauseFag = !pauseFag;
		if (GetAsyncKeyState(VK_NUMPAD9) & 1) break;
		if (GetAsyncKeyState(VK_NUMPAD5) & 1) test = !test;
		if (GetAsyncKeyState(VK_NUMPAD1) & 1 && timer_btn) {
			gui::exit = !gui::exit;
			if (gui::exit) thread(Bild).detach();
			timer_btn = false;
		}

		engine.clientState->base = engine.clientState->GetBase();
		if (engine.clientState->base <= NULL) continue;

 		if (engine.clientState->State() != EState::InGame) { Sleep(1000); load = true; continue; }
		if (load) { Sleep(2000); load = false; }

		auto glowObjectManagerSize = client.glowObjectManager->Size();
		if (glowObjectManagerSize <= NULL || pauseFag) continue;

		bool lifelocalplayer = client.localPlayer->GetLife();

		ETeam localplayertem = client.localPlayer->Team();
		if (localplayertem <= ETeam::Spectator)continue;

		client.localPlayer->base = client.localPlayer->GetBase();
		if (client.localPlayer->base <= NULL) continue;

		for (auto glowObject : client.glowObjectManager->Attay(glowObjectManagerSize)) {

			Entity entity(glowObject.definition.baseEntity);
			if (entity.base <= NULL) continue;

			EClassId classid = entity.ClassId();
			if(classid<=EClassId::Invalid)continue;
			if (classid == EClassId::CC4) {
				memory.Write<ColorRGBA>(client.glowObjectManager->GetGlowObjectBase(glowObject) +0x8, floatToRGBA(colorC4));
				memory.Write<bool>(client.glowObjectManager->GetGlowObjectBase(glowObject) + 0x28, true);
				if (colorWH) memory.Write<ColorRGB>(entity.base + m_clrRender, floatToRGBA(colorC4).ToRGB());
				else if (bloc_brightness != 0) memory.Write<ColorRGB>(entity.base + m_clrRender, { 204,204,204 });
				if(radarHack && localplayertem==ETeam::CounterTerrorist) memory.Write<bool>((entity.base + m_bSpotted), true);
			}
			else if (classid == EClassId::CPlantedC4) {
				memory.Write<ColorRGBA>(client.glowObjectManager->GetGlowObjectBase(glowObject) + 0x8, floatToRGBA(colorC4));
				memory.Write<bool>(client.glowObjectManager->GetGlowObjectBase(glowObject) + 0x28, true);
				if (colorWH)memory.Write<ColorRGB>(entity.base + m_clrRender, floatToRGBA(colorC4).ToRGB());
				else if (bloc_brightness != 0) memory.Write<ColorRGB>(entity.base + m_clrRender, { 204,204,204 });
				if (radarHack && localplayertem == ETeam::CounterTerrorist) memory.Write<bool>((entity.base+ m_bSpotted), true);
			}
			else if (classid != EClassId::CCSPlayer) continue;
			else {
				Player player(entity);
				if (player.base <= NULL) continue;

				auto localPlayerIndex = engine.clientState->GetLocalPayerIndex();
				if (localPlayerIndex <= NULL)continue;

				if (player.GetGlowIndex() < 0) continue;

				int heil = player.Health();
				if (heil<=NULL)continue;

				ETeam playrtimmm = player.Team();
				if (playrtimmm <= ETeam::Spectator)continue;

				if (playrtimmm == localplayertem) {
					glowObject.definition.SetColorFloat(timat);
					if (colorWH)memory.Write<ColorRGB>(player.base + m_clrRender, floatToRGBA(timat).ToRGB());
					else if (bloc_brightness != 0) memory.Write<ColorRGB>(player.base + m_clrRender, { 204,204,204 });
					glowObject.definition.renderWhenOccluded = true;
					glowObject.definition.style = (int)EGlowStyle::FullBody;
					if (wh_Working)memory.Write<GlowObjectDefinition>(client.glowObjectManager->GetGlowObjectBase(glowObject), glowObject.definition);

				}
				else {
				     if (heil > 25 && heil <= 50) {
						glowObject.definition.SetColorFloat(wrag1);
						if (colorWH)memory.Write<ColorRGB>(player.base + m_clrRender, floatToRGBA(wrag1).ToRGB());
						else if (bloc_brightness!=0)  memory.Write<ColorRGB>(player.base + m_clrRender, { 204,204,204 });
					 }
					 else if (heil <= 25) {
						  glowObject.definition.SetColorFloat(wrag2);
						  if (colorWH)memory.Write<ColorRGB>(player.base + m_clrRender, floatToRGBA(wrag2).ToRGB());
						  else if(bloc_brightness!=0) memory.Write<ColorRGB>(player.base + m_clrRender, { 204,204,204 });
					 }
					 else if (player.IsSpottedByMask(localPlayerIndex)) {
						  glowObject.definition.SetColorFloat(wrag3);
						  if (colorWH)memory.Write<ColorRGB>(player.base + m_clrRender, floatToRGBA(wrag3).ToRGB());
						  else if(bloc_brightness!=0) memory.Write<ColorRGB>(player.base + m_clrRender, { 204,204,204 });
					 }
					 else {
						  glowObject.definition.SetColorFloat(wrag4);
						  if (colorWH)memory.Write<ColorRGB>(player.base + m_clrRender, floatToRGBA(wrag4).ToRGB());
						 else  if(bloc_brightness!=0) memory.Write<ColorRGB>(player.base + m_clrRender, { 204,204,204 });
					 }
					 glowObject.definition.renderWhenOccluded = true;
					 glowObject.definition.style = (int)EGlowStyle::FullBody;
					 if (wh_Working)memory.Write<GlowObjectDefinition>(client.glowObjectManager->GetGlowObjectBase(glowObject), glowObject.definition);
					 // радар хак
					 if (radarHack && heil > 0) memory.Write<bool>((player.base + m_bSpotted), true);
					 ////////////
				}

				if (colorWH && brightness_last != brightness) {
					auto _this = static_cast<uintptr_t>(engineDll.base + model_ambient_min - 0x2c);
					memory.Write<int32_t>(engineDll.base + model_ambient_min, *reinterpret_cast<uintptr_t*>(&brightness) ^ _this);
					brightness_last = brightness;
				}
				else if (!colorWH && brightness_last == brightness) {
					 auto _this = static_cast<uintptr_t>(engineDll.base + model_ambient_min - 0x2c);
					 memory.Write<int32_t>(engineDll.base + model_ambient_min, 0 ^ _this);
					 brightness_last = 0;
				}
				// аим бот
				if (aimBot && GetAsyncKeyState(VK_LBUTTON) < 0) {
				   auto localPosition = client.localPlayer->GetLocalPosition();
				   viewAngles = engine.clientState->GetLocalPayerViewAngles();
				   auto aimPunch = client.localPlayer->GetAimPunch();
				   float bestFov = 5.f;
				   if ((aimfriendlyfire || localplayertem != playrtimmm) && player.GetLife() && player.IsSpottedByMask(localPlayerIndex)) {
					  Vec3 playerHeadPosition = player.GetBodyPartPosition(bon);
					  auto angle = CalculateAngle(localPosition, playerHeadPosition, viewAngles + aimPunch);
					  auto fov = hypot(angle.x, angle.y);
					  if (fov < bestFov) {
						 bestFov = fov;
						 bestAngle = angle;
						 memory.Write<Vec3>(engine.clientState->base + dwClientState_ViewAngles, viewAngles + bestAngle / 3.f);
						 timer_LKM = false;//test
						 milliseconds(10);
					  }
				   }
				}
				/////////////////

			}

		}

		if (!colorWH && bloc_brightness == 1) bloc_brightness++;
		else if (!colorWH && bloc_brightness == 2) bloc_brightness = 0;

		if (!lifelocalplayer) continue;

		// антифлеш
		bool flashstate = client.localPlayer->GetFlash();
		if (flashstate) test_start_time = clock();
		else if (!flashstate && test_start_time)test_end_time = clock();
		if (flashstate && flash_Working) {
		   if (start_timeFlash == 0 && pauseFlash) { start_timeFlash = clock(); }
		   end_time = clock();
		   if (end_time - start_timeFlash > 150) {
			  memory.Write<int>((client.localPlayer->base + m_flFlashDuration), 0);
			  start_timeFlash = 0;// пиздец костыли
			  pauseFlash = false;
		   }
		}
		else  pauseFlash = true;
		////////////

		// Тригер бот
		if (GetAsyncKeyState(VK_LBUTTON) < 0 && !timer_LKM) {
			start_timeLKM = clock();
			timer_LKM = true;
		}
		
		if (triggerBot && !timer_LKM) {
			DWORD CroshairId = client.localPlayer->GetCrosshairId();
			short ActiveWeaponID = client.localPlayer->GetActiveWeaponID();
			if (end_time - start_triger > 100 && (ActiveWeaponID != EWeaponsId::REVOLVER && GetTipeWeapon(ActiveWeaponID)>=1 && GetTipeWeapon(ActiveWeaponID) <=6)) {
				Player player1(memory.Read<DWORD>(clientDll.base + dwEntityList + (CroshairId - 1) * 0x10));
				if (player1.base!=NULL && (teamsot || player1.Team() != localplayertem) && player1.Health()>0) {
					if (!start_timeTriger) start_timeTriger = clock();
					end_time = clock();
					if ((end_time - start_timeTriger) >= trigerDelay) {
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						chrono::milliseconds(10);
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						start_triger = clock();
						start_timeTriger = 0;
					}
				}
			}
		}
		////////////////////////
	
	    // bunnyhop
		if (bunnyhop && GetAsyncKeyState(VK_SPACE) && client.localPlayer->GetFlag()) memory.Write<int>(clientDll.base + dwForceJump, 6);
		///////////////////////////////

		// вид от 3 лица
		if (vidin3 && !vidin3int) {
			memory.Write<int>(client.localPlayer->base + m_iObserverMode, 1);
			vidin3int = true;
		}
		else if(!vidin3 && vidin3int) {
			memory.Write<int>(client.localPlayer->base + m_iObserverMode, 0); 
			vidin3int = false;
	    }
		/////////////////////////////
		
		// Fov Changer
		if (fovloc) {
			memory.Write<int>(client.localPlayer->base + m_iDefaultFOV, fov);
			fovloc = false;
		}
		////////////////////
		
		 // контроль отдачи
		 if (RCS&&(GetAsyncKeyState(VK_LSHIFT)|| GetAsyncKeyState(VK_LCONTROL))) {
			  int shotsFired = client.localPlayer->GetShotsFired();
			  short ActiveWeaponID = client.localPlayer->GetActiveWeaponID();
			  if (shotsFired ) {
				  auto viewAngles =(engine.clientState->GetLocalPayerViewAngles()).ToVec2();
				  Vec2 aimPunch = (client.localPlayer->GetAimPunch()).ToVec2();
				  Vec2 newAngles = viewAngles + oldPunch - aimPunch;
				  if (newAngles.x > 89.f)newAngles.x = 89.f;
				  if (newAngles.x < -89.f)newAngles.x = -89.f;
				  while (newAngles.y > 180.f)newAngles.y -= 360.f;
				  while (newAngles.y < -180.f) newAngles.y += 360.f;
				  memory.Write<Vec2>(engine.clientState->base + dwClientState_ViewAngles, newAngles);
				  oldPunch = aimPunch ;
			  }
			  else {
				   oldPunch.x = 0;
				   oldPunch.y = 0;
			  }
		 }
		 ///////////////////////////////

		 // скинчеенджер
		  if (skin) {
			  auto weapons = memory.Read<array<unsigned long, 8>>(client.localPlayer->base + m_hMyWeapons);
			  for (auto handle : weapons) {
				  auto weapon = memory.Read<uintptr_t>((clientDll.base + dwEntityList + (handle & 0xFFF) * 0x10) - 0x10);
				  if (weapon!=NULL) {
					  int paint = GetWeaponPaint(memory.Read<short>(weapon + m_iItemDefinitionIndex));
					  if(paint!=NULL){
						  bool shouldUpdate = (memory.Read<int32_t>(weapon + m_nFallbackPaintKit) != paint);
						  if (shouldUpdate) { 
							  memory.Write<int32_t>(weapon + m_iItemIDHigh, -1);
							  memory.Write<int32_t>(weapon + m_nFallbackPaintKit, paint);
							  memory.Write<float>(weapon + m_flFallbackWear, 0.0f);
							 /*memory.Write<int>(weapon + m_iEntityQuality, 3);
							  memory.Write<int32_t>(weapon + m_nFallbackSeed, 0);
							  memory.Write<int32_t>(weapon + m_nFallbackStatTrak, 1337);
							  memory.Write<int>(weapon + m_iAccountID,memory.Read<int>(weapon + m_OriginalOwnerXuidHigh));*/
							  memory.Write<int32_t>(engine.clientState->base + 0x174, -1); 
						  }
					  }
				  }
			  }
		  }
		  /////////////////////////
		 
		  milliseconds(1);
	}
	return 0;
}
bool saveconfig() {
	json js;

	js["timat"] = timat;
	js["wrag1"] = wrag1;
	js["wrag2"] = wrag2;
	js["wrag3"] = wrag3;
	js["wrag4"] = wrag4;
	js["colorC4"] = colorC4;
	js["colorWH"] = colorWH;
	js["brightness"] = brightness;
	js["triggerBot"] = triggerBot;
	js["trigerDelay"] = trigerDelay;
	js["teamsot"] = teamsot;
	js["aimBot"] = aimBot;
	js["aimfriendlyfire"] = aimfriendlyfire;
	js["bon"] = bon;
	js["skin"] = skin;
	js["bunnyhop"] = bunnyhop;
	js["radarHack"] = radarHack;
	js["RCS"] = RCS;
	js["flash_Working"] = flash_Working;
	js["vidin3"] = vidin3;
	js["fov"] = fov;
	js["fovbtn"] = fovbtn;
	js["wh_Working"] = wh_Working;

	ofstream fout("ddv.json");
	if (!fout) { 
		fout.close();
		return false; 
	}

	fout << js << endl;
	fout.close();

	return true;
}

bool loadconfig() {
	json js;
	ifstream fin("ddv.json");
	if (!fin) {
		fin.close();
		return false;
	}

	fin >> js;
	fin.close();

	floatload(timat,js["timat"]);
	floatload(wrag1,js["wrag1"]);
	floatload(wrag2,js["wrag2"]);
	floatload(wrag3,js["wrag3"]);
	floatload(wrag4,js["wrag4"]);
	floatload(colorC4,js["colorC4"]);
	colorWH=js["colorWH"].get<bool>();
	brightness=js["brightness"].get<float>();
	triggerBot=js["triggerBot"].get<bool>();
	trigerDelay=js["trigerDelay"].get<int>();
	teamsot=js["teamsot"].get<bool>();
	aimBot=js["aimBot"].get<bool>();
	aimfriendlyfire = js["aimfriendlyfire"].get<bool>();
	bon=js["bon"].get<int>();
	skin=js["skin"].get<bool>();
	bunnyhop = js["bunnyhop"].get<bool>();
	radarHack=js["radarHack"].get<bool>() ;
	RCS=js["RCS"].get<bool>();
	flash_Working=js["flash_Working"].get<bool>();
	vidin3=js["vidin3"].get<bool>();
	fov=js["fov"].get<int>();
	fovbtn=js["fovbtn"].get<bool>();
	wh_Working=js["wh_Working"].get<bool>();

	return true;
}

void resetconfig() {
	timat[0] = 0.f; timat[1] = 1.f; timat[2] = 0.f; timat[3] = 1.f;
	wrag1[0] = 1.f; wrag1[1] = 1.f; wrag1[2] = 0.f; wrag1[3] = 1.f;
	wrag2[0] = 1.f; wrag2[1] = 0.f; wrag2[2] = 0.f; wrag2[3] = 1.f;
	wrag3[0] = 0.f; wrag3[1] = 0.f; wrag3[2] = 1.f; wrag3[3] = 1.f;
	wrag4[0] = 1.f; wrag4[1] = 1.f; wrag4[2] = 1.f; wrag4[3] = 1.f;
	colorC4[0] = 0.5803922f; colorC4[1] = 0.f; colorC4[2] = 0.827451f; colorC4[3] = 1.f;
	brightness = 5.f;

	wh_Working = true;
	flash_Working = true;
	radarHack = true;
	triggerBot = true;
	aimBot = false;
	RCS = true;
	skin = false;
	bunnyhop = true;
	colorWH = false;
	teamsot = false;
	vidin3 = false;
	fovloc = false;
	fovbtn = true;
	aimfriendlyfire = false;

	bon = 8;
	trigerDelay = 25;
	fov = 90;
}

void floatload(float *f1,json &f2) {for (int i = 0; i < 4; i++) f1[i] = f2[i].get<float>();}