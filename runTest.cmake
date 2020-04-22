# arguments checking
if( NOT TEST_PROGRAM )
  message( FATAL_ERROR "Require TEST_PROGRAM to be defined" )
endif( NOT TEST_PROGRAM )
if( NOT TEST_ARGS )
  message( FATAL_ERROR "Require TEST_ARGS to be defined" )
endif( NOT TEST_ARGS )
if( NOT TEST_OUTPUT )
  message( FATAL_ERROR "Require TEST_OUTPUT to be defined" )
endif( NOT TEST_OUTPUT )
if( NOT TEST_REFERENCE )
  message( FATAL_ERROR "Require TEST_REFERENCE to be defined" )
endif( NOT TEST_REFERENCE )

set(ENV{BOX86_LOG} 0)
set(ENV{LD_LIBRARY_PATH} ${CMAKE_SOURCE_DIR}/x86lib)
# run the test program, capture the stdout/stderr and the result var
execute_process(
  COMMAND ${TEST_PROGRAM} ${TEST_ARGS} ${TEST_ARGS2}
  OUTPUT_FILE ${TEST_OUTPUT}
  ERROR_VARIABLE TEST_ERROR
  RESULT_VARIABLE TEST_RESULT
  )

# if the return value is !=0 bail out
if( TEST_RESULT )
  message( FATAL_ERROR "Failed: Test program ${TEST_PROGRAM} exited != 0.\n${TEST_ERROR}" )
endif( TEST_RESULT )

# now compare the output with the reference
execute_process(
  COMMAND ${CMAKE_COMMAND} -E compare_files ${TEST_OUTPUT} ${TEST_REFERENCE}
  RESULT_VARIABLE TEST_RESULT
  )

# again, if return value is !=0 scream and shout
if( TEST_RESULT )
  message( FATAL_ERROR "Failed: The output of ${TEST_PROGRAM} did not match ${TEST_REFERENCE}")
endif( TEST_RESULT )

# everything went fine...
message( "Passed: The output of ${TEST_PROGRAM} matches ${TEST_REFERENCE}" )
