#pragma once

#include "GlowObjectManager.h"
#include "LocalPlayer.h"

class Client{
      public:
	  Client (){
		     this->localPlayer = new LocalPlayer();
		     this->glowObjectManager = new GlowObjectManager();
	  }
	  LocalPlayer* localPlayer = nullptr;
	  GlowObjectManager* glowObjectManager = nullptr;
};

extern Client client;