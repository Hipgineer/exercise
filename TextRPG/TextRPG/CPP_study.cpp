#include <iostream>
using namespace std;
#include "Game.h"
//오늘의 주제: TextRPG #4
//- 파일 분할과 객체 지향!

//로비/플레이어/몬스터 등 모두 객체지향!


int main()
{
	srand((unsigned int)time(nullptr));

	Game game;
	game.Init();

	while (true)
	{
		game.Update();
	}


	return 0;
}