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

	char _dummy[4096] = {}; // ������� ���� �迭
};

void TestItem(Item item)
{
	// ���⼭ �ԷµǴ� ���� �����ڰ�ȣ��˴ϴ�. => ��������� ==> �����а� �ƴ϶� �׳� �Ѱ��ָ� ��ū�� ����ǰ� �ִ°ž�...
}
void TestItemPtr(Item* item)
{
	// ��� ������ X
}

int main() 
{
	// ���� : Ÿ�Ժ�ȯ�� �߸��ϸ� ������ �ɰſ�
	{
		// Stack [ type(4)  dbid(4) dummy(4096] ] 
		Item item;

		// Stack [�ּ�(4-8)] : ���ּ� : [ type(4)  dbid(4) dummy(4096] ] 
		Item* item2 = new Item(); // �����Ҵ� ==> ���࿡ ������ �ϰ� ���ٸ� �Ҹ��ڸ� �������� ����

		TestItem(item);
		TestItem(*item2);

		TestItemPtr(&item);
		TestItemPtr(item2);



		delete item2; // ��������ؿ� ���ϸ� Memory Laek => ����޸𸮰� �پ� Crash�� �߻�

	}

	//�迭
	{
		// ��¥ ������ 100�� ���� ==> �����ڰ� 100�� ȣ���
		Item item3[100] = {};

		// �ٱ��ϰ� 100��, �� �ϳ��� �������� ���� ==> �������ϸ� ȣ�� X
		Item* item4[100] = {};

	}

	return 0;
}