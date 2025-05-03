#ifndef FASTFILE_FACTORY_H
#define FASTFILE_FACTORY_H

#include "360/fastfile_cod2_360.h"
//#include "360/fastfile_cod3_360.h"
//#include "360/fastfile_cod4_360.h"
#include "360/fastfile_cod5_360.h"
//#include "360/fastfile_cod6_360.h"
#include "360/fastfile_cod7_360.h"
//#include "360/fastfile_cod8_360.h"
#include "360/fastfile_cod9_360.h"
//#include "360/fastfile_cod10_360.h"
//#include "360/fastfile_cod11_360.h"
//#include "360/fastfile_cod12_360.h"

//#include "PS3/fastfile_cod3_ps3.h"
//#include "PS3/fastfile_cod4_ps3.h"
#include "PS3/fastfile_cod5_ps3.h"
//#include "PS3/fastfile_cod6_ps3.h"
#include "PS3/fastfile_cod7_ps3.h"
//#include "PS3/fastfile_cod8_ps3.h"
#include "PS3/fastfile_cod9_ps3.h"
//#include "PS3/fastfile_cod10_ps3.h"
//#include "PS3/fastfile_cod11_ps3.h"
//#include "PS3/fastfile_cod12_ps3.h"

//#include "PC/fastfile_cod3_pc.h"
//#include "PC/fastfile_cod4_pc.h"
#include "PC/fastfile_cod5_pc.h"
//#include "PC/fastfile_cod6_pc.h"
#include "PC/fastfile_cod7_pc.h"
//#include "PC/fastfile_cod8_360.h"
#include "PC/fastfile_cod9_pc.h"
//#include "PC/fastfile_cod10_pc.h"
//#include "PC/fastfile_cod11_pc.h"
#include "PC/fastfile_cod12_pc.h"

#include "Wii//fastfile_cod7_wii.h"

#include "WiiU/fastfile_cod9_wiiu.h"
//#include "WiiU/fastfile_cod10_wiiu.h"

#include <QByteArray>
#include <QString>
#include <memory>
#include <QFile>
#include <QDebug>

class FastFile;

enum FastFile_Platform {
    PLATFORM_NONE = 0x00,
    PLATFORM_PC   = 0x01,
    PLATFORM_360  = 0x02,
    PLATFORM_PS3  = 0x03,
    PLATFORM_WII  = 0x04,
    PLATFORM_WIIU = 0x05
};

enum FastFile_Game {
    GAME_NONE  = 0x00,
    GAME_COD2  = 0x01,
    GAME_COD3  = 0x02,
    GAME_COD4  = 0x03,
    GAME_COD5  = 0x04,
    GAME_COD6  = 0x05,
    GAME_COD7  = 0x06,
    GAME_COD8  = 0x07,
    GAME_COD9  = 0x08,
    GAME_COD10 = 0x09,
    GAME_COD11 = 0x010,
    GAME_COD12 = 0x011
};

class FastFileFactory {
public:
    static std::shared_ptr<FastFile> Create(const QString& aFilePath) {
        QFile fastFile(aFilePath);
        if (!fastFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Factory failed to open fast file: " << aFilePath;
            return nullptr;
        }

        const QString stem = aFilePath.split('/').last().split('.').first();
        const QByteArray data = fastFile.readAll();
        std::shared_ptr<FastFile> resultFF = nullptr;
        if (pGetPlatform(data) == PLATFORM_360) {
            if (pGetGame(data) == GAME_COD2) {
                resultFF = std::make_shared<FastFile_COD2_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_360>(aFilePath);
            } else if (pGetGame(data) == GAME_COD12) {
                //resultFF = std::make_shared<FastFile_COD12_360>(aFilePath);
            }
        } else if (pGetPlatform(data) == PLATFORM_PC) {
            if (pGetGame(data) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_PC>(aFilePath);
            } else if (pGetGame(data) == GAME_COD12) {
                resultFF = std::make_shared<FastFile_COD12_PC>(aFilePath);
            }
        } else if (pGetPlatform(data) == PLATFORM_PS3) {
            if (pGetGame(data) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_PS3>(aFilePath);
            } else if (pGetGame(data) == GAME_COD12) {
                //resultFF = std::make_shared<FastFile_COD12_PS3>(aFilePath);
            }
        } else if (pGetPlatform(data) == PLATFORM_WII) {
            if (pGetGame(data) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_Wii>(aFilePath);
            }
        } else if (pGetPlatform(data) == PLATFORM_WIIU) {
            if (pGetGame(data) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_WiiU>(aFilePath);
            } else if (pGetGame(data) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_WiiU>(aFilePath);
            }
        }
        return resultFF;
    }
    static std::shared_ptr<FastFile> Create(const QByteArray& aData, const QString aStem = "no_name") {
        std::shared_ptr<FastFile> resultFF = nullptr;
        if (pGetPlatform(aData) == PLATFORM_360) {
            if (pGetGame(aData) == GAME_COD2) {
                resultFF = std::make_shared<FastFile_COD2_360>(aData);
            } else if (pGetGame(aData) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_360>(data);
            } else if (pGetGame(aData) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_360>(data);
            } else if (pGetGame(aData) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_360>(aData);
            } else if (pGetGame(aData) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_360>(data);
            } else if (pGetGame(aData) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_360>(aData);
            } else if (pGetGame(aData) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_360>(data);
            } else if (pGetGame(aData) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_360>(aData);
            } else if (pGetGame(aData) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_360>(data);
            } else if (pGetGame(aData) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_360>(data);
            } else if (pGetGame(aData) == GAME_COD12) {
                //resultFF = std::make_shared<FastFile_COD12_360>(data);
            }
        } else if (pGetPlatform(aData) == PLATFORM_PC) {
            if (pGetGame(aData) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_PC>(data);
            } else if (pGetGame(aData) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_PC>(data);
            } else if (pGetGame(aData) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_PC>(aData);
            } else if (pGetGame(aData) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_PC>(data);
            } else if (pGetGame(aData) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_PC>(aData);
            } else if (pGetGame(aData) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_PC>(data);
            } else if (pGetGame(aData) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_PC>(aData);
            } else if (pGetGame(aData) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_PC>(data);
            } else if (pGetGame(aData) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_PC>(data);
            } else if (pGetGame(aData) == GAME_COD12) {
                //resultFF = std::make_shared<FastFile_COD12_PC>(data);
            }
        } else if (pGetPlatform(aData) == PLATFORM_PS3) {
            if (pGetGame(aData) == GAME_COD3) {
                //resultFF = std::make_shared<FastFile_COD3_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD4) {
                //resultFF = std::make_shared<FastFile_COD4_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD5) {
                resultFF = std::make_shared<FastFile_COD5_PS3>(aData);
            } else if (pGetGame(aData) == GAME_COD6) {
                //resultFF = std::make_shared<FastFile_COD6_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_PS3>(aData);
            } else if (pGetGame(aData) == GAME_COD8) {
                //resultFF = std::make_shared<FastFile_COD8_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_PS3>(aData);
            } else if (pGetGame(aData) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD11) {
                //resultFF = std::make_shared<FastFile_COD11_PS3>(data);
            } else if (pGetGame(aData) == GAME_COD12) {
                //resultFF = std::make_shared<FastFile_COD12_PS3>(data);
            }
        } else if (pGetPlatform(aData) == PLATFORM_WII) {
            if (pGetGame(aData) == GAME_COD7) {
                resultFF = std::make_shared<FastFile_COD7_Wii>(aData);
            }
        } else if (pGetPlatform(aData) == PLATFORM_WIIU) {
            if (pGetGame(aData) == GAME_COD9) {
                resultFF = std::make_shared<FastFile_COD9_WiiU>(aData);
            } else if (pGetGame(aData) == GAME_COD10) {
                //resultFF = std::make_shared<FastFile_COD10_WiiU>(data);
            }
        }
        if (resultFF) {
            resultFF->SetStem(aStem);
        }
        return resultFF;
    }
private:
    static QStringList pGetDataSections(const QByteArray& aData) {
        QStringList sections;

        sections << aData.mid(0, 2).toHex().toUpper();
        sections << aData.mid(2, 2).toHex().toUpper();
        sections << aData.mid(4, 2).toHex().toUpper();
        sections << aData.mid(6, 2).toHex().toUpper();
        sections << aData.mid(8, 2).toHex().toUpper();
        sections << aData.mid(10, 2).toHex().toUpper();

        return sections;
    }

    static FastFile_Platform pGetPlatform(const QByteArray& aData) {
        const QStringList sections = pGetDataSections(aData);
        if (sections[0] == "0000") {
            return PLATFORM_360;
        } else if (sections[4] == "0000") {
            if (sections[5] == "0001" ||
                sections[5] == "0183" ||
                sections[5] == "010D" ||
                sections[5] == "01D9" ||
                sections[5] == "0070" ||
                sections[5] == "0092" ||
                sections[5] == "022E" ||
                sections[5] == "072E" ||
                sections[5] == "0253") {
                return PLATFORM_360;
            }
        } else if (sections[5] == "0000") {
            return PLATFORM_PC;
        }
        return PLATFORM_NONE;
    }

    static FastFile_Game pGetGame(const QByteArray& aData) {
        const QStringList sections = pGetDataSections(aData);
        if (sections[0] == "0000") {
            return GAME_COD2;
        } else if (sections[5] == "0183") {
            return GAME_COD5;
        } else if (sections[0] == "5331") {
            return GAME_COD11;
        } else if (sections[2] == "3030") {
            return GAME_COD12;
        }
        return GAME_NONE;
    }
};

#endif // FASTFILE_FACTORY_H
