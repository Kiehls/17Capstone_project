#ifndef __ADJCENCY__GRAPH__  
#define __ADJCENCY__GRAPH__  

#include "Statenode.h"
#include <iostream>
#include <vector>

#define WIDTH_SIZE 10
#define HEIGHT_SIZE 11

using namespace std ;

class Adjcency_grpah
{
private :
	State_node *root ;
	State_node *leaf ;
	vector<State_node*> *node_list ;

	friend class boost::serialization::access;
	template <typename AR>
	void serialize(AR &ar, const unsigned int ver) {
		ar & *root;
		ar & *node_list;
	}
public:
	Adjcency_grpah();
	Adjcency_grpah(Adjcency_grpah &graph);
	Adjcency_grpah(Adjcency_grpah *graph);

	void Insert(vector<State_node*> state);

	State_node* getRoot();
	State_node* getLeaf();

	// ���� ��ġ�� ��忡���� �ڽĳ��� �߰��� state�� ������ �ִ���.
	int Is_Have_childnode(State_node* sub_root, State_node* state);

	// ���� ��� state�� �׷����� �����ϰ� �ִ���
	State_node* Is_In_The_List_State(State_node *state);

	// �� state�� ������ �ٸ��� Ȯ���ϴ� �Լ�.
	bool Diff_State(State_node *stateA, State_node *stateB);
};

#endif