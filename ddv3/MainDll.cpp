#include "Includer.h"


#define PROCESS_NAME "csgo.exe"

using namespace std;
using namespace hazedumper::netvars;
using namespace hazedumper::signatures;

Memory memory;

Memory::Module clientDll;
Memory::Module engineDll;

Client client;
Engine engine;

/*void test() {
	gui::CreateHWindow("Cheat Menu", "Cheat Menu Class");
	gui::CreateDevice();
	gui::CreateImGui();
	while (gui::exit) {
		  gui::BeginRender();
		  gui::Render();
		  gui::EndRender();
		  this_thread::sleep_for(chrono::milliseconds(10));
	}
	gui::DestroyImGui();
	gui::DestroyDevice();
	gui::DestroyHWindow();
}*/

unsigned int start_time[9] ;
unsigned int start_timeFlash = 0;
unsigned int start_timeLKM = 0;
unsigned int start_timeTriger = 0;
unsigned int end_time = 0;

bool timer[9];
bool timer_LKM = false;

void timersWorks() {
	end_time = clock();
	for (int i = 0; i < 9; i++) if (timer[i]&&end_time - start_time[i] > 500) timer[i] = false;
	if (timer_LKM&&end_time - start_timeLKM > 2000) timer_LKM = false;
}
void eraseCyclos() {
	for (int i = 0; i < 9; i++) timer[i] = false;
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//test();
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
	while (clientDll.base == 0 || engineDll.base == 0) {
		Sleep(1000);
		clientDll = memory.GetModule("client.dll");
		engineDll = memory.GetModule("engine.dll");
	}
	cout << "Модуль найден " << clientDll.base << ", размер " << clientDll.size << endl;

	bool wh_Working = true;
	bool flash_Working = true;
	bool radarHack = true;
	bool load = true;
	bool triggerBot = true;
	bool aimBot = false;
	bool pauseFag = false;
	bool pauseFlash = true;
	bool RCS = true;
	bool skin = true;
	bool bunnyhop = true;
	Vec3 bestAngle;
	Vec3 viewAngles;
	Vec2 oldPunch;

	eraseCyclos();
	ZeroMemory(start_time, sizeof(start_time));

	while (true){
		timersWorks();
		if (engine.clientState->State() != EState::InGame) { Sleep(1000); load = true; continue; }
		if (load) {Sleep(1000); load = false;}
		if (GetAsyncKeyState(VK_NUMPAD1) < 0 && !timer[0]) {
			timer[0] = true;
			start_time[0] = clock();
			wh_Working = !wh_Working;
			(wh_Working) ? cout << "Вх включены" << endl : cout << "Вх выключены" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD2) < 0 && !timer[1]) {
			timer[1] = true;
			flash_Working = !flash_Working;
			start_time[1] = clock();
			(flash_Working)?cout << "Анти флеш включен" << endl : cout << "Анти флеш выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD3) < 0 && !timer[2]) {
			timer[2] = true;
			radarHack = !radarHack;
			start_time[2] = clock();
			(radarHack) ? cout << "Радар хак включен" << endl : cout << "Радар хак выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD4) < 0 && !timer[3]) {
			triggerBot = !triggerBot;
			start_time[3] = clock();
			timer[3] = true;
			(triggerBot) ? cout << "Тригер бот включен" << endl : cout << "Тригер бот выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD5) < 0 && !timer[4]) {
			aimBot = !aimBot;
			start_time[4] = clock();
			timer[4] = true;
			(aimBot) ? cout << "Аим бот включен" << endl : cout << "Аим бот выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD6) < 0 && !timer[5]) {
			bunnyhop = !bunnyhop;
			start_time[5] = clock();
			timer[5] = true;
			(bunnyhop) ? cout << "Бонихоп включен" << endl : cout << "Бонихоб выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD7) < 0 && !timer[6]) {
			RCS = !RCS;
			start_time[6] = clock();
			timer[6] = true;
			(RCS) ? cout << "Контроль отдачи включен" << endl : cout << "Контроль отдачи выключен" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD8) < 0 && !timer[7]) {
			pauseFag = !pauseFag;
			start_time[7] = clock();
			timer[7] = true;
			(pauseFag) ? cout << "Пауза" << endl : cout << "Пуск" << endl;
		}
		if (GetAsyncKeyState(VK_NUMPAD9) < 0) {
			cout << "Выход" << endl;
			break;
		}
		if (GetAsyncKeyState(VK_NUMPAD0) < 0 && !timer[8]) {
			skin = !skin;
			start_time[8] = clock();
			timer[8] = true;
			(skin) ? cout << "Скин чеэнджер включен" << endl : cout << "Скин чеээнжер выключен" << endl;
		}
		  auto glowObjectManagerSize = client.glowObjectManager->Size();
		  if (glowObjectManagerSize == NULL|| pauseFag) continue;
		  for (auto glowObject : client.glowObjectManager->Attay(glowObjectManagerSize)) {
			  Entity entity(glowObject.definition.baseEntity);
			  if(entity.base == NULL) continue;
			  if (entity.ClassId() == EClassId::CC4) { glowObject.definition.SetColor(148, 0, 211, 255); memory.Write<ColorRGB>(entity.base + m_clrRender, { 148,0,211 }); }
			  else if (entity.ClassId() != EClassId::CCSPlayer) continue; 
			  else {
				   Player player(entity);
				   if (player.base == NULL||player.Team() == ETeam::Invalid||player.Team()==ETeam::InvalidLast) continue;
				   auto localPlayerIndex = engine.clientState->GetLocalPayerIndex();
				   if (localPlayerIndex == NULL) continue;
				   if (player.Team() == client.localPlayer->Team()) { glowObject.definition.SetColor(0, 255, 0, 255);
				   memory.Write<ColorRGB>(player.base+m_clrRender, {0,255,0});
				   }
				   else if (player.Health() <= 50 && player.Health() > 25) { glowObject.definition.SetColor(255, 255, 0, 255);  memory.Write<ColorRGB>(player.base+m_clrRender, {255,255,0});}
				   else if (player.Health() <= 25) { glowObject.definition.SetColor(255, 0, 0, 255);  memory.Write<ColorRGB>(player.base + m_clrRender, { 255,0,0 });}
				   else if (player.IsSpottedByMask(localPlayerIndex)) { glowObject.definition.SetColor(0, 0, 255, 255); memory.Write<ColorRGB>(player.base + m_clrRender, { 0,0,255 }); }
				   else { glowObject.definition.SetColor(255, 255, 255, 255); memory.Write<ColorRGB>(player.base + m_clrRender, { 255,255,255 }); }
				   if (client.localPlayer->GetFlash() > 0 && flash_Working) {
					  if (start_timeFlash == 0 && pauseFlash) { start_timeFlash = clock();  }
					  end_time = clock();
					   if (end_time - start_timeFlash > 150) {
						 memory.Write<int>((client.localPlayer->GetBase() + m_flFlashDuration), 0);
						 start_timeFlash = 0;// пиздец костыли
						 pauseFlash = false; 
					  }
				   }
				   else  pauseFlash = true;
				   if (radarHack && player.Team() != client.localPlayer->Team() && player.Health()>0) memory.Write<bool>((entity.GetBase() + m_bSpotted), true);
				   if (aimBot) {
					   auto localPosition = client.localPlayer->GetLocalPosition();
					   viewAngles = engine.clientState->GetLocalPayerViewAngles();
					   auto aimPunch = client.localPlayer->GetAimPunch();
					   float bestFov = 5.f;
					   if (client.localPlayer->Team() != player.Team() && !player.GetDormant() && player.Health() > 0&&player.IsSpottedByMask(localPlayerIndex)) {
						   Vec3 playerHeadPosition = player.GetBodyPartPosition();
						   auto angle = CalculateAngle(localPosition, playerHeadPosition, viewAngles + aimPunch);
						   auto fov = hypot(angle.x, angle.y);
						   if (fov < bestFov) {
							   bestFov = fov;
							   bestAngle = angle;
							   memory.Write<Vec3>(engine.clientState->GetBase() + dwClientState_ViewAngles, viewAngles + bestAngle / 3.f);
							   Sleep(10);
						   }
					   }
				   }

			  }
			  float brightness = 5.f;
			  auto _this = static_cast<uintptr_t>(engineDll.base + model_ambient_min - 0x2c);
			  memory.Write<int32_t>(engineDll.base + model_ambient_min, *reinterpret_cast<uintptr_t*>(&brightness) ^ _this);
			  glowObject.definition.renderWhenOccluded = true;
			  glowObject.definition.style = (int)EGlowStyle::FullBody;
			  if(wh_Working)memory.Write<GlowObjectDefinition>(client.glowObjectManager->GetGlowObjectBase(glowObject), glowObject.definition);
		  }
		 
		  if (GetAsyncKeyState(VK_LBUTTON)<0 &&!timer_LKM){
			  start_timeLKM = clock();
			  timer_LKM = true;
		  }
		  if (triggerBot && !timer_LKM && client.localPlayer->Health()>0) {
			  DWORD CroshairId = client.localPlayer->GetCrosshairId();
			  short ActiveWeaponID = client.localPlayer->GetActiveWeaponID();
			  if (ActiveWeaponID == NULL) continue;
			  if (end_time - start_time[7] > 100 && (ActiveWeaponID < EWeaponsId::KNIFE_CT || ActiveWeaponID > EWeaponsId::INCGRENADE) && (ActiveWeaponID != EWeaponsId::ZEUSE && ActiveWeaponID != EWeaponsId::KNIFE_T && ActiveWeaponID != EWeaponsId::REVOLVER)) {
				  Player player1(memory.Read<DWORD>(clientDll.base + dwEntityList + (CroshairId - 1) * 0x10));
				  if (player1.base == NULL)continue;
				  if (player1.Team() != client.localPlayer->Team() && player1.Health()>0) {
					  if (!start_timeTriger) start_timeTriger = clock();
					  end_time = clock();
					  if (end_time - start_timeTriger > 25) {
							  mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
							  mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
							  start_time[7] = clock();
							  start_timeTriger = 0;
					  }
				  }
			  }
		  }
		  if (bunnyhop) {
			 int flag = client.localPlayer->GetFlag();
			 if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0)) memory.Write<int>(clientDll.base + dwForceJump, 6);
		  }
		  if (RCS&&(GetAsyncKeyState(VK_LSHIFT)|| GetAsyncKeyState(VK_LCONTROL))) {
			  int shotsFired = client.localPlayer->GetShotsFired();
			  short ActiveWeaponID = client.localPlayer->GetActiveWeaponID();
			  if (shotsFired&&(ActiveWeaponID < EWeaponsId::KNIFE_CT || ActiveWeaponID > EWeaponsId::INCGRENADE)&& (ActiveWeaponID != EWeaponsId::ZEUSE && ActiveWeaponID != EWeaponsId::KNIFE_T && ActiveWeaponID != EWeaponsId::REVOLVER && ActiveWeaponID != EWeaponsId::USPS && ActiveWeaponID != EWeaponsId::NOVA && ActiveWeaponID != EWeaponsId::AWP && ActiveWeaponID != EWeaponsId::SSG08 && ActiveWeaponID != EWeaponsId::XM1014 && ActiveWeaponID != EWeaponsId::MAG7 && ActiveWeaponID != EWeaponsId::SAWED && ActiveWeaponID != EWeaponsId::P2000 && ActiveWeaponID != EWeaponsId::P250 && ActiveWeaponID != EWeaponsId::TEC9 && ActiveWeaponID != EWeaponsId::CZ75)&& ActiveWeaponID > EWeaponsId::CLOCK) {
				  auto viewAngles =(engine.clientState->GetLocalPayerViewAngles()).ToVec2();
				  Vec2 aimPunch = (client.localPlayer->GetAimPunch()).ToVec2();
				  Vec2 newAngles = viewAngles + oldPunch - aimPunch;
				  if (newAngles.x > 89.f)newAngles.x = 89.f;
				  if (newAngles.x < -89.f)newAngles.x = -89.f;
				  while (newAngles.y > 180.f)newAngles.y -= 360.f;
				  while (newAngles.y < -180.f) newAngles.y += 360.f;
				  memory.Write<Vec2>(engine.clientState->GetBase() + dwClientState_ViewAngles, newAngles);
				  oldPunch = aimPunch ;
			  }
			  else {
				   oldPunch.x = 0;
				   oldPunch.y = 0;
			  }
		  }
		  if (skin) {
			  auto weapons = memory.Read<array<unsigned long, 8>>(client.localPlayer->GetBase() + m_hMyWeapons);
			  for (auto handle : weapons) {
				  auto weapon = memory.Read<uintptr_t>((clientDll.base + dwEntityList + (handle & 0xFFF) * 0x10) - 0x10);
				  if (!weapon) continue;
				  if (auto paint = GetWeaponPaint(memory.Read<short>(weapon + m_iItemDefinitionIndex))) {
					 bool shouldUpdate = (memory.Read<int32_t>(weapon + m_nFallbackPaintKit) != paint);
					 memory.Write<int32_t>(weapon + m_iItemIDHigh, -1);
					 memory.Write<int32_t>(weapon + m_nFallbackPaintKit, paint);
					 memory.Write<float>(weapon + m_flFallbackWear, 0.1f);
					 /* memory.Write<int>(weapon + m_iEntityQuality, 3);
					  memory.Write<int32_t>(weapon + m_nFallbackSeed, 0);
					  memory.Write<int32_t>(weapon + m_nFallbackStatTrak, 1337);
					  memory.Write<int32_t>(weapon + m_iAccountID, memory.Read<int32_t>(weapon + m_OriginalOwnerXuidHigh));*/
					 if (shouldUpdate) { memory.Write<int32_t>(engine.clientState->GetBase() + 0x174, -1); cout << "ok" << endl; }
				  }
			  }
		  }
		 // Sleep(1);
	}
	return 0;
}
