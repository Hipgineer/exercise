#include <iostream>
using namespace std;
#include "Game.h"
//������ ����: TextRPG #4
//- ���� ���Ұ� ��ü ����!

//�κ�/�÷��̾�/���� �� ��� ��ü����!


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