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
int clifmeg_send_sub(struct block_list *bl, va_list ap);
int clifmeg_broadcast(struct block_list *bl, std::string pk, std::string data, int target);
void clifmeg_dispbottom(int aid, std::string msg);
void clifmeg_playsound(int aid, std::string sound);
void clifmeg_stopsound(int aid);
void clifmeg_sticker(int aid, std::string id);
void clifmeg_requestmac(int aid);
void clifmeg_dressroomopened(int aid, int state);
void clifmeg_rpc(int aid, std::string title, std::string desc, std::string lik, std::string lit, std::string sik = "NONE", std::string sit = "NONE");
void clifmeg_openmastery(int aid, int zeny, int events, int instance);
void clifmeg_mastery(int aid, int mastery_id, int mastery_level);
void cligmeg_addsticker(int aid, int sticker_id);
void clifmeg_points(int aid, int zeny, int events, int instance);
void clifmeg_clearplayerdata(int aid, int data);

#endif /* CLIFMEG_HPP */
