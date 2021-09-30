/*
Subject : C++ cache tag model.
Date    : 1/12/2018
Author  : Bharath (bharath.malalurrao@lgepartner.com) 

*/

#ifndef CACHE_MODEL_H
#define CACHE_MODEL_H
  
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <array>
#include "nmp_defines.h"

class Cache_model {

  public:

    Cache_model (sim_t* p_sim, int tl_idx, int num_tlt,
                 uint32_t cache_sets, uint32_t cache_ways, uint32_t cache_linesz);
    ~Cache_model ();

    sim_t* sim;
    uint32_t tl_idx;  
    uint32_t num_tlt;

    vector <vector <bool> >     cache_way_valid;
    vector <vector <bool> >     cache_plru;
    vector <vector <uint32_t> > cache_tag_addr;

    uint32_t cache_sets;
    uint32_t cache_ways;
    uint32_t cache_linesz;

    uint32_t cache_line_bits;
    uint32_t cache_set_bits;   
    uint32_t cache_hit_cnt;   
    uint32_t cache_miss_cnt;   
    uint32_t cache_req_cnt; 

    void cache_update(uint32_t addr); 
    void cache_set_plru(uint32_t set, uint32_t way); 
};  


#endif
