/**
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

}

Sequencer::~Sequencer() {
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

}

void Sequencer::UnregisterSequence() {
    // XXX IMPLEMENT ME - see sequencer.h for description


}

void Sequencer::AddEvent(SequencerButtons_t event) {
    // XXX IMPLEMENT ME - see sequencer.h

}

/// @}
