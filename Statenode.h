#ifndef __STATE__NODE__  
#define __STATE__NODE__  

#include <iostream>
#include <vector>

#include <boost/archive/binary_iarchive.hpp> // ���̳ʸ� ���·� �Է��ϱ� ����
#include <boost/archive/binary_oarchive.hpp> // ���̳ʸ� ���·� ����ϱ� ����
#include <boost/serialization/vector.hpp> // ����ȭ vector�� ����ϱ� ����

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class State_node
{
private:
	friend class boost::serialization::access;
	template <typename AR>
	void serialize(AR &ar, const unsigned int ver) {
		ar & num_of_prev;
		ar & num_of_next;
		ar & state_ordernum;
		ar & *next;
		ar & *prev;
		ar & arr;
	}
public:
	int num_of_prev ; // ���� ����� ���� 
	int num_of_next ;  // ���� ����� ����
	int state_ordernum ; 
	vector<State_node*> *next ; 
	vector<State_node*> *prev ; 

	char arr[HEIGHT_SIZE][WIDTH_SIZE] ;

	State_node(char data[HEIGHT_SIZE][WIDTH_SIZE]) ;
	State_node();

	// state�� ���¸� ����Ѵ�.
	void Print_State();

	//node�� �ڽ��� ����.
	void Addlist_Child(State_node *add_state);
	void Connect_Parent(State_node *parent_state) ;

	// n��° �ڽ��� return
	State_node* NthCheck_Childnode(int n);
	State_node* NthCheck_Parentnode(int n);
};

#endif