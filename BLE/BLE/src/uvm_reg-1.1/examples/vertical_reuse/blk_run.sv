// 
// -------------------------------------------------------------
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
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

`include "apb.sv"
`include "blk_reg_pkg.sv"
`include "blk_pkg.sv"
`include "blk_top.sv"

program tb;

import ovm_pkg::*;
import uvm_reg_pkg::*;
import blk_reg_pkg::*;
import blk_pkg::*;

`include "blk_testlib.sv"


class dut_reset_seq extends ovm_sequence;

   function new(string name = "dut_reset_seq");
      super.new(name);
   endfunction

   `ovm_object_utils(dut_reset_seq)
   
   virtual task body();
      blk_top.rst = 1;
      repeat (5) @(negedge blk_top.clk);
      blk_top.rst = 0;
   endtask
endclass


initial
begin
   static blk_env env = new("env");

   //ovm_config_db#(apb_vif)::set(env, "apb", "vif", $root.blk_top.apb0);
   ovm_container #(apb_vif) vif = new;
   vif.val = $root.blk_top.apb0;
   set_config_object("env.apb","vif",vif,0);

   ovm_top.set_report_id_action("CFGNTS",OVM_NO_ACTION);


   run_test();
end

endprogram
