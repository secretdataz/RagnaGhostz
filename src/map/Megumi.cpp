
#include "megumi.hpp"

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <map>

#include "../common/cbasetypes.hpp"
#include "../common/ers.hpp"
#include "../common/malloc.hpp"
#include "../common/nullpo.hpp"
#include "../common/random.hpp"
#include "../common/showmsg.hpp"
#include "../common/socket.hpp"
#include "../common/strlib.hpp"
#include "../common/timer.hpp"
#include "../common/utils.hpp"

#include "chrif.hpp"
#include "clif.hpp"
#include "map.hpp"
#include "mob.hpp"
#include "path.hpp"
#include "pc.hpp"
#include "npc.hpp"
#include "clifmeg.hpp"
#include "battle.hpp"
#include "atcommand.hpp"

#include <algorithm>

static std::map<int, megumi> megumiList;
static std::map<int, megumi>::iterator megumiIT;


/*
	Megumi Database
*/

uint32_t GenerateMegumiHash(const std::string& str)
{
	uint32_t hash = 0x811c9dc5;
	uint32_t prime = 0x1000193;

	for (int i = 0; i < str.size(); ++i) {
		uint8_t value = str[i];
		hash = hash ^ value;
		hash *= prime;
	}

	return hash;
}

void DeleteMegumi(uint32 hash)
{
	megumiIT = megumiList.find(hash);

	if (megumiIT != megumiList.end())
		megumiList.erase(hash);
}

struct megumi GetMegumiData(uint32 hash)
{
	megumiIT = megumiList.find(hash);

	if (megumiIT != megumiList.end())
		return megumiList[hash];

	struct megumi meg(0);

	meg.activate = false;

	return meg;
}

void UpdateMegumi(int hash, struct megumi meg)
{
	megumiIT = megumiList.find(hash);

	if (megumiIT != megumiList.end())
		megumiList[hash] = meg;
}

int AddMegumi(std::string UP, int fd)
{
	struct megumi meg(fd);
	meg.fd = fd;

	meg.activate = true;

	uint32 hash = GenerateMegumiHash(UP);

	megumiIT = megumiList.find(hash);

	if (megumiIT == megumiList.end())
		megumiList[hash] = meg;

	return hash;
}

//
std::vector<std::string> util_explode(std::string s, std::string delimiter) {

	std::vector<std::string>result;

	while (s.size()) {
		int index = s.find(delimiter);
		if (index != std::string::npos) {
			result.push_back(s.substr(0, index));
			s = s.substr(index + delimiter.size());
			if (s.size() == 0)result.push_back(s);
		}
		else {
			result.push_back(s);
			s = "";
		}
	}
	return result;
}

/*
	Cuida do Recebimento dos Packets de Megumi
*/
int megumipackethandle(int fd)
{
	char data1[MAX_MEGPACKETSIZE];
	char UP[50];
	uint32 clienttype;

	safestrncpy(data1, RFIFOCP(fd, 2), 300);
	safestrncpy(UP, RFIFOCP(fd, 302), 50);
	clienttype = RFIFOL(fd, 352);

	std::string npc = "";

	//ShowError(data1);

	RFIFOSKIP(fd, 356);

	struct megumi meg(fd);

	switch (clienttype)
	{
		case MP_LOGIN:
		{
			session[fd]->hash = AddMegumi(std::string(UP), fd);
			session[fd]->flag.megumi = true;

			ShowInfo("[Megumi] Megumi for [%s] is now connected to emulator.\n", UP);

			//TODO: Remover Megumi depois de alguns segundos caso o jogador n?o se conecte.
			return 1;
		}
	}

	meg = GetMegumiData(GenerateMegumiHash(std::string(UP)));

	if (meg.account_id == 0 || !meg.activate)
		return 1;

	struct map_session_data *sd = map_id2sd(meg.account_id);

	if (sd == NULL)
		return 1;

	sd->megumi_packet.data1 = data1;
	std::vector<std::string> d;

	switch (clienttype)
	{
	case MP_STYLE:
		{
			d = util_explode(data1, ":");

			pc_changelook(sd, LOOK_HAIR, std::atoi(d[0].c_str()));
			pc_changelook(sd, LOOK_HAIR_COLOR, std::atoi(d[1].c_str()));
			pc_changelook(sd, LOOK_CLOTHES_COLOR, std::atoi(d[2].c_str()));

			sd->state.dressroom = 0;
		}
		return 1;

	case MP_CLOSEDMASTERY:
		sd->state.mastery_flag = 0;
		return 1;

	case MP_BUYMASTERY:
		if (!sd->state.mastery_flag) return 1;

		d = util_explode(data1, ":");

		pc_setreg(sd, add_str("@MASTERY_UP"), std::atoi(d[0].c_str()));
		pc_setreg(sd, add_str("@MASTERY_LEVEL"), std::atoi(d[1].c_str()));

		npc = "BUY_MASTERY";
		break;

	case MP_SENDMAC:
		pc_setregstr(sd, add_str("@MAC$"), data1);
		break;

	case MP_TALKING:
		if (is_atcommand(sd->fd, sd, data1, 1))
			return 1;

		clif_disp_overhead_(&sd->bl, std::string("[").append(std::string(sd->status.name).append("] ")).append(std::string(data1)).c_str(), AREA);
		break;

	case MP_STICK:
	{
		int uid = add_str(std::string("#STICKER").c_str());

		if (pc_readglobalreg(sd, reference_uid(uid, atoi(std::string(data1).c_str()))) > 0)
		{
			bool wait = ((int)time(NULL) - (pc_readglobalreg(sd, add_str("#STICKERTIMER"))) < 10);

			if (wait)
			{
				clifmeg_dispbottom(sd->status.account_id, "#ERRO#Aguarde 10 segundos para enviar um Sticker novamente.");
				return 1;
			}

			pc_setglobalreg(sd, add_str("#STICKERTIMER"), (int)time(NULL));

			map_foreachinallarea(clifmeg_send_sub, sd->bl.m, sd->bl.x - (AREA_SIZE - 5), sd->bl.y - (AREA_SIZE - 5),
				sd->bl.x + (AREA_SIZE - 5), sd->bl.y + (AREA_SIZE - 5), BL_PC, std::string("STICKER"), std::string(data1));

			clif_disp_overhead_(&sd->bl, std::string("* ").append(std::string(sd->status.name).append(" mandou um sticker *")).c_str(), AREA);
		}
	}
		break;

	case MP_WHISPER:
	{
		if (!sd->mast[MASTERY_CONTADOR_DE_SEGREDOS]->active)
		{
			clifmeg_dispbottom(sd->status.account_id, "#ERRO#A Maestria [Contador de Segredos] é necessária para executar esta ação.");
			return 1;
		}

		d = util_explode(data1, "|");

		map_session_data *tsd = map_nick2sd(d[0].c_str(), false);

		if (!tsd)
		{
			clifmeg_dispbottom(sd->status.account_id, "#ERRO#Jogador não existe ou não está online no momento.");
			return 1;
		}

		if (strcmp(tsd->status.name, sd->status.name) == 0)
		{
			clif_disp_overhead_(&sd->bl, "Hehe, sou mongoloide", AREA);
			return 1;
		}

		if (tsd->csd[CSD_BLOCKALL]->active)
		{
			clifmeg_dispbottom(sd->status.account_id, "#ERRO#Jogador está com a habilidade [Foco] ativada e por isso não foi possível enviar sua mensagem.");
			return 1;
		}

		clifmeg_dispbottom(tsd->status.account_id, std::string("#WHISPER#").append("[").append(sd->status.name).append("] ").append(d[1]));
		return 1;
	}
	}

	npcInvoker(&sd->bl, npc.c_str());

	return 1;
}
