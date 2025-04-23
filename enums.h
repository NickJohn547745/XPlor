#ifndef ENUMS_H
#define ENUMS_H

#include "qtypes.h"
enum LUMP_TYPE
{
    LUMP_MATERIALS = 0x0,
    LUMP_LIGHTBYTES = 0x1,
    LUMP_LIGHTGRIDENTRIES = 0x2,
    LUMP_LIGHTGRIDCOLORS = 0x3,
    LUMP_PLANES = 0x4,
    LUMP_BRUSHSIDES = 0x5,
    LUMP_BRUSHSIDEEDGECOUNTS = 0x6,
    LUMP_BRUSHEDGES = 0x7,
    LUMP_BRUSHES = 0x8,
    LUMP_TRIANGLES = 0x9,
    LUMP_DRAWVERTS = 0xA,
    LUMP_DRAWINDICES = 0xB,
    LUMP_CULLGROUPS = 0xC,
    LUMP_CULLGROUPINDICES = 0xD,
    LUMP_OBSOLETE_1 = 0xE,
    LUMP_OBSOLETE_2 = 0xF,
    LUMP_OBSOLETE_3 = 0x10,
    LUMP_OBSOLETE_4 = 0x11,
    LUMP_OBSOLETE_5 = 0x12,
    LUMP_PORTALVERTS = 0x13,
    LUMP_OBSOLETE_6 = 0x14,
    LUMP_UINDS = 0x15,
    LUMP_BRUSHVERTSCOUNTS = 0x16,
    LUMP_BRUSHVERTS = 0x17,
    LUMP_AABBTREES = 0x18,
    LUMP_CELLS = 0x19,
    LUMP_PORTALS = 0x1A,
    LUMP_NODES = 0x1B,
    LUMP_LEAFS = 0x1C,
    LUMP_LEAFBRUSHES = 0x1D,
    LUMP_LEAFSURFACES = 0x1E,
    LUMP_COLLISIONVERTS = 0x1F,
    LUMP_COLLISIONTRIS = 0x20,
    LUMP_COLLISIONEDGEWALKABLE = 0x21,
    LUMP_COLLISIONBORDERS = 0x22,
    LUMP_COLLISIONPARTITIONS = 0x23,
    LUMP_COLLISIONAABBS = 0x24,
    LUMP_MODELS = 0x25,
    LUMP_VISIBILITY = 0x26,
    LUMP_ENTITIES = 0x27,
    LUMP_PATHCONNECTIONS = 0x28,
    LUMP_REFLECTION_PROBES = 0x29,
    LUMP_VERTEX_LAYER_DATA = 0x2A,
    LUMP_PRIMARY_LIGHTS = 0x2B,
    LUMP_LIGHTGRIDHEADER = 0x2C,
    LUMP_LIGHTGRIDROWS = 0x2D,
    LUMP_OBSOLETE_10 = 0x2E,

    //Obsolete in BO1/////////////////
    LUMP_UNLAYERED_TRIANGLES = 0x2F,
    LUMP_UNLAYERED_DRAWVERTS = 0x30,
    LUMP_UNLAYERED_DRAWINDICES = 0x31,
    LUMP_UNLAYERED_CULLGROUPS = 0x32,
    LUMP_UNLAYERED_AABBTREES = 0x33,
    //////////////////////////////////

    LUMP_WATERHEADER = 0x34,
    LUMP_WATERCELLS = 0x35,
    LUMP_WATERCELLDATA = 0x36,
    LUMP_BURNABLEHEADER = 0x37,
    LUMP_BURNABLECELLS = 0x38,
    LUMP_BURNABLECELLDATA = 0x39,
    LUMP_SIMPLELIGHTMAPBYTES = 0x3A,
    LUMP_LODCHAINS = 0x3B,
    LUMP_LODINFOS = 0x3C,
    LUMP_LODSURFACES = 0x3D,
    LUMP_LIGHTREGIONS = 0x3E,
    LUMP_LIGHTREGION_HULLS = 0x3F,
    LUMP_LIGHTREGION_AXES = 0x40,
    LUMP_WIILIGHTGRID = 0x41,
    LUMP_LIGHTGRID2D_LIGHTS = 0x42,
    LUMP_LIGHTGRID2D_INDICES = 0x43,
    LUMP_LIGHTGRID2D_POINTS = 0x44,
    LUMP_LIGHTGRID2D_CELLS = 0x45,
    LUMP_LIGHT_CORONAS = 0x46,

    //BO Specific/////////////////////////
    LUMP_SHADOWMAP_VOLUMES = 0x47,
    LUMP_SHADOWMAP_VOLUME_PLANES = 0x48,
    LUMP_EXPOSURE_VOLUMES = 0x49,
    LUMP_EXPOSURE_VOLUME_PLANES = 0x4A,
    LUMP_OCCLUDERS = 0x4B,
    LUMP_OUTDOORBOUNDS = 0x4C,
    LUMP_HERO_ONLY_LIGHTS = 0x4D,
    //////////////////////////////////////

    INFO_LUMP_TYPE_COUNT
};

enum BSPVERSION_TYPE
{
    BSPVERSION_COD_WAW = 31,
    BSPVERSION_COD_BO = 45
};

enum MENU_ITEM_TYPE {
    ITEM_TYPE_TEXT = 0,                             // simple text
    ITEM_TYPE_BUTTON = 1,                           // button, basically text with a border
    ITEM_TYPE_RADIOBUTTON = 2,                      // toggle button, may be grouped
    ITEM_TYPE_CHECKBOX = 3,                         // check box
    ITEM_TYPE_EDITFIELD = 4,                        // editable text, associated with a dvar
    ITEM_TYPE_COMBO  = 5,                           // drop down list
    ITEM_TYPE_LISTBOX = 6,                          // scrollable list
    ITEM_TYPE_MODEL  = 7,                           // model
    ITEM_TYPE_OWNERDRAW = 8,                        // owner draw, name specs what it is
    ITEM_TYPE_NUMERICFIELD = 9,                     // editable text, associated with a dvar
    ITEM_TYPE_SLIDER = 10,                          // mouse speed, volume, etc.
    ITEM_TYPE_YESNO  = 11,                          // yes no dvar setting
    ITEM_TYPE_MULTI  = 12,                          // multiple list setting, enumerated
    ITEM_TYPE_DVARENUM  = 13,                       // multiple list setting, enumerated from a dvar
    ITEM_TYPE_BIND = 14,                            // bind
    ITEM_TYPE_MENUMODEL = 15,                       // special menu model
    ITEM_TYPE_VALIDFILEFIELD = 16,                  // text must be valid for use in a dos filename
    ITEM_TYPE_DECIMALFIELD = 17,                    // editable text, associated with a dvar, which allows decimal input
    ITEM_TYPE_UPREDITFIELD = 18,                    // editable text, associated with a dvar
    ITEM_TYPE_GAME_MESSAGE_WINDOW = 19,             // game message window
    ITEM_TYPE_SCALEFORM = 20,                       // Flash movie for Scaleform GFx
    ITEM_TYPE_BIND2 = 21,                           // bind2
};

enum MENU_ITEM_H_ALIGN {
    ITEM_ALIGN_LEFT = 0,                            // aligns left of text to left of containing rectangle
    ITEM_ALIGN_CENTER = 1,                          // aligns center of text to center of containing rectangle
    ITEM_ALIGN_RIGHT = 2,                           // aligns right of text to right of containing rectangle
    ITEM_ALIGN_X_MASK = 3,
};

enum MENU_ITEM_V_ALIGN {
    ITEM_ALIGN_LEGACY = 0,                          // aligns bottom of text to top of containing rectangle
    ITEM_ALIGN_TOP = 4,                             // aligns top of text to top of containing rectangle
    ITEM_ALIGN_MIDDLE = 8,                          // aligns middle of text to middle of containing rectangle
    ITEM_ALIGN_BOTTOM = 12,                         // aligns bottom of text to bottom of containing rectangle
    ITEM_ALIGN_Y_MASK = 12,
};

enum MENU_ITEM_ALIGN {
    ITEM_ALIGN_LEGACY_LEFT = 0,
    ITEM_ALIGN_LEGACY_CENTER = 1,
    ITEM_ALIGN_LEGACY_RIGHT = 2,
    ITEM_ALIGN_TOP_LEFT = 4,
    ITEM_ALIGN_TOP_CENTER = 5,
    ITEM_ALIGN_TOP_RIGHT = 6,
    ITEM_ALIGN_MIDDLE_LEFT = 8,
    ITEM_ALIGN_MIDDLE_CENTER = 9,
    ITEM_ALIGN_MIDDLE_RIGHT = 10,
    ITEM_ALIGN_BOTTOM_LEFT = 12,
    ITEM_ALIGN_BOTTOM_CENTER = 13,
    ITEM_ALIGN_BOTTOM_RIGHT = 14
};

enum MENU_ITEM_TEXTSTYLE {
    ITEM_TEXTSTYLE_NORMAL = 0,                      // normal text
    ITEM_TEXTSTYLE_BLINK = 1,                       // fast blinking
    ITEM_TEXTSTYLE_SHADOWED = 3,                    // drop shadow ( need a color for this )
    ITEM_TEXTSTYLE_SHADOWEDMORE = 6,                // drop shadow ( need a color for this )
    ITEM_TEXTSTYLE_MONOSPACE = 128
};

enum MENU_WINDOW_BORDER {
    WINDOW_BORDER_NONE = 0,                         // no border
    WINDOW_BORDER_FULL = 1,                         // full border based on border color ( single pixel )
    WINDOW_BORDER_HORZ = 2,                         // horizontal borders only
    WINDOW_BORDER_VERT = 3,                         // vertical borders only
    WINDOW_BORDER_KCGRADIENT = 4,                   // horizontal border using the gradient bars
    WINDOW_BORDER_RAISED = 5,                       // darken the bottom and right sides of the border
    WINDOW_BORDER_SUNKEN = 6                        // darken the top and left sides of the border
};

enum MENU_WINDOW_STYLE {
    WINDOW_STYLE_EMPTY = 0,                         // no background
    WINDOW_STYLE_FILLED = 1,                        // filled with background color
    WINDOW_STYLE_GRADIENT = 2,                      // gradient bar based on background color
    WINDOW_STYLE_SHADER = 3,                        // shader based on background color
    WINDOW_STYLE_TEAMCOLOR = 4,                     // team color
    WINDOW_STYLE_DVAR_SHADER = 5,                   // draws the shader specified by the dvar
    WINDOW_STYLE_LOADBAR = 6,                       // shader based on background color
};

enum MENU_MODE {
    MODE_BOTTOMUP_ALIGN_TOP = 0,                    // text appears on bottom of list and moves up to specified Y coordinate as old text fades out
    MODE_BOTTOMUP_ALIGN_BOTTOM = 1,                 // text appears on bottom of list and moves away from specified Y coordinate as new text pushes it up
    MODE_TOPDOWN_ALIGN_TOP = 2,                     // text appears on top of list and moves away from specified Y coordinate as new text pushes it down
    MODE_TOPDOWN_ALIGN_BOTTOM = 3                   // text appears on top of list and moves down to specified Y coordinate as old text fades out
};

enum MENU_BOOL {
    MENU_TRUE = 1,
    MENU_FALSE = 0
};

enum MENU_ORIENTATION {
    HUD_VERTICAL = 0x00,
    HUD_HORIZONTAL = 0x01
};

enum MENU_RANGETYPE {
    RANGETYPE_ABSOLUTE = 0,
    RANGETYPE_RELATIVE = 1
};

// list box element types
enum MENU_LIST_BOX {
    LISTBOX_TEXT = 0x00,
    LISTBOX_IMAGE = 0x01
};

// list feeders
enum MENU_FEEDERS {
    FEEDER_HEADS = 0x00,                             // model heads
    FEEDER_MAPS = 0x01,                             // text maps based on game type
    FEEDER_SERVERS = 0x02,                          // servers
    FEEDER_CLAN_MEMBERS = 0x03,                     // clan names
    FEEDER_ALLMAPS = 0x04,                          // all maps available, in graphic format
    FEEDER_REDTEAM_LIST = 0x05,                     // red team members
    FEEDER_BLUETEAM_LIST = 0x06,                    // blue team members
    FEEDER_PLAYER_LIST = 0x07,                      // players
    FEEDER_TEAM_LIST = 0x08,                        // team members for team voting
    FEEDER_MODS = 0x09,                             // team members for team voting
    FEEDER_DEMOS = 0x0a,                            // team members for team voting
    FEEDER_SCOREBOARD = 0x0b,                       // team members for team voting
    FEEDER_Q3HEADS = 0x0c,                          // model heads
    FEEDER_SERVERSTATUS = 0x0d,                     // server status
    FEEDER_FINDPLAYER = 0x0e,                       // find player
    FEEDER_CINEMATICS = 0x0f,                       // cinematics
    FEEDER_SAVEGAMES = 0x10,                        // savegames
    FEEDER_PICKSPAWN = 0x11,                        // pickspawn
    FEEDER_LOBBY_MEMBERS = 0x12,                    // list of players in your party
    FEEDER_LOBBY_MEMBERS_TALK = 0x13,               // icon for whether they are speaking or not
    FEEDER_MUTELIST = 0x14,                         // list of musted players
    FEEDER_PLAYERSTALKING = 0x15,                   // list of players who are currently talking
    FEEDER_SPLITSCREENPLAYERS = 0x16,               // list of all players who are playing splitscreen
    FEEDER_LOBBY_MEMBERS_READY = 0x17,              // icon for whether they are ready or not
    FEEDER_PLAYER_PROFILES = 0x18,                  // player profiles
    FEEDER_PARTY_MEMBERS = 0x19,                    // list of players in your party
    FEEDER_PARTY_MEMBERS_TALK = 0x1a,               // icon for whether they are speaking or not
    FEEDER_PARTY_MEMBERS_READY = 0x1b,              // icon for whether they are ready or not
    FEEDER_PLAYLISTS = 0x1c,                        // list of all playlists
    FEEDER_GAMEMODES = 0x1d,                        // list of all game type modes, including any player custom modes
    FEEDER_CATEGORIES = 0x1e,                       // list of all categories
    FEEDER_LEADERBOARD = 0x1f,                      // list of rows for a leaderboard
    FEEDER_MYTEAM_MEMBERS = 0x20,                   // list of marine team members
    FEEDER_MYTEAM_MEMBERS_TALK = 0x21,              // icon for whether they are speaking
    FEEDER_ENEMY_MEMBERS = 0x22,                    // list of opfor team members
    FEEDER_ENEMY_MEMBERS_TALK = 0x23,               // icon for whether they are speaking
    FEEDER_LOBBY_MEMBERS_STAT = 0x24,               // last round stats for lobby members
    FEEDER_MYTEAM_MEMBERS_STAT = 0x25,              // last round stats for marine team members
    FEEDER_ENEMY_MEMBERS_STAT = 0x26,               // last round stats for opfor team members
    FEEDER_ONLINEFRIENDS = 0x27,                    // list of your online friends
    FEEDER_LOBBY_MEMBERS_RANK = 0x28,               // rank icon
    FEEDER_PARTY_MEMBERS_RANK = 0x29,               // rank icon
    FEEDER_ENEMY_MEMBERS_RANK = 0x2a,               // rank icon
    FEEDER_MYTEAM_MEMBERS_RANK = 0x2b,              // rank icon
    FEEDER_TESTMAPS = 0x2c,                         // department test maps
    FEEDER_SYSTEMLINK_LOBBY_MEMBERS	= 0x2d,         // list of players in a system link lobby
    FEEDER_LOBBY_MEMBERS_CONTROLLER	= 0x2e,         // icon for controller quadrant for splitscreen
    FEEDER_PARTY_MEMBERS_CONTROLLER	= 0x2f,         // icon for controller quadrant for splitscreen
    FEEDER_MYTEAM_MEMBERS_SQUAD = 0x30,             // squad icon
    FEEDER_ENEMY_MEMBERS_SQUAD = 0x31,              // squad icon
    FEEDER_INGAME_SQUAD_MEMBERS = 0x32,             // Squad members displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_MEMBERS_FULL = 0x33,        // Squad members' name, rank, talk, leader displayed in PC MP 'Pause' menu
    FEEDER_INGAME_SQUAD_NAMES = 0x34,               // Squad names displayed in MP 'Join Squad' menu
    FEEDER_INGAME_SQUAD_NAMES2 = 0x35,              // Squad names displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_NAMES_FULL = 0x36,          // Squad names, lock, invite displayed in PC MP 'Pause' menu
    FEEDER_CUSTOM_GAMETYPES = 0x37,                 // list of all the gametypes for custom matches
    FEEDER_INGAME_SQUAD_MEMBER_RANK = 0x38,         // Squad members' rank displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_MEMBER_TALK	= 0x39,         // Squad members' talk icon displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_LOCKED = 0x3a,              // Squad lock icon displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_MEMBER_INVITED = 0x3b,      // Squad invite icon displayed in MP 'Pause' menu
    FEEDER_INGAME_SQUAD_INVITE = 0x3c,              // Squad invite icon displayed in MP 'Join Squad' menu
    FEEDER_INGAME_SQUAD_LEADER = 0x3d,              // Squad leader icon displayled in MP 'Pause' menu
    FEEDER_FRIENDS = 0x3e,                          // list of your friends
    FEEDER_PENDINGFRIENDS = 0x3f,                   // list of your pending friends
    FEEDER_INVITES = 0x40,                          // list of the game invites from your friends
};

// display flags
enum MENU_DISPLAY_FLAG {
    CG_SHOW_BLUE_TEAM_HAS_REDFLAG = 0x00000001,
    CG_SHOW_RED_TEAM_HAS_BLUEFLAG = 0x00000002,
    CG_SHOW_ANYTEAMGAME = 0x00000004,
    CG_SHOW_CTF = 0x00000020,
    CG_SHOW_OBELISK = 0x00000040,
    CG_SHOW_HEALTHCRITICAL = 0x00000080,
    CG_SHOW_SINGLEPLAYER = 0x00000100,
    CG_SHOW_TOURNAMENT = 0x00000200,
    CG_SHOW_DURINGINCOMINGVOICE = 0x00000400,
    CG_SHOW_IF_PLAYER_HAS_FLAG = 0x00000800,
    CG_SHOW_LANPLAYONLY = 0x00001000,
    CG_SHOW_MINED = 0x00002000,
    CG_SHOW_HEALTHOK = 0x00004000,
    CG_SHOW_TEAMINFO = 0x00008000,
    CG_SHOW_NOTEAMINFO = 0x00010000,
    CG_SHOW_OTHERTEAMHASFLAG = 0x00020000,
    CG_SHOW_YOURTEAMHASENEMYFLAG = 0x00040000,
    CG_SHOW_ANYNONTEAMGAME = 0x00080000,
    CG_SHOW_TEXTASINT = 0x00200000,
    CG_SHOW_HIGHLIGHTED = 0x00100000,
    CG_SHOW_NOT_V_CLEAR = 0x02000000,
    CG_SHOW_2DONLY = 0x10000000
};

enum MENU_UI_FLAG{
    UI_SHOW_LEADER = 0x00000001,
    UI_SHOW_NOTLEADER = 0x00000002,
    UI_SHOW_FAVORITESERVERS = 0x00000004,
    UI_SHOW_ANYNONTEAMGAME = 0x00000008,
    UI_SHOW_ANYTEAMGAME = 0x00000010,
    UI_SHOW_NEWHIGHSCORE = 0x00000020,
    UI_SHOW_DEMOAVAILABLE = 0x00000040,
    UI_SHOW_NEWBESTTIME = 0x00000080,
    UI_SHOW_FFA = 0x00000100,
    UI_SHOW_NOTFFA = 0x00000200,
    UI_SHOW_NETANYNONTEAMGAME = 0x00000400,
    UI_SHOW_NETANYTEAMGAME = 0x00000800,
    UI_SHOW_NOTFAVORITESERVERS = 0x00001000
};

// font types
enum MENU_FONT_TYPE{
    UI_FONT_DEFAULT = 0,                            // auto-chose betwen big/reg/small
    UI_FONT_NORMAL = 1,
    UI_FONT_BIG = 2,
    UI_FONT_SMALL = 3,
    UI_FONT_BOLD = 4,
    UI_FONT_CONSOLE = 5,
    UI_FONT_OBJECTIVE = 6,
    UI_FONT_MAX = 6,
};

// owner draw types
// ideally these should be done outside of this file but
// this makes it much easier for the macro expansion to
// convert them for the designers ( from the .menu files )
enum MENU_OWNER_DRAW_TYPE {
    CG_OWNERDRAW_BASE = 1,
    CG_PLAYER_AMMO_VALUE = 5,
    CG_PLAYER_AMMO_BACKDROP = 6,
    CG_PLAYER_HEAT_VALUE = 7,
    CG_PLAYER_STANCE = 20,
    CG_SPECTATORS = 60,
    CG_HOLD_BREATH_HINT = 71,
    CG_CURSORHINT = 72,
    CG_PLAYER_POWERUP = 73,
    CG_PLAYER_HOLDABLE = 74,
    CG_PLAYER_INVENTORY = 75,
    CG_CURSORHINT_STATUS = 78,                      // like 'health' bar when pointing at a func_explosive
    CG_PLAYER_BAR_HEALTH = 79,
    CG_MANTLE_HINT = 80,
    CG_PLAYER_WEAPON_NAME = 81,
    CG_PLAYER_WEAPON_NAME_BACK = 82,
    CG_CENTER_MESSAGE = 90,                         // for things like "You were killed by ..."
    CG_TANK_BODY_DIR = 95,
    CG_TANK_BARREL_DIR = 96,
    CG_DEADQUOTE = 97,
    CG_PLAYER_BAR_HEALTH_BACK = 98,
    CG_MISSION_OBJECTIVE_HEADER = 99,
    CG_MISSION_OBJECTIVE_LIST = 100,
    CG_MISSION_OBJECTIVE_BACKDROP = 101,
    CG_PAUSED_MENU_LINE = 102,
    CG_OFFHAND_WEAPON_ICON_FRAG = 103,
    CG_OFFHAND_WEAPON_ICON_SMOKEFLASH = 104,
    CG_OFFHAND_WEAPON_AMMO_FRAG = 105,
    CG_OFFHAND_WEAPON_AMMO_SMOKEFLASH = 106,
    CG_OFFHAND_WEAPON_NAME_FRAG = 107,
    CG_OFFHAND_WEAPON_NAME_SMOKEFLASH = 108,
    CG_OFFHAND_WEAPON_SELECT_FRAG = 109,
    CG_OFFHAND_WEAPON_SELECT_SMOKEFLASH = 110,
    CG_SAVING = 111,
    CG_PLAYER_LOW_HEALTH_OVERLAY = 112,
    CG_INVALID_CMD_HINT = 113,
    CG_PLAYER_SPRINT_METER = 114,
    CG_PLAYER_SPRINT_BACK = 115,
    CG_PLAYER_WEAPON_BACKGROUND = 116,
    CG_PLAYER_WEAPON_AMMO_CLIP_GRAPHIC = 117,
    CG_PLAYER_WEAPON_PRIMARY_ICON = 118,
    CG_PLAYER_WEAPON_AMMO_STOCK = 119,
    CG_PLAYER_WEAPON_LOW_AMMO_WARNING = 120,
    CG_BATTLE_COMPASS_MARKERS = 122,
    CG_BATTLE_FULLMAP_MARKERS = 123,
    CG_SUCCESSFUL_CMD_HINT = 130,
    CG_WAR_TEXT = 135,
    CG_PLAYER_COMPASS_TICKERTAPE = 145,
    CG_PLAYER_COMPASS_TICKERTAPE_NO_OBJ = 146,
    CG_PLAYER_COMPASS_DOGS = 147,
    CG_PLAYER_COMPASS_ARTILLERY_ICON = 148,
    CG_PLAYER_COMPASS_SQUAD_OBJECTIVE = 149,
    CG_PLAYER_COMPASS_PLAYER = 150,
    CG_PLAYER_COMPASS_BACK = 151,
    CG_PLAYER_COMPASS_POINTERS = 152,
    CG_PLAYER_COMPASS_ACTORS = 153,
    CG_PLAYER_COMPASS_TANKS = 154,
    CG_PLAYER_COMPASS_HELICOPTERS = 155,
    CG_PLAYER_COMPASS_PLANES = 156,
    CG_PLAYER_COMPASS_AUTOMOBILES = 157,
    CG_PLAYER_COMPASS_FRIENDS = 158,
    CG_PLAYER_COMPASS_MAP = 159,
    CG_PLAYER_COMPASS_NORTHCOORD = 160,
    CG_PLAYER_COMPASS_EASTCOORD	= 161,
    CG_PLAYER_COMPASS_NCOORD_SCROLL = 162,
    CG_PLAYER_COMPASS_ECOORD_SCROLL = 163,
    CG_PLAYER_COMPASS_GOALDISTANCE = 164,
    CG_PLAYER_ACTIONSLOT_DPAD = 165,
    CG_PLAYER_ACTIONSLOT_1 = 166,
    CG_PLAYER_ACTIONSLOT_2 = 167,
    CG_PLAYER_ACTIONSLOT_3 = 168,
    CG_PLAYER_ACTIONSLOT_4 = 169,
    CG_PLAYER_COMPASS_ENEMIES = 170,
    CG_PLAYER_FULLMAP_DOGS = 176,
    CG_PLAYER_FULLMAP_VEHICLES = 177,
    CG_PLAYER_FULLMAP_ARTILLERY_ICON = 178,
    CG_PLAYER_FULLMAP_SQUAD_OBJECTIVE = 179,
    CG_PLAYER_FULLMAP_BACK = 180,
    CG_PLAYER_FULLMAP_MAP = 181,
    CG_PLAYER_FULLMAP_POINTERS = 182,
    CG_PLAYER_FULLMAP_PLAYER = 183,
    CG_PLAYER_FULLMAP_ACTORS = 184,
    CG_PLAYER_FULLMAP_FRIENDS = 185,
    CG_PLAYER_FULLMAP_LOCATION_SELECTOR = 186,
    CG_PLAYER_FULLMAP_BORDER = 187,
    CG_PLAYER_FULLMAP_ENEMIES = 188,
    CG_PLAYER_COMPASS = 189,
    CG_VEHICLE_RETICLE = 190,
    CG_HUD_TARGETS_VEHICLE = 191,
    CG_HUD_TARGETS_JAVELIN = 192,
    CG_TALKER1 = 193,
    CG_TALKER2 = 194,
    CG_TALKER3 = 195,
    CG_TALKER4 = 196,
    CG_FRIENDLYARROWS = 197,
    CG_FRIENDLYNAMES = 198,
    UI_OWNERDRAW_BASE = 200,
    UI_HANDICAP = 200,
    UI_EFFECTS = 201,
    UI_PLAYERMODEL = 202,
    UI_GAMETYPE = 205,
    UI_SKILL = 207,
    UI_NETSOURCE = 220,
    UI_NETFILTER = 222,
    UI_VOTE_KICK = 238,
    UI_NETGAMETYPE = 245,
    UI_SERVERREFRESHDATE = 247,
    UI_SERVERMOTD = 248,
    UI_GLINFO = 249,
    UI_KEYBINDSTATUS = 250,
    UI_JOINGAMETYPE = 253,
    UI_MAPPREVIEW = 254,
    UI_MENUMODEL = 257,
    UI_SAVEGAME_SHOT = 258,
    UI_SAVEGAMENAME = 262,
    UI_SAVEGAMEINFO = 263,
    UI_LOADPROFILING = 264,
    UI_RECORDLEVEL = 265,
    UI_AMITALKING = 266,
    UI_TALKER1 = 267,
    UI_TALKER2 = 268,
    UI_TALKER3 = 269,
    UI_TALKER4 = 270,
    UI_PARTYSTATUS = 271,
    UI_LOGGEDINUSER = 272,
    UI_RESERVEDSLOTS = 273,
    UI_PLAYLISTNAME = 274,
    UI_PLAYLISTDESCRIPTION = 275,
    UI_USERNAME = 276,
    UI_CINEMATIC = 277,
    UI_TOTALONLINE = 278,
    UI_CATEGORYNAME = 279,
    UI_CATEGORYDESCRIPTION = 280,
    UI_PLAYLISTICON = 281,
    UI_CATEGORYICON = 282,
    UI_GAMETYPE_MAPNAME = 283,
    CG_HUD_WAR_MOMENTUM_PROGRESS = 284,
    CG_HUD_WAR_MOMENTUM_MULTIPLIER = 285,
    CG_HUD_WAR_MOMENTUM_MULTIPLIER_DETAIL = 286,
    CG_HUD_WAR_MOMENTUM_MULTIPLIER_BLITZKRIEG = 287,
    CG_COMPETITIVE_MODE_SCORES = 288,
    UI_LOAD_STATUS_SCREEN = 289,
    UI_LEADERBOARD_GAMEMODE = 290,
    CG_PLAYER_ACTIONSLOT_BACK_1 = 290,
    CG_PLAYER_ACTIONSLOT_BACK_2 = 291,
    CG_PLAYER_ACTIONSLOT_BACK_3 = 292,
    CG_PLAYER_ACTIONSLOT_BACK_4 = 293,
    CG_PLAYER_ACTIONSLOT_ARROW_1 = 294,
    CG_PLAYER_ACTIONSLOT_ARROW_2 = 295,
    CG_PLAYER_ACTIONSLOT_ARROW_3 = 296,
    CG_PLAYER_ACTIONSLOT_ARROW_4 = 297,
    UI_DIFFICULTY_INFO = 298,
    UI_DIFFICULTY_ICON = 299,
    UI_LOBBY_CHAT = 300
};

// Edge relative placement values for rect->h_align and rect->v_align
enum MENU_H_ALIGNMENT {
    HORIZONTAL_ALIGN_SUBLEFT = 0,                   // left edge of a 4:3 screen (safe area not included)
    HORIZONTAL_ALIGN_LEFT = 1,                      // left viewable (safe area) edge
    HORIZONTAL_ALIGN_CENTER = 2,                    // center of the screen (reticle)
    HORIZONTAL_ALIGN_RIGHT = 3,                     // right viewable (safe area) edge
    HORIZONTAL_ALIGN_FULLSCREEN	= 4,                // disregards safe area
    HORIZONTAL_ALIGN_NOSCALE = 5,                   // uses exact parameters - neither adjusts for safe area nor scales for screen size
    HORIZONTAL_ALIGN_TO640 = 6,                     // scales a real-screen resolution x down into the 0 - 640 range
    HORIZONTAL_ALIGN_CENTER_SAFEAREA = 7,           // center of the safearea
    HORIZONTAL_ALIGN_MAX = HORIZONTAL_ALIGN_CENTER_SAFEAREA,
    HORIZONTAL_ALIGN_DEFAULT = HORIZONTAL_ALIGN_SUBLEFT
};

enum MENU_V_ALIGNMENT {
    VERTICAL_ALIGN_SUBTOP = 0,                      // top edge of the 4:3 screen (safe area not included)
    VERTICAL_ALIGN_TOP = 1,                         // top viewable (safe area) edge
    VERTICAL_ALIGN_CENTER = 2,                      // center of the screen (reticle)
    VERTICAL_ALIGN_BOTTOM = 3,                      // bottom viewable (safe area) edge
    VERTICAL_ALIGN_FULLSCREEN = 4,                  // disregards safe area
    VERTICAL_ALIGN_NOSCALE = 5,                     // uses exact parameters - neither adjusts for safe area nor scales for screen size
    VERTICAL_ALIGN_TO480 = 6,                       // scales a real-screen resolution y down into the 0 - 480 range
    VERTICAL_ALIGN_CENTER_SAFEAREA = 7,             // center of the save area
    VERTICAL_ALIGN_MAX = VERTICAL_ALIGN_CENTER_SAFEAREA,
    VERTICAL_ALIGN_DEFAULT = VERTICAL_ALIGN_SUBTOP
};

enum MENU_BUTTON {
    BUTTON_A = 1,
    BUTTON_B = 2,
    BUTTON_X = 3,
    BUTTON_Y = 4,
    BUTTON_LSHLDR = 5,
    BUTTON_RSHLDR = 6,
    BUTTON_START = 14,
    BUTTON_BACK = 15,
    BUTTON_LSTICK = 16,
    BUTTON_RSTICK = 17,
    BUTTON_LTRIG = 18,
    BUTTON_RTRIG = 19,
    DPAD_UP = 20,
    DPAD_DOWN = 21,
    DPAD_LEFT = 22,
    DPAD_RIGHT = 23,
    APAD_UP = 28,
    APAD_DOWN = 29,
    APAD_LEFT = 30,
    APAD_RIGHT = 31
};

enum ASSET_TYPE {
    ASSET_UNKNOWN = 0,
    ASSET_ANIMATION = 4,        // x_anim                 PARTIALLY VERIFIED
    ASSET_MODEL = 5,            // xmodel                 PARTIALLY VERIFIED
    ASSET_MATERIAL = 6,         // material               VERIFIED
    ASSET_BIK_FILE = 7,         // .bik file              PARTIALLY VERIFIED
    ASSET_SOUND = 9,            // loaded_sound           VERIFIED
    ASSET_COLLISION_MAP = 12,   // collision_map          PARTIALLY VERIFIED
    ASSET_SHADER = 13,          // shader                 PARTIALLY VERIFIED
    ASSET_D3DBSP_DUMP = 17,     // d3dbsp dump            VERIFIED
    ASSET_FONT = 20,            // font                   PARTIALLY VERIFIED
    ASSET_MENU = 21,            // menu_file              VERIFIED
    ASSET_LOCAL_STRING = 23,    // localized string       VERIFIED
    ASSET_WEAPON = 24,          // weapon                 VERIFIED
    ASSET_EFFECT = 26,          // fx                     VERIFIED
    ASSET_RAW_FILE = 32,        // raw_file               VERIFIED
    ASSET_STRING_TABLE = 33     // string_table           PARTIALLY VERIFIED
};

// Change this depending on the platform
// PC
#define DEVMAP_LEVEL_FIRST "devmap intro_pac"
#define DEVMAP "devmap"
// Not PC
// #define DEVMAP_LEVEL_FIRST "map intro_pac"
// #define DEVMAP "map"

// Remove this to restore full frontend instead of limited EPD frontend
#define COOP_EPD	0

// LDS - This enables a German SKU with Nazi Zombies enabled *SHOULD BE SET TO 0 IF NOT APPROVED*
#define GERMAN_ZOMBIE_BUILD 0

#define DEVMAP_LEVEL_TRAINING "devmap training"
#define LEVEL_FIRST "intro_pac"
#define LEVEL_TRAINING "training"
#define FIRST_PLAYABLE_CAMPAIGN_LEVEL "mak"
#define FIRST_PLAYABLE_ZOMBIE_LEVEL "nazi_zombie_prototype"

// Size define for the hud compass
// These are used for both the dynamic & non-dynamic compass drawing
// If these are changed, the cgame should be recompiled
#define COMPASS_SIZE		160
#define MINIMAP_X			11.5
#define MINIMAP_Y			5
#define MINIMAP_W			89.5
#define	MINIMAP_H			89.5

#define COMPASS_SIZE_MP		125
#define MINIMAP_X_MP		0
#define MINIMAP_Y_MP		12
#define MINIMAP_W_MP		102
#define	MINIMAP_H_MP		102

#define FULLSCREEN			0 0 640 480
#define FULLSCREEN_WIDE		-107 0 854 480

// PC
#define ORIGIN_TITLE		30 34
// Not PC
// #define	ORIGIN_TITLE		0 0

#define ORIGIN_TITLE_SS		104 120

#define FONTSCALE_SMALL		0.3095  //0.3750 // <-- COD4 // COD5 --> 0.30952//0.35897//0.24138 //14 pt //0.2900 //0.2750 // 18
#define FONTSCALE_LOBBY		0.26    // <--Slate // 0.3010 <-- Slate Compressed // 0.3750 // <-- COD4 CONDUIT ITC small
#define FONTSCALE_NORMAL	0.3810  //0.35897//0.4583
#define FONTSCALE_BOLD		0.5476  //0.4583
#define FONTSCALE_BIG		0.5476  //0.5833
#define FONTSCALE_EXTRABIG	1       //1.0000

// new settings
#define TEXTSIZE_SMALL		FONTSCALE_SMALL
#define TEXTSIZE_SMALL_SS	(FONTSCALE_SMALL*2)
#define TEXTSIZE_DEFAULT	FONTSCALE_NORMAL
#define TEXTSIZE_DEFAULT_SS	(FONTSCALE_NORMAL*2)
#define TEXTSIZE_TITLE		FONTSCALE_BIG
#define TEXTSIZE_TITLE_SS	1

#define TEXTSIZE_BOLD		TEXTSIZE_DEFAULT
#define TEXTSIZE_BIG		TEXTSIZE_TITLE

//#define COLOR_TITLE			1 0.8 0.4 1
#define COLOR_TITLE			1 1 1 1
#define COLOR_HEADER		0.69 0.69 0.69 1
#define COLOR_FOCUSED		0.95294 0.72156 0.21176 1 //1 0.788 0.129 1
//#define COLOR_FOCUS_YELLOW	0.95294 0.72156 0.21176 1
#define COLOR_UNFOCUSED		0.4823 0.4823 0.4823 1
//#define COLOR_DISABLED		0.35 0.35 0.35 1
#define COLOR_SAFEAREA		0 0 1 1

#define COLOR_INFO_YELLOW	COLOR_FOCUSED//1 0.84706 0 1
#define COLOR_TEXT			0.84313 0.84313 0.84313 1
#define COLOR_DISABLED		0.34118 0.36863 0.37647 1
#define COLOR_TITLEBAR		0.14510 0.16078 0.16862 0.3//1
#define COLOR_RED_TEXT		0.69020 0.00784 0.00784 1

#define COLOR_FADEOUT		0.09412 0.09412 0.04912 0.65

#define COLOR_BODY_TEXT		0.62745 0.66667 0.67451 1

#define	COLOR_USMC		0 0.0196 0.41
#define COLOR_JPN		0.53 0.027 0.027
#define COLOR_USSR		0.368 0.035 0.035
#define COLOR_GER		0.937 0.9 0.607

#define DEFAULT_MP_CFG			"default_mp.cfg"
#define SPLITSCREEN_MP_CFG		"default_splitscreen.cfg"
#define SYSTEMLINK_MP_CFG		"default_systemlink.cfg"
#define XBOXLIVE_MP_CFG			"default_xboxlive.cfg"

#define MAX_RANK		int(tableLookup( "mp/rankTable.csv", 0, "maxrank", 1))
#define MAX_PRESTIGE	int(tableLookup( "mp/rankIconTable.csv", 0, "maxprestige", 1))

#define PRESTIGE_AVAIL (stat(2326) < MAX_PRESTIGE && stat(2301) == int(tableLookup("mp/rankTable.csv",0,MAX_RANK,7)))
#define PRESTIGE_NEXT (stat(2326) < MAX_PRESTIGE && stat(252) == MAX_RANK)
#define PRESTIGE_FINISH (stat(2326) == MAX_PRESTIGE)

#define CAN_RANK_UP	(stat(252) < MAX_RANK || stat(2326) < MAX_PRESTIGE)

// Bink constants
const quint32 BINK_SURFACE32RGBA = 6;

#endif // ENUMS_H
