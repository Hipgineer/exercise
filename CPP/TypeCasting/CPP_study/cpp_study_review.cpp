#include <iostream>

using namespace std;


class Item
{
public:

	Item()
	{
		cout << "item()" << endl;
	}

	Item() 
	{
		cout << "~item()" << endl;
	}

public:

	int _itemType = 0;
	int _itenDbId = 0;

	char _dummy[4096] = {}; // 비대해진 뭔가 배열
};

void TestItem(Item item)
{
	// 여기서 입력되는 값도 생성자가호출됩니다. => 복사생성자 ==> 포인털갈 아니라 그냥 넘겨주면 개큰게 복사되고 있는거야...
}
void TestItemPtr(Item* item)
{
	// 얘는 생성자 X
}

int main() 
{
	// 복습 : 타입변환을 잘못하면 역적이 될거여
	{
		// Stack [ type(4)  dbid(4) dummy(4096] ] 
		Item item;

		// Stack [주소(4-8)] : 힙주소 : [ type(4)  dbid(4) dummy(4096] ] 
		Item* item2 = new Item(); // 동적할당 ==> 만약에 생성만 하고 만다면 소멸자를 생성하지 않음

		TestItem(item);
		TestItem(*item2);

		TestItemPtr(&item);
		TestItemPtr(item2);



		delete item2; // 없애줘야해요 안하면 Memory Laek => 가용메모리가 줄어 Crash가 발생

	}

	//배열
	{
		// 진짜 아이템 100개 생성 ==> 생성자가 100번 호출됨
		Item item3[100] = {};

		// 바구니가 100개, 즉 하나도 없을수도 있음 ==> 생성안하면 호출 X
		Item* item4[100] = {};

	}

	return 0;
}