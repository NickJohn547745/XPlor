#ifndef AUTOTEST_COD_CPP
#define AUTOTEST_COD_CPP

#include <QtTest/QtTest>

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
    QStringList findFastFiles(const QString &aBaseDir, int aMaxIter = MAX_ITER) {
        QStringList fastFiles;

        QDirIterator it(aBaseDir, QStringList() << "*.ff", QDir::Files, QDirIterator::Subdirectories);

        int i = 0;
        while (it.hasNext() && i < aMaxIter) {
            fastFiles << it.next();
            ++i;
        }

        return fastFiles;
    }
    QStringList findZoneFiles(const QString &aBaseDir, int aMaxIter = MAX_ITER) {
        QStringList zoneFiles;

        QDirIterator it(aBaseDir, QStringList() << "*.zone", QDir::Files, QDirIterator::Subdirectories);

        int i = 0;
        while (it.hasNext() && i < aMaxIter) {
            zoneFiles << it.next();
            ++i;
        }

        return zoneFiles;
    }
    virtual void initTestCase() = 0;
    virtual void testDecompression_data() = 0;
    virtual void testDecompression() = 0;
    virtual void testCompression_data() = 0;
    virtual void testCompression() = 0;
    virtual void cleanupTestCase() = 0;

private:
    static const int MAX_ITER = 10000;
    QString mFastFileDirectory;
    QString mZoneFileDirectory;
};

#endif // AUTOTEST_COD_CPP
