#ifndef __PLAY__
#define __PLAY__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "node.h"

#define MIN 200
#define TOKEN_SIZE 6

using namespace std;

class Play {
private:
	// �⺸ ��ȣ
	int reportNumber;
	// �� ������ ����
	int cho_order;
	int han_order;
	int victory;

public:
	void printBoard();
	char StateInfo[HEIGHT_SIZE][WIDTH_SIZE];
	vector<node*> game;
	Play();
	Play(int reportNum, int cho, int han, int vic);

	// State�� ��� ������ ����
	void insertStage(node *state);

	// State�� ����
	/*void createState(int pos[], int unit);*/
	void createState(string line);

	Play* createPlay(ifstream &file);

	void initailize();
};
#endif
