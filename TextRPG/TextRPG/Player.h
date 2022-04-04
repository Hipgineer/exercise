#pragma once
#include "Creature.h" // ��Ӱ���� ��¿ �� ���� include

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
		// �����Լ��� ������ ��� ��ӵȰ� �ѹ��� delete ����
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

