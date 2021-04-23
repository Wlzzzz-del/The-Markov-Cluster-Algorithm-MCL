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
  void read_edges(std::fstream &myfile); // process edges
  void resize_adj();
  std::vector<std::vector<int>> adj_matrix;
  std::unordered_map<int, std::string> graph;

public:
  Load_data(){};
  ~Load_data(){};
  void read_gml(std::string address);
  std::vector<std::vector<int>> get_adj();
  std::unordered_map<int, std::string> get_graph();
};

void Load_data::read_gml(std::string address) {
  std::string line;
  std::fstream myfile;

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
      resize_adj(); // resize the adj_matrix
      if (line.find("edge") != line.npos) {
        read_edges(myfile);
        continue;
      }
    } else {
      break;
    }
  }
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

void Load_data::read_edges(std::fstream &myfile) {

  std::string line;
  num_edges++;

  // pass
  getline(myfile, line);

  // get source
  getline(myfile, line);
  int source = atoi(line.substr(line.find("e") + 1).c_str());
  std::cout << "source:" << source << std::endl;

  // get target
  getline(myfile, line);
  int target = atoi(line.substr(line.find("e") + 2).c_str());

  // get value
  getline(myfile, line);
  std::cout << "target:" << target << std::endl;
  int value = atoi(line.substr(line.find("e") + 1).c_str());

  // pass
  getline(myfile, line);
}

void Load_data::resize_adj() {

  adj_matrix.resize(num_nodes);
  for (int i = 0; i < num_nodes; i++) {
    adj_matrix.resize(num_nodes);
  }
}

std::vector<std::vector<int>> Load_data::get_adj() { return adj_matrix; }
std::unordered_map<int, std::string> Load_data::get_graph() { return graph; }

