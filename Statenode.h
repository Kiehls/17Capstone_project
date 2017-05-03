#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/vector.hpp> // ����ȭ vector�� ����ϱ� ����
#include <boost/serialization/deque.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/stack.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/archive/binary_iarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����
#include <boost/archive/binary_oarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/exception/all.hpp>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11
#define PIECE_NUM 8 
#define INIT_WEIGHT 100000

using namespace std;

typedef pair<int, int> Cha_pos;
typedef pair<int, int> Pho_pos;
typedef char (*STATE)[WIDTH_SIZE] ;

class Now_turn
{
private:
	char actor;
	char killed;
	bool checkmate;
	int host;
	pair<int, int> pos;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(actor);
		ar & BOOST_SERIALIZATION_NVP(killed);
		ar & BOOST_SERIALIZATION_NVP(checkmate);
		ar & BOOST_SERIALIZATION_NVP(host);
		ar & BOOST_SERIALIZATION_NVP(pos);
	}

public:
	Now_turn(char act, char kill, bool check, int host);
	Now_turn();
	char GetActor();
	char GetKilled();
	bool GetCheckmate();
	int Gethost() ;
	pair<int, int> Getpos();
	void SetTurn(char act, char kill, bool check, int host, pair<int, int> Pos);
};


class State_node
{
private:
	int state_ordernum; //���� �θ��� n��° �ڽ�. n�� ����.
	int unit_of_han;
	int unit_of_cho;
	int travel_count;
	int state_number; //  state ��ȣ�� ����.

	// ��
	vector<int> *han_weight ;
	vector<int> *cho_weight ;
	int score;
	char State[HEIGHT_SIZE][WIDTH_SIZE];

	Now_turn *this_turn;
	vector<State_node*>* next;
	vector<State_node*>* prev;
	pair<Cha_pos, Pho_pos> sum_of_horsepos;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(state_ordernum);
		ar & BOOST_SERIALIZATION_NVP(state_number);
		ar & BOOST_SERIALIZATION_NVP(unit_of_cho);
		ar & BOOST_SERIALIZATION_NVP(unit_of_han);
		ar & BOOST_SERIALIZATION_NVP(travel_count);
		ar & BOOST_SERIALIZATION_NVP(han_weight);
		ar & BOOST_SERIALIZATION_NVP(cho_weight);
		ar & BOOST_SERIALIZATION_NVP(score);
		ar & BOOST_SERIALIZATION_NVP(State);
		ar & BOOST_SERIALIZATION_NVP(sum_of_horsepos);
		ar & BOOST_SERIALIZATION_NVP(next);
		ar & BOOST_SERIALIZATION_NVP(prev);
		ar & BOOST_SERIALIZATION_NVP(this_turn);
	}
public:

	State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]);
	State_node();

	// state�� ���¸� ����Ѵ�.
	void Print_State();

	//node�� �ڽ��� ����.
	void Addlist_Child(State_node *add_state);
	void Connect_Parent(State_node *parent_state);
	void Set_numUnit(int cho, int han);
	void Set_Stateorder(int data);
	void SetHorse_position(pair<Cha_pos, Pho_pos> s);
	void Init();
	void TravelCountPlus();
	void SetState_number(int setnum);
	void Print_weight(int idx);
	// overeading (?)
	void SetHan_weight(vector<int> *h_weight);
	void SetCho_weight(vector<int> *c_weight);
	void SetScore(int score_);
	void SetTravelcount(int _travelCount);

	void WeightCalculate(int idx, const int score, int host);
	void evaluateBoard();

	const bool operator==(State_node *node);
	State_node State_node::Copy_node(State_node *_operandNode);
	void SetNext(vector<State_node*> *_next);
	void SetPrev(vector<State_node*> *_prev);
	void SetNow_turn(Now_turn *_turn);

	// n��° �ڽ��� return
	State_node* NthCheck_Childnode(int n);
	State_node* NthCheck_Parentnode(int n);
	Now_turn* GetTurn();
	STATE GetState();

	int Getnumprev();
	int Getnumnext();
	int Getstate_ordernum();
	int Gethan();
	int Getcho();
	int GetTravelcount();
	int GetState_number();
	vector<int>* Get_hanweight();
	vector<int>* Get_choweight();
	int GetScore();

	vector<State_node*> *Getnext();
	vector<State_node*> *Getprev();
	pair<Cha_pos, Pho_pos> GetHorse_pos();
};

#endif