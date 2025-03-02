#include "logmanager.h"

void LogManager::addEntry(const QString &entry) {
    emit entryAdded(entry);
}

void LogManager::addError(const QString &error) {
    emit entryAdded(QString("ERROR: " + error));
}

void LogManager::addLine() {
    emit entryAdded("");
}
