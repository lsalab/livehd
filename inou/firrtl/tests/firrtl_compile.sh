#!/bin/bash
rm -rf ./lgdb
FIRRTL_LEVEL='lo'

pts_long_lec='GCD'

pts_todo_advanced='FPU ICache MemoryController RWSmem Smem Rob ICache
HwachaSequencer RocketCore'

pts_todo=' Shifts PlusAnd RegXor Test4 Test5 Test6 SimpleBitOps Ops
BundleConnect Smem_simple SubModule Coverage AddNot Test3 MaxN Adder4 Adder
ByteSelector Combinational Darken EnableShiftRegister FullAdder Functionality
HiLoMultiplier Life LogShifter Parity ResetShiftRegister Risc Router
ShiftRegister SimpleALU Stack Tbl VecSearch Counter DynamicMemorySearch MaxN
Memo Mul Mux4 RealGCD SingleEvenFilter VecShiftRegister VecShiftRegisterParam
VecShiftRegisterSimple VendingMachine VendingMachineSwitch'

pts='Decrementer TrivialAdd Test1 Test2 NotAnd Trivial Accumulator Flop
Tail RegisterSimple Register TrivialArith GCD_3bits Max2'

pts='LFSR16'
pts='TrivialAdd'


LGSHELL=./bazel-bin/main/lgshell
LGCHECK=./inou/yosys/lgcheck
PATTERN_PATH=./inou/firrtl/tests/proto

if [ ! -f $LGSHELL ]; then
    if [ -f ./main/lgshell ]; then
        LGSHELL=./main/lgshell
        echo "lgshell is in $(pwd)"
    else
        echo "ERROR: could not find lgshell binary in $(pwd)";
    fi
fi

firrtl_test() {
  echo ""
  echo ""
  echo ""
  echo "===================================================="
  echo "LoFIRRTL Full Compilation"
  echo "===================================================="


  for pt in $1
  do
    if [ ! -f ${PATTERN_PATH}/${pt}.${FIRRTL_LEVEL}.pb ]; then
        echo "ERROR: could not find ${pt}.${FIRRTL_LEVEL}.pb in ${PATTERN_PATH}"
        exit 1
    fi

    ${LGSHELL} "inou.firrtl.tolnast files:${PATTERN_PATH}/${pt}.${FIRRTL_LEVEL}.pb |> pass.compiler gviz:true top:${pt} firrtl:true"
    ret_val=$?
    if [ $ret_val -ne 0 ]; then
      echo "ERROR: could not compile with pattern: ${pt}.${FIRRTL_LEVEL}.pb!"
      exit $ret_val
    fi
  done #end of for


  # Verilog code generation
  for pt in $1
  do
    echo ""
    echo ""
    echo ""
    echo "----------------------------------------------------"
    echo "LGraph -> Verilog"
    echo "----------------------------------------------------"

    ${LGSHELL} "lgraph.open name:${pt} |> inou.yosys.fromlg hier:true"
    if [ $? -eq 0 ] && [ -f ${pt}.v ]; then
        echo "Successfully generate Verilog: ${pt}.v"
        rm -f  yosys_script.*
    else
        echo "ERROR: Pyrope compiler failed: verilog generation, testcase: ${PATTERN_PATH}/${pt}.${FIRRTL_LEVEL}.pb"
        exit 1
    fi
  done


  # Logic Equivalence Check
  for pt in $1
  do
    echo ""
    echo ""
    echo ""
    echo "----------------------------------------------------"
    echo "Logic Equivalence Check"
    echo "----------------------------------------------------"

    ${LGCHECK} --implementation=${pt}.v --reference=./inou/firrtl/tests/verilog_gld/${pt}.gld.v

    if [ $? -eq 0 ]; then
      echo "Successfully pass LEC!"
    else
        echo "FAIL: "${pt}".v !== "${pt}".gld.v"
        exit 1
    fi
  done

  rm -f *.v
  rm -f *.dot
  rm -f lgcheck*
}

firrtl_test "$pts"
