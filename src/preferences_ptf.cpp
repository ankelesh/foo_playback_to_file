#include "stdafx.h"
#include "preferences_ptf.h"
#include <SDK/advconfig.h>



static pfc::string default_format("%artist% - %title%");
static pfc::string default_stop_message("Not playing");
static pfc::string default_filename("C:\\now_playing.txt");

GUID branch_g = { 0x04df95bc, 0xda61, 0x4ed6, { 0x98, 0xd7, 0x88, 0x4b, 0x99, 0x84, 0xd9, 0x44 } };
GUID format_string_g = { 0x04df95b1, 0xda62, 0x4ed7, { 0x99, 0xd7, 0x88, 0x4b, 0x99, 0x84, 0xd9, 0x44 } };
GUID filename_string_g = { 0x04df95b2, 0xda63, 0x4ed8, { 0x9A, 0xd8, 0x89, 0x4C, 0x99, 0x84, 0xd9, 0x44 } };
GUID stop_string_g = { 0x04df95b3, 0xda64, 0x4ed9, { 0x9B, 0xd9, 0x8A, 0x4D, 0x9A, 0x84, 0xd9, 0x44 } };

static advconfig_branch_factory ptf_config_branch("Playback to file",
	branch_g,
	advconfig_branch::guid_branch_display,
	0);

static advconfig_string_factory ptf_format_config_entry("File contents formatting",
	format_string_g,
	branch_g, 
	0,
	default_format);

static advconfig_string_factory ptf_filename_config_entry("File name for writing playback",
	filename_string_g,
	branch_g,
	0,
	default_filename);

static advconfig_string_factory ptf_stopmessage_config_entry("Message for display while off",
	stop_string_g,
	branch_g,
	0,
	default_stop_message);

pfc::string configuration::get_format_string()
{
	pfc::string temp;
	ptf_format_config_entry.get(temp);
	return temp;
}

pfc::string configuration::get_filename_path()
{
	pfc::string temp;
	ptf_filename_config_entry.get(temp);
	return temp;
}

pfc::string configuration::get_stop_message()
{
	pfc::string temp;
	ptf_stopmessage_config_entry.get(temp);
	return temp;
}
