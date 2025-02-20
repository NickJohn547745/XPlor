#include "zonefile.h"
#include "utils.h"

#include <QFile>
#include <QDataStream>
#include <QDebug>

ZoneFile::ZoneFile() :
    mStem(),
    mSize(),
    mTagCount(),
    mTags(),
    mRecordCount(),
    mRecords(),
    mAssetMap() {

}

ZoneFile::~ZoneFile() {

}

ZoneFile::ZoneFile(const ZoneFile &aZoneFile) {
    mStem = aZoneFile.mStem;
    mSize = aZoneFile.mSize;
    mTagCount = aZoneFile.mTagCount;
    mTags = aZoneFile.mTags;
    mRecordCount = aZoneFile.mRecordCount;
    mRecords = aZoneFile.mRecords;
    mAssetMap = aZoneFile.mAssetMap;
}

ZoneFile &ZoneFile::operator=(const ZoneFile &other) {
    if (this != &other) {
        mStem = other.mStem;
        mSize = other.mSize;
        mTagCount = other.mTagCount;
        mTags = other.mTags;
        mRecordCount = other.mRecordCount;
        mRecords = other.mRecords;
        mAssetMap = other.mAssetMap;
    }
    return *this;
}

QString ZoneFile::GetStem() {
    return mStem;
}

quint32 ZoneFile::GetSize() {
    return mSize;
}

quint32 ZoneFile::GetTagCount() {
    return mTagCount;
}

QStringList ZoneFile::GetTags() {
    return mTags;
}

quint32 ZoneFile::GetRecordCount() {
    return mRecordCount;
}

QStringList ZoneFile::GetRecords() {
    return mRecords;
}

AssetMap ZoneFile::GetAssetMap() {
    return mAssetMap;
}

void ZoneFile::SetStem(const QString aStem) {
    mStem = aStem;
}

void ZoneFile::SetSize(quint32 aSize) {
    mSize = aSize;
}

void ZoneFile::SetTagCount(quint32 aTagCount) {
    mTagCount = aTagCount;
}

void ZoneFile::SetTags(const QStringList aTags) {
    mTags = aTags;
}

void ZoneFile::SetRecordCount(quint32 aRecordCount) {
    mRecordCount = aRecordCount;
}

void ZoneFile::SetRecords(const QStringList aRecords) {
    mRecords = aRecords;
}

void ZoneFile::SetAssetMap(const AssetMap aAssetMap) {
    mAssetMap = aAssetMap;
}

