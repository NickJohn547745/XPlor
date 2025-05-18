TEMPLATE = subdirs

SUBDIRS += libs \
           app \
           tools \
           tests

tests.depends = libs
app.depends = libs
tools.depends = libs
