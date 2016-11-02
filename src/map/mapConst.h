/* 
 * File:   mapDef.h
 * Author: lighta
 *
 * Ensemble of constant of mapserv.
 * TODO transform that shit in static const
 * Created on July 5, 2016, 4:09 AM
 */

#ifndef MAPDEF_H
#define	MAPDEF_H

#define MAX_NPC_PER_MAP 512
#define AREA_SIZE battle_config.area_size
#define DAMAGELOG_SIZE 30
#define LOOTITEM_SIZE 10
#define MAX_MOBSKILL 50		//Max 128, see mob skill_idx type if need this higher
#define MAX_MOB_LIST_PER_MAP 128
#define MAX_EVENTQUEUE 2
#define MAX_EVENTTIMER 32
#define NATURAL_HEAL_INTERVAL 500
#define MIN_FLOORITEM 2
#define MAX_FLOORITEM START_ACCOUNT_NUM
#define MAX_LEVEL 175
#define MAX_DROP_PER_MAP 48
#define MAX_IGNORE_LIST 20 	// official is 14
#define MAX_VENDING 12
#define MAX_MAP_SIZE 512*512 	// Wasn't there something like this already? Can't find it.. [Shinryo]

//The following system marks a different job ID system used by the map server,
//which makes a lot more sense than the normal one. [Skotlex]
//
//These marks the "level" of the job.
#define JOBL_2_1 0x100 //256
#define JOBL_2_2 0x200 //512
#define JOBL_2 0x300 //768

#define JOBL_UPPER 0x1000 //4096
#define JOBL_BABY 0x2000  //8192
#define JOBL_THIRD 0x4000 //16384

//for filtering and quick checking.
#define MAPID_BASEMASK 0x00ff
#define MAPID_UPPERMASK 0x0fff
#define MAPID_THIRDMASK (JOBL_THIRD|MAPID_UPPERMASK)

//Max size for inputs to Graffiti, Talkie Box and Vending text prompts
#define MESSAGE_SIZE (79 + 1)
//String length you can write in the 'talking box'
#define CHATBOX_SIZE (70 + 1)
//Chatroom-related string sizes
#define CHATROOM_TITLE_SIZE (36 + 1)
#define CHATROOM_PASS_SIZE (8 + 1)
//Max allowed chat text length
#define CHAT_SIZE_MAX (255 + 1)
// <NPC_NAME_LENGTH> for npc name + 2 for a "::" + <NAME_LENGTH> for label + 1 for EOS
#define EVENT_NAME_LENGTH ( NPC_NAME_LENGTH + 2 + NAME_LENGTH + 1 )

#define DEFAULT_AUTOSAVE_INTERVAL 5*60*1000


#define MAX_SKILLTIMERSKILL 50
#define MAX_SKILLUNITGROUP 25 /// Maximum skill unit group (for same skill each source)
#define MAX_SKILLUNITGROUPTICKSET 25

#endif	/* MAPDEF_H */

