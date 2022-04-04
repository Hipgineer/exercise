#include <iostream>

using namespace std;

// ������ ����: ĳ���� (Ÿ�Ժ�ȯ)



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

// 1) static_cast	: ���� ���� ���
// 2) dynamic_cast	: �״������� ���
// 3) const_cast	: 

void PrintName(char* str)
{
	cout << str << endl;
}
int main()
{
	// // static_cast : Ÿ�� ��Ģ�� ���� ���� ������� �ɽ��ø� ���
	// 1) int <-> float
	// 2) Player* -> Knight* (�ٿ� �ɽ���) <- ��, ������ ���� ���� (��ó�� Knight�� �ִ´ٴ���!)

	int hp = 100;
	int maxHp = 200;
	float ratio = (float)hp/maxHp;

	cout << ratio << endl;

	Player* p = new Knight();
	Knight* k1 = (Knight*)p; // �������߷��� �������� �� �ִ� ��Ȳ
	Knight* k2 = static_cast<Knight*>(p); // �̷��� �ٲٴ°� �ξ� ��Ȯ

	Knight* k = new Knight();
	Player* p2 = k; // �׳� ���� �Ǵ� ��Ȳ


	// // dyniamic_cast : ��� ���迡���� ���� ����ȯ
	// RTTI ( RunTime Type Information)
	// �������� Ȱ���ϴ� ��� (virtual �Լ��� ����ؾ��Ѵ�!)
	// - virtual �Լ��� �ϳ��� �����, ��ü�� �޸𸮿� �����Լ� ���̺� (vftable) �ּҰ� ����
	// - ���� �߸��� Ÿ������ ĳ������ ������, nullptr ��ȯ ******_*_*_*_*_*_*_*_*_
	// �̸� �̿��ؼ� �´� �������� ĳ������ �ߴ��� Ȯ�ο� �����ϴ�.
	Knight* k3 = dynamic_cast<Knight*>(p); // <- ������ ���Ŀ���? ��� ������ �����ϰ� �ֱ� ������, nullptr

	// // const_cast : const�� ���ų� ���̰ų�!
	//PrintName("Dongbin\n"); // > �̰� const�� ���� ������ ������ ���ϴ�
	PrintName(const_cast<char*>("Dongbin")); // > �̰� const�� ���� ������ ������ �ȳ��ϴ�
	

	// // reinterpre_cast
	// ���� �����ϰ� ������ ������ ĳ����
	// re-interpret : �ٽ�-�����ϴ�/�����ϴ�
	// - �����Ͷ� ���� ������� �ٸ� Ÿ�� ��ȯ
	__int64 address = (__int64)(k3);
	__int64 address = reinterpret_cast<__int64>(k3);
	// ���־��� ��������
	void* p = malloc(1000);
	Knight* knight = (Knight*)p;
	Knight* knight = reinterpret_cast<Knight*>(p);




	return 0;
}