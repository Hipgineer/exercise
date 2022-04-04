#include "Field.h"
#include <stdlib.h>
#include "Monster.h"
#include "Player.h"

Field::Field() : _monster(nullptr)
{

}

Field::~Field()
{
	if (_monster != nullptr)
		delete _monster;
}

void Field::Update(Player* player)
{
	if (_monster == nullptr)
		CreateMonster();
	

	StartBattle(player);
}

void Field::CreateMonster()
{
	int randValue = 1 + rand() % 3;
	
	switch (randValue)
	{
	case MT_SLIME:
		_monster = new Slime();
		break;
	case MT_ORC:
		_monster = new Orc();
		break;
	case MT_SKELETON:
		_monster = new Skeleton();
		break;
	}
}


void Field::StartBattle(Player* player)
{
	while (true)
	{
		player->PrintInfo();
		_monster->PrintInfo();

		// 치고 박고 하는거는 field 가 관여할 일이 아니다!
		// 객체지향적 관점에서는? 대미지 판정은 크리쳐에서!
		_monster->OnAttacked(player);

		if (_monster->IsDead())
		{
			_monster->PrintInfo();
			delete _monster;
			_monster = nullptr;
			break;
		}

		player->OnAttacked(_monster);

		if (player->IsDead())
		{
			player->PrintInfo();
			//player는 왜 널 포인터로 안미는가?
			//-생명주기와 관련
			//--_monster의 경우 field에서 생성이 되지만,
			//--player의 경우 Game 에서 관리되고 있음
			break;

		}


	}
}
