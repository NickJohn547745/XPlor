#ifndef ASSET_STRUCTS_H
#define ASSET_STRUCTS_H

#include "enums.h"

#include <QString>
#include <QColor>
#include <QRectF>
#include <QMap>

enum AssetType {
    ASSET_NONE = 0x00,
    ASSET_RAW_FILE = 0x01,
    ASSET_SCRIPT_PARSE_TREE = 0x02,
    ASSET_EFFECT = 0x03,
    ASSET_SOUND = 0x04,
    ASSET_ANIMATION = 0x05,
    ASSET_COLLISION_MAP = 0x06,
    ASSET_STRING_TABLE = 0x07,
    ASSET_MENU = 0x08,
    ASSET_TECH_SET = 0x09,
    ASSET_WEAPON = 0x10,
    ASSET_GFX_MAP = 0x11,
    ASSET_LIGHT_DEF = 0x12,
    ASSET_FONT = 0x13,
    ASSET_MODEL = 0x14,
    ASSET_D3DBSP = 0x15,
    ASSET_IMAGE = 0x16,
    ASSET_GAME_MAP_SP = 0x17,
    ASSET_COL_MAP_SP = 0x18,
    ASSET_PHYS_PRESET = 0x19,
    ASSET_DESTRUCTIBLE = 0x20,
    ASSET_LOCAL_STRING = 0x21,
    ASSET_SHADER = 0x22,
    ASSET_MP_MAP = 0x23,
    ASSET_SP_MAP = 0x24,
    ASSET_UI_MAP = 0x25,
    ASSET_SND_DRIVER_GLOBALS = 0x26,
    ASSET_AI_TYPE = 0x27,
    ASSET_MATERIAL = 0x28,
    ASSET_COMPUTE_SHADER_SET = 0x29,
    ASSET_LIGHT_DESCRIPTION = 0x30,
    ASSET_BIT_FIELD = 0x31,
    ASSET_STRUCTURED_TABLE = 0x32,
    ASSET_LEADERBOARD_DEF = 0x33,
    ASSET_DDL = 0x34,
    ASSET_KEY_VALUE_PAIRS = 0x35,
    ASSET_SCRIPT_BUNDLE = 0x36,
    ASSET_SCRIPT_BUNDLE_LIST = 0x37,
    ASSET_MAP_TABLE = 0x38,
    ASSET_MAP_TABLE_LOADING_IMAGES = 0x39,
    ASSET_SURFACE_SOUND_DEF = 0x40,
    ASSET_SURFACE_FX_TABLE = 0x41,
    ASSET_RUMBLE = 0x42,
    ASSET_AIM_TABLE = 0x43,
    ASSET_MEDAL = 0x44,
    ASSET_MEDAL_TABLE = 0x45,
    ASSET_OBJECTIVE = 0x46,
    ASSET_OBJECTIVE_LIST = 0x47,
    ASSET_LASER = 0x48,
    ASSET_BEAM = 0x49,
    ASSET_STREAMER_HINT = 0x50,
    ASSET_ANIM_SELECTOR_TABLE = 0x51,
    ASSET_ANIM_MAPPING_TABLE = 0x52,
    ASSET_ANIM_STATE_MACHINE = 0x53,
    ASSET_BEHAVIOR_TREE = 0x54,
    ASSET_BEHAVIOR_STATE_MACHINE = 0x55,
    ASSET_FOOTSTEP_TABLE = 0x56,
    ASSET_ENTITY_FX_IMPACTS = 0x57,
    ASSET_ENTITY_SOUND_IMPACTS = 0x58,
    ASSET_VEHICLE_FX_DEF = 0x59,
    ASSET_VEHICLE_SOUND_DEF = 0x60,
    ASSET_VEHICLE = 0x61,
    ASSET_VEHICLE_TRACER = 0x62,
    ASSET_PLAYER_SOUNDS_TABLE = 0x63,
    ASSET_PLAYER_FX_TABLE = 0x64,
    ASSET_SHARED_WEAPON_SOUNDS = 0x65,
    ASSET_ATTACHMENT = 0x66,
    ASSET_ATTACHMENT_UNIQUE = 0x67,
    ASSET_WEAPON_CAMO = 0x68,
    ASSET_CUSTOMIZATION_TABLE = 0x69,
    ASSET_CUSTOMIZATION_TABLE_FEIMAGES = 0x70,
    ASSET_CUSTOMIZATION_TABLE_COLOR = 0x71,
    ASSET_PHYS_CONSTRAINTS = 0x72,
    ASSET_DESTRUCTIBLE_DEF = 0x73,
    ASSET_MODEL_MESH = 0x74,
    ASSET_S_ANIM = 0x75,
    ASSET_FONT_ICON = 0x76,
    ASSET_CG_MEDIA_TABLE = 0x77
};

struct LocalString {
    QString string;
    QString alias;
};

struct RawFile {
    quint32 length;
    QString path;
    QString contents;
};

struct GscFile {
    quint64 length;
    QString path;
    QString contents;
};

struct TechSet {
    QString name;
    bool hasShaders = false;
    QVector<quint32> pointers;
};

struct Shader {
    quint32 shaderPtr;
};

struct XModelCollSurf_s
{
    float mins[3];
    float maxs[3];
    int boneIdx;
    int contents;
    int surfFlags;
};

struct XModelLodInfo
{
    float dist;
    unsigned short numsurfs;
    unsigned short surfIndex;
    int partBits[5];
};

struct XModelHighMipBounds
{
    float mins[3];
    float maxs[3];
};

struct XModelStreamInfo
{
    XModelHighMipBounds *highMipBounds;
};

struct XBoneInfo
{
    float bounds[2][3];
    float offset[3];
    float radiusSquared;
};

struct Model {
    quint32 namePtr;
    quint8 tagCount;
    quint8 rootTagCount;
    quint8 surfCount;
    quint8 unknownCount;
    quint32 boneNamePtr;
    quint32 parentListPtr;
    quint32 quatsPtr;
    quint32 transPtr;
    quint32 partClassPtr;
    quint32 baseMatPtr;
    quint32 surfsPtr;
    quint32 materialHandlesPtr;

    XModelLodInfo lodInfo[4];
    quint32 collSurfsPtr;
    int numCollSurfs;
    int contents;
    quint32 boneInfoPtr;
    float radius;
    float mins[3];
    float maxs[3];
    short numLods;
    short collLod;
    quint32 streamInfoPtr;	// is not loaded on ps3
    int memUsage;
    char flags;
    quint32 physPresetPtr;
    quint32 physGeomsPtr;

    QString modelName;
};

struct Animation {
    quint16 dataByteCount;
    quint16 dataShortCount;
    quint16 dataIntCount;
    quint16 randomDataByteCount;
    quint16 randomDataIntCount;
    quint16 numframes;
    bool isLooped;
    bool isDelta;
    quint8 noneRotatedBoneCount;
    quint8 twoDRotatedBoneCount;
    quint8 normalRotatedBoneCount;
    quint8 twoDStaticRotatedBoneCount;
    quint8 normalStaticRotatedBoneCount;
    quint8 normalTranslatedBoneCount;
    quint8 preciseTranslatedBoneCount;
    quint8 staticTranslatedBoneCount;
    quint8 noneTranslatedBoneCount;
    quint8 totalBoneCount;
    quint8 otherBoneCount1;
    quint8 otherBoneCount2;
    quint8 notifyCount;
    quint8 assetType;
    bool pad;
    unsigned int randomDataShortCount;
    unsigned int indexCount;
    float frameRate;
    float frequency;
    quint32 boneIDsPtr;
    quint32 dataBytePtr;
    quint32 dataShortPtr;
    quint32 dataIntPtr;
    quint32 randomDataShortPtr;
    quint32 randomDataBytePtr;
    quint32 randomDataIntPtr;
    quint32 longIndiciesPtr;
    quint32 notificationsPtr;
    quint32 deltaPartsPtr;
    QString name;
};

struct StringTable {
    quint32 columnCount;
    quint32 rowCount;
    QString name;
    QVector<QString> tablePointers;
    QMap<QString, QString> content;
};

struct Image {
    QString name;
    QString materialName;
    quint32 size1;
    quint32 size2;
    IMAGE_COMPRESSION compression;
    quint32 unknowna;
    quint32 unknownb;
    quint32 unknownc;
    quint32 unknownd;
    quint32 unknowne;
    quint32 unknownf;
    quint32 unknowng;
    quint32 unknownh;
    quint32 unknowni;
    quint32 unknownj;
    quint32 unknownk;
    quint32 unknownl;
    quint32 unknownm;
    quint32 unknown1;
    quint32 unknown2;
    quint32 unknown3;
    quint32 unknown4;
    quint32 unknown5;
    quint32 unknown6;
    quint32 unknown7;
    quint32 unknown8;
    quint32 unknown9;
};

struct Material {
    qint32 namePtr;
    QString name;
    quint32 refNamePtr;
    QString refName;
    QVector<quint32> pointers;
    quint32 stateBits[2];
    quint16 textureCount;
    quint16 constCount;
    quint32 techSetPtr;
    quint32 texturePtr;
    quint32 constPtr;
};

struct Menu {
    QString filePath;
    QString name;
    QString definition;
    quint32 menuNamePtr;
    QRectF rect;
    MENU_H_ALIGNMENT hAlign;
    MENU_V_ALIGNMENT vAlign;
    QRectF clientRect;
    MENU_H_ALIGNMENT hClientAlign;
    MENU_V_ALIGNMENT vClientAlign;
    quint32 groupPtr;
    MENU_WINDOW_STYLE style;
    MENU_WINDOW_BORDER border;
    quint32 ownerDraw;
    quint32 ownerDrawFlags;
    float borderSize;
    int staticFlags;
    float dynamicFlags;
    float nextTime;
    QColor foregroundColor;
    QColor backgroundColor;
    QColor borderColor;
    QColor outlineColor;
    quint32 materialPtr;
    quint32 fontPtr;
    quint32 fullScreen;
    quint32 itemCount;
    quint32 fontIndex;
    quint32 cursorItem;
    quint32 fadeCycle;
    float fadeClamp;
    float fadeAmount;
    float fadeInAmount;
    float blurRadius;
    quint32 onOpenPtr;
    quint32 onFocusPtr;
    quint32 onClosePtr;
    quint32 onESCPtr;
    quint32 onKeyPtr;
    quint32 visibleExpCount;
    quint32 expEntryPtr;
    quint32 allowedBindingPtr;
    quint32 soundNamePtr;
    quint32 imageTrack;
    QColor focusColor;
    QColor disabledColor;
    quint32 rectXExpCount;
    quint32 rectXExpPtr;
    quint32 rectYExpCount;
    quint32 rectYExpPtr;
    quint32 itemWindowDefNamePtr;
    QRectF itemRect;
    MENU_H_ALIGNMENT itemHAlignment;
    MENU_V_ALIGNMENT itemVAlignment;
    quint32 itemGroupPtr;
    MENU_WINDOW_STYLE itemWindowStyle;
    MENU_WINDOW_BORDER itemWindowBorder;
    quint32 itemOwnerDraw;
    quint32 itemOwnerDrawFlags;
    float itemBorderSize;
    int itemStaticFlags;
    int itemDynamicFlags;
    int itemNextTime;
    QColor itemForegroundColor;
    QColor itemBackgroundColor;
    QColor itemBorderColor;
    QColor itemOutlineColor;
    quint32 itemMaterialPtr;
    QRectF itemTextRect;
    MENU_H_ALIGNMENT itemText_hAlign;
    MENU_V_ALIGNMENT itemText_vAlign;
    MENU_ITEM_TYPE itemType;
    quint32 dataType;
    quint32 alignment;
    MENU_FONT_TYPE fontEnum;
    quint32 textAlignMode;
    float textalignx;
    float textaligny;
    float textscale;
    MENU_ITEM_TEXTSTYLE textStyle;
    int gameMsgWindowIndex;
    int gameMsgWindowMode;
    quint32 testPtr;
    quint32 textSavegameInfo;
    quint32 parentPtr;
    quint32 mouseEnterText;
    quint32 mouseExitText;
    quint32 mouseEnter;
    quint32 mouseExit;
    quint32 action;
    quint32 onAccept;
    quint32 onFocus;
    quint32 leaveFocus;
    quint32 dvar;
    quint32 dvarTest;
    quint32 keyHandlerPtr;
    quint32 enableDvarPtr;
    quint32 dvarFlags;
    quint32 focusSoundPtr;
    float special;
    quint32 cursorPos;
    // itemDefData_t typeData;
    // listBoxDef_s *listBox;
    quint32 startPos;
    quint32 endPos;
    quint32 drawPadding;
    float elementWidth, elementHeight;
    quint32 elementStyle, numColumns;
    //columnInfo_s columnInfo[16];
    quint32 doubleClickPtr;
    int notselectable;
    int noScrollBars;
    int usePaging;
    QColor itemSelectBorderColor;
    QColor itemDisableColor;
    QColor itemFocusColor;
    quint32 selectIconPtr;
    quint32 backgroundItemListboxPtr;
    quint32 highlightTexturePtr;
    // editFieldDef_s *editField;
    float minVal;
    float maxVal;
    float defVal;
    float range;
    int maxChars;
    int maxCharsGotoNext;
    int maxPaintChars;
    int paintOffset;
    // multiDef_s *multi;
    QVector<quint32> dvarListPtrs;
    QVector<quint32> dvarStrPtrs;
    QVector<float> dvarValues;
    quint32 count;
    quint32 strDef;
    quint32 enumDvarNamePtr;
    quint32 dataPtr;
    quint32 itemImageTrack;
};

struct MenuFile {
    quint32 menuCount;
    QVector<Menu> menuDefs;
};

struct Sound {
    QString path;
    QString alias;
    quint32 dataPtr;
    quint32 dataLength;
    QByteArray data;
};

struct SoundAsset {
    QString name;
    quint32 count;
    QVector<Sound> sounds;
};

struct AssetMap {
    QVector<LocalString> localStrings;
    QVector<RawFile> rawFiles;
    QVector<GscFile> gscFiles;
    //QVector<PhysPreset> phyPresets;
    QVector<Model> models;
    QVector<Material> materials;
    //QVector<Shader> shaders;
    QVector<TechSet> techSets;
    QVector<Image> images;
    QVector<SoundAsset> sounds;
    //QVector<CollisionMap> collMaps;
    //QVector<LightDefinition> lightDefs;
    //QVector<UiMap> uiMaps;
    //QVector<DriverGlobal> driverGlobals;
    //QVector<AiType> aiType;
    //QVector<Effect> effects;
    QVector<Animation> animations;
    QVector<StringTable> stringTables;
    QVector<MenuFile> menuFiles;
    //QVector<Weapon> weapons;
    //QVector<D3DBSP> d3dbspDumps;
    //QVector<SingleplayerMap> spMaps;
};

#endif // ASSET_STRUCTS_H
