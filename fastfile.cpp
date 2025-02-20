#include "fastfile.h"

#include "fastfile_cod2.h"
#include "fastfile_cod5.h"
#include "fastfile_cod7.h"
#include "fastfile_cod9.h"
#include "compressor.h"

#include <QFile>
#include <QDebug>

FastFile::FastFile()
    : mStem(""),
      mType(FILETYPE_NONE),
      mCompany(COMPANY_NONE),
      mSignage(SIGNAGE_NONE),
      mMagic(""),
      mVersion(0),
      mZoneFile(nullptr),
      mGame(""),
      mPlatform("") {

}

FastFile::FastFile(FastFile &fastFile)
    : mStem(fastFile.GetStem()),
      mType(fastFile.GetType()),
      mCompany(fastFile.GetCompany()),
      mSignage(fastFile.GetSignage()),
      mMagic(fastFile.GetMagic()),
      mVersion(fastFile.GetVersion()),
      mZoneFile(fastFile.GetZoneFile()),
      mGame(fastFile.GetGame()),
      mPlatform(fastFile.GetPlatform()) {

}

FastFile::~FastFile() {

}

FF_COMPANY FastFile::pParseFFCompany(QDataStream *afastFileStream, quint32 &aCompanyInt) {
    // Check for null datastream ptr
    if (!afastFileStream) { return COMPANY_NONE; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);
    aCompanyInt = companyData.toUInt();

    if (companyData == "IW") {
        qDebug() << "Company found: 'INFINITY_WARD'";
        return COMPANY_INFINITY_WARD;
    } else if (companyData == "TA") {
        qDebug() << "Company found: 'TREYARCH'";
        return COMPANY_TREYARCH;
    } else if (companyData == "Sl") {
        qDebug() << "Company found: 'SLEDGEHAMMER'";
        return COMPANY_SLEDGEHAMMER;
    } else if (companyData == "NX") {
        qDebug() << "Company found: 'NEVERSOFT'";
        return COMPANY_NEVERSOFT;
    } else {
        qDebug() << QString("Failed to find company, found '%1'!").arg(companyData);
    }
    return COMPANY_NONE;
}

FF_COMPANY FastFile::pParseFFCompany(QDataStream *afastFileStream) {
    // Check for null datastream ptr
    if (!afastFileStream) { return COMPANY_NONE; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);

    if (companyData == "IW") {
        qDebug() << "Company found: 'INFINITY_WARD'";
        return COMPANY_INFINITY_WARD;
    } else if (companyData == "TA") {
        qDebug() << "Company found: 'TREYARCH'";
        return COMPANY_TREYARCH;
    } else if (companyData == "Sl") {
        qDebug() << "Company found: 'SLEDGEHAMMER'";
        return COMPANY_SLEDGEHAMMER;
    } else if (companyData == "NX") {
        qDebug() << "Company found: 'NEVERSOFT'";
        return COMPANY_NEVERSOFT;
    } else {
        qDebug() << QString("Failed to find company, found '%1'!").arg(companyData);
    }
    return COMPANY_NONE;
}

FF_FILETYPE FastFile::pParseFFFileType(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray fileTypeData(2, Qt::Uninitialized);
    afastFileStream->readRawData(fileTypeData.data(), 2);
    if (fileTypeData == "ff") {
        qDebug() << "File type found: 'FAST_FILE'";
        return FILETYPE_FAST_FILE;
    } else {
        qDebug() << "Failed to find file type!";
    }
    return FILETYPE_NONE;
}

FF_SIGNAGE FastFile::pParseFFSignage(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray signedData(1, Qt::Uninitialized);
    afastFileStream->readRawData(signedData.data(), 1);
    if (signedData == "u") {
        qDebug() << "Found valid signage: Unsigned";
        return SIGNAGE_UNSIGNED;
    } else if (signedData == "0" || signedData == "x") {
        qDebug() << "Found valid signage: Signed";
        return SIGNAGE_SIGNED;
    } else {
        qDebug() << "Failed to determine signage of fastfile!";
    }
    return SIGNAGE_NONE;
}

QString FastFile::pParseFFMagic(QDataStream *afastFileStream) {
    // Parse magic
    QByteArray magicData(3, Qt::Uninitialized);
    afastFileStream->readRawData(magicData.data(), 3);
    if (magicData == "100") {
        qDebug() << QString("Found valid magic: '%1'").arg(magicData);
        return magicData;
    } else {
        qDebug() << "Magic invalid!";
    }
    return "";
}

quint32 FastFile::pParseFFVersion(QDataStream *afastFileStream) {
    // Parse version
    quint32 version;
    *afastFileStream >> version;
    qDebug() << QString("Found version: '%1'").arg(version);
    return version;
}

QString FastFile::pCalculateFFPlatform(quint32 aVersion) {
    QString result = "NONE";
    switch (aVersion) {
    case 387:           // PC World at War
    case 473:           // PC Black Ops 1
    case 1:             // PC Modern Warfare 3
    case 147:           // PC Black Ops 2
        result = "PC";
        break;
    case 3640721408:    // Xbox 360 Black Ops 1
    case 2449473536:    // Xbox 360 Black Ops 2
        result = "360";
        break;
    }
    qDebug() << QString("Found platform: '%1'").arg(result);
    return result;
}

QString FastFile::pCalculateFFGame(quint32 aVersion) {
    QString result = "NONE";
    switch (aVersion) {
    case 387:           // PC World at War
        result = "COD5";
        break;
    case 473:           // PC Black Ops 1
        break;
    case 3640721408:    // Xbox 360 Black Ops 1
        result = "COD7";
        break;
    case 1:             // PC Modern Warfare 3
        result = "COD8";
        break;
    case 147:           // PC Black Ops 2
    case 2449473536:    // Xbox 360 Black Ops 2
        result = "COD9";
        break;
    }
    qDebug() << QString("Found game: '%1'").arg(result);
    return result;
}

std::shared_ptr<FastFile> FastFile::Create(const QString &aFilePath) {
    if (aFilePath.isEmpty()) {
        return nullptr;
    }

    // Check fastfile can be read
    QFile *file = new QFile(aFilePath);
    if (!file->open(QIODevice::ReadOnly)) {
        qDebug() << QString("Error: Failed to open FastFile: %1!").arg(aFilePath);
        return nullptr;
    }

    const QByteArray data = file->readAll();
    file->close();

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(data);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    quint32 companyInt;
    FF_COMPANY company = pParseFFCompany(&fastFileStream, companyInt);
    FF_FILETYPE fileType;
    FF_SIGNAGE signage;
    QString magic;
    quint32 version;
    QString platform;
    QString game;

    if ((company == COMPANY_NONE) && (companyInt == 0)) {
        company = COMPANY_INFINITY_WARD;
        game = "COD2";
        platform = "360";
    } else {
        fileType = pParseFFFileType(&fastFileStream);
        signage = pParseFFSignage(&fastFileStream);
        magic = pParseFFMagic(&fastFileStream);
        version = pParseFFVersion(&fastFileStream);
        platform = pCalculateFFPlatform(version);
        game = pCalculateFFGame(version);

        qDebug() << "Type: " << fileType;
        qDebug() << "Signage: " << signage;
        qDebug() << "Magic: " << magic;
        qDebug() << "Version: " << version;
    }
    qDebug() << "Company: " << company;
    qDebug() << "Game: " << game;
    qDebug() << "Platform: " << platform;

    const QString fastFileStem = aFilePath.section("/", -1, -1).section('.', 0, 0);
    qDebug() << "Stem: " << fastFileStem;

    FastFile *fastFile;
    if (game == "COD2") {
        fastFile = new FastFile_COD2();
    } else if (game == "COD5") {
        fastFile = new FastFile_COD5();
    } else if (game == "COD7") {
        fastFile = new FastFile_COD7();
    } else if (game == "COD9") {
        fastFile = new FastFile_COD9();
    }
    if (fastFile) {
        fastFile->SetCompany(company);
        fastFile->SetStem(fastFileStem);
        fastFile->Load(data);
        return std::unique_ptr<FastFile>(fastFile);
    }

    // Open zone file after decompressing ff and writing
    return nullptr;
}
