#ifndef UTILS_H
#define UTILS_H

#include "enums.h"

#include <QString>
#include <QtZlib/zlib.h>
#include <QFileDialog>
#include <QMessageBox>

class Utils {
public:
    static bool ExportData(const QString aFileName, const QByteArray aData) {
        QDir workingDir = QDir::currentPath();
        workingDir.mkdir("exports");

        QFile testFile("exports/" + aFileName);
        if(!testFile.open(QIODevice::WriteOnly)) {
            return false;
        }
        testFile.write(aData);
        testFile.close();
        return true;
    }
    static bool ReadUntilString(QDataStream* stream, const QString& targetString) {
        if (!stream || targetString.isEmpty()) {
            return false; // Invalid input
        }

        QByteArray buffer;
        QByteArray targetBytes = targetString.toUtf8(); // Handle multibyte characters
        const int targetLength = targetBytes.size();
        qDebug() << targetBytes << targetLength;

        // Read as unsigned bytes to handle all possible values (0-255)
        unsigned char byte;
        while (!stream->atEnd()) {
            // Read one byte at a time
            *stream >> byte;
            buffer.append(static_cast<char>(byte)); // Append as char for QByteArray

            // Keep buffer size limited to the target length
            if (buffer.size() > targetLength) {
                buffer.remove(0, 1);
            }

            // Check if the buffer matches the target string in raw bytes
            if (buffer == targetBytes) {
                // Backup to the start of the matched string
                stream->device()->seek(stream->device()->pos() - targetLength);
                return true;
            }
        }

        // Target string not found
        return false;
    }

    static bool ReadUntilHex(QDataStream* stream, const QString& hexString) {
        if (!stream || hexString.isEmpty() || hexString.size() % 2 != 0) {
            return false; // Invalid input
        }

        // Convert hex string to byte array
        QByteArray targetBytes = QByteArray::fromHex(hexString.toUtf8());
        const int targetLength = targetBytes.size();

        QByteArray buffer;
        unsigned char byte;

        while (!stream->atEnd()) {
            // Read one byte at a time
            *stream >> byte;
            buffer.append(static_cast<char>(byte)); // Append as char for QByteArray

            // Keep buffer size limited to the target length
            if (buffer.size() > targetLength) {
                buffer.remove(0, 1);
            }

            // Check if the buffer matches the target byte sequence
            if (buffer == targetBytes) {
                // Backup to the start of the matched sequence
                stream->device()->seek(stream->device()->pos() - targetLength);
                return true;
            }
        }

        // Target sequence not found
        return false;
    }

    /*
    LumpTypeToString()

    Convert BSP lump type to desc string
*/
    static QString LumpTypeToString(LUMP_TYPE aLumpType) {
        switch (aLumpType) {
        case LUMP_MATERIALS: return "LUMP_MATERIALS";
        case LUMP_LIGHTBYTES: return "LUMP_LIGHTBYTES";
        case LUMP_LIGHTGRIDENTRIES: return "LUMP_LIGHTGRIDENTRIES";
        case LUMP_LIGHTGRIDCOLORS: return "LUMP_LIGHTGRIDCOLORS";
        case LUMP_PLANES: return "LUMP_PLANES";
        case LUMP_BRUSHSIDES: return "LUMP_BRUSHSIDES";
        case LUMP_BRUSHSIDEEDGECOUNTS: return "LUMP_BRUSHSIDEEDGECOUNTS";
        case LUMP_BRUSHEDGES: return "LUMP_BRUSHEDGES";
        case LUMP_BRUSHES: return "LUMP_BRUSHES";
        case LUMP_TRIANGLES: return "LUMP_TRIANGLES";
        case LUMP_DRAWVERTS: return "LUMP_DRAWVERTS";
        case LUMP_DRAWINDICES: return "LUMP_DRAWINDICES";
        case LUMP_CULLGROUPS: return "LUMP_CULLGROUPS";
        case LUMP_CULLGROUPINDICES: return "LUMP_CULLGROUPINDICES";
        case LUMP_OBSOLETE_1: return "LUMP_OBSOLETE_1";
        case LUMP_OBSOLETE_2: return "LUMP_OBSOLETE_2";
        case LUMP_OBSOLETE_3: return "LUMP_OBSOLETE_3";
        case LUMP_OBSOLETE_4: return "LUMP_OBSOLETE_4";
        case LUMP_OBSOLETE_5: return "LUMP_OBSOLETE_5";
        case LUMP_PORTALVERTS: return "LUMP_PORTALVERTS";
        case LUMP_OBSOLETE_6: return "LUMP_OBSOLETE_6";
        case LUMP_UINDS: return "LUMP_UINDS";
        case LUMP_BRUSHVERTSCOUNTS: return "LUMP_BRUSHVERTSCOUNTS";
        case LUMP_BRUSHVERTS: return "LUMP_BRUSHVERTS";
        case LUMP_AABBTREES: return "LUMP_AABBTREES";
        case LUMP_CELLS: return "LUMP_CELLS";
        case LUMP_PORTALS: return "LUMP_PORTALS";
        case LUMP_NODES: return "LUMP_NODES";
        case LUMP_LEAFS: return "LUMP_LEAFS";
        case LUMP_LEAFBRUSHES: return "LUMP_LEAFBRUSHES";
        case LUMP_LEAFSURFACES: return "LUMP_LEAFSURFACES";
        case LUMP_COLLISIONVERTS: return "LUMP_COLLISIONVERTS";
        case LUMP_COLLISIONTRIS: return "LUMP_COLLISIONTRIS";
        case LUMP_COLLISIONEDGEWALKABLE: return "LUMP_COLLISIONEDGEWALKABLE";
        case LUMP_COLLISIONBORDERS: return "LUMP_COLLISIONBORDERS";
        case LUMP_COLLISIONPARTITIONS: return "LUMP_COLLISIONPARTITIONS";
        case LUMP_COLLISIONAABBS: return "LUMP_COLLISIONAABBS";
        case LUMP_MODELS: return "LUMP_MODELS";
        case LUMP_VISIBILITY: return "LUMP_VISIBILITY";
        case LUMP_ENTITIES: return "LUMP_ENTITIES";
        case LUMP_PATHCONNECTIONS: return "LUMP_PATHCONNECTIONS";
        case LUMP_REFLECTION_PROBES: return "LUMP_REFLECTION_PROBES";
        case LUMP_VERTEX_LAYER_DATA: return "LUMP_VERTEX_LAYER_DATA";
        case LUMP_PRIMARY_LIGHTS: return "LUMP_PRIMARY_LIGHTS";
        case LUMP_LIGHTGRIDHEADER: return "LUMP_LIGHTGRIDHEADER";
        case LUMP_LIGHTGRIDROWS: return "LUMP_LIGHTGRIDROWS";
        case LUMP_OBSOLETE_10: return "LUMP_OBSOLETE_10";
        case LUMP_UNLAYERED_TRIANGLES: return "LUMP_UNLAYERED_TRIANGLES";
        case LUMP_UNLAYERED_DRAWVERTS: return "LUMP_UNLAYERED_DRAWVERTS";
        case LUMP_UNLAYERED_DRAWINDICES: return "LUMP_UNLAYERED_DRAWINDICES";
        case LUMP_UNLAYERED_CULLGROUPS: return "LUMP_UNLAYERED_CULLGROUPS";
        case LUMP_UNLAYERED_AABBTREES: return "LUMP_UNLAYERED_AABBTREES";
        case LUMP_WATERHEADER: return "LUMP_WATERHEADER";
        case LUMP_WATERCELLS: return "LUMP_WATERCELLS";
        case LUMP_WATERCELLDATA: return "LUMP_WATERCELLDATA";
        case LUMP_BURNABLEHEADER: return "LUMP_BURNABLEHEADER";
        case LUMP_BURNABLECELLS: return "LUMP_BURNABLECELLS";
        case LUMP_BURNABLECELLDATA: return "LUMP_BURNABLECELLDATA";
        case LUMP_SIMPLELIGHTMAPBYTES: return "LUMP_SIMPLELIGHTMAPBYTES";
        case LUMP_LODCHAINS: return "LUMP_LODCHAINS";
        case LUMP_LODINFOS: return "LUMP_LODINFOS";
        case LUMP_LODSURFACES: return "LUMP_LODSURFACES";
        case LUMP_LIGHTREGIONS: return "LUMP_LIGHTREGIONS";
        case LUMP_LIGHTREGION_HULLS: return "LUMP_LIGHTREGION_HULLS";
        case LUMP_LIGHTREGION_AXES: return "LUMP_LIGHTREGION_AXES";
        case LUMP_WIILIGHTGRID: return "LUMP_WIILIGHTGRID";
        case LUMP_LIGHTGRID2D_LIGHTS: return "LUMP_LIGHTGRID2D_LIGHTS";
        case LUMP_LIGHTGRID2D_INDICES: return "LUMP_LIGHTGRID2D_INDICES";
        case LUMP_LIGHTGRID2D_POINTS: return "LUMP_LIGHTGRID2D_POINTS";
        case LUMP_LIGHTGRID2D_CELLS: return "LUMP_LIGHTGRID2D_CELLS";
        case LUMP_LIGHT_CORONAS: return "LUMP_LIGHT_CORONAS";
        case LUMP_SHADOWMAP_VOLUMES: return "LUMP_SHADOWMAP_VOLUMES";
        case LUMP_SHADOWMAP_VOLUME_PLANES: return "LUMP_SHADOWMAP_VOLUME_PLANES";
        case LUMP_EXPOSURE_VOLUMES: return "LUMP_EXPOSURE_VOLUMES";
        case LUMP_EXPOSURE_VOLUME_PLANES: return "LUMP_EXPOSURE_VOLUME_PLANES";
        case LUMP_OCCLUDERS: return "LUMP_OCCLUDERS";
        case LUMP_OUTDOORBOUNDS: return "LUMP_OUTDOORBOUNDS";
        case LUMP_HERO_ONLY_LIGHTS: return "LUMP_HERO_ONLY_LIGHTS";
        default: return "Unknown Lump Type";
        }
        return "Unknown Lump Type";
    }

    static QString ZLibErrorToString(int result) {
        switch (result) {
        case Z_ERRNO:
            return "Encountered file operation error!";
        case Z_STREAM_ERROR:
            return "Stream was not initialized properly!";
        case Z_DATA_ERROR:
            return "The input data was corrupted or incomplete!";
        case Z_MEM_ERROR:
            return "There was not enough memory!";
        case Z_BUF_ERROR:
            return "There was not enough room in the output buffer!";
        case Z_VERSION_ERROR:
            return "Linked libraries are out of date!";
        }
        return "";
    }

    static quint32 PadInt4(quint32 size) {
        return (size + 3) & ~3; // Align size to 4 bytes
    }

    static quint32 PaddingSize(quint32 size) {
        return PadInt4(size) - size;
    }

    static QString GetOpenFastFileName(QWidget *parent = nullptr) {
        // Open file dialog to steam apps
        const QString steamPath = "C:/Program Files (x86)/Steam/steamapps/common/Call of Duty World at War/zone/english/";
        const QString fastFilePath = QFileDialog::getOpenFileName(parent, "Open Fast File", steamPath, "Fast File (*.ff);;All Files (*.*)");
        if (fastFilePath.isNull()) {
            // User pressed cancel
            return "";
        } else if (!QFile::exists(fastFilePath)) {
            QMessageBox::warning(parent, "Warning!", QString("%1 does not exist!.").arg(fastFilePath));
            return "";
        }
        return fastFilePath;
    }

    static QString GetOpenZoneFileName(QWidget *parent = nullptr) {
        // Open file dialog to steam apps
        const QString steamPath = "C:/Program Files (x86)/Steam/steamapps/common/Call of Duty World at War/zone/english/";
        const QString zoneFilePath = QFileDialog::getOpenFileName(parent, "Open Zone File", steamPath, "Zone File (*.zone);;All Files (*.*)");
        if (zoneFilePath.isNull()) {
            // User pressed cancel
            return "";
        } else if (!QFile::exists(zoneFilePath)) {
            QMessageBox::warning(parent, "Warning!", QString("%1 does not exist!.").arg(zoneFilePath));
            return nullptr;
        }
        return zoneFilePath;
    }

    static QString CompanyEnumToStr(FF_COMPANY aCompany) {
        switch (aCompany) {
        case COMPANY_NONE:
            return "None";
        case COMPANY_INFINITY_WARD:
            return "Infinity Ward";
        case COMPANY_TREYARCH:
            return "Treyarch";
        case COMPANY_SLEDGEHAMMER:
            return "Sledgehammer";
        case COMPANY_NEVERSOFT:
            return "Neversoft";
        }
        return "None";
    }

    static QString FileTypeEnumToStr(FF_FILETYPE aFileType) {
        switch (aFileType) {
        case FILETYPE_NONE:
            return "None";
        case FILETYPE_FAST_FILE:
            return "Fast File";
        }
        return "None";
    }

    static QString SignageEnumToStr(FF_SIGNAGE aSignage) {
        switch (aSignage) {
        case SIGNAGE_NONE:
            return "None";
        case SIGNAGE_SIGNED:
            return "Signed";
        case SIGNAGE_UNSIGNED:
            return "Unsigned";
        }
        return "None";
    }

    static QString MenuVAlignToStr(MENU_V_ALIGNMENT align) {
        if (align == VERTICAL_ALIGN_SUBTOP) {
            return "VERTICAL_ALIGN_SUBTOP";
        } else if (align == VERTICAL_ALIGN_TOP) {
            return "VERTICAL_ALIGN_TOP";
        } else if (align == VERTICAL_ALIGN_CENTER) {
            return "VERTICAL_ALIGN_CENTER";
        } else if (align == VERTICAL_ALIGN_BOTTOM) {
            return "VERTICAL_ALIGN_BOTTOM";
        } else if (align == VERTICAL_ALIGN_FULLSCREEN) {
            return "VERTICAL_ALIGN_FULLSCREEN";
        } else if (align == VERTICAL_ALIGN_NOSCALE) {
            return "VERTICAL_ALIGN_NOSCALE";
        } else if (align == VERTICAL_ALIGN_TO480) {
            return "VERTICAL_ALIGN_TO480";
        } else if (align == VERTICAL_ALIGN_CENTER_SAFEAREA) {
            return "VERTICAL_ALIGN_CENTER_SAFEAREA";
        } else if (align == VERTICAL_ALIGN_MAX) {
            return "VERTICAL_ALIGN_CENTER_SAFEAREA";
        } else if (align == VERTICAL_ALIGN_DEFAULT) {
            return "VERTICAL_ALIGN_SUBTOP";
        }
        return "VERTICAL_ALIGN_SUBTOP";
    }

    static QString MenuHAlignToStr(MENU_H_ALIGNMENT align) {
        if (align == HORIZONTAL_ALIGN_SUBLEFT) {
            return "HORIZONTAL_ALIGN_SUBLEFT";
        } else if (align == HORIZONTAL_ALIGN_LEFT) {
            return "HORIZONTAL_ALIGN_LEFT";
        } else if (align == HORIZONTAL_ALIGN_CENTER) {
            return "HORIZONTAL_ALIGN_CENTER";
        } else if (align == HORIZONTAL_ALIGN_RIGHT) {
            return "HORIZONTAL_ALIGN_RIGHT";
        } else if (align == HORIZONTAL_ALIGN_FULLSCREEN) {
            return "HORIZONTAL_ALIGN_FULLSCREEN";
        } else if (align == HORIZONTAL_ALIGN_NOSCALE) {
            return "HORIZONTAL_ALIGN_NOSCALE";
        } else if (align == HORIZONTAL_ALIGN_TO640) {
            return "HORIZONTAL_ALIGN_TO640";
        } else if (align == HORIZONTAL_ALIGN_CENTER_SAFEAREA) {
            return "HORIZONTAL_ALIGN_CENTER_SAFEAREA";
        } else if (align == HORIZONTAL_ALIGN_MAX) {
            return "HORIZONTAL_ALIGN_CENTER_SAFEAREA";
        } else if (align == HORIZONTAL_ALIGN_DEFAULT) {
            return "HORIZONTAL_ALIGN_SUBLEFT";
        }
        return "HORIZONTAL_ALIGN_SUBLEFT";
    }

    static QColor ColorFromNormalized(float r, float g, float b, float a) {
        // Ensure values are clamped between 0 and 1
        r = qBound(0.0f, r, 1.0f);
        g = qBound(0.0f, g, 1.0f);
        b = qBound(0.0f, b, 1.0f);
        a = qBound(0.0f, a, 1.0f);

        // Convert to 0-255 scale
        int red = static_cast<int>(r * 255);
        int green = static_cast<int>(g * 255);
        int blue = static_cast<int>(b * 255);
        int alpha = static_cast<int>(a * 255);

        return QColor(red, green, blue, alpha);
    }
};

#endif // UTILS_H
