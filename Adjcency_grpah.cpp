#include "Adjcency_grpah.h"

Adjcency_grpah::Adjcency_grpah() {

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE];
	for (int i = 0; i < HEIGHT_SIZE; i++) {
		memset(Init_jannggi[i], 'X', sizeof(char)*WIDTH_SIZE);
	}

	root = new State_node(Init_jannggi);
	root->Set_numUnit(0, 0);
	statenode_num = 0;
	Init_hashtable();
	PushList_Hashtable(root);
	root->SetState_number(0);

	leaf = NULL;
}
//Reload Serialize�� ���� ���� ���� ������
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah &graph) {
	root = graph.root;
	leaf = graph.leaf;
	Init_hashtable();
	statenode_num = graph.statenode_num;

	memcpy(hashstate_list, graph.hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
//Save Serialize�� ���� ���� ���� ������
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	root = graph->root;
	leaf = graph->leaf;
	Init_hashtable();
	statenode_num = graph->statenode_num;

	memcpy(hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT);
}
void Adjcency_grpah::Init_hashtable() {
	for (int i = 0; i < NUMUNIT; i++) {
		for (int j = 0; j < NUMUNIT; j++) {
			hashstate_list[i][j] = new hash_4d();
		}
	}
}

void Adjcency_grpah::PushList_Hashtable(State_node* state) {
	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y;	int cha_x;	int pho_y;	int pho_x;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);
	hashstate_list[cho][han]->insert(hash_4d::value_type(pair_key(Cha_pos(cha_y, cha_x), Pho_pos(pho_y, pho_x)), state));
}


void Adjcency_grpah::Insert(vector<State_node*>* state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);

		// �ڱ� �ڽİ� ������ ������ �״�� �̵�.
		if (childnode >= 0) {
			now_state = now_state->NthCheck_Childnode(childnode);
		}
		else {
			// �ڱ� �ڽİ� ������ ������ � ��忡 �����ϸ� �� ��带 next�� �����Ѵ�.
			State_node* check_node = Is_In_The_List_State(add_state);
			if (check_node) {
				now_state->Addlist_Child(check_node);
				check_node->Connect_Parent(now_state);
				now_state = check_node;
			}
			else {
				PushList_Hashtable(add_state);
				add_state->SetState_number(++statenode_num);
				now_state->Addlist_Child(add_state);
				add_state->Connect_Parent(now_state);
				add_state->Set_Stateorder(now_state->Getnext()->size());
				now_state = add_state;
			}
		}
		state_stack.push(now_state);
		now_state->TravelCountPlus();
	}
	leaf = now_state;
}

void Adjcency_grpah::Second_insert(vector<State_node*>* state) {
	State_node *now_state = root;

	for (int index = 0; index < state->size(); index++) {
		State_node* add_state = state->at(index);

		int childnode = Is_Have_childnode(now_state, add_state);
		// �ڱ� �ڽİ� ������ ������ �״�� �̵�.
		now_state = now_state->NthCheck_Childnode(childnode);
		state->at(index) = now_state;
	}
}

void Adjcency_grpah::Backtracking_stack() {
	State_node* temp = leaf;

	temp->Print_State();
	cout << temp->Getcho() << " " << temp->Gethan() << " " << temp->GetTravelcount() << endl;
	state_stack.pop();

	cout << "\n< Start ! > " << endl;
	while (!state_stack.empty()) {
		cout << "borad No." << state_stack.size() << endl; //�߰�
		temp->Print_State();
		cout << temp->Getcho() << " " << temp->Gethan() << endl;
		temp = temp->Getprev()->at(Direction_parentnode(temp));
	}

	// ���� ����
	while (!state_stack.empty()) state_stack.pop();
	cout << "< End ! >" << endl << endl << endl;
}

void Adjcency_grpah::Set_4Dhashdata(int &cha_y, int &cha_x, int &pho_y, int &pho_x, State_node* state) {
	cha_y = state->GetHorse_pos().first.first;
	cha_x = state->GetHorse_pos().first.second;
	pho_y = state->GetHorse_pos().second.first;
	pho_x = state->GetHorse_pos().second.second;
}


void Adjcency_grpah::Travelgraph_bfs() {
	ofstream stream("output.txt");
	queue<State_node*> *q = new queue<State_node*>();
	State_node *temp;
	int* bfs_check = new int[statenode_num + 1];
	for (int i = 0; i <= statenode_num; i++) {
		bfs_check[i] = i;
	}
	q->push(root);

	cout << " ������Ʈ ��ȣ , �湮 Ƚ�� " << endl;
	while (!q->empty()) {
		temp = q->front();
		q->pop();
		stream << "state ��ȣ : " << temp->GetState_number() << " �湮 Ƚ�� : " << temp->GetTravelcount() << endl;
		for (int i = 0; i < temp->Getnumnext(); i++) {
			if (bfs_check[temp->NthCheck_Childnode(i)->GetState_number()] != -1) {
				bfs_check[temp->NthCheck_Childnode(i)->GetState_number()] = -1;
				q->push(temp->NthCheck_Childnode(i));
			}
		}
	}

}

State_node* Adjcency_grpah::getRoot() {
	return root;
}

State_node* Adjcency_grpah::getLeaf() {
	return leaf;
}

// ���� ��ġ�� ��忡���� �ڽĳ��� �߰��� state�� ������ �ִ���.
int Adjcency_grpah::Is_Have_childnode(State_node* sub_root, State_node* state) {
	for (int i = 0; i < sub_root->Getnumnext(); i++)
		if (!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i;
	return -1;
}

int Adjcency_grpah::Direction_parentnode(State_node* sub_node) {
	State_node* temp = state_stack.top();
	state_stack.pop();
	for (int i = 0; i < sub_node->Getnumprev(); i++) {
		if (!Diff_State(sub_node->NthCheck_Parentnode(i), temp))
			return i;
	}
	return -1;
}

// ���� ��� state�� �׷����� �����ϰ� �ִ���
State_node* Adjcency_grpah::Is_In_The_List_State(State_node *state) {

	int cho = state->Getcho();
	int han = state->Gethan();
	int cha_y;	int cha_x;	int pho_y;	int pho_x;
	Set_4Dhashdata(cha_y, cha_x, pho_y, pho_x, state);

	hash_4d* m = hashstate_list[cho][han];
	hash_4d::iterator itCur;
	pair<hash_4d::iterator, hash_4d::iterator> it_pair;
	it_pair = m->equal_range(pair_key(Cha_pos(cha_y, cha_x), Pho_pos(pho_y, pho_x)));

	for (itCur = it_pair.first; itCur != it_pair.second; itCur++) {
		if (!Diff_State(itCur->second, state) )
			return itCur->second;
	}

	return NULL;
}

// �� state�� ������ �ٸ��� Ȯ���ϴ� �Լ�.
bool Adjcency_grpah::Diff_State(State_node *stateA, State_node *stateB) {
	if ( stateA->GetTurn()->Gethost() != stateB->GetTurn()->Gethost())
		return true ;
	for (int i = 1; i < HEIGHT_SIZE; i++)
		for (int j = 1; j < WIDTH_SIZE; j++) {
			if (stateA->arr[i][j] != stateB->arr[i][j] )
				return true;
		}
	return false  ;
}

const bool Adjcency_grpah::operator==(Adjcency_grpah *graph) {
	if (memcmp(this->hashstate_list, graph->hashstate_list, sizeof(hash_4d*) * NUMUNIT * NUMUNIT)) {
		return false;
	}
	else if (!(this->root->operator==(graph->getRoot()))) {
		return false;
	}
	else if (!(this->leaf->operator==(graph->getLeaf()))) {
		return false;
	}
	else
		return true;
}

Second_Graph::Second_Graph(Adjcency_grpah *g) {
	original_g = new Adjcency_grpah(g);
}

void Second_Graph::Value_process(vector<State_node*>* state) {
	State_node * now_state = new State_node();
	State_node * prev_state = new State_node();
	State_node * next_state = new State_node();
	for (int i = 1; i < state->size(); i++) {
		now_state = state->at(i);
		prev_state = GetPrev_state(state, i);
		next_state = GetNext_state(state, i);
		int actor = now_state->GetTurn()->GetActor();
		int killed = now_state->GetTurn()->GetKilled();
		int checkmate = now_state->GetTurn()->GetCheckmate();
		int host = now_state->GetTurn()->Gethost() ;


	}
}

Adjcency_grpah * Second_Graph::Getgraph() {
	return original_g;
}


State_node* Second_Graph::GetPrev_state(vector<State_node*>* state, int index) {
	if (index >= 1)
		return state->at(index - 1);
	return NULL;
}

State_node* Second_Graph::GetNext_state(vector<State_node*>* state, int index) {
	if (index <= state->size() - 2)
		return state->at(index + 1);
	return NULL;
}