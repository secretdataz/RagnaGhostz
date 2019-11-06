#ifndef CLIFMEG_HPP
#define CLIFMEG_HPP

#include <vector>

#include <stdarg.h>

#include "../common/cbasetypes.hpp"
#include "../common/db.hpp" //dbmap
#include "../common/mmo.hpp"
#include "../common/timer.hpp" // t_tick

enum PK_MEGCLIF
{
	PK_NONE
};

void clifmeg_send(int account_id, std::string pk, std::string data);

void clifmeg_dressroomopened(int aid, int state);
void clifmeg_rpc(int aid, std::string title, std::string desc, std::string lik, std::string lit, std::string sik = "NONE", std::string sit = "NONE");

#endif /* CLIFMEG_HPP */
