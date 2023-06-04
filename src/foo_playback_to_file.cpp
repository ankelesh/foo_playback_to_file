#include "stdafx.h"
#include "SDK/play_callback.h"
#include <fstream>
#include <memory>
#include "preferences_ptf.h"


DECLARE_COMPONENT_VERSION(
    "foo_playback_to_file",
    "0.2",
    "Sends track data to file." "\n"
);

VALIDATE_COMPONENT_FILENAME("foo_playback_to_file.dll");

class playback_to_file_callback : private play_callback, public initquit
{

	pfc::string generate_title(metadb_handle_ptr p_track);
	void update_file(metadb_handle_ptr p_track);

	virtual void on_playback_starting(play_control::t_track_command p_command, bool p_paused);
	//! Playback advanced to new track.
	virtual void on_playback_new_track(metadb_handle_ptr p_track) { update_file(p_track); }
	//! Playback stopped.
	virtual void on_playback_stop(play_control::t_stop_reason p_reason);



	//! User has seeked to specific time.
	virtual void on_playback_seek(double p_time) {};
	//! Called on pause/unpause.
	virtual void on_playback_pause(bool p_state) {};
	//! Called when currently played file gets edited.
	virtual void on_playback_edited(metadb_handle_ptr p_track) {};
	//! Dynamic info (VBR bitrate etc) change.
	virtual void on_playback_dynamic_info(const file_info& p_info) {};
	//! Per-track dynamic info (stream track titles etc) change. Happens less often than on_playback_dynamic_info().
	virtual void on_playback_dynamic_info_track(const file_info& p_info) {};
	//! Called every second, for time display
	virtual void on_playback_time(double p_time) {};
	//! User changed volume settings. Possibly called when not playing.
	//! @param p_new_val new volume level in dB; 0 for full volume.
	virtual void on_volume_change(float p_new_val) {};
public:
	playback_to_file_callback() {};
	virtual void on_init()
	{
		console::formatter() << "'foo_playback_to_file' started!";
		play_callback_manager::get()->register_callback(this, flag_on_playback_new_track, false);
	}

	virtual void on_quit() {}
};

static initquit_factory_t< playback_to_file_callback > foo_initquit_pbtf;

pfc::string playback_to_file_callback::generate_title(metadb_handle_ptr p_track)
{
	titleformat_object::ptr h;
	titleformat_compiler_v2::get()->compile_safe(h, configuration::get_format_string());
	pfc::string s;
	p_track->format_title(nullptr, s, h, nullptr);
	return s;
}

void playback_to_file_callback::update_file(metadb_handle_ptr p_track)
{
	try {
		std::ofstream f;
		f.open(configuration::get_filename_path());
		if (!f.is_open())
		{
			console::formatter() << "Playback to file error: can not open file '" << configuration::get_filename_path() << "'.";
			return;
		}
		f << generate_title(p_track).c_str();
		f.close();
	}
	catch (std::exception& e)
	{
		console::formatter() << "Playback to file error: caught exception " << e.what();
	}
}

void playback_to_file_callback::on_playback_starting(play_control::t_track_command p_command, bool p_paused)
{
	try {
		std::ofstream f;
		f.open(configuration::get_filename_path());
		if (!f.is_open())
		{
			console::formatter() << "Playback to file error: can not open file '" << configuration::get_filename_path() << "'.";
			return;
		}
		f << "Playback to file started";
		f.close();
	}
	catch (std::exception& e)
	{
		console::formatter() << "Playback to file error: caught exception " << e.what();
	}
}

void playback_to_file_callback::on_playback_stop(play_control::t_stop_reason p_reason)
{
	try {
		std::ofstream f;
		f.open(configuration::get_filename_path());
		if (!f.is_open())
		{
			console::formatter() << "Playback to file error: can not open file '" << configuration::get_filename_path() << "'.";
			return;
		}
		f << configuration::get_stop_message().c_str();
		f.close();
	}
	catch (std::exception& e)
	{
		console::formatter() << "Playback to file error: caught exception " << e.what();
	}
}
