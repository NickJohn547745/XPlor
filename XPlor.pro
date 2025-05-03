TEMPLATE = subdirs

SUBDIRS += libs \
           app \
           tools \
           tests

QMAKE_PRE_BUILD += make clean
