#include <iostream>

using namespace std;

// 오늘의 주제: 캐스팅 (타입변환)



class Player
{
public:
	virtual ~Player() {}
	
};

class Knight : public Player
{
	virtual ~Knight() {}

};

class Archer: public Player
{
	virtual ~Archer() {}

};

// 1) static_cast	: 가장 많이 사용
// 2) dynamic_cast	: 그다음으로 사용
// 3) const_cast	: 

void PrintName(char* str)
{
	cout << str << endl;
}
int main()
{
	// // static_cast : 타입 원칙에 비춰 볼때 상식적인 케스팅만 허용
	// 1) int <-> float
	// 2) Player* -> Knight* (다운 케스팅) <- 단, 안정성 보장 못함 (아처를 Knight로 넣는다던가!)

	int hp = 100;
	int maxHp = 200;
	float ratio = (float)hp/maxHp;

	cout << ratio << endl;

	Player* p = new Knight();
	Knight* k1 = (Knight*)p; // 끼워맞추려면 끼워맞출 수 있는 상황
	Knight* k2 = static_cast<Knight*>(p); // 이렇게 바꾸는게 훨씩 명확

	Knight* k = new Knight();
	Player* p2 = k; // 그냥 말이 되는 상황


	// // dyniamic_cast : 상속 관계에서만 안전 형변환
	// RTTI ( RunTime Type Information)
	// 다형성을 활용하는 방식 (virtual 함수를 사용해야한다!)
	// - virtual 함수를 하나라도 만들면, 객체의 메모리에 가상함수 테이블 (vftable) 주소가 기입
	// - 만약 잘못된 타입으로 캐스팅을 했으며, nullptr 반환 ******_*_*_*_*_*_*_*_*_
	// 이를 이용해서 맞는 탕비으로 캐스팅을 했는지 확인에 유용하다.
	Knight* k3 = dynamic_cast<Knight*>(p); // <- 원본이 아쳐였다? 계속 원본을 추적하고 있기 때문에, nullptr

	// // const_cast : const를 때거나 붙이거나!
	//PrintName("Dongbin\n"); // > 이건 const로 들어가기 때문에 에러가 납니다
	PrintName(const_cast<char*>("Dongbin")); // > 이건 const로 들어가기 때문에 에러가 안납니다
	

	// // reinterpre_cast
	// 가장 위험하고 강력한 형태의 캐스팅
	// re-interpret : 다시-간주하다/생각하다
	// - 포인터랑 전혀 관계없는 다른 타입 변환
	__int64 address = (__int64)(k3);
	__int64 address = reinterpret_cast<__int64>(k3);
	// 아주아주 가끔쓰임
	void* p = malloc(1000);
	Knight* knight = (Knight*)p;
	Knight* knight = reinterpret_cast<Knight*>(p);




	return 0;
}