#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>
#include "graph.h"
#include "Bezier.h"
void Graph::trace(int root_id){
    std::vector<int> L;
    L.push_back(root_id);
    int i = 0;
    int seg_size;
    do{
        seg_size = L.size();
        int u = L[i];
        for(int j = 0; j < nodes[u].edge_list.size(); j++){
            
            Edge e = nodes[u].edge_list[j];
            int v = e.dest_id;
            
            nodes[v].slack = e.slack;
            nodes[v].flag = 1;
            
            // v belongs to existing segment
            if(e.slack == nodes[u].slack && nodes[u].flag){
                nodes[v].seg_num = nodes[u].seg_num;
                seg[nodes[v].seg_num].push_back(v);
                nodes[u].flag = 0;
                L.push_back(v);
            }
            else{// new segment
                nodes[v].seg_num = seg.size();
                std::vector<int> s;
                s.push_back(u);
                s.push_back(v);
                seg.push_back(s);
                root_list.push_back(v);
                //delete edge?
            }     
        }
        i++;
    }while(seg_size != L.size());    
};
    
    
void Graph::segmentation(){
    
    while(!root_list.empty()){
        int next_root = root_list.back();
        root_list.pop_back();
        trace(next_root);
    }
    //print_seg();
};

int Graph::smooth(char** argv){
    std::ofstream outf(argv[2]);

    if(!outf){
        std::cerr <<"Failed to open output file"<<std::endl;
        return 1;
    }  
    
    int num_seg = seg.size();
    outf<< num_seg << std::endl;

    for(int i=0; i<num_seg; i++){
       int gate; double s; 
       find_critical(i, &gate, &s);
       int head, tail;
       head = seg[i].front(); tail = seg[i].back();
       outf<< "(" <<nodes[head].gate_id << ", "<< nodes[tail].gate_id<< ")" << std::endl;
       outf<< gate << " "<< std::fixed << std::setprecision(3) << s << std::endl;
    }    
    
    outf.close();
    return 0;
};

void Graph::find_critical(int seg_id, int* gate, double* s){
    int n = seg[seg_id].size();
    
    Bezier **B = new Bezier*[n];
    for(int i = 0; i < n; i++)
        B[i] = new Bezier[n];
    // fill in  boundary 
    for(int i = 0; i < n; i++){
        B[0][i].m_x = nodes[seg[seg_id][i]].x;  
        B[0][i].m_y = nodes[seg[seg_id][i]].y;
    }
    // Sampling
    double t = 0.0;
    //double step = 1 / (double)(n-1);
    double smax = 0.0;
    int max_id;
    for(unsigned int k = 0; k < n; k++){
        
        // dynamic programming
        for(int i = 1; i < n; i++){
            for(int j = 0; j < n-i; j++)
                B[i][j] = Combine(B[i-1][j], B[i-1][j+1], t);
            
        }
        //std::cout<< B[n-1][0].m_x << " " << B[n-1][0].m_y <<std::endl;
        // compute smoothness
        double smo = fabs(B[n-1][0].m_x - B[0][k].m_x) + fabs(B[n-1][0].m_y - B[0][k].m_y);
        if(smo > smax){
            smax = smo;
            max_id = seg[seg_id][k];
        }
        //std::cout<< nodes[k].gate_id << " " << smo <<std::endl;
        //t += step;
        t = (k+1)/(double)(n-1);
    }
    *s = smax;
    *gate = nodes[max_id].gate_id;
    
    for(int i = 0; i < n; i++)
        delete [] B[i];
    delete [] B;

}    
int Graph::parser(char** argv){
    std::ifstream inf(argv[1]);
    if(!inf){
        std::cerr <<"Failed to open input file"<<std::endl;
        return 1;
    }  
    
    int num_gate;
    inf >> num_gate;
    std::string garbage;    
    Node n; int gid, x, y;
    for(int i=0; i<num_gate; i++){

       inf >> gid;
       inf >> garbage;
       inf >> garbage;
       inf >> x;
       inf >> y;
       n.gate_id = gid;
       n.x = x;
       n.y = y;
       nodes.push_back(n);
       nodes_idx.push_back(gid);
       num_in.push_back(0);
    }    
    
    Edge e; 
    int head, tail, unused;
    std::vector<int>::iterator it;
    int num_edge;
    inf >> num_edge;
    for(int i=0; i<num_edge; i++){
        
        inf >> unused; inf >> head; inf >> tail; inf >> e.slack;
        // find the tail of the edge
        it = std::find(nodes_idx.begin(), nodes_idx.end(), tail);
        e.dest_id = it - nodes_idx.begin();
        num_in[e.dest_id]++;
        // record index of head of the edge
        it = std::find(nodes_idx.begin(), nodes_idx.end(), head);
        
        int index = it - nodes_idx.begin();
        nodes[index].edge_list.push_back(e);
    } 
    // find the node with no incoming edges
    // put it to segment 0
    it = std::find(num_in.begin(), num_in.end(), 0);
    int index = it - num_in.begin();
    root_list.push_back(index);
    std::vector<int> s;
    s.push_back(index);
    seg.push_back(s);
    nodes[index].seg_num = 0;
    nodes[index].slack = (nodes[index].edge_list)[0].slack;
    return 0;
    //std::cout<<"first root "<< root_list.back()<<std::endl;
};
/*
void Graph::output(){
};*/
