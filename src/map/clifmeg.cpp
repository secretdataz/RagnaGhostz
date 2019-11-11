#include "clifmeg.hpp"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "../common/cbasetypes.hpp"
#include "../common/conf.hpp"
#include "../common/ers.hpp"
#include "../common/grfio.hpp"
#include "../common/malloc.hpp"
#include "../common/nullpo.hpp"
#include "../common/random.hpp"
#include "../common/showmsg.hpp"
#include "../common/socket.hpp"
#include "../common/strlib.hpp"
#include "../common/timer.hpp"
#include "../common/utils.hpp"

#include "pc.hpp"
#include "megumi.hpp"

#include <string>
#include <sstream>

void clifmeg_send(int account_id, std::string pk, std::string data) {

	if (account_id <= 0) return;

	struct map_session_data *sd = map_id2sd(account_id);

	if (sd == NULL) return;

	std::string pk_complete = "CMD:";
	pk_complete.append(pk);
	pk_complete.append(":");
	pk_complete.append(data);
	pk_complete.append("<>");

	const char *pkc = pk_complete.c_str();

	unsigned short data_len = (unsigned short)(strlen(pkc) + 1);
	uint8 buf[CHAT_SIZE_MAX];

	nullpo_retv(sd);

	if (data_len > sizeof(buf) - 12) {
		ShowWarning("clif_data_recv: Truncating too long message '%s' (len=%u).\n", pkc, data_len);
		data_len = sizeof(buf) - 12;
	}

	megumi meg = GetMegumiData(sd->megHash);

	if (!meg.activate) return;

	memcpy(WBUFCP(buf, 0), pkc, data_len);

	WFIFOHEAD(meg.fd, data_len);
	memcpy(WFIFOP(meg.fd, 0), buf, data_len);
	WFIFOSET(meg.fd, data_len);
}

// Avisa que a Tela de Dressroom está aberta.
// CMD:DRESSROOM:STATE
void clifmeg_dressroomopened(int aid, int state)
{
	std::string pk = std::to_string(state);
	
	clifmeg_send(aid, "DRESSROOM", pk);
}

void clifmeg_rpc(int aid, std::string title, std::string desc, std::string lik, std::string lit, std::string sik, std::string sit)
{
	std::string pk = title;
	pk.append("|");
	pk.append(desc);
	pk.append("|");
	pk.append(lik);
	pk.append("|");
	pk.append(lit);
	pk.append("|");
	pk.append(sik);
	pk.append("|");
	pk.append(sit);

	clifmeg_send(aid, "RPC", pk);
}

void clifmeg_openmastery(int aid, int zeny, int events, int instance)
{
	std::string pk = std::to_string(zeny);
	pk.append("|");
	pk.append(std::to_string(events));
	pk.append("|");
	pk.append(std::to_string(instance));

	clifmeg_send(aid, "OPENMASTERY", pk);
}

void clifmeg_mastery(int aid, int mastery_id, int mastery_level)
{
	std::string pk = std::to_string(mastery_id);
	pk.append("|");
	pk.append(std::to_string(mastery_level));

	clifmeg_send(aid, "MASTERY", pk);
}

void clifmeg_points(int aid, int zeny, int events, int instance)
{
	std::string pk = std::to_string(zeny);
	pk.append(std::to_string(events));
	pk.append(std::to_string(instance));

	clifmeg_send(aid, "POINTS", pk);
}

void clifmeg_clearplayerdata(int aid)
{
	std::string pk = std::to_string(aid);

	clifmeg_send(aid, "CLEARPLAYERDATA", pk);
}
