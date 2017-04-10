#ifndef __NODE__
#define __NODE__

#include <iostream>
#include <vector>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std;

typedef char(*State)[WIDTH_SIZE];
typedef pair<int, int> Cha_pos;
typedef pair<int, int> Pho_pos;

class node
{
private:
	int host;
	int num_of_han;
	int num_of_cho;

	char killed;
	char actor;
	char arr[HEIGHT_SIZE][WIDTH_SIZE];

	bool checkMate;

	pair<Cha_pos, Pho_pos> sum_of_horsepos;

public:
	
	node(State board);
	node();

	// state�� ���¸� ����Ѵ�.
	void Print_State();

	// state�� ���� ��ȯ
	State returnState();

	// state�� ���¸� �ʱ�ȭ�Ѵ�.
	void UnitOrder(int cho_order, int han_order);

	// state�� ���¸� �����Ѵ�.
	void changeState(int pos[]);

	// state�� ��, ���� ���� ������ ���Ѵ�.
	void getNumOfUnit();

	void Init_Hashkeydata();

	// state initialize
	void Init();

	pair<Cha_pos, Pho_pos> getPair();

	int getNumOfHan();

	int getNumOfCho();

	int getHost();

	char getActor();

	char getKilled();

	bool getCheckMate();

	void setCheckMate(bool is);

	void setActor(char unit);

	void setKilled(char unit);

	void setHost(int host);

	char getArrPos(int xPos, int yPos);
};

#endif
