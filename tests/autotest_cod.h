#ifndef AUTOTEST_COD_CPP
#define AUTOTEST_COD_CPP

#include <QtTest/QtTest>

#include "fastfile_factory.h"

#define FILE_MAX 1

class AutoTest_COD : public QObject {
    Q_OBJECT

protected:
    QList<QPair<QString, bool>> m_subtestResults;

public:
    const QList<QPair<QString, bool>>& getCollectedTestResults() const {
        return m_subtestResults;
    }
    void recordResult(const QString& name, bool passed) {
        m_subtestResults.append({ name, passed });
    }
    void setFastFileDirectory(const QString aFastFileDir) {
        mFastFileDirectory = aFastFileDir;
    }
    QString getFastFileDirectory() {
        return mFastFileDirectory;
    }

    void setZoneFileDirectory(const QString aZoneFileDir) {
        mZoneFileDirectory = aZoneFileDir;
    }
    QString getZoneFileDirectory() {
        return mZoneFileDirectory;
    }

    void createDirectory(const QString aDir) {
        QDir newDir(".");
        newDir.mkpath(aDir);
    }
    QStringList findZoneFiles(const QString &aBaseDir, int aMaxIter = FILE_MAX) {
        QList<QPair<qint64, QString>> fileList;

        QDirIterator it(aBaseDir, QStringList() << "*.zone", QDir::Files, QDirIterator::Subdirectories);
        int i = 0;
        while (it.hasNext() && i < aMaxIter) {
            QString path = it.next();
            QFileInfo fi(path);
            fileList.append(qMakePair(fi.size(), path));
            ++i;
        }

        std::sort(fileList.begin(), fileList.end(),
                  [](const QPair<qint64, QString> &a, const QPair<qint64, QString> &b) {
                      return a.first < b.first; // sort by size
                  });

        QStringList sorted;
        for (const auto &pair : fileList)
            sorted << pair.second;

        return sorted;
    }

    QStringList findFastFiles(const QString &aBaseDir, int aMaxIter = FILE_MAX) {
        QList<QPair<qint64, QString>> fileList;

        QDirIterator it(aBaseDir, QStringList() << "*.ff", QDir::Files, QDirIterator::Subdirectories);
        int i = 0;
        while (it.hasNext() && i < aMaxIter) {
            QString path = it.next();
            QFileInfo fi(path);
            fileList.append(qMakePair(fi.size(), path));
            ++i;
        }

        std::sort(fileList.begin(), fileList.end(),
                  [](const QPair<qint64, QString> &a, const QPair<qint64, QString> &b) {
                      return a.first < b.first; // sort by size
                  });

        QStringList sorted;
        for (const auto &pair : fileList)
            sorted << pair.second;

        return sorted;
    }

    virtual void initTestCase() = 0;

    void testDecompression_data() {
        QTest::addColumn<QString>("fastFilePath");

        QStringList ffFiles = findFastFiles(getFastFileDirectory());
        for (const QString &filePath : ffFiles) {
            QString fileName = QFileInfo(filePath).fileName();
            QTest::newRow(qPrintable(fileName)) << filePath;
        }
    }
    virtual void testDecompression() = 0;

    void testCompression_data() {
        QTest::addColumn<QString>("zoneFilePath");

        QStringList zoneFiles = findZoneFiles(getZoneFileDirectory());
        for (const QString &filePath : zoneFiles) {
            QString fileName = QFileInfo(filePath).fileName();
            QTest::newRow(qPrintable(fileName)) << filePath;
            break;
        }
    }
    virtual void testCompression() = 0;

    void testFactory_data() {
        QTest::addColumn<QString>("fastFilePath");

        QStringList ffFiles = findFastFiles(getFastFileDirectory());
        for (const QString &filePath : ffFiles) {
            QString fileName = QFileInfo(filePath).fileName();
            QTest::newRow(qPrintable(fileName)) << filePath;
        }
    }
    virtual void testFactory() = 0;

    virtual void cleanupTestCase() = 0;

private:
    QString mFastFileDirectory;
    QString mZoneFileDirectory;
};

#endif // AUTOTEST_COD_CPP
