TEMPLATE = app
CONFIG += no_main

# Enable the testlib module
QT += testlib

# Define a test-specific flag
DEFINES += QT_TESTS

TARGET = tests

# List all test source files
SOURCES += \
    autotest_cod5.cpp \
    test_main.cpp \
    autotest_cod.cpp \
    autotest_xplor.cpp


# Prevent tests from being built in release mode (optional)
# CONFIG(debug, debug|release) {
#     message("Including test files in Debug mode")
# } else {
#     SOURCES -= autotest_cod5.cpp
# }
