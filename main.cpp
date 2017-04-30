#include "Graph.h"
#include <time.h>

int main()
{
	clock_t start_t = clock();
	
	vector<vector<State_node*>*> *state = new vector<vector<State_node*>*>();
	vector<Play*> *LoadPlay = new vector<Play*>(); //--> ������ Vector�� �����ϱ� ����
	vector<Play*> *play = new vector<Play*>();
	Adjcency_grpah *g = new Adjcency_grpah();
	
	Insert_Gibo(play);
	Graph_made(g, play, state);
	Second_Graph *second_g = new Second_Graph(g);
	Second_Graph_made(second_g, play, state);
	second_g->Getgraph()->Travelgraph_bfs();

//	SaveVectorData(play, "V_BinaryFile");
//	LoadPlay = LoadVectorData("V_BinaryFile");

	SaveGraphData(second_g->Getgraph(), "G_BinaryFile");
	Adjcency_grpah *AiGraph = new Adjcency_grpah(LoadGraphData("G_BinaryFile"));



	clock_t end_t = clock();
	cout << "�ð� : " << (end_t - start_t) / 1000 << endl;

	return 0;
}