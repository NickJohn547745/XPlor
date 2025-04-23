#ifndef LOCALSTRINGVIEWER_H
#define LOCALSTRINGVIEWER_H

#include "asset_structs.h"
#include "zonefile.h"
#include <QWidget>

namespace Ui {
class LocalStringViewer;
}

class LocalStringViewer : public QWidget
{
    Q_OBJECT

public:
    explicit LocalStringViewer(QWidget *parent = nullptr);
    ~LocalStringViewer();

    void SetVersion(quint32 aVersion);
    void SetConfigPath(const QString aConfigPath);
    void SetFileNotes(const QString aFileNotes);
    void AddLocalString(LocalString aLocalString);
    void SetZoneFile(std::shared_ptr<ZoneFile> aZoneFile);

private:
    Ui::LocalStringViewer *ui;
    quint32 mVersion;
    QString mConfigPath;
    QString mFileNotes;
    QVector<LocalString> mLocalStrings;
};

#endif // LOCALSTRINGVIEWER_H
