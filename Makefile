# Required environment variables:
#  - ARDUINO_DIR (path to arduino IDE installation directory)
#  - MONITOR_PORT (path to the device)
#
# You may also want to override:
#  - BOARD_TAG (identifier of Arduino-like board)
#  - AVR_TOOLS_DIR (base directory of the avr toolchain)
#  - AVRDUDE (path to the avrdude executable)

PROJECT_DIR       = $(CURDIR)
ARDMK_DIR         = $(PROJECT_DIR)/lib/ardmk
USER_LIB_PATH    :=  $(PROJECT_DIR)/lib
BOARD_TAG         = ethernet
AVR_TOOLS_DIR     = /usr
AVRDDUDE          = /usr/bin/avrdude
CFLAGS_STD        = -std=gnu11
CXXFLAGS_STD      = -std=gnu++11
CXXFLAGS         += -pedantic -Wall -Wextra
CURRENT_DIR       = $(shell basename $(CURDIR))
OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

include $(ARDMK_DIR)/Arduino.mk
