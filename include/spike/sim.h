// See LICENSE for license details.
// File Modified for NMP :
//      For changes look for "Code Added for NMP"

#ifndef _RISCV_SIM_H
#define _RISCV_SIM_H

// Code Added for NMP
//-------------------------------------------------
#include "nmc_model.h"
#include "cache_model.h"
#include "time.h"
#include "nmp_defines.h"
//-------------------------------------------------
#include "processor.h"
#include "devices.h"
#include "debug_module.h"
#include <fesvr/htif.h>
#include <fesvr/context.h>
#include <vector>
#include <string>
#include <memory>

class mmu_t;
class gdbserver_t;

// this class encapsulates the processors and memory in a RISC-V machine.
class sim_t : public htif_t
{
public:
  sim_t(const char* isa, size_t _nprocs, size_t ntls,size_t mem_mb, bool halted, bool en_sdk,
        bool blobs_all, size_t add_mb3, size_t mb_size, size_t mb0_size, size_t mb1_size, size_t mb2_size, size_t mb3_size, size_t dmem_size, const std::vector<std::string>& args);
  ~sim_t();

  // run the simulation to completion
  int run();
  void set_debug(bool value);
  void set_log(bool value);
  void set_histogram(bool value);
  void set_procs_debug(bool value);
  void set_gdbserver(gdbserver_t* gdbserver) { this->gdbserver = gdbserver; }
  const char* get_config_string() { return config_string.c_str(); }
  processor_t* get_core(size_t i) { return procs.at(i); }
  // Code Added for NMP
  //-------------------------------------------------
  bool get_debug() {return debug;}
  void set_mblb_dump(bool value); // To Dump contents of MBLB in the nmc_model
  void set_sdk(bool value); 
  void read_ddr_init();
  
  bool mblb_dump; 
  virtual void dump_mblb(int tl, int tlt, int cnt); // Currently not used
  size_t add_mb3;
  size_t ntls;     // Number of Tiles
  size_t nproctl;  // Number of processors per Tile
  Nmc_model* get_tl(size_t i) { return tls.at(i); }  // returns tile pointer
  Cache_model* get_cic(size_t i) { return cic.at(i); }  // returns CIC pointer
  Cache_model* get_cdc() { return cdc; }  // returns CDC pointer
  virtual void nmp_host_access(bool rw,uint32_t addr,uint32_t data);
  void nmp_dmem_write(uint32_t addr, uint32_t data); 
  size_t get_memsz() { return memsz;}
  bool dbg_msg = false;
  bool ddr_dmp = false;              // At the end of simulation, dump DDR upto ddr_dmp_size
  string stat = "";  // For statistics dump
                                     // ddr_dmp is made 'true' @ read_ddr_init()
  //  uint32_t ddr_dmp_size=0x10000000;  // Set Dump size as 256 MB for layer test.
  clock_t st_sim_tim; 
  clock_t end_sim_tim; 
  clock_t st_dmp_tim; 
  clock_t end_dmp_tim; 
  double  sim_tim;
  double  dmp_tim;
  double  tot_tim;
  //-------------------------------------------------

private:
  char* mem; // main memory
  size_t memsz; // memory size in bytes
  mmu_t* debug_mmu;  // debug port into main memory
  std::vector<processor_t*> procs;
  // Code Added for NMP
  //-------------------------------------------------
  std::vector<Nmc_model*> tls;     // Tiles
  std::vector<Cache_model*> cic;   // Common Instruction Cache per Tile
  Cache_model* cdc;                // Common Data Cache  
  //-------------------------------------------------
  std::string config_string;
  std::unique_ptr<rom_device_t> boot_rom;
  std::unique_ptr<rtc_t> rtc;
  bus_t bus;
  debug_module_t debug_module;

  processor_t* get_core(const std::string& i);
  void step(size_t n); // step through simulation
  // Code Added for NMP : Made 5000 to 1 
  //-------------------------------------------------
  //static const size_t INTERLEAVE = 5000;
  static const size_t INTERLEAVE = 1;
  //-------------------------------------------------
  static const size_t INSNS_PER_RTC_TICK = 100; // 10 MHz clock for 1 BIPS core
  size_t current_step;
  size_t current_proc;
  bool debug;
  bool log;
  bool histogram_enabled; // provide a histogram of PCs
  gdbserver_t* gdbserver;

  // memory-mapped I/O routines
  bool addr_is_mem(reg_t addr) {
    return addr >= DRAM_BASE && addr < DRAM_BASE + memsz;
  }
  char* addr_to_mem(reg_t addr) { return mem + addr - DRAM_BASE; }
  reg_t mem_to_addr(char* x) { return x - mem + DRAM_BASE; }
  bool mmio_load(reg_t addr, size_t len, uint8_t* bytes);
  bool mmio_store(reg_t addr, size_t len, const uint8_t* bytes);
  void make_config_string();

  // presents a prompt for introspection into the simulation
  void interactive();

  // functions that help implement interactive()
  void interactive_help(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_quit(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run(const std::string& cmd, const std::vector<std::string>& args, bool noisy);
  void interactive_run_noisy(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_run_silent(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_reg(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_fregs(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_fregd(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_pc(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_mem(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_str(const std::string& cmd, const std::vector<std::string>& args);
  void interactive_until(const std::string& cmd, const std::vector<std::string>& args);
  reg_t get_reg(const std::vector<std::string>& args);
  reg_t get_freg(const std::vector<std::string>& args);
  reg_t get_mem(const std::vector<std::string>& args);
  reg_t get_pc(const std::vector<std::string>& args);
  // Code Added for NMP
  //-------------------------------------------------
  void interactive_mb(const std::string& cmd, const std::vector<std::string>& args);
  int8_t get_mb(const std::vector<std::string>& args);
  void interactive_dmem(const std::string& cmd, const std::vector<std::string>& args);
  int8_t get_dmem(const std::vector<std::string>& args);
  const char* nmp_csr_nm[N_NMPCSR] = {"status","cfg0","cfg1","maddr",
                              "mdata","err","sema","id",
                              "p0","p1","p2","p3","p4",
                              "stpcfg0","stpcfg1","pc","cachebase", 
                              "gpr0","gpr1","gpr2","gpr3" 
                             }; 

  const char* nmp_tlreg_nm[16] = {"status","cfg","Tsema","Gsema",
                                 "int_st","int_clr","pf_cnt1","pfcnt2",
                                 "ID_ntlt","int_enset","int_enclr","int_grp",
                                 "gpr0","gpr1","gpr2","gpr3"
                                }; 
  //-------------------------------------------------

  friend class processor_t;
  friend class mmu_t;
  friend class gdbserver_t;
  // Code Added for NMP
  //-------------------------------------------------
  friend class Nmc_model;
  friend class Cache_model;
  //-------------------------------------------------

  // htif
  friend void sim_thread_main(void*);
  void main();

  context_t* host;
  context_t target;
  void reset() { }
  void idle();
  void read_chunk(addr_t taddr, size_t len, void* dst);
  void write_chunk(addr_t taddr, size_t len, const void* src);
  size_t chunk_align() { return 8; }
  size_t chunk_max_size() { return 8; }
};

extern volatile bool ctrlc_pressed;
// Code Added for NMP : has_nmp_error is set when there is programing failure is occured @nmc_model
//-------------------------------------------------
extern volatile bool has_nmp_error;
extern volatile bool error_on_halt;
extern size_t chk_mb_size;
extern size_t chk_mb0_size;
extern size_t chk_mb1_size;
extern size_t chk_mb2_size;
extern size_t chk_mb3_size;
extern size_t num_mblobs;
extern size_t chk_dmem_size;
// CIC Model
extern uint32_t cic_ways  ;
extern uint32_t cic_sets  ;
extern uint32_t cic_linesz;
// CDC Model
extern uint32_t cdc_ways  ;
extern uint32_t cdc_sets  ;
extern uint32_t cdc_linesz;
extern uint32_t cdc_reqsz;
extern uint32_t cdc_reqsz_bits;
//-------------------------------------------------

#endif
