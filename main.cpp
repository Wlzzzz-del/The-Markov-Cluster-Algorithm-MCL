#include <iostream>
#include <vector>
#include <map>
#include "mcl.cpp"
#include "data.cpp"
#include "chamelon.cpp"
int main(){

				Load_data file;
				//file.read_gml_w("dataset/netscience.gml");
				file.read_karate_gml("./dataset/karate.gml");
				//file.show_adjmatrix();
				//file.show_graph();
				std::vector<std::vector<double>> adj;
				std::map<int, std::vector<int>> society;
				std::map<int, int> dictionary;
				adj = file.get_adj();
				mcl a(2, 2, true, adj, 50);
				a.run();
				a.show();
				dictionary = a.get_dictionary();
				society = a.get_society();
				//chamelon b(1, 0.5, society, dictionary, adj);
				//b.run();
}
