#ifndef GRAPH_H
#define GRAPH_H
//#include "Bezier.h"
#include <vector>

class Edge {
    public:
        double slack;
        int dest_id;
        Edge():slack(0.0), dest_id(0)
        {
        }
        void print(){
           std::cout<<slack<<" "<<dest_id<<" "<<std::endl;
        }
};

class Node {
    public:
        int gate_id;
        int seg_num; 
        double slack;
        int flag;
        //Bezier ctrl_pnt;
        double x;
        double y;
        std::vector<Edge> edge_list;
        Node():gate_id(0), seg_num(0), slack(0.0), flag(1), x(0), y(0)
        {
        }
        void print(){
           std::cout<<gate_id<<" "<<x<<" "<<y<<" "<<std::endl;
           for(int i=0; i<edge_list.size(); i++)
               edge_list[i].print();
        }
};

class Graph{
    public:
        std::vector<Node> nodes;
        std::vector<int> nodes_idx;
        std::vector<int> root_list;
        std::vector<int> num_in;
        
        //std::vector<std::vector<Bezier> > seg;
        std::vector<std::vector<int> > seg;
        //int num_seg = 0; 
        int parser(char** argv);
        void trace(int root_id);
        void segmentation();
        int smooth(char** argv);
        void find_critical(int seg_id, int* gate_id, double* s);
        void print_seg(){
            for(int i=0; i<seg.size(); i++){
                std::cout<<"Seg"<<i<<std::endl;
                for(int j=0; j<seg[i].size(); j++)
                    std::cout<<nodes[seg[i][j]].gate_id<<" ";
                std::cout<<std::endl;
            }
        }    
        //void output();

};
#endif
