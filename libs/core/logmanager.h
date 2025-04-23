#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QString>

class LogManager : public QObject
{
    Q_OBJECT

public:
    static LogManager &instance() {
        static LogManager instance;
        return instance;
    }

    void addEntry(const QString &entry);
    void addError(const QString &error);
    void addLine();

signals:
    void entryAdded(const QString &entry);

private:
    LogManager() {} // Private constructor for singleton
    ~LogManager() {}

    Q_DISABLE_COPY(LogManager)
};

#endif // LOGMANAGER_H
