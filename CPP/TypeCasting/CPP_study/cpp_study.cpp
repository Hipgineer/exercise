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
//	char _dummy[4096] = {}; // ������� ���� �迭
//};
//
//void TestItem(Item item)
//{
//	// ���⼭ �ԷµǴ� ���� �����ڰ�ȣ��˴ϴ�. => ��������� ==> �����а� �ƴ϶� �׳� �Ѱ��ָ� ��ū�� ����ǰ� �ִ°ž�...
//}
//void TestItemPtr(Item* item)
//{
//	// ��� ������ X
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
//		// _itemType = 1; // ���� Ŭ������ ���̴ϱ� �̷��� �������� �����ڸ� ���� �ʱ�ȭ
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
//		// _itemType = 1; // ���� Ŭ������ ���̴ϱ� �̷��� �������� �����ڸ� ���� �ʱ�ȭ
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
//	//�������� ���� Ŭ���� ������ ������ ��ȯ
//	{
//	//	Knight* knight = new Knight(); //���ÿ� �ּ�, ���� ��¥ ������
//
//		// �Ͻ������δ� X
//		// ��������δ� O
//
//		//Item* item = (Item*)knight;
//		//item->_itemType = 2;
//		//item->_itenDbId = 1;
//
//		//delete knight; // �������Ŵ�. ���� ������ ������ ������ �� ���̴�.
//
//	} 
//
//	// �׷��ٸ� �������� ���� ��쿡��?
//	{
//		//Item* item = new Item();
//
//		//Weapon* weapon = new Weapon();
//
//		//Item* item2 = weapon; // O
//
//		//  Weapon* weapon2 = item; // �Ϛ��� X , ����� O
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
//			// == > �̷��� �ϸ� Waepon�� �Ҹ��ڴ� �ȵ�...! 
//
//			// �� ���������� �ϳ��ϳ� ��������ϴ� ��Ȳ�� �Ǵ°���
//			
//			// �׷��̰Ŵ� ��� �ذ���? --> ��� �̹� ���
//
//			// �Ҹ��ڵ� �ᱹ�� �Լ��̱� ������ // �������̵��� �Ǵ°Ŵ�.
//
//			// �� virtual�� ����� �ָ� ���� Ÿ��Ÿ�� �ö󰡸鼭 ��� ȣ���ҰŴ�. 
//
//			// �ֻ����� ���縦 ���̸� ��� Ŭ������ �Ҹ��ڵ� ��� ����
//
//			// �̷��� �Ǹ� �ڱ� Ÿ�Ե� ������ ��� �Ҹ��� ȣ��
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
//		//		Weapon* weapon = (Weapon*)item; // ū�ָ� �����ַ� �о�ִ� ������ ���������� ������ Wapon�̾��� ������ ��
//		//}
//
//	}
//
//	return 0;
//}