#ifndef UTILS_H
#define UTILS_H

#include "enums.h"

#include <QString>
#include <QtZlib/zlib.h>
#include <QFileDialog>
#include <QMessageBox>

class Utils {
public:
    /*
    AssetTypeToString()

    Convert asset type string to asset desc string
*/
    static QString AssetTypeToString(const QString aAssetType) {
        const QString cleanedType = aAssetType.toUpper();
        if (cleanedType == "17000000") {        // localized string       PARTIALLY VERIFIED
            return "LOCAL STRING";
        } else if (cleanedType == "20000000") { // raw_file               PARTIALLY VERIFIED
            return "RAW FILE";
        } else if (cleanedType == "1A000000") { // fx                     PARTIALLY VERIFIED
            return "EFFECT";
        } else if (cleanedType == "09000000") { // loaded_sound           PARTIALLY VERIFIED
            return "SOUND";
        } else if (cleanedType == "04000000") { // x_anim                 PARTIALLY VERIFIED
            return "ANIMATION";
        } else if (cleanedType == "0C000000") { // collision_map          PARTIALLY VERIFIED
            return "COLLISION MAP";
        } else if (cleanedType == "21000000") { // string_table           PARTIALLY VERIFIED
            return "STRING TABLE";
        } else if (cleanedType == "15000000") { // menu_file              PARTIALLY VERIFIED
            return "MENU";
        } else if (cleanedType == "07000000") { // tech set               PARTIALLY VERIFIED
            return "TECH SET";
        } else if (cleanedType == "18000000") { // weapon                 PARTIALLY VERIFIED
            return "WEAPON";
        } else if (cleanedType == "11000000") { // d3dbsp dump            PARTIALLY VERIFIED
            return "D3DBSP DUMP";
        } else if (cleanedType == "12000000") { // light_def              PARTIALLY VERIFIED
            return "LIGHT DEF";
        } else if (cleanedType == "14000000") { // font                   PARTIALLY VERIFIED
            return "FONT";
        } else if (cleanedType == "05000000") { // xmodel                 PARTIALLY VERIFIED
            return "MODEL";
        } else if (cleanedType == "0D000000") { // shader                 PARTIALLY VERIFIED
            return "SHADER";
        }
        return "UNKNOWN";
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
    }

    static QString FileTypeEnumToStr(FF_FILETYPE aFileType) {
        switch (aFileType) {
        case FILETYPE_NONE:
            return "None";
        case FILETYPE_FAST_FILE:
            return "Fast File";
        }
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
    }
};

#endif // UTILS_H
