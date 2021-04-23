#include <cstdio>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Load_data {
private:
  int num_edges = 0;
  int num_nodes = 0;
  void read_nodes(std::fstream &myfile); // process nodes
	void read_karate_nodes(std::fstream &myfile);//process karate nodes
	void read_karate_edges(std::fstream &myfile);//process karate edges
  void read_edges_w(std::fstream &myfile); // process weighted edges
	void read_edges(std::fstream &myfile);//process unweighted edges
  void resize_adj();
	double atod(std::string s);
  std::vector<std::vector<double>> adj_matrix;
  std::unordered_map<int, std::string> graph;

public:
  Load_data(){};
  ~Load_data(){};
  void read_gml_w(std::string address);
	void read_gml(std::string address);
	void read_karate_gml(std::string address);
	void show_adjmatrix();
	void show_graph();
  std::vector<std::vector<double>> get_adj();
  std::unordered_map<int, std::string> get_graph();
};

double Load_data::atod(std::string s){
				std::stringstream sstream;
				double result;
				sstream<<s;
				sstream>>result;
				return result;
}
void Load_data::read_gml(std::string address){
  std::string line;
  std::fstream myfile;
	bool have_resize = true;

  // open file
  myfile.open(address);

  // pass three line
  getline(myfile, line);
  getline(myfile, line);
  getline(myfile, line);

  while (1) {
    if (getline(myfile, line)) {
      if (line.find("node") != line.npos) {
        read_nodes(myfile);
        continue;
      }
      if (line.find("edge") != line.npos) {
				if (have_resize) {
				std::cout<<"size of adj_matrix:"<<num_nodes<<std::endl;
				resize_adj();
				have_resize = false;
				}
        read_edges(myfile);
      }
    } else {
      break;
    }
  }
	std::cout<<"successfully load dataset!!"<<std::endl;
}

void Load_data::read_edges(std::fstream &myfile) {

  std::string line;
  num_edges++;

  // pass
  getline(myfile, line);

  // get source
  getline(myfile, line);
  int source = atoi(line.substr(line.find("e") + 1).c_str());
  //std::cout << "source:" << source << std::endl;

  // get target
  getline(myfile, line);
  int target = atoi(line.substr(line.find("e") + 2).c_str());

  //std::cout << "target:" << target << std::endl;

  adj_matrix[source][target] = 1;
  adj_matrix[target][source] = 1;
  // pass
  getline(myfile, line);
}

void Load_data::read_gml_w(std::string address) {
  std::string line;
  std::fstream myfile;
	bool have_resize = true;

  // open file
  myfile.open(address);

  // pass three line
  getline(myfile, line);
  getline(myfile, line);
  getline(myfile, line);

  while (1) {
    if (getline(myfile, line)) {
      if (line.find("node") != line.npos) {
        read_nodes(myfile);
        continue;
      }
      if (line.find("edge") != line.npos) {
				if (have_resize) {
				resize_adj();
				have_resize = false;
				}
        read_edges_w(myfile);
      }
    } else {
      break;
    }
  }
	std::cout<<"successfully load dataset!!"<<std::endl;
}

void Load_data::read_karate_gml(std::string address){
  std::string line;
  std::fstream myfile;
	bool have_resize = true;

  // open file
  myfile.open(address);

  // pass three line
  getline(myfile, line);
  getline(myfile, line);
  getline(myfile, line);

  while (1) {
    if (getline(myfile, line)) {
      if (line.find("node") != line.npos) {
        read_karate_nodes(myfile);
        continue;
      }
      if (line.find("edge") != line.npos) {
				if (have_resize) {
				std::cout<<"size of adj_matrix:"<<num_nodes<<std::endl;
				resize_adj();
				have_resize = false;
				}
        read_karate_edges(myfile);
      }
    } else {
      break;
    }
  }
	std::cout<<"successfully load dataset!!"<<std::endl;
}

void Load_data::read_nodes(std::fstream &myfile) {
  num_nodes++;
  std::string line;

  // pass
  getline(myfile, line);

  // get id
  getline(myfile, line);
  int id = atoi(line.substr(line.find("d") + 1).c_str());

  // get label
  getline(myfile, line);
  int pos = line.find("\"") + 1;
  std::string label = line.substr(pos, line.find("\"", pos) - pos);

  // insert into graph
  graph.insert(std::pair<int, std::string>(id, label));

  // pass
  getline(myfile, line);
}

void Load_data::read_karate_nodes(std::fstream &myfile){
  num_nodes++;
  std::string line;

  // pass
  getline(myfile, line);

  // get id
  getline(myfile, line);
  int id = atoi(line.substr(line.find("d") + 1).c_str());

	std::string label = line.substr(line.find("d") + 1).c_str();
  // insert into graph
  graph.insert(std::pair<int, std::string>(id, label));

  // pass
  getline(myfile, line);
}

void Load_data::read_karate_edges(std::fstream &myfile) {

  std::string line;
  num_edges++;

  // pass
  getline(myfile, line);

  // get source
  getline(myfile, line);
  int source = atoi(line.substr(line.find("e") + 1).c_str())-1;
  //std::cout << "source:" << source << std::endl;

  // get target
  getline(myfile, line);
  double target = atoi(line.substr(line.find("e") + 2).c_str())-1;

  //std::cout << "target:" << target << std::endl;

  adj_matrix[source][target] = 1;
  adj_matrix[target][source] = 1;
  // pass
  getline(myfile, line);
}
void Load_data::read_edges_w(std::fstream &myfile) {

  std::string line;
  num_edges++;

  // pass
  getline(myfile, line);

  // get source -1
  getline(myfile, line);
  int source = atoi(line.substr(line.find("e") + 1).c_str());
  std::cout << "source:" << source << std::endl;

  // get target -1
  getline(myfile, line);
  int target = atoi(line.substr(line.find("e") + 2).c_str());

  // get value
  getline(myfile, line);
  std::cout << "target:" << target << std::endl;
  double value = atod(line.substr(line.find("e") + 1).c_str());
  std::cout<< "value:" <<value<<std::endl;
	adj_matrix[source][target] = value;
	adj_matrix[target][source] = value;
  // pass
  getline(myfile, line);
}

void Load_data::resize_adj() {
  adj_matrix.resize(num_nodes);
  for (int i = 0; i < num_nodes; i++) {
    adj_matrix[i].resize(num_nodes);
  }
  std::cout << "successfully built adj_matrix!" << std::endl;
}

std::vector<std::vector<double>> Load_data::get_adj() { return adj_matrix; }
std::unordered_map<int, std::string> Load_data::get_graph() { return graph; }

void Load_data::show_adjmatrix() {
  for (int i = 0; i < num_nodes; i++) {
    for (int j = 0; j < num_nodes; j++) {
      std::cout << adj_matrix[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Load_data::show_graph(){
				auto iter = graph.begin();
				while (iter!=graph.end()) {
								std::cout<<iter->first<<" "<<iter->second<<std::endl;
								iter++;
				}
}
