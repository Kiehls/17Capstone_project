#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp> // �ؽ�Ʈ ���·� �Է��ϱ� ����
#include <boost/archive/text_oarchive.hpp> // �ؽ�Ʈ ���·� ����ϱ� ����
#include <boost/serialization/vector.hpp> // ����ȭ vector�� ����ϱ� ����
#include <boost/serialization/deque.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/stack.hpp> // ����ȭ stack�� ����ϱ� ����
#include <boost/serialization/map.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/exception/all.hpp>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std;

typedef pair<int, int> Cha_pos;
typedef pair<int, int> Pho_pos;

class Now_turn
{
private:
	char actor;
	char killed;
	bool checkmate;

public:
	Now_turn(char act, char kill, bool check);
	Now_turn();
	char GetActor();
	char GetKilled();
	bool GetCheckmate();
	void SetTurn(char act, char kill, bool check);
};


class State_node
{
private:
	int state_ordernum;
	int unit_of_han;
	int unit_of_cho;
	int travel_count;
	int state_number;
	Now_turn *this_turn;
	vector<State_node*>* next;
	vector<State_node*>* prev;
	pair<Cha_pos, Pho_pos> sum_of_horsepos;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive &ar, const unsigned int ver) {
		ar & BOOST_SERIALIZATION_NVP(state_ordernum);
		ar & BOOST_SERIALIZATION_NVP(unit_of_cho);
		ar & BOOST_SERIALIZATION_NVP(unit_of_han);
		ar & BOOST_SERIALIZATION_NVP(arr);
		ar & BOOST_SERIALIZATION_NVP(sum_of_horsepos);
		ar & BOOST_SERIALIZATION_NVP(next);
		ar & BOOST_SERIALIZATION_NVP(prev);
	}
public:
	char arr[HEIGHT_SIZE][WIDTH_SIZE];

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

	// n��° �ڽ��� return
	State_node* NthCheck_Childnode(int n);
	State_node* NthCheck_Parentnode(int n);
	Now_turn* GetTurn();

	int Getnumprev();
	int Getnumnext();
	int Getstate_ordernum();
	int Gethan();
	int Getcho();
	int GetTravelcount();
	int GetState_number();

	vector<State_node*> *Getnext();
	vector<State_node*> *Getprev();
	pair<Cha_pos, Pho_pos> GetHorse_pos();
};

#endif