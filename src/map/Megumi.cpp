
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

#include <algorithm>

static std::map<int, megumi> megumiList;
static std::map<int, megumi>::iterator megumiIT;

/*
	Megumi Database
*/

inline uint32_t GenerateMegumiHash(const std::string& str)
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

	return NULL;
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

/*
	Cuida do Recebimento dos Packets de Megumi
*/
int megumipackethandle(int fd)
{
	char data1[MAX_MEGPACKETSIZE];
	char UP[50];
	uint32 clienttype;

	safestrncpy(data1, RFIFOCP(fd, 6), MAX_MEGPACKETSIZE);
	safestrncpy(UP, RFIFOCP(fd, 306), 50);
	clienttype = RFIFOL(fd, 356);

	RFIFOSKIP(fd, RFIFOREST(fd));

	std::string npc = "";

	struct megumi meg(fd);

	switch (clienttype)
	{
		case MP_LOGIN:
		{
			session[fd]->hash = AddMegumi(std::string(UP), fd);
			session[fd]->flag.megumi = true;

			ShowInfo("[Megumi] Megumi for [%s] is now connected to emulator.\n", UP);

			//TODO: Remover Megumi depois de alguns segundos caso o jogador n�o se conecte.
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

	npcInvoker(&sd->bl, npc.c_str());

	switch (clienttype)
	{

	}

	return 1;
}
