#include "Game.h"
#include "Player.h"
#include "Field.h"
#include <iostream>
using namespace std;
// namespace? 이름 공간!
// 라이브러리를 여러개 쓰게 될 것이니까
// 겹치는 애들이 있을 수도 있자나?
// 그렇지 않으려고 !
//using namespace Dongbin;
//namespace Dongbin
//{
//	class Test {};
//}

Game::Game() : _player(nullptr), _field(nullptr)
{

}

Game::~Game()
{
	if (_player != nullptr) delete _player;
	if (_field != nullptr) delete _field;
}

void Game::Init()
{
	_field = new Field();
}

void Game::Update()
{
	if (_player == nullptr)
		CreatePlayer();

	if (_player->IsDead())
	{
		delete _player;
		_player = nullptr;
		CreatePlayer();
	}

	_field->Update(_player);
}

void Game::CreatePlayer()
{
	while (_player == nullptr)
	{
		cout << "- - - - - - - - - - - -" << endl;
		cout << "- 캐릭터를 생성하세요 -" << endl;
		cout << "1) 전사 2) 궁수 3) 법사" << endl;
		cout << "- - - - - - - - - - - -" << endl;
		cout << "> ";

		int input = 0;
		cin >> input;

		if (input == PT_Knight)
		{
			_player = new Knight();
		}
		else if (input == PT_Archer)
		{
			_player = new Archer();
		}
		else if (input == PT_Mage)
		{
			_player = new Mage();
		}
	}
}