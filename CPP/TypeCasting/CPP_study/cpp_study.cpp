//#include <iostream>
//
//using namespace std;
//
//class Knight
//{
//public:
//	int _hp;
//};
//
//
//
//class Item
//{
//public:
//
//	Item()
//	{
//		cout << "item()" << endl;
//	}
//
//	Item(int itemType)
//	{
//		_itemType = itemType;
//	}
//
//	~Item() 
//	{
//		cout << "~item()" << endl;
//	}
//
//public:
//
//	int _itemType = 0;
//	int _itenDbId = 0;
//
//	char _dummy[4096] = {}; // 비대해진 뭔가 배열
//};
//
//void TestItem(Item item)
//{
//	// 여기서 입력되는 값도 생성자가호출됩니다. => 복사생성자 ==> 포인털갈 아니라 그냥 넘겨주면 개큰게 복사되고 있는거야...
//}
//void TestItemPtr(Item* item)
//{
//	// 얘는 생성자 X
//}
//
//enum ItemType
//{
//	IT_WEAPON = 1,
//	IT_ARMOR = 2,
//};
//
//class Weapon : public Item {
//public:
//
//	Weapon() : Item(IT_WEAPON)
//	{
//		// _itemType = 1; // 상위 클래스의 값이니까 이렇게 하지말고 생성자를 통해 초기화
//		cout << "Weapon()" << endl;
//	}
//	~Weapon()
//	{
//		cout << "~Weapon()" << endl;
//	}
//
//	int Damage;
//};
//
//
//
//class Armor : public Item {
//public:
//
//	Armor() : Item(IT_ARMOR)
//	{
//		// _itemType = 1; // 상위 클래스의 값이니까 이렇게 하지말고 생성자를 통해 초기화
//		cout << "Armor()" << endl;
//	}
//	~Armor()
//	{
//		cout << "~Armor()" << endl;
//	}
//
//	int Defence;
//};
//
//int main() 
//{
//
//	//연고나성이 없는 클래스 사이의 포인터 변환
//	{
//	//	Knight* knight = new Knight(); //스택에 주소, 힙에 진짜 데이터
//
//		// 암시적으로는 X
//		// 명시적으로는 O
//
//		//Item* item = (Item*)knight;
//		//item->_itemType = 2;
//		//item->_itenDbId = 1;
//
//		//delete knight; // 에러날거다. 힙에 문제가 있음을 인지하 할 것이다.
//
//	} 
//
//	// 그렇다면 연관성이 있을 경우에는?
//	{
//		//Item* item = new Item();
//
//		//Weapon* weapon = new Weapon();
//
//		//Item* item2 = weapon; // O
//
//		//  Weapon* weapon2 = item; // 암싲적 X , 명시적 O
//	}
//
//	{
//		Item* inventory[20] = {};
//		
//		srand((unsigned int)time(nullptr));
//
//		for (int i = 0; i < 20; i++)
//		{
//			int randvalue = rand() % 2;
//			switch (randvalue)
//			{
//			case 0:
//				inventory[i] = new Weapon();
//				break;
//			case 1:
//				inventory[i] = new Armor();
//				break;
//			}
//			delete inventory[i]; 
//			// == > 이렇게 하면 Waepon의 소멸자는 안되...! 
//
//			// 즉 이프문으로 하나하나 지워줘야하는 상황이 되는건지
//			
//			// 그럼이거는 어떻게 해결해? --> 사실 이미 배움
//
//			// 소멸자도 결국엔 함수이기 때문에 // 오버라이딩이 되는거다.
//
//			// 즉 virtual로 만들어 주면 위로 타고타고 올라가면서 모두 호출할거다. 
//
//			// 최상위에 버춰를 붙이면 상속 클래스의 소멸자도 모두 버춰
//
//			// 이렇게 되면 자기 타입도 물고물고 모두 소멸자 호출
//		}
//
//
//		//for (int i = 0; i < 20; i ++ )
//		//{
//		//	Item* item = inventory[i];
//		//	if (item == nullptr)
//		//		continue;
//
//		//	if (item->_itemType == IT_WEAPON)
//		//		Weapon* weapon = (Weapon*)item; // 큰애를 작은애로 밀어넣는 위험한 아이이지만 원래도 Wapon이었기 떄문에 괜
//		//}
//
//	}
//
//	return 0;
//}