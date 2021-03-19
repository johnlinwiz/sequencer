/**
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "unity.h"
#include "sequencer.h"

#define MAX_STRINGLEN 64

bool sequenceComplete(uint8_t *params, uint32_t paramsLen) {
    if (paramsLen == sizeof(bool)) {
        bool *b = (bool *)params;
        *b = true;
    }
    return true;
}

void test_EmptySequence_should_Error(void) {
    Sequencer *seq = new Sequencer();
    SequencerButtons_t sequence[] = { };
    TEST_ASSERT_FALSE(seq->RegisterSequence(&sequence[0], NELEM(sequence), sequenceComplete, NULL, 0));
}

void test_IncompleteShortSequence_should_Fail(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t sequence[] = {SEQUENCER_A_UP,
                                     SEQUENCER_A_UP,
                                     SEQUENCER_A_DOWN,
                                     SEQUENCER_A_DOWN};

    TEST_ASSERT_TRUE(seq->RegisterSequence(&sequence[0], NELEM(sequence),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_A_UP);
    TEST_ASSERT_FALSE(cbCalled);
    delete seq;

}

void test_ValidSequence_should_Succeed(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t konamiSeq[] = {SEQUENCER_A_UP,
                                      SEQUENCER_A_UP,
                                      SEQUENCER_A_DOWN,
                                      SEQUENCER_A_DOWN,
                                      SEQUENCER_C_UP,
                                      SEQUENCER_C_DOWN,
                                      SEQUENCER_C_UP,
                                      SEQUENCER_C_DOWN,
                                      SEQUENCER_B_DOWN,
                                      SEQUENCER_B_UP};
    TEST_ASSERT_TRUE(seq->RegisterSequence(&konamiSeq[0], NELEM(konamiSeq),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_B_DOWN);
    seq->AddEvent(SEQUENCER_B_UP);

    TEST_ASSERT_TRUE(cbCalled);
    delete seq;

}

void test_EmbeddedValidSequence_should_Succeed(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t konamiSeq[] = {SEQUENCER_A_UP,
                                      SEQUENCER_A_DOWN,
                                      SEQUENCER_A_UP,
                                      SEQUENCER_A_DOWN};
    TEST_ASSERT_TRUE(seq->RegisterSequence(&konamiSeq[0], NELEM(konamiSeq),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
    // buncha garbage first
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_B_DOWN);
    seq->AddEvent(SEQUENCER_B_UP);
    TEST_ASSERT_FALSE(cbCalled);

    // the valid sequence
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);

    TEST_ASSERT_TRUE(cbCalled);
    delete seq;

}

void test_ValidMaxSequence_should_Succeed(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t sequence[SEQUENCE_MAX_LEN];
    for (int i = 0; i < 4; i++) {
        sequence[i*4    ] = SEQUENCER_A_UP;
        sequence[i*4 + 1] = SEQUENCER_A_DOWN;
        sequence[i*4 + 2] = SEQUENCER_B_DOWN;
        sequence[i*4 + 3] = SEQUENCER_B_UP;
    }

    TEST_ASSERT_TRUE(seq->RegisterSequence(&sequence[0], NELEM(sequence),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
    for (int i = 0; i < 4; i++) {
        seq->AddEvent(SEQUENCER_A_UP);
        seq->AddEvent(SEQUENCER_A_DOWN);
        seq->AddEvent(SEQUENCER_B_DOWN);
        seq->AddEvent(SEQUENCER_B_UP);
    }

    TEST_ASSERT_TRUE(cbCalled);
    delete seq;

}

void test_TooLongSequences_should_Fail(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t sequence[SEQUENCE_MAX_LEN + 1];

    TEST_ASSERT_FALSE(seq->RegisterSequence(&sequence[0], NELEM(sequence),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
                                           delete seq;
}

void test_InvalidKeyMidsequence_should_Fail(void) {
    Sequencer *seq = new Sequencer();
    bool cbCalled = false;
    SequencerButtons_t sequence[] = {SEQUENCER_A_UP,
                                      SEQUENCER_A_UP,
                                      SEQUENCER_A_DOWN,
                                      SEQUENCER_A_DOWN,
                                      SEQUENCER_C_UP,
                                      SEQUENCER_C_DOWN,
                                      SEQUENCER_C_UP,
                                      SEQUENCER_C_DOWN,
                                      SEQUENCER_B_DOWN,
                                      SEQUENCER_B_UP};
    TEST_ASSERT_TRUE(seq->RegisterSequence(&sequence[0], NELEM(sequence),
                                           sequenceComplete, (uint8_t *)&cbCalled, sizeof(cbCalled)));
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_A_DOWN);
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_A_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_C_UP);
    seq->AddEvent(SEQUENCER_C_DOWN);
    seq->AddEvent(SEQUENCER_B_DOWN);
    seq->AddEvent(SEQUENCER_B_UP);

    TEST_ASSERT_FALSE(cbCalled);
    delete seq;
}

int main(void) {
    UNITY_BEGIN();
  #if 1
    RUN_TEST(test_EmptySequence_should_Error);
    RUN_TEST(test_IncompleteShortSequence_should_Fail);
    RUN_TEST(test_ValidSequence_should_Succeed);
    RUN_TEST(test_EmbeddedValidSequence_should_Succeed);
    RUN_TEST(test_ValidMaxSequence_should_Succeed);
    RUN_TEST(test_TooLongSequences_should_Fail);
    #endif
    RUN_TEST(test_InvalidKeyMidsequence_should_Fail);
    return UNITY_END();
}
