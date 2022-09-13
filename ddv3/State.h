#pragma once

enum struct EState : int {
	Invalid = -1,
	Lobby = 0,
	Loading = 1,
	Connecting = 2,
	Connected = 5,
	InGame = 6,
	InvalidLast,
};