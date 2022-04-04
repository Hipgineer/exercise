#pragma once

// is-a ? has-a? 
// 플레이어를 포함해야한다!

// 전방 선언 
// >> 선언부 구현부 하듯이 어차피 나중에 Player가 정의되니 기다려라! 가만해라! 요느낌
// >> 왜 #include "Player.h"를 쓰지 않는가?
// >>>> 일단은 cpp 파일에서만 과감하게 불러와도 된다고 이해하고 넘어가라!
class Player; // 웬만하면 전방선언
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

	// [4-8주소바구니] ---->>> [ 진짜 저장소 ]
	Player* _player;
	Field* _field;

	//Player _player;	// 이렇게 되면 무조건 플래이어를 할당받아야함 
						// Knight를 받았다면 바구니가 좀 작아잉?
						// 게다가 이렇게 되면 순환구조가 될수도 있다.

};

