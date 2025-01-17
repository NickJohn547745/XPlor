#ifndef FFPARSER_H
#define FFPARSER_H

#include "enums.h"
#include "structs.h"

#include <QDataStream>
#include <QDebug>

class FastFileParser {
public:
    static FF_COMPANY ParseFFCompany(QDataStream *afastFileStream) {
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

    static FF_FILETYPE ParseFFFileType(QDataStream *afastFileStream) {
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

    static FF_SIGNAGE ParseFFSignage(QDataStream *afastFileStream) {
        // Parse filetype
        QByteArray signedData(1, Qt::Uninitialized);
        afastFileStream->readRawData(signedData.data(), 1);
        if (signedData == "u") {
            qDebug() << "Found valid signage: Unsigned";
            return SIGNAGE_UNSIGNED;
        } else if (signedData == "0") {
            qDebug() << "Found valid signage: Signed";
            return SIGNAGE_SIGNED;
        } else {
            qDebug() << "Failed to determine signage of fastfile!";
        }
        return SIGNAGE_NONE;
    }

    static QString ParseFFMagic(QDataStream *afastFileStream) {
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

    static quint32 ParseFFVersion(QDataStream *afastFileStream) {
        // Parse version
        quint32 version;
        *afastFileStream >> version;
        qDebug() << "Version:" << version;
        if (version == 387) {
            qDebug() << QString("Found valid version: '%1'").arg(version);
            return 387;
        } else {
            qDebug() << "Version invalid!";
        }
        return -1;
    }

    static FastFile ParseFFHeader(QDataStream *afastFileStream) {
        FastFile fastFile;
        fastFile.company = ParseFFCompany(afastFileStream);
        fastFile.fileType = ParseFFFileType(afastFileStream);
        fastFile.signage = ParseFFSignage(afastFileStream);
        fastFile.magic = ParseFFMagic(afastFileStream);
        fastFile.version = ParseFFVersion(afastFileStream);
        return fastFile;
    }
};

#endif // FFPARSER_H
