/* 
Suject: C++ model for NMC registers. 
        It is the reference model for verification.
Date: 9/20/2016
Author: Jenny Zhang 
*/
#ifndef NMC_MODEL_H
#define NMC_MODEL_H
  
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <cstdint>
#include <array>
#include <thread>             
#include <mutex>              
#include <condition_variable> 
#include <chrono>
#include <atomic>

#include "nmp_defines.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;


//#define BLOBS 3
//#define NUM_MB 3
//#define BANKS 16
//#define BANK_SIZE 1024
#define MAX_NUM_MB 4
#define BANKS 2
#define BANK_SIZE 8192
#define TLTS    128  
#define CLK 10  

#define DDR_SIZE 1024*1024*2  // 2 MB

#define LNE_MAJ_VER 2
#define LNE_MIN_VER 5

static vector<uint16_t> ddr_mem;

class processor_t;
class sim_t;

class Nmc_model
{
 public:
 
    Nmc_model (string test_type,sim_t* p_sim, int tl_idx, int num_tlt, bool en_sdk, bool blobs_all);
  ~Nmc_model ();
    
 sim_t* sim;
 uint32_t tl_idx=1;  //overwriten in sim.cc
 uint32_t num_tlt=1;  //overwriten in sim.cc
 bool dbg;
 bool en_sdk=false;
 bool blobs_all=false; 


 struct Dt_Type {
     int8_t  val_8b;
     int16_t val_16b;
     int32_t val_32b;
     int64_t val_64b;
 }; 
 
 void load(processor_t* p, uint32_t tlt, uint32_t adr_ddr, uint32_t adr_mb, uint16_t n_byts, uint8_t t_mem, uint32_t elmsize); 
 void store(processor_t* p, uint32_t tlt, uint32_t adr_ddr, uint32_t adr_mb, uint16_t n_byts, uint8_t t_mem); 
 void load3d(processor_t* p, uint32_t tlt, uint32_t adr_ddr, uint32_t adr_mb, uint16_t sig_done,uint32_t n_byts, uint8_t t_mem,
             uint32_t n_rows, uint32_t n_chans, uint32_t b_rowskip, uint32_t b_chskip, uint32_t mcast,
             uint32_t lcl_rowskip, uint32_t lcl_chskip, uint32_t zero_fill, uint32_t elmsize); 
 void store3d(processor_t* p, uint32_t tlt, uint32_t adr_ddr, uint32_t adr_mb, uint16_t sig_done,uint32_t n_byts, uint8_t t_mem,
              uint32_t n_rows, uint32_t n_chans, uint32_t b_rowskip, uint32_t b_chskip, uint32_t mcast,
              uint32_t lcl_rowskip, uint32_t lcl_chskip, uint32_t zero_fill); 
 void activate(uint32_t tlt, uint32_t src_adr, uint32_t dst_adr, uint32_t in_size, uint32_t act_type, uint32_t alpha);
 void pool(uint32_t tlt, uint32_t src_adr, uint32_t dst_adr, uint32_t xsize, uint32_t ysize, uint32_t p_type, uint32_t kx, uint32_t ky, uint32_t sx, uint32_t sy);
 void percpt(uint32_t tlt, uint32_t din_adr, uint32_t dout_adr, uint32_t wgt_adr, uint32_t in_size, uint32_t out_size,
             uint32_t act_type, uint32_t alpha, bool prcpt_type, uint32_t be);
 void veop(uint32_t tlt, uint32_t src1_adr, uint32_t src2_adr, uint32_t dst_adr, uint32_t vec_size, uint32_t num_vec,
           uint32_t src2_type, uint32_t vop);
 void conv3d(uint32_t tlt, uint32_t src_adr, uint32_t dst_adr, uint32_t wgt_adr, uint32_t ba_addr, uint32_t conv_typ, 
             uint32_t ofm, uint32_t ifm, uint32_t out_rows, uint32_t out_cols, uint32_t kx, uint32_t ky, uint32_t strd,
             uint32_t in_rows, uint32_t in_cols, uint32_t bias, uint32_t act, uint32_t alpha, uint32_t be);
 void pwait(processor_t* p, uint32_t tlt, uint32_t domain, uint32_t mask);
 void signal(processor_t* p, uint32_t tlt, uint32_t domain, uint32_t sop, uint32_t mask); 
 void halt(processor_t* p, uint32_t tlt, uint32_t hop, uint32_t mask);
 void cpy2stp(processor_t* p, uint32_t tlt, uint32_t src_adr, uint32_t n_byts);
 void cnfg_mb(uint32_t tlt, uint32_t cfg_val);
 void cnfg_frmt(uint32_t tlt, uint32_t cfg_val);
 
 void read_scn_file(string scn_file);
 void MblbDump(int num_tlt, string cmd);
 void DmemDump(int num_tlt, string cmd);
 void RegsDump(uint32_t num_tlt, int cnt, string cmd);
 void tl_regs_updt();
 void MemInit(int num_tlt, bool en_sdk);
 void mem_updt(int tlt,int targ,int dq_v,int wq_v);
 void read_ddr_init();
 Dt_Type cal_conv(uint32_t wgt_adr, uint32_t st_adr, uint32_t kx, uint32_t ky,uint32_t i_ifm, 
                  uint32_t i_ofm,uint32_t tlt, uint32_t in_rows,uint32_t in_cols,uint32_t dil,
                  uint32_t stack_conv, uint32_t be, uint32_t dst_adr, uint32_t ba_addr, uint32_t bias, uint32_t act);
 int16_t  p_cal(uint32_t tlt, uint32_t p_type, vector <int16_t> pl_v);
 int16_t  sig_cal(uint32_t tlt, int16_t x);
 int16_t act_relu(int16_t data_v);
 int16_t act_relu6(uint32_t tlt, int16_t data_v, string cmd_type);
 int16_t act_prelu(uint32_t tlt, int16_t data_v);
 int16_t get16bit(uint32_t tlt,uint32_t mb_v,uint32_t adr); 
 void    set16bit(uint32_t tlt,uint32_t mb_v,uint32_t adr,int16_t d_in);
 int32_t get32bit(uint32_t tlt,uint32_t mb_v,uint32_t adr); 
 void    set32bit(uint32_t tlt,uint32_t mb_v,uint32_t adr,int32_t d_in);
 int64_t get48bit(uint32_t tlt,uint32_t mb_v,uint32_t adr); 
 void    set48bit(uint32_t tlt,uint32_t mb_v,uint32_t adr,int64_t d_in);
 void    mb_adr_chk(uint32_t addr,uint8_t t_mem);
 void    dmem_adr_chk(uint32_t addr);
 void    chk_non_zero(uint32_t value);
 void    t_mem_chk(uint8_t t_mem);
 void    dmem_ldst_chk(uint8_t t_mem);
 void    mb_cfg_chk(string cmd, uint32_t tlt);
 int16_t vec_offs(uint32_t tlt, uint32_t src1_adr, uint32_t src2_adr, bool src2_type);
 int16_t vec_add(uint32_t tlt, uint32_t num_vec, uint32_t vec_size, uint32_t src1_adr, uint32_t src2_adr, bool src2_type); 
 int16_t vec_norm(uint32_t tlt, uint32_t src1_adr, uint32_t src2_adr, bool src2_type);
 int16_t vec_mul(uint32_t tlt, uint32_t src1_adr, uint32_t src2_adr);  
 int64_t scale(uint32_t tlt,int64_t val,string cmd_type);
 int64_t saturate(uint32_t tlt,int64_t val,string cmd_type);
 int64_t truncate(uint32_t tlt,int64_t val,string cmd_type);
 int64_t nmp_round(int64_t val,int32_t q_val);

 ofstream cmem_file[TLTS];				
 ifstream myfile[TLTS];
 ofstream cregs_file;
 
 int8_t    mb[TLTS][MAX_NUM_MB][BANKS*BANK_SIZE];
 int8_t    dmem[TLTS][RC_DMEM_SIZE];
 unordered_map <string, atomic<uint32_t>> tl_regs;

 // Variables added to extract statistics
 unordered_map <string, array<uint32_t,TLTS>> stat_dme_byt_count;
 unordered_map <string, array<uint32_t,TLTS>> stat_pool_byt_count;
 unordered_map <string, array<uint32_t,TLTS>> stat_act_byt_count;
 unordered_map <string, array<uint32_t,TLTS>> stat_conv_byt_count;
 unordered_map <string, array<uint32_t,TLTS>> stat_veop_byt_count;
 unordered_map <string, array<uint32_t,TLTS>> stat_percpt_byt_count;
 uint32_t stat_pool_cyc_count[TLTS];
 uint32_t stat_act_cyc_count[TLTS];
 uint32_t stat_conv_cyc_count[TLTS];
 uint32_t stat_veop_cyc_count[TLTS];
 uint32_t stat_percpt_cyc_count[TLTS];
 uint32_t stat_pool_count[TLTS];
 uint32_t stat_act_count[TLTS];
 uint32_t stat_conv_count[TLTS];
 uint32_t stat_veop_count[TLTS];
 uint32_t stat_percpt_count[TLTS];

 private:
  string cmd_type,pl_type;
  vector <string> scn_ops;

  condition_variable cv[TLTS];
  mutex mtx[TLTS];

  //Global registers
  mutex ts_mtx;
  mutex gs_mtx;
  
  uint32_t dt_size[TLTS];
  uint32_t wgt_size[TLTS];
  uint32_t wgt_map[TLTS];
  uint32_t wq_val[TLTS];
  uint32_t dq_val[TLTS];
  uint32_t bq_val[TLTS];
  uint8_t  lscale[TLTS];
  bool     sat_en[TLTS]; 
  uint32_t pl_avg_divisor_q[TLTS];
  
  atomic<uint32_t> R[32][TLTS];
  uint32_t TR[17];
  uint32_t mb_cfg[16][TLTS]={{0}};
  uint32_t dump_cnt[TLTS]={0};
  ofstream f_mb_cpp;
  ofstream f_dmem_cpp;
  ofstream f_mb_tlt_cpp[TLTS];
  ofstream f_dmem_tlt_cpp[TLTS];
  ofstream f_cregs_tlt_cpp[TLTS];


  
 };


#endif
  
