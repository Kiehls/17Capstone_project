#include "Adjcency_grpah.h"

Adjcency_grpah::Adjcency_grpah(){

	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] = {
		{'O','O','O','O','O','O','O','O','O','O'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'},
		{'O','X','X','X','X','X','X','X','X','X'}};

	root = new State_node(Init_jannggi) ;
	node_list = new vector<State_node*>() ; // Ž���� ���� �ؾ� �ϹǷ� vector STL�� ���.
	node_list->push_back(root) ;
  leaf = NULL;
}
//Serialize�� ���� ���� ���� ������
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah &graph) {
	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ 'O','O','O','O','O','O','O','O','O','O' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' } };

	root = graph.getRoot();
	node_list = new vector<State_node*>();
	node_list->push_back(root);
}
//Serialize�� ���� ���� ���� ������
Adjcency_grpah::Adjcency_grpah(Adjcency_grpah *graph) {
	char Init_jannggi[HEIGHT_SIZE][WIDTH_SIZE] = {
		{ 'O','O','O','O','O','O','O','O','O','O' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' },
		{ 'O','X','X','X','X','X','X','X','X','X' } };

	root = graph->getRoot();
	node_list = new vector<State_node*>();
	node_list->push_back(root);
}

void Adjcency_grpah::Insert(vector<State_node*> state){
	State_node *now_state = root ;

	for(int index = 0 ; index < state.size() ; index++){
		State_node* add_state = state.at(index) ;

		int childnode = Is_Have_childnode(now_state,add_state) ;

		// �ڱ� �ڽİ� ������ ������ �״�� �̵�.
		if(childnode >= 0){
			now_state = now_state->NthCheck_Childnode(childnode) ;
			cout << childnode << endl;
		}
		else {
			// �ڱ� �ڽİ� ������ ������ � ��忡 �����ϸ� �� ��带 next�� �����Ѵ�.
			State_node* check_node = Is_In_The_List_State(add_state) ;
			if(check_node){
				now_state->Addlist_Child(check_node) ;
				check_node->Connect_Parent(now_state) ;
				now_state = check_node ;
			}
			else {
				node_list->push_back(add_state) ;
		//		add_state->Print_State() ;
				now_state->Addlist_Child(add_state) ;
				add_state->Connect_Parent(now_state) ;
				add_state->state_ordernum = now_state->next->size() ;
				// cout << add_state->state_ordernum << endl ;
				now_state = add_state ;
			}
		}
		state_stack.push(now_state) ;
	}
	state_stack.pop() ;
	leaf = now_state ;
}

void Adjcency_grpah::Backtracking_stack(){
	State_node* temp = leaf ;

	cout << "\n< Start ! > " << endl ;
	while(!state_stack.empty()){
		temp->Print_State() ;
		temp = temp->prev->at(Direction_parentnode(temp)) ;
	}

	// ���� ����
	while(!state_stack.empty()) state_stack.pop() ;
	cout << "< End ! >" << endl << endl << endl ;
}


State_node* Adjcency_grpah::getRoot(){
	return root ;
}

State_node* Adjcency_grpah::getLeaf(){
	return leaf ;
}

// ���� ��ġ�� ��忡���� �ڽĳ��� �߰��� state�� ������ �ִ���.
int Adjcency_grpah::Is_Have_childnode(State_node* sub_root, State_node* state){	
	for(int i=0; i<sub_root->num_of_next ; i++)
		if(!Diff_State(sub_root->NthCheck_Childnode(i), state))
			return i ;
	return -1 ;
}

int Adjcency_grpah::Direction_parentnode(State_node* sub_node){	
	State_node* temp = state_stack.top() ;
	state_stack.pop() ;
	for(int i=0; i<sub_node->num_of_prev ; i++){
		if(!Diff_State(sub_node->NthCheck_Parentnode(i), temp))
			return i ;
	}
	return -1 ;		
}

// ���� ��� state�� �׷����� �����ϰ� �ִ���
State_node* Adjcency_grpah::Is_In_The_List_State(State_node *state){
	for(int i=0; i<node_list->size() ; i++)
		if(!Diff_State(node_list->at(i), state))
			return node_list->at(i) ;
	return NULL ; 
}

// �� state�� ������ �ٸ��� Ȯ���ϴ� �Լ�.
bool Adjcency_grpah::Diff_State(State_node *stateA, State_node *stateB){
	for(int i=1 ; i< HEIGHT_SIZE; i++)
		for(int j=1 ; j< WIDTH_SIZE ; j++){
			if ( stateA->arr[i][j] != stateB->arr[i][j] )
				return true ;
		}
		return false ;
}