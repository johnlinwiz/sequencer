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
    Init_();    // call init when class just constructed

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
                // this func could be modified to process key press in the future, and
                // this is the "case" that can be used to do something when key pressed:
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
    if (numElem == 0) { // if there is nothing to compare to:
        return false;   // FAIL
    } else if (numElem > SEQUENCE_MAX_LEN) {   // if numElem exceeds the max length
        return false;   // FAIL
    } else {
        #ifdef _DEBUG
            for (int i; i < numElem; i++) {
                printf("{%i}", seq[i]);
            }
        #endif

        for (int i; i<numElem; i++) {
            sequence_[i] = seq[i];
        }

        sequenceIdx_ = 0;   // reset sequence index

        callback_ = cb; // register the callback func
        callbackParams_ = params;   // register the params
        callbackParamsLen_ = paramsLen;

        return true;    // registeration succeed
    }

    return false;   // fail if reached this point for some unexpected reason!
}

/// Unregister a sequence and callback.
void Sequencer::UnregisterSequence() {
    // XXX IMPLEMENT ME - see sequencer.h for description

    #ifdef _DEBUG
        printf("[UnregisterSequence]");
    #endif

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
    bool status;
    bool match = false;

    #ifdef _DEBUG
        printf("[%i]", event);
    #endif


    status = callback_(callbackParams_, callbackParamsLen_); // calling the callback func
    if (!status) match = false;     // if callback failed -> match fail (?)

    // assign params the status result for the search
    if (callbackParamsLen_ == sizeof(bool)) {
        bool *b = (bool *)callbackParams_;
        *b = match;
    }
}

/// @}
