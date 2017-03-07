/**
 * Copyright 2015 Orion, Inc.
 * All rights reserved. Do not redistribute.
 *
 * @file sequencer.h
 *
 * @brief Register a sequence of buttons to match and a callback for when that
 * sequence completes.
 *
 *
 * @{
 */
#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

/// @return the number of elements in array a
#define NELEM(a) sizeof(a)/sizeof(a[0])

/// The maximum length of a sequence
static const uint8_t SEQUENCE_MAX_LEN = 16;

/// Callback invoked when sequence is complete
typedef bool (*SequencerCb_Fn)(uint8_t *params, uint32_t params_len);

/// Recognized buttons for sequence
typedef enum SequencerButtons_ {
    SEQUENCER_BUTTON_INVALID     = 0x00,
    SEQUENCER_A_UP               = 0x01,
    SEQUENCER_A_DOWN             = 0x02,
    SEQUENCER_B_UP               = 0x03,
    SEQUENCER_B_DOWN             = 0x04,
    SEQUENCER_C_UP               = 0x05,
    SEQUENCER_C_DOWN             = 0x06,
    SEQUENCER_D_UP               = 0x07,
    SEQUENCER_D_DOWN             = 0x08,
    SEQUENCER_MAX                = 0xFF
} SequencerButtons_t;

class Sequencer {
  public:
    Sequencer();
    ~Sequencer();

    /// Register a sequence and callback to be invoked when the sequence has
    /// been matched.  If memory was allocated for the params, the caller is
    /// responsible for freeing that memory.
    /// @param sequence to match
    /// @param number of elements in sequence
    /// @param cb function pointer to callback
    /// @param params extra data to be passed in callback from caller
    /// @param params_len length of extra data passed in callback from caller
    /// @return true if sequence valid, false otherwise
    bool RegisterSequence(SequencerButtons_t *seq, uint8_t numElem,
                          SequencerCb_Fn cb, uint8_t *params, uint32_t paramsLen);

    /// Unregister a sequence and callback.
    void UnregisterSequence();

    /// Add a button event.  This method is invoked each time an event (such as a button press) occurs.
    /// @param The new button event
    void AddEvent(SequencerButtons_t event);

  private:
    // Currently only one sequence can be registered at a time.
    SequencerButtons_t sequence_[SEQUENCE_MAX_LEN];
    uint8_t sequenceIdx_;
    uint8_t sequenceNumElem_;

    SequencerCb_Fn callback_;
    uint8_t *callbackParams_;
    uint32_t callbackParamsLen_;

    void Init_();
};

#endif /* _SEQUENCER_H_ */
/// @}
