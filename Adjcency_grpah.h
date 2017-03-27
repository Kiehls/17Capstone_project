#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>
#include <stack>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class Adjcency_grpah
{
private :
	State_node *root ;
	State_node *leaf ;
	vector<State_node*> *node_list ;
	stack<State_node *> state_stack ;

	friend class boost::serialization::access;
	template <typename AR>
	void serialize(AR &ar, const unsigned int ver) {
		ar & *root;
		ar & *node_list;
		//ar & state_stack;
		ar & *leaf;
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void Insert(vector<State_node*> state);
	//void Backtracking_stack() ;

	State_node* getRoot();
	State_node* getLeaf();

	// ���� ��ġ�� ��忡���� �ڽĳ��� �߰��� state�� ������ �ִ���.
	int Is_Have_childnode(State_node* sub_root, State_node* state);
	// ���� ��ġ�� ��忡�� � �θ��忡�� �Դ��� ����.
	int Direction_parentnode(State_node* sub_node);

	// ���� ��� state�� �׷����� �����ϰ� �ִ���
	State_node* Is_In_The_List_State(State_node *state);

	// �� state�� ������ �ٸ��� Ȯ���ϴ� �Լ�.
	bool Diff_State(State_node *stateA, State_node *stateB);
};

#endif