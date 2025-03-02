#ifndef STATUSBARMANAGER_H
#define STATUSBARMANAGER_H

#include <QObject>
#include <QString>

class StatusBarManager : public QObject
{
    Q_OBJECT

public:
    static StatusBarManager &instance() {
        static StatusBarManager instance;
        return instance;
    }

    void updateStatus(const QString &message, int timeout = 5000);
    void updateProgressStatus(const QString &message, int progress, int max);

signals:
    void statusUpdated(const QString &message, int timeout);
    void progressUpdated(const QString &message, int progress, int max);

private:
    StatusBarManager() {} // Private constructor for singleton
    ~StatusBarManager() {}

    Q_DISABLE_COPY(StatusBarManager)
};

#endif // STATUSBARMANAGER_H
