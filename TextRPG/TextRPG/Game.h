#pragma once

// is-a ? has-a? 
// �÷��̾ �����ؾ��Ѵ�!

// ���� ���� 
// >> ����� ������ �ϵ��� ������ ���߿� Player�� ���ǵǴ� ��ٷ���! �����ض�! �����
// >> �� #include "Player.h"�� ���� �ʴ°�?
// >>>> �ϴ��� cpp ���Ͽ����� �����ϰ� �ҷ��͵� �ȴٰ� �����ϰ� �Ѿ��!
class Player; // �����ϸ� ���漱��
class Field; 


class Game
{
public :
	Game();
	~Game();

	void Init();
	void Update();

	void CreatePlayer();
	void CreateMonster();

private:

	// [4-8�ּҹٱ���] ---->>> [ ��¥ ����� ]
	Player* _player;
	Field* _field;

	//Player _player;	// �̷��� �Ǹ� ������ �÷��̾ �Ҵ�޾ƾ��� 
						// Knight�� �޾Ҵٸ� �ٱ��ϰ� �� �۾���?
						// �Դٰ� �̷��� �Ǹ� ��ȯ������ �ɼ��� �ִ�.

};

