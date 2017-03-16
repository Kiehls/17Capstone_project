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
	// 기보 번호
	int reportNumber;
	// 각 진영의 포진
	int cho_order;
	int han_order;
	int victory;

public:
	void printBoard();
	char StateInfo[HEIGHT_SIZE][WIDTH_SIZE];
	vector<node*> game;
	Play();
	Play(int reportNum, int cho, int han, int vic);

	// State를 멤버 변수에 삽입
	void insertStage(node *state);

	// State를 생성
	/*void createState(int pos[], int unit);*/
	void createState(string line);

	Play* createPlay(ifstream &file);

	void initailize();
};
#endif
