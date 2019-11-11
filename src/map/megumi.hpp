#ifndef MEGUMI_HPP
#define MEGUMI_HPP

#include <algorithm>
#include <stdarg.h>
#include <unordered_map>
#include <vector>

#include "../common/cbasetypes.hpp"
#include "../common/mmo.hpp"
#include "../config/core.hpp"

#include "map.hpp"

constexpr auto MAX_MEGPACKETSIZE = 300;

enum e_megumi_packet
{
	MP_LOGIN = 2478,
	MP_STYLE = 3000,
	MP_CLOSEDMASTERY,
	MP_BUYMASTERY,
	MP_HELPMASTERY,
	MP_REFRESHMASTERY
};

struct megumi {
	megumi(int fd_) : fd(fd_) {}
	megumi() : activate(false) {}

	bool activate;

	int fd;
	int account_id;
	int char_id;
};

void DeleteMegumi(uint32 hash);
struct megumi GetMegumiData(uint32 hash);
void UpdateMegumi(int hash, struct megumi);
int AddMegumi(std::string UP, int fd);

inline uint32_t GenerateMegumiHash(const std::string& str);
int megumipackethandle(int fd);

#endif /* MEGUMI_HPP */
