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
#define _DEBUG

Sequencer::Sequencer() {

}

Sequencer::~Sequencer() {
}

void Sequencer::Init_() {
    UnregisterSequence();   // Unregister seq and callback

    // other init stuff...
}

bool validKeyCheck(SequencerButtons_t key) {
    if (key > SEQUENCER_MAX) {  // fail when it exceed Max len
        return false;
    } else {
        switch(key) {
            case SEQUENCER_BUTTON_INVALID:
                return false;   // invalid -> fail
                break;
            case SEQUENCER_A_UP:
            case SEQUENCER_A_DOWN:
            case SEQUENCER_B_UP:
            case SEQUENCER_B_DOWN:
            case SEQUENCER_C_UP:
            case SEQUENCER_C_DOWN:
            case SEQUENCER_D_UP:
            case SEQUENCER_D_DOWN:
                return true;    // valid keys -> great!
                break;
            default:
                return false;   // unexpected -> fail
                break;
        }
    }
}

bool validSeqCheck() {

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
    if (numElem > SEQUENCE_MAX_LEN) {   // if numElem exceeds the max length
        return false;   // FAIL
    } else {
        #ifdef _DEBUG
            for (int i; i < numElem; i++) {
                printf("{%i}", seq[i]);
            }
        #endif

    }

    return false;   // fail if reached this point for some unexpected reason!
}

/// Unregister a sequence and callback.
void Sequencer::UnregisterSequence() {
    // XXX IMPLEMENT ME - see sequencer.h for description

    //Init_();    // init already unregister a sequence and callback
    // moved Init_() here since init might be doing other Init in the future..
    memset(sequence_, 0, sizeof(sequence_));
    sequenceIdx_= 0;
    callback_ = NULL;
    callbackParams_ = NULL;
    callbackParamsLen_ = 0;
}

/// Add a button event.  This method is invoked each time an event (such as a button press) occurs.
/// @param The new button event
void Sequencer::AddEvent(SequencerButtons_t event) {
    #ifdef _DEBUG
        printf("[%i]", event);
    #endif

    if (sequenceIdx_ < (SEQUENCE_MAX_LEN - 1) ) { // index within range
        sequence_[sequenceIdx_] = event;    // store the event into the sequence array
        sequenceIdx_++;
    } else {    // overflow
        #ifdef _DEBUG
            printf("[AddEvent] ERROR: Sequence Length Too Long!");
        #endif
        sequenceIdx_ = SEQUENCE_MAX_LEN - 1;    // index set to the MAX; to avoid overflow
    }
}

/// @}
