#include "mcl.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>
#include <map>

/*
 * add self_loop
 */
void mcl::self_loop(){
				for (int i=0; i<num_nodes; i++) {
				this->adj[i][i] = 1;
				}
}

/*
 * normalize adj_matrix
 */
void mcl::normalization(){
				// sum of every raw
				std::vector<double> sum_list(num_nodes);
				double sum = 0;
				for (int i=0; i<this->num_nodes; i++,sum=0) {
								for (int j=0; j<this->num_nodes; j++) {
								sum += this->adj[i][j];
								}
								sum_list[i] = sum;
				}
				// v_ij / sum
				for (int i=0; i<this->num_nodes; i++) {
				for (int j=0; j<this->num_nodes; j++) {
								double value = this->adj[i][j] / sum_list[i];
				this->adj[i][j] = value;
				}
				}
}

/*
 * show result
 */
void mcl::show(){
				for (int i=0; i<num_nodes; i++) {
				for (int j=0; j<num_nodes; j++) {
								std::cout<<this->adj[i][j]<<" ";
				}
				std::cout<<std::endl;
				}
				get_result();
}
/*
 * run algrothim
 */
void mcl::run()
{
				int t =0;
				while (t<times) {
				normalization();
				expansion();
				inflation();
				t++;
				}
}
/*
 *  run inflation 
 */
void mcl::inflation(){
				for (int i = 0; i<num_nodes; i++) {
				for (int j=0; j<num_nodes; j++) {
				double temp = this->adj[i][j];
				this->adj[i][j] = pow(temp, this->r);
				}
				}
}

/*
 * expansion 
 */
void mcl::expansion(){
				std::vector<std::vector<double>> temp(adj);
				for (int i = 0; i<num_nodes; i++) {
				for (int j=0; j<num_nodes; j++) {
				get_power(i, j, temp);
				}
				}
}

/*
 * 
 */
void mcl::get_power(int x, int y, std::vector<std::vector<double>> &temp){
				double sum =0;
				for (int i=0; i<num_nodes; i++) {
				sum += temp[i][x]*temp[y][i];
				}
				this->adj[x][y] = sum;
}

/*
 * output result as dict
 */
void mcl::get_result(){
				/*
				 * 初始化数组
				 * temp存储 该点是否已经加入社区
				 * society存储节点-社区的map
				 * result 存放社区编号->社区节点
				 *
				 */
				std::vector<int> temp(34);
				//std::vector<std::vector<int>> society;
				//society.resize(num_nodes);
				std::map<int , int> society;

				// 每行中不为0的节点为一个社区
				// 将这些点通过map映射出社区
				for (int i = 0; i<num_nodes; i++) {
				for (int j = 0; j<num_nodes; j++) {
								if (this->adj[i][j]!=0 && temp[j]!=1) {
												society[j] = i;
												temp[j]=1;
								}
				}
				}
				// 将社区节点加入result中
				std::map<int, int>::iterator iter;
				std::map<int, std::vector<int>> result;
				for (iter = society.begin(); iter != society.end(); iter++) {
								//std::cout<<"节点:"<<iter->first<<" 社区:"<<iter->second;
								if (result.count(iter->second)==0)
								{
												result[iter->second] = {iter->first};
								}
								else {
								result[iter->second].push_back(iter->first);
								}
				}
				// show result
				std::map<int, std::vector<int>>::iterator iter2;
				for (iter2 = result.begin(); iter2 != result.end(); iter2++) {
								std::cout<<"community："<<iter2->first<<" "<<"node:";
								for (int i=0; i<iter2->second.size(); i++) {
												std::cout<<iter2->second[i]<<",";
								}
								std::cout<<std::endl;
				}
				this->society = result;
				this->dictionary = society;

}
std::map<int, std::vector<int>> mcl::get_society() { return this->society; }
std::map<int, int> mcl::get_dictionary() { return this->dictionary; }
