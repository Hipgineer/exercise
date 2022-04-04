#pragma once
#include "Creature.h" // 상속관계면 어쩔 수 없이 include

enum PlayerType
{
	PT_Knight = 1,
	PT_Archer = 2,
	PT_Mage = 3,
};

class Player : public Creature
{
public:
	Player(int playerType) : Creature(CT_PLAYER), _playerType(playerType)
	{

	}

	virtual ~Player()
	{
		// 가상함수로 만들어야 모든 상속된게 한번에 delete 가능
	}

	virtual void PrintInfo();

protected:
	int _playerType;
};

class Knight : public Player
{
public:
	Knight() : Player(PT_Knight) 
	{
		_hp = 150;
		_attack = 20;
		_defence = 10;
	}
};

class Archer : public Player
{
public:
	Archer() : Player(PT_Archer)
	{
		_hp = 150;
		_attack = 20;
		_defence = 10;
	}
};

class Mage : public Player
{
public:
	Mage() : Player(PT_Mage) 
	{
		_hp = 150;
		_attack = 20;
		_defence = 10;
	}
};

