/******************************************************************************
 * Memember functions for data structure VerilogTestbenchOption
 ******************************************************************************/
#include "vtr_assert.h"
#include "vtr_log.h"

#include "verilog_testbench_options.h"

/* begin namespace openfpga */
namespace openfpga {

/**************************************************
 * Public Constructors
 *************************************************/
VerilogTestbenchOption::VerilogTestbenchOption() {
  output_directory_.clear();
  fabric_netlist_file_path_.clear();
  reference_benchmark_file_path_.clear();
  print_preconfig_top_testbench_ = false;
  print_formal_verification_top_netlist_ = false;
  print_top_testbench_ = false;
  simulation_ini_path_.clear();
  explicit_port_mapping_ = false;
  include_signal_init_ = false;
  default_net_type_ = VERILOG_DEFAULT_NET_TYPE_NONE;
  embedded_bitstream_hdl_type_ = EMBEDDED_BITSTREAM_HDL_MODELSIM;
  time_unit_ = 1E-3;
  time_stamp_ = true;
  verbose_output_ = false;
}

/**************************************************
 * Public Accessors 
 *************************************************/
std::string VerilogTestbenchOption::output_directory() const {
  return output_directory_;
}

std::string VerilogTestbenchOption::fabric_netlist_file_path() const {
  return fabric_netlist_file_path_;
}

std::string VerilogTestbenchOption::reference_benchmark_file_path() const {
  return reference_benchmark_file_path_;
}

bool VerilogTestbenchOption::print_formal_verification_top_netlist() const {
  return print_formal_verification_top_netlist_;
}

bool VerilogTestbenchOption::print_preconfig_top_testbench() const {
  return print_preconfig_top_testbench_;
}

bool VerilogTestbenchOption::print_top_testbench() const {
  return print_top_testbench_;
}

bool VerilogTestbenchOption::fast_configuration() const {
  return fast_configuration_;
}

bool VerilogTestbenchOption::print_simulation_ini() const {
  return !simulation_ini_path_.empty();
}

std::string VerilogTestbenchOption::simulation_ini_path() const {
  return simulation_ini_path_;
}

bool VerilogTestbenchOption::explicit_port_mapping() const {
  return explicit_port_mapping_;
}

bool VerilogTestbenchOption::include_signal_init() const {
  return include_signal_init_;
}

bool VerilogTestbenchOption::no_self_checking() const {
  return reference_benchmark_file_path_.empty();
}

e_verilog_default_net_type VerilogTestbenchOption::default_net_type() const {
  return default_net_type_;
}

float VerilogTestbenchOption::time_unit() const {
  return time_unit_;
}

e_embedded_bitstream_hdl_type VerilogTestbenchOption::embedded_bitstream_hdl_type() const {
  return embedded_bitstream_hdl_type_; 
}

bool VerilogTestbenchOption::time_stamp() const {
  return time_stamp_;
}

bool VerilogTestbenchOption::verbose_output() const {
  return verbose_output_;
}

/******************************************************************************
 * Private Mutators
 ******************************************************************************/
void VerilogTestbenchOption::set_output_directory(const std::string& output_dir) {
  output_directory_ = output_dir;
}

void VerilogTestbenchOption::set_fabric_netlist_file_path(const std::string& fabric_netlist_file_path) {
  fabric_netlist_file_path_ = fabric_netlist_file_path;
}

void VerilogTestbenchOption::set_reference_benchmark_file_path(const std::string& reference_benchmark_file_path) {
  reference_benchmark_file_path_ = reference_benchmark_file_path;
  /* Chain effect on other options: 
   * Enable/disable the print_preconfig_top_testbench and print_top_testbench
   */
  set_print_preconfig_top_testbench(print_preconfig_top_testbench_); 
  set_print_top_testbench(print_top_testbench_); 
}
 
void VerilogTestbenchOption::set_print_formal_verification_top_netlist(const bool& enabled) {
  print_formal_verification_top_netlist_ = enabled;
}

void VerilogTestbenchOption::set_fast_configuration(const bool& enabled) {
  fast_configuration_ = enabled;
}

void VerilogTestbenchOption::set_print_preconfig_top_testbench(const bool& enabled) {
  print_preconfig_top_testbench_ = enabled
                                 && (!reference_benchmark_file_path_.empty());
  /* Enable print formal verification top_netlist if this is enabled */
  if (true == print_preconfig_top_testbench_) {
    if (false == print_formal_verification_top_netlist_) { 
      VTR_LOG_WARN("Forcely enable to print top-level Verilog netlist in formal verification purpose as print pre-configured top-level Verilog testbench is enabled\n");
      print_formal_verification_top_netlist_ = true;
    }
  }
}

void VerilogTestbenchOption::set_print_top_testbench(const bool& enabled) {
  print_top_testbench_ = enabled && (!reference_benchmark_file_path_.empty());
}

void VerilogTestbenchOption::set_print_simulation_ini(const std::string& simulation_ini_path) {
  simulation_ini_path_ = simulation_ini_path;
}

void VerilogTestbenchOption::set_explicit_port_mapping(const bool& enabled) {
  explicit_port_mapping_ = enabled;
}

void VerilogTestbenchOption::set_include_signal_init(const bool& enabled) {
  include_signal_init_ = enabled;
}

void VerilogTestbenchOption::set_default_net_type(const std::string& default_net_type) {
  /* Decode from net type string */;
  if (default_net_type == std::string(VERILOG_DEFAULT_NET_TYPE_STRING[VERILOG_DEFAULT_NET_TYPE_NONE])) {
    default_net_type_ = VERILOG_DEFAULT_NET_TYPE_NONE;
  } else if (default_net_type == std::string(VERILOG_DEFAULT_NET_TYPE_STRING[VERILOG_DEFAULT_NET_TYPE_WIRE])) {
    default_net_type_ = VERILOG_DEFAULT_NET_TYPE_WIRE;
  } else {
    VTR_LOG_WARN("Invalid default net type: '%s'! Expect ['%s'|'%s']\n",
                 default_net_type.c_str(),
                 VERILOG_DEFAULT_NET_TYPE_STRING[VERILOG_DEFAULT_NET_TYPE_NONE],
                 VERILOG_DEFAULT_NET_TYPE_STRING[VERILOG_DEFAULT_NET_TYPE_WIRE]);
  }
}

void VerilogTestbenchOption::set_embedded_bitstream_hdl_type(const std::string& embedded_bitstream_hdl_type) {
  /* Decode from HDL type string */;
  if (embedded_bitstream_hdl_type == std::string(EMBEDDED_BITSTREAM_HDL_TYPE_STRING[NUM_EMBEDDED_BITSTREAM_HDL_TYPES])) {
    embedded_bitstream_hdl_type_ = NUM_EMBEDDED_BITSTREAM_HDL_TYPES;
  } else if (embedded_bitstream_hdl_type == std::string(EMBEDDED_BITSTREAM_HDL_TYPE_STRING[EMBEDDED_BITSTREAM_HDL_IVERILOG])) {
    embedded_bitstream_hdl_type_ = EMBEDDED_BITSTREAM_HDL_IVERILOG;
  } else if (embedded_bitstream_hdl_type == std::string(EMBEDDED_BITSTREAM_HDL_TYPE_STRING[EMBEDDED_BITSTREAM_HDL_MODELSIM])) {
    embedded_bitstream_hdl_type_ = EMBEDDED_BITSTREAM_HDL_MODELSIM;
  } else {
    VTR_LOG_WARN("Invalid embedded bitstream type: '%s'! Expect ['%s'|'%s'|'%s']\n",
                 embedded_bitstream_hdl_type.c_str(),
                 EMBEDDED_BITSTREAM_HDL_TYPE_STRING[NUM_EMBEDDED_BITSTREAM_HDL_TYPES],
                 EMBEDDED_BITSTREAM_HDL_TYPE_STRING[EMBEDDED_BITSTREAM_HDL_IVERILOG],
                 EMBEDDED_BITSTREAM_HDL_TYPE_STRING[EMBEDDED_BITSTREAM_HDL_MODELSIM]);
  }
}

void VerilogTestbenchOption::set_time_unit(const float& time_unit) {
  time_unit_ = time_unit;
}


void VerilogTestbenchOption::set_time_stamp(const bool& enabled) {
  time_stamp_ = enabled;
}

void VerilogTestbenchOption::set_verbose_output(const bool& enabled) {
  verbose_output_ = enabled;
}

} /* end namespace openfpga */
