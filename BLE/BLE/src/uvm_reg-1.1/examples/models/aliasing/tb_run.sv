// 
// -------------------------------------------------------------
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
//    Copyright 2010-2011 Cadence Design Systems, Inc.
//    All Rights Reserved Worldwide
// 
//    Licensed under the Apache License, Version 2.0 (the
//    "License"); you may not use this file except in
//    compliance with the License.  You may obtain a copy of
//    the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in
//    writing, software distributed under the License is
//    distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//    CONDITIONS OF ANY KIND, either express or implied.  See
//    the License for the specific language governing
//    permissions and limitations under the License.
// -------------------------------------------------------------
// 

`include "ovm_macros.svh"
`include "uvm_reg_macros.svh"

program tb;

import ovm_pkg::*;
import uvm_reg_pkg::*;

`include "regmodel.sv"
`include "tb_env.sv"


class tb_test extends ovm_test;

   function new(string name = "tb_test", ovm_component parent = null);
      super.new(name, parent);
   endfunction

   virtual task run();
      tb_env env;
      uvm_status_e   status;
      uvm_reg_data_t data;

      ovm_test_done.raise_objection(this);
      
      if (!$cast(env, ovm_top.find("env")) || env == null) begin
         `ovm_fatal("test", "Cannot find tb_env");
      end

      env.regmodel.reset();

      begin
         uvm_reg_sequence seq;

         seq = uvm_reg_bit_bash_seq::type_id::create("seq");
         seq.model = env.regmodel;
         seq.start(env.bus.sqr);
         seq.wait_for_sequence_state(FINISHED);

         `ovm_info("Test", "Verifying aliasing...", OVM_NONE);
         env.regmodel.Ra.write(status, 32'hDEADBEEF, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
         env.regmodel.Rb.write(status, 32'h87654320, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
         
         env.regmodel.Ra.F1.write(status, 8'hA5, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
         env.regmodel.Rb.F1.write(status, 8'hC3, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
         
         env.regmodel.Ra.F2.write(status, 8'hBD, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
         env.regmodel.Rb.F2.write(status, 8'h2A, .parent(seq));
         env.regmodel.mirror(status, UVM_CHECK, .parent(seq));
      end
      ovm_test_done.drop_objection(this);
   endtask
endclass


initial begin
   tb_env env;
   tb_test test;
   ovm_report_server svr;
   
   env = new("env");
   test = new("test");

   svr = _global_reporter.get_report_server();
   svr.set_max_quit_count(10);
   
   run_test();
end

endprogram