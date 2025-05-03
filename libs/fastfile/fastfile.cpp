#include "fastfile.h"

#include "fastfile_factory.h"
#include "logmanager.h"

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

FastFile::FastFile(const QByteArray &aData) {
    Q_UNUSED(aData);
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

QString FastFile::GetStem() const {
    return mStem;
}

FF_FILETYPE FastFile::GetType() const {
    return mType;
}

FF_COMPANY FastFile::GetCompany() const {
    return mCompany;
}

FF_SIGNAGE FastFile::GetSignage() const {
    return mSignage;
}

QString FastFile::GetMagic() const {
    return mMagic;
}

quint32 FastFile::GetVersion() const {
    return mVersion;
}

std::shared_ptr<ZoneFile> FastFile::GetZoneFile() const {
    return mZoneFile;
}

QString FastFile::GetGame() const {
    return mGame;
}

QString FastFile::GetPlatform() const {
    return mPlatform;
}

void FastFile::SetStem(const QString aStem) {
    mStem = aStem;
}

void FastFile::SetType(const FF_FILETYPE aType) {
    mType = aType;
}

void FastFile::SetCompany(const FF_COMPANY aCompany) {
    mCompany = aCompany;
}

void FastFile::SetSignage(const FF_SIGNAGE aSignage) {
    mSignage = aSignage;
}

void FastFile::SetMagic(const QString aMagic) {
    mMagic = aMagic;
}

void FastFile::SetVersion(const quint32 aVersion) {
    mVersion = aVersion;
}

void FastFile::SetZoneFile(const std::shared_ptr<ZoneFile> aZoneFile) {
    mZoneFile = aZoneFile;
}

void FastFile::SetGame(const QString aGame) { mGame = aGame;
}

void FastFile::SetPlatform(const QString aPlatform) {
    mPlatform = aPlatform;
}

FF_COMPANY FastFile::pParseFFCompany(QDataStream *afastFileStream, quint32 &aCompanyInt) {
    LogManager::instance().addEntry("Parsing company into reference...");
    // Check for null datastream ptr
    if (!afastFileStream) { return COMPANY_NONE; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);
    aCompanyInt = companyData.toUInt();

    if (companyData == "IW") {
        return COMPANY_INFINITY_WARD;
    } else if (companyData == "TA") {
        return COMPANY_TREYARCH;
    } else if (companyData == "Sl") {
        return COMPANY_SLEDGEHAMMER;
    } else if (companyData == "NX") {
        return COMPANY_NEVERSOFT;
    }
    LogManager::instance().addEntry(QString("Failed to find company, found '%1'!").arg(companyData));
    return COMPANY_NONE;
}

FF_COMPANY FastFile::pParseFFCompany(QDataStream *afastFileStream) {
    LogManager::instance().addEntry("Parsing company...");
    // Check for null datastream ptr
    if (!afastFileStream) { return COMPANY_NONE; }
    // Parse company
    QByteArray companyData(2, Qt::Uninitialized);
    afastFileStream->readRawData(companyData.data(), 2);

    if (companyData == "IW") {
        return COMPANY_INFINITY_WARD;
    } else if (companyData == "TA") {
        return COMPANY_TREYARCH;
    } else if (companyData == "Sl") {
    } else if (companyData == "NX") {
        return COMPANY_NEVERSOFT;
    }
    LogManager::instance().addEntry(QString("Failed to find company, found '%1'!").arg(companyData));
    return COMPANY_NONE;
}

FF_FILETYPE FastFile::pParseFFFileType(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray fileTypeData(2, Qt::Uninitialized);
    afastFileStream->readRawData(fileTypeData.data(), 2);
    if (fileTypeData == "ff") {
        return FILETYPE_FAST_FILE;
    }
    LogManager::instance().addEntry("Failed to find file type!");
    return FILETYPE_NONE;
}

FF_SIGNAGE FastFile::pParseFFSignage(QDataStream *afastFileStream) {
    // Parse filetype
    QByteArray signedData(1, Qt::Uninitialized);
    afastFileStream->readRawData(signedData.data(), 1);
    if (signedData == "u") {
        return SIGNAGE_UNSIGNED;
    } else if (signedData == "0" || signedData == "x") {
        return SIGNAGE_SIGNED;
    }
    LogManager::instance().addEntry("Failed to determine signage of fastfile!");
    return SIGNAGE_NONE;
}

QString FastFile::pParseFFMagic(QDataStream *afastFileStream) {
    // Parse magic
    QByteArray magicData(3, Qt::Uninitialized);
    afastFileStream->readRawData(magicData.data(), 3);
    if (magicData == "100") {
        return magicData;
    }
    LogManager::instance().addEntry("Magic invalid!");
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
    switch (aVersion) {
    case 387:           // PC World at War
    case 473:           // PC Black Ops 1
    case 1:             // PC Modern Warfare 3
    case 147:           // PC Black Ops 2
        return "PC";
    case 3640721408:    // Xbox 360 Black Ops 1
    case 2449473536:    // Xbox 360 Black Ops 2
        return "360";
    case 3707830272:    // Wii Black Ops 1
        return "Wii";
    }
    return "NONE";
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
    case 3707830272:    // Wii Black Ops 1
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

std::shared_ptr<FastFile> FastFile::Open(const QString &aFilePath) {
    LogManager::instance().addEntry("Processing Fastfile...");

    if (aFilePath.isEmpty()) {
        LogManager::instance().addError("Attempted to open file w/no name!");
        return nullptr;
    }
    LogManager::instance().addEntry("File Path: " + aFilePath);

    // Check fastfile can be read
    QFile *file = new QFile(aFilePath);
    if (!file->open(QIODevice::ReadOnly)) {
        LogManager::instance().addError(QString("File failed to open: %1").arg(file->errorString()));
        return nullptr;
    }
    LogManager::instance().addEntry("File opened");

    const QByteArray data = file->readAll();
    LogManager::instance().addEntry("Contents read in");
    LogManager::instance().addEntry(QString("- Size: %1 B").arg(data.size()));

    LogManager::instance().addEntry("File closed");
    file->close();

    // Create a QDataStream on the input data.
    QDataStream fastFileStream(data);
    fastFileStream.setByteOrder(QDataStream::LittleEndian);

    quint32 companyInt;
    FF_COMPANY company = pParseFFCompany(&fastFileStream, companyInt);
    qDebug() << "Company: " << company;
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

        LogManager::instance().addEntry(QString("Type: %1").arg(fileType));
        LogManager::instance().addEntry(QString("Signage: %1").arg(signage));
        LogManager::instance().addEntry(QString("Magic: %1").arg(magic));
        LogManager::instance().addEntry(QString("Version: %1").arg(version));
    }
    LogManager::instance().addEntry(QString("Company: %1").arg(company));
    LogManager::instance().addEntry(QString("Game: %1").arg(game));
    LogManager::instance().addEntry(QString("Platform: %1").arg(platform));

    const QString fastFileStem = aFilePath.section("/", -1, -1).section('.', 0, 0);
    LogManager::instance().addEntry(QString("Stem: %1").arg(fastFileStem));

    std::shared_ptr<FastFile> fastFile =  FastFileFactory::Create(data);

    fastFile->SetCompany(company);
    fastFile->SetStem(fastFileStem);

    return fastFile;
}
bool FastFile::ExportFastFile(const QString aFastFilePath) {
    QFile fastFile(aFastFilePath);
    if (!fastFile.open(QIODevice::WriteOnly)) {
        LogManager::instance().addEntry("Failed to write fast file! " +
                                        fastFile.errorString());
        return false;
    }
    fastFile.write(GetBinaryData());
    fastFile.close();

    return true;
}
