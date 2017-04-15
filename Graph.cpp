#include "Graph.h"

//�ø������� �� �׷����� ���Ϸ� ������.
void SaveTestData(Adjcency_grpah *i, char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName, std::ios::binary);
	//boost::archive::text_oarchive oa(ofs);
	boost::archive::binary_oarchive oa(ofs);
	oa & BOOST_SERIALIZATION_NVP(g);
	cout << "Storing Serialize Success\n" << endl;
}
////������� ������ �ٽ� �ε�
Adjcency_grpah LoadTestData(char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName, std::ios::binary);
	if (!ifs) {
		cout << "Read Error" << endl;
		exit(1);
	}
	//boost::archive::text_iarchive ia(ifs);
	boost::archive::binary_iarchive ia(ifs);
	ia & BOOST_SERIALIZATION_NVP(g);
	cout << "Restoring Serialize Success\n" << endl;
	return g;
}

void Play_to_Statenode(vector<Play*> *play, vector<State_node*> *state, int now_state)
{
	for (int j = 0; j < play->at(now_state)->game.size(); j++) {
		node * node_t = play->at(now_state)->game.at(j);
		State_node* now_state = new State_node(node_t->returnState());
		now_state->Set_numUnit(node_t->getNumOfCho(), node_t->getNumOfHan());
		now_state->SetHorse_position(node_t->getPair());
		now_state->GetTurn()->SetTurn(node_t->getActor(), node_t->getKilled(), node_t->getCheckMate());
		state->push_back(now_state);
	}

}

void Graph_made(Adjcency_grpah* g, vector<Play*>* play, vector<State_node*>* state) {
	try {
		for (int i = 0; i < play->size(); i++) {
			state->clear();
			Play_to_Statenode(play, state, i);
			g->Insert(state);
			//g->Backtracking_stack();
			if(i % 100 == 0)
				cout << i << "��°\n" << endl;
		}
	}
	catch (exception &e) {
		std::cerr << e.what();
	}
	cout << "Graph Generated\n" << endl;
}

void Second_Graph_made(Second_Graph* g2, vector<Play*>* play, vector<State_node*>* state) {
	try {
		for (int i = 0; i < play->size(); i++) {
			state->clear();
			Play_to_Statenode(play, state, i);
			g2->Getgraph()->Second_insert(state);
			g2->Value_process(state);
		}
	}
	catch (exception &e) {
		std::cerr << e.what();
	}
	cout << "Graph Generated_2" << endl;
}

void Insert_Gibo(vector<Play*> *play)
{
	ifstream inStream("testFile.txt");
	if (inStream.fail()) {
		cout << "Stream File Failed" << endl;
		exit(1);
	}
	while (!inStream.eof()) {
		Play *each_game = NULL;
		Play *temp = each_game->createPlay(inStream);
		if (temp->getRightNode()) {
			play->push_back(temp);
		}
	}
}