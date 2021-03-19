### FW Coding Problem - Sequence Detection
  The sequencer is a component that is used to detect a specific sequence of
  events and do something in response.  For instance, the application may want
  to switch on special LED lights if the user presses `A_UP`, `A_DOWN`,
  `A_UP`, `A_DOWN`, `B_DOWN`, `B_UP`.

### Problem
  Your task is to implement the following methods (in sequencer.cpp):
  * RegisterSequence
  * UnregisterSequence
  * AddEvent

  The descriptions of these methods are in the sequencer.h header file.  The
  header file is complete and no modifications should be necessary. Note that
  currently only one sequence can be registered at a time.

### Expected Results
  We have provided a set of unit tests that should pass when you have correctly
  implemented the required methods.  To run these, type:
  `make test`

  The correct test results be:

  [test] Running unit tests for sequencer
  test/test_sequencer.cpp:170:test_EmptySequence_should_Error:PASS
  test/test_sequencer.cpp:171:test_IncompleteShortSequence_should_Fail:PASS
  test/test_sequencer.cpp:172:test_ValidSequence_should_Succeed:PASS
  test/test_sequencer.cpp:173:test_EmbeddedValidSequence_should_Succeed:PASS
  test/test_sequencer.cpp:174:test_ValidMaxSequence_should_Succeed:PASS
  test/test_sequencer.cpp:175:test_TooLongSequences_should_Fail:PASS
  test/test_sequencer.cpp:176:test_InvalidKeyMidsequence_should_Fail:PASS

  -----------------------
  7 Tests 0 Failures 0 Ignored
  OK

### Evaluation
  The code will be evaluated for
  * correctness
  * completeness
  * coding style

### Requirements
  * C++ compiler (e.g. g++)
  * make
