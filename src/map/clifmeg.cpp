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
#include "battle.hpp"
#include "party.hpp"
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

int clifmeg_send_sub(struct block_list *bl, va_list ap)
{
	struct block_list *src_bl;

	nullpo_ret(src_bl = va_arg(ap, struct block_list*));

	std::string pk = va_arg(ap, std::string);
	std::string data = va_arg(ap, std::string);

	clifmeg_send(bl->id, pk, data);

	return 1;
}

int clifmeg_broadcast(struct block_list *bl, std::string pk, std::string data, int target)
{
	if (target != ALL_CLIENT)
		nullpo_ret(bl);

	struct map_session_data *sd = BL_CAST(BL_PC, bl);
	struct map_session_data *tsd;
	struct party_data *p = NULL;
	struct guild *g = NULL;

	int x0 = 0, x1 = 0, y0 = 0, y1 = 0, fd, i;
	struct s_mapiterator* iter;

	switch (target)
	{
	case ALL_CLIENT:
		iter = mapit_getallusers();
		while ((tsd = (TBL_PC*)mapit_next(iter)) != NULL) {
			clifmeg_send(tsd->status.account_id, pk, data);
		}
		mapit_free(iter);
		break;

	case ALL_SAMEMAP:
		iter = mapit_getallusers();
		while ((tsd = (TBL_PC*)mapit_next(iter)) != NULL)
		{
			if (bl->m == tsd->bl.m) {
				clifmeg_send(tsd->status.account_id, pk, data);
			}
		}
		mapit_free(iter);
		break;

	case AREA:
	case AREA_WOSC:
		if (sd && bl->prev == NULL) //Otherwise source misses the packet.[Skotlex]
			clifmeg_send(sd->status.account_id, pk, data);
	case AREA_WOC:
	case AREA_WOS:
		map_foreachinallarea(clifmeg_send_sub, bl->m, bl->x - AREA_SIZE, bl->y - AREA_SIZE, bl->x + AREA_SIZE, bl->y + AREA_SIZE,
			BL_PC, bl, pk, data);
		break;
	case AREA_CHAT_WOC:
		map_foreachinallarea(clifmeg_send_sub, bl->m, bl->x - (AREA_SIZE - 5), bl->y - (AREA_SIZE - 5),
			bl->x + (AREA_SIZE - 5), bl->y + (AREA_SIZE - 5), BL_PC, bl, pk, data);
		break;

	case PARTY_AREA:
	case PARTY_AREA_WOS:
		x0 = bl->x - AREA_SIZE;
		y0 = bl->y - AREA_SIZE;
		x1 = bl->x + AREA_SIZE;
		y1 = bl->y + AREA_SIZE;
	case PARTY:
	case PARTY_WOS:
	case PARTY_SAMEMAP:
	case PARTY_SAMEMAP_WOS:
		if (sd && sd->status.party_id)
			p = party_search(sd->status.party_id);

		if (p) {
			for (i = 0; i < MAX_PARTY; i++) {
				if ((sd = p->data[i].sd) == NULL)
					continue;

				if (!(fd = sd->fd))
					continue;

				if (sd->bl.id == bl->id && (target == PARTY_WOS || target == PARTY_SAMEMAP_WOS || target == PARTY_AREA_WOS))
					continue;

				if (target != PARTY && target != PARTY_WOS && bl->m != sd->bl.m)
					continue;

				if ((target == PARTY_AREA || target == PARTY_AREA_WOS) && (sd->bl.x < x0 || sd->bl.y < y0 || sd->bl.x > x1 || sd->bl.y > y1))
					continue;

				clifmeg_send(sd->status.account_id, pk, data);
			}
		}
		break;

	case SELF:
		if (sd && (fd = sd->fd)) {
			clifmeg_send(sd->status.account_id, pk, data);
		}
		break;

	case GUILD_AREA:
	case GUILD_AREA_WOS:
		x0 = bl->x - AREA_SIZE;
		y0 = bl->y - AREA_SIZE;
		x1 = bl->x + AREA_SIZE;
		y1 = bl->y + AREA_SIZE;
	case GUILD_SAMEMAP:
	case GUILD_SAMEMAP_WOS:
	case GUILD:
	case GUILD_WOS:
	case GUILD_NOBG:
		if (sd && sd->status.guild_id)
			g = sd->guild;

		if (g) {
			for (i = 0; i < g->max_member; i++) {
				if ((sd = g->member[i].sd) != NULL)
				{
					if (!(fd = sd->fd))
						continue;

					if (target == GUILD_NOBG && sd->bg_id)
						continue;

					if (sd->bl.id == bl->id && (target == GUILD_WOS || target == GUILD_SAMEMAP_WOS || target == GUILD_AREA_WOS))
						continue;

					if (target != GUILD && target != GUILD_NOBG && target != GUILD_WOS && sd->bl.m != bl->m)
						continue;

					if ((target == GUILD_AREA || target == GUILD_AREA_WOS) && (sd->bl.x < x0 || sd->bl.y < y0 || sd->bl.x > x1 || sd->bl.y > y1))
						continue;

					clifmeg_send(sd->status.account_id, pk, data);
				}
			}
		}
		break;

	default:
		ShowError("clif_megsend: Unrecognized target %d\n", target);
		return -1;
	}

	return 0;
}

// Envia mensagem para o chat
// CMD:DISP:COLOR:MSG
void clifmeg_dispbottom(int aid, std::string msg)
{
	std::string pk = msg;

	clifmeg_send(aid, "DISP", pk);
}

// Mostra um Sticker no chat
// CMD:STICKER:ID
void clifmeg_sticker(int aid, std::string id)
{
	std::string pk = id;

	clifmeg_send(aid, "STICKER", pk);
}

// Pede o MAC
void clifmeg_requestmac(int aid)
{
	std::string pk = std::to_string(aid);

	clifmeg_send(aid, "REQMAC", pk);
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

void clifmeg_clearplayerdata(int aid, int data)
{
	std::string pk = std::to_string(data);

	clifmeg_send(aid, "CLEARPLAYERDATA", pk);
}
