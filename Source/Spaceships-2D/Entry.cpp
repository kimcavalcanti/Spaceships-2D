#include <Windows.h>
#include "GameLogic.h"

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glu32.lib")

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	GameLogic::Initialise(hInstance);

	GameLogic::GetInstance().Run();
	GameLogic::GetInstance().Destroy();

	ExitProcess(0);

	return 0;
}