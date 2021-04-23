#include <vector>
#include <map>
class mcl
{
				private:
								int e;
								int r;
								int if_loop;
								int num_nodes;
								int times;
								std::vector<std::vector<double>> adj;
								std::vector<std::vector<double>> matrix;
								std::map<int, std::vector<int>> society;
								std::map<int, int> dictionary;
								void self_loop();
								void expansion();
								void inflation();
								void normalization();
								void get_power(int x, int y, std::vector<std::vector<double>> &temp);
								void get_result();
				public:
								mcl(int e, int r,bool if_loop, std::vector<std::vector<double>> adj, int times){
												this->e = e;
												this->times = times;
												this->r = r;
												this->if_loop= if_loop;
												this->adj = adj;
												this->matrix = adj;
												this->num_nodes = adj.size();
												if(if_loop){
																self_loop();
												}

								}
								void run();
								void show();
								std::map<int, std::vector<int>> get_society();
								std::map<int, int> get_dictionary();


};

