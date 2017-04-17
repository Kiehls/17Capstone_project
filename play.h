#ifndef __PLAY__
#define __PLAY__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "node.h"

#define MIN 200
#define TOKEN_SIZE 6
#define INITIAL_ORDER -2

using namespace std;

static int fileNum = 0;

class Play {
private:
	// �⺸ ��ȣ
	int reportNumber;
	// �� ������ ����
	int cho_order;
	int han_order;
	int victory;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(cho_order);
		ar & BOOST_SERIALIZATION_NVP(han_order);
		ar & BOOST_SERIALIZATION_NVP(victory);
		ar & BOOST_SERIALIZATION_NVP(game);
	}

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

	bool getRightNode() {
		if (cho_order == INITIAL_ORDER ||
			han_order == INITIAL_ORDER ||
			victory == INITIAL_ORDER) {
			return false;
		}
		else {
			return true;
		}
	}
	void initailize();
};
#endif