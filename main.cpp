#include "Graph.h"
#include <time.h>

//�ø������� �� �׷����� ���Ϸ� ������.
void SaveTestData(Adjcency_grpah *i, char *fileName) {
	Adjcency_grpah g(i);
	std::ofstream ofs(fileName);
	boost::archive::text_oarchive oa(ofs);
	oa & BOOST_SERIALIZATION_NVP(g);
}

//������� ������ �ٽ� �ε�
Adjcency_grpah LoadTestData(char *fileName) {
	Adjcency_grpah g;
	std::ifstream ifs(fileName);
	boost::archive::text_iarchive ia(ifs);
	ia & BOOST_SERIALIZATION_NVP(g);

	return g;
}

int main()
{
	clock_t t = clock();

	Adjcency_grpah *g = new Adjcency_grpah();
	vector<State_node*> state;
	vector<Play*> play;
	Insert_Gibo(play);

	try {
		for (int i = 0; i < play.size(); i++) {
			state.clear();
			Play_to_Statenode(play, state, i);
			g->Insert(state);
		//	g->Backtracking_stack();
			cout << i << "��°\n" << endl;
		}
	}
	catch (exception &e) {
		std::cerr << e.what();
	}

//	SaveTestData(g, "G");
	cout << "Graph Generated" << endl;

	g->Travelgraph_bfs();
//	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadTestData("G"));
	
	clock_t end_t = clock();
	cout << "�ð� : " << (end_t - t) / 1000 << endl;

	return 0;
}

void Play_to_Statenode(vector<Play*> play, vector<State_node*> &state, int now_state)
{
	for (int j = 0; j < play.at(now_state)->game.size(); j++) {
		node * node_t = play.at(now_state)->game.at(j);
		State_node* t = new State_node(node_t->returnState());
		t->Set_numUnit(node_t->num_of_cho, node_t->num_of_han);
		t->SetHorse_position(node_t->sum_of_horsepos);
		state.push_back(t);
	}

}

void Insert_Gibo(vector<Play*> &play)
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
			play.push_back(temp);
		}
	}
}
