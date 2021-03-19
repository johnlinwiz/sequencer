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

// DEBUG FLAG (to be removed in final stage)
// should be in the headerfile, but the headerfile is asked not to be modified...
#define DEBUG

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

/// Register a sequence and callback to be invoked when the sequence has
/// been matched.  If memory was allocated for the params, the caller is
/// responsible for freeing that memory.
/// @param sequence to match
/// @param number of elements in sequence
/// @param cb function pointer to callback
/// @param params extra data to be passed in callback from caller
/// @param params_len length of extra data passed in callback from caller
/// @return true if sequence valid, false otherwise
bool Sequencer::RegisterSequence(SequencerButtons_t *seq, uint8_t numElem, SequencerCb_Fn cb,
                                 uint8_t *params, uint32_t paramsLen) 
{
    #ifdef DEBUG
        for (int i; i < numElem; i++) {
            printf("{%i}", seq[i]);
        }
    #endif

}

/// Unregister a sequence and callback.
void Sequencer::UnregisterSequence() {
    // XXX IMPLEMENT ME - see sequencer.h for description


}

/// Add a button event.  This method is invoked each time an event (such as a button press) occurs.
/// @param The new button event
void Sequencer::AddEvent(SequencerButtons_t event) {
    #ifdef DEBUG
        printf("[%i]", event);
    #endif

    if (sequenceIdx_ < SEQUENCE_MAX_LEN) {
        sequence_[sequenceIdx_] = event;
        sequenceIdx_++;
    } else {
        printf("ERROR: Sequence Length Too Long!");
    }
}

/// @}
