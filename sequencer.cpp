/**
 * Copyright 2015 Orion, Inc.
 * All rights reserved. Do not redistribute.
 *
 * @file sequencer.h
 *
 * @brief Register a sequence of buttons to match and a callback for when that
 * sequence completes.
 *
 * @{
 */
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "sequencer.h"

Sequencer::Sequencer() {
    Init_();
}

Sequencer::~Sequencer() {
    Init_();
}

void Sequencer::Init_() {
    memset(sequence_, 0, sizeof(sequence_));
    sequenceIdx_= 0;
    callback_ = NULL;
    callbackParams_ = NULL;
    callbackParamsLen_ = 0;
}

bool Sequencer::RegisterSequence(SequencerButtons_t *seq, uint8_t numElem, SequencerCb_Fn cb,
                                 uint8_t *params, uint32_t paramsLen) {
    // XXX IMPLEMENT ME - see sequencer.h for description
    // 1) Ensure input is correct
    // 2) Register the sequence for detection
    return true;
}

void Sequencer::UnregisterSequence() {
    // XXX IMPLEMENT ME - see sequencer.h for description
}

void Sequencer::AddEvent(SequencerButtons_t event) {
    // XXX IMPLEMENT ME - see sequencer.h
    // 1) Check the base case
    // 2) Check events if they match the seqeuence.
}

/// @}
