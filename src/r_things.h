// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Copyright (C) 1993-1996 by id Software, Inc.
// Copyright (C) 1998-2000 by DooM Legacy Team.
// Copyright (C) 1999-2018 by Sonic Team Junior.
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  r_things.h
/// \brief Rendering of moving objects, sprites

#ifndef __R_THINGS__
#define __R_THINGS__

#include "sounds.h"
#include "r_plane.h"
#include "r_patch.h"

// number of sprite lumps for spritewidth,offset,topoffset lookup tables
// Fab: this is a hack : should allocate the lookup tables per sprite
#if defined(__x86_64__) || defined(__amd64__) || defined(__aarch64__) || defined(__arm64__) // only for 64bit (idk how else to proper check lmao)
#define MAXVISSPRITES 4096
#else
#define MAXVISSPRITES 2048 // added 2-2-98 was 128
#endif

#define VISSPRITECHUNKBITS 6	// 2^6 = 64 sprites per chunk
#define VISSPRITESPERCHUNK (1 << VISSPRITECHUNKBITS)
#define VISSPRITEINDEXMASK (VISSPRITESPERCHUNK - 1)

#define FEETADJUST (4<<FRACBITS) // R_AddSingleSpriteDef

// Takes 2 fixed-point coordinates, returns "distance" between them and camera,
// as an non-fixed-point integer.
// It is very rough, tho it is used only for optimizing out unnecessary
// interpolation, so it is kinda ok on big distances.
#define R_QuickCamDist(x, y) max(abs(((x)>>FRACBITS) - (viewx>>FRACBITS)), abs(((y)>>FRACBITS) - (viewy>>FRACBITS)))

// Constant arrays used for psprite clipping
//  and initializing clipping.
extern INT16 *negonearray;
extern INT16 *screenheightarray;

// vars for R_DrawMaskedColumn
extern INT16 *mfloorclip;
extern INT16 *mceilingclip;
extern fixed_t spryscale;
extern fixed_t sprtopscreen;
extern fixed_t sprbotscreen;
extern fixed_t windowtop;
extern fixed_t windowbottom;

fixed_t R_GetShadowZ(mobj_t *thing, pslope_t **shadowslope);

void R_DrawMaskedColumn(column_t *column);
void R_SortVisSprites(void);

//faB: find sprites in wadfile, replace existing, add new ones
//     (only sprites from namelist are added or replaced)
void R_AddSpriteDefs(UINT16 wadnum);

//SoM: 6/5/2000: Light sprites correctly!
void R_AddSprites(sector_t *sec, INT32 lightlevel);
void R_InitSprites(void);
void R_ClearSprites(void);
void R_DrawMasked(void);

// -----------
// SKINS STUFF
// -----------
#define SKINNAMESIZE 16
// should be all lowercase!! S_SKIN processing does a strlwr
#define DEFAULTSKIN "sonic"
#define DEFAULTSKIN2 "tails" // secondary player
#define DEFAULTSKIN3 "knuckles" // third player
#define DEFAULTSKIN4 "eggman" // fourth player

typedef struct
{
	char name[SKINNAMESIZE+1]; // INT16 descriptive name of the skin
	spritedef_t spritedef;
	spriteinfo_t sprinfo;
	UINT16 wadnum;
	char sprite[4]; // Sprite name, if seperated from S_SKIN.
	skinflags_t flags;

	char realname[SKINNAMESIZE+1]; // Display name for level completion.
	char hudname[SKINNAMESIZE+1]; // HUD name to display (officially exactly 5 characters long)
	char facerank[9], facewant[9], facemmap[9]; // Arbitrarily named patch lumps

	// SRB2kart
	UINT8 kartspeed;
	UINT8 kartweight;
	//

	// Definable color translation table
	UINT8 starttranscolor;
	UINT8 prefcolor;
	fixed_t highresscale; // scale of highres, default is 0.5

	// specific sounds per skin
	sfxenum_t soundsid[NUMSKINSOUNDS]; // sound # in S_sfx table
	
	boolean localskin;
	INT32 localnum;
} skin_t;

extern CV_PossibleValue_t Forceskin_cons_t[];

// -----------
// NOT SKINS STUFF !
// -----------
typedef enum
{
	SC_NONE = 0,
	SC_TOP = 1,
	SC_BOTTOM = 2,
	SC_VFLIP = 3,
	SC_NOTVISIBLE = 4,
	SC_CUTMASK    = SC_TOP|SC_BOTTOM|SC_NOTVISIBLE,
	SC_FLAGMASK   = ~SC_CUTMASK
} spritecut_e;

// A vissprite_t is a thing that will be drawn during a refresh,
// i.e. a sprite object that is partly visible.
typedef struct vissprite_s
{
	// Doubly linked list.
	struct vissprite_s *prev;
	struct vissprite_s *next;

	mobj_t *mobj; // for easy access

	INT32 x1, x2;

	fixed_t gx, gy; // for line side calculation
	fixed_t gz, gzt; // global bottom/top for silhouette clipping
	fixed_t pz, pzt; // physical bottom/top for sorting with 3D floors

	fixed_t startfrac; // horizontal position of x1
	fixed_t xscale, scale; // projected horizontal and vertical scales
	fixed_t thingscale; // the object's scale
	fixed_t sortscale; // sortscale only differs from scale for flat sprites
	fixed_t scalestep; // only for flat sprites, 0 otherwise
	fixed_t xiscale; // negative if flipped

	fixed_t texturemid;
	patch_t *patch;

	lighttable_t *colormap; // for color translation and shadow draw
	                        // maxbright frames as well

	UINT8 *transmap; // for MF2_SHADOW sprites, which translucency table to use

	INT32 mobjflags;

	INT32 heightsec; // height sector for underwater/fake ceiling support

	extracolormap_t *extra_colormap; // global colormaps

	// Precalculated top and bottom screen coords for the sprite.
	fixed_t thingheight; // The actual height of the thing (for 3D floors)
	sector_t *sector; // The sector containing the thing.
	INT16 sz, szt;

	spritecut_e cut;
	UINT32 renderflags;
	UINT8 rotateflags;

	fixed_t spritexscale, spriteyscale;
	fixed_t spritexoffset, spriteyoffset;


	INT16 *clipbot, *cliptop;

	boolean precip;
	boolean vflip; // Flip vertically
	boolean isScaled;
	INT32 dispoffset; // copy of info->dispoffset, affects ordering but not drawing
} vissprite_t;

extern UINT32 visspritecount, numvisiblesprites;

void R_ClipSprites(void);

void R_AllocVisSpriteMemory(void);

UINT8 *R_GetSpriteTranslation(vissprite_t *vis);

// ----------
// DRAW NODES
// ----------

// A drawnode is something that points to a 3D floor, 3D side, or masked
// middle texture. This is used for sorting with sprites.
typedef struct drawnode_s
{
	visplane_t *plane;
	drawseg_t *seg;
	drawseg_t *thickseg;
	ffloor_t *ffloor;
	vissprite_t *sprite;

	struct drawnode_s *next;
	struct drawnode_s *prev;
} drawnode_t;

extern INT32 numskins;
extern INT32 numlocalskins;
extern INT32 numallskins;
extern skin_t skins[MAXSKINS];
extern UINT16 skinstats[9][9][MAXSKINS];
extern UINT16 skinstatscount[9][9];
extern UINT16 skinsorted[MAXSKINS];

void sortSkinGrid(void);
extern skin_t localskins[MAXSKINS];
extern skin_t allskins[MAXSKINS*2];

boolean SetPlayerSkin(INT32 playernum,const char *skinname);
void SetPlayerSkinByNum(INT32 playernum,INT32 skinnum); // Tails 03-16-2002
void SetLocalPlayerSkin(INT32 playernum,const char *skinname, consvar_t *cvar);
INT32 R_SkinAvailable(const char *name);
INT32 R_AnySkinAvailable(const char *name);
INT32 R_LocalSkinAvailable(const char *name, boolean local);
void R_AddSkins(UINT16 wadnum, boolean local);

void R_InitDrawNodes(void);

char *GetPlayerFacePic(INT32 skinnum);

// Functions to go from sprite character ID to frame number
// for 2.1 compatibility this still uses the old 'A' + frame code
// The use of symbols tends to be painful for wad editors though
// So the future version of this tries to avoid using symbols
// as much as possible while also defining all 64 slots in a sane manner
// 2.1:    [[ ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~   ]]
// Future: [[ ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdefghijklmnopqrstuvwxyz!@ ]]
FUNCMATH FUNCINLINE static ATTRINLINE char R_Frame2Char(UINT8 frame)
{
#if 1 // 2.1 compat
	return 'A' + frame;
#else
	if (frame < 26) return 'A' + frame;
	if (frame < 36) return '0' + (frame - 26);
	if (frame < 62) return 'a' + (frame - 36);
	if (frame == 62) return '!';
	if (frame == 63) return '@';
	return '\xFF';
#endif
}

FUNCMATH FUNCINLINE static ATTRINLINE UINT8 R_Char2Frame(char cn)
{
#if 1 // 2.1 compat
	if (cn == '+') return '\\' - 'A'; // PK3 can't use backslash, so use + instead
	return cn - 'A';
#else
	if (cn >= 'A' && cn <= 'Z') return (cn - 'A');
	if (cn >= '0' && cn <= '9') return (cn - '0') + 26;
	if (cn >= 'a' && cn <= 'z') return (cn - 'a') + 36;
	if (cn == '!') return 62;
	if (cn == '@') return 63;
	return 255;
#endif
}

// "Left" and "Right" character symbols for additional rotation functionality
#define ROT_L 17
#define ROT_R 18

FUNCMATH FUNCINLINE static ATTRINLINE char R_Rotation2Char(UINT8 rot)
{
	if (rot <=     9) return '0' + rot;
	if (rot <=    16) return 'A' + (rot - 10);
	if (rot == ROT_L) return 'L';
	if (rot == ROT_R) return 'R';
	return '\xFF';
}

FUNCMATH FUNCINLINE static ATTRINLINE UINT8 R_Char2Rotation(char cn)
{
	if (cn >= '0' && cn <= '9') return (cn - '0');
	if (cn >= 'A' && cn <= 'G') return (cn - 'A') + 10;
	if (cn == 'L') return ROT_L;
	if (cn == 'R') return ROT_R;
	return 255;
}

#endif //__R_THINGS__
