ifeq ($(V),1)
# if user specifies V=1, print full compile commands
C :=
E := @:
else
# by default, we echo a user friendly version of the compile command
C := @
E := @echo
endif

# Unit testing
TEST_DIR := build_test
TEST_BIN := $(TEST_DIR)/test

TEST_INCLUDES_COMMON := -I. -I.. \
	-Ilib/Unity/src

TEST_SOURCES_COMMON := \
	lib/Unity/src/unity.c

TEST_SOURCES_sequencer := \
	$(TEST_SOURCES_COMMON) \
	sequencer.cpp \
	test/test_sequencer.cpp

TESTS := sequencer

TEST_SOURCES_ALL := $(foreach i,$(TESTS),$(TEST_SOURCES_$(i)))

VPATH += $(sort $(dir $(TEST_SOURCES_ALL)))

include Makefile.defs
include Makefile.rules
