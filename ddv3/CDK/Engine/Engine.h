#pragma once
#include "ClientState.h"
class Engine {
      public:
	  ClientState* clientState = nullptr;
	  Engine (){
		     this->clientState = new ClientState();
	  }
};

extern Engine engine;