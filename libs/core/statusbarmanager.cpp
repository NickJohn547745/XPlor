#include "statusbarmanager.h"

void StatusBarManager::updateStatus(const QString &message, int timeout) {
    emit statusUpdated(message, timeout);
}

void StatusBarManager::updateProgressStatus(const QString &message, int progress, int max) {
    emit progressUpdated(message, progress, max);
}
