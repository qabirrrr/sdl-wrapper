#include "../../include/audio"
#include "../../include/globals"
#include <iostream>

namespace sdl 
{
    namespace audio
	{
		sound_t::sound_t(const std::string& filepath, int channel)
		{
			load_sound(filepath);
			m_channel = channel;
		}

		sound_t::~sound_t()
		{
			Mix_FreeChunk(m_sound);
		}

		sound_t::sound_t(sound_t&& old) noexcept
		{
			m_sound = old.m_sound; 
			m_channel = old.m_channel;
			m_volume = old.m_volume;
			m_filepath = std::move(old.m_filepath);
			old.m_sound = nullptr;
		}

		sound_t& sound_t::operator=(sound_t&& old) noexcept 
		{
			if (this != &old)
			{
				if (m_sound) Mix_FreeChunk(m_sound);
				m_sound = old.m_sound; 
				m_channel = old.m_channel;
				m_volume = old.m_volume;
				m_filepath = std::move(old.m_filepath);
				old.m_sound = nullptr;
			}
			return *this;
		}

		bool sound_t::load_sound(const std::string& filepath)
		{
			m_filepath = filepath;
			m_sound = Mix_LoadWAV(m_filepath.c_str());
			if (m_sound == nullptr)
			{
				std::cout << "Error (Loading sound): " << Mix_GetError() << '\n';
				return false;
			}
			return true;
		}

		const std::string sound_t::get_filepath()
		{
			return m_filepath;
		}

		void sound_t::change_channel(int channel)
		{
			m_channel = channel;
		}

		bool sound_t::channel_is_playing()
		{
			if (Mix_Playing(m_channel))
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void sound_t::adjust_volume(int volume)
		{
			if (volume >= 0 && volume <= 128) m_volume = volume;
			Mix_VolumeChunk(m_sound, volume);
		}

		int sound_t::get_channel() const
		{
			return m_channel;
		}

		int sound_t::get_volume() const
		{
			return m_volume;
		}

		bool sound_t::is_paused()
		{
			return m_paused;
		}


		void sound_t::play(int loops)
		{
			Mix_PlayChannel(m_channel, m_sound, loops); 
		}

		void sound_t::stop()
		{
			Mix_HaltChannel(m_channel);
		}

		void sound_t::pause()
		{
			Mix_Pause(m_channel);
			m_paused = true;
		}

		void sound_t::resume()
		{
			Mix_Resume(m_channel);
			m_paused = false;
		}




		music_t::music_t(const std::string& filepath)
		{
			load_music(filepath);
		}

		music_t::music_t(music_t&& old) noexcept
		{
			m_music = old.m_music; 
			m_volume = old.m_volume;
			m_filepath = std::move(old.m_filepath);
			old.m_music = nullptr;
		}

		music_t& music_t::operator=(music_t&& old) noexcept 
		{
			if (this != &old)
			{
				if (m_music) Mix_FreeMusic(m_music);
				m_music = old.m_music;
				m_volume = old.m_volume;
				m_filepath = std::move(old.m_filepath);
				old.m_music = nullptr;
			}
			return *this;
		}

		bool music_t::load_music(const std::string& filepath)
		{
			m_filepath = filepath;
			m_music = Mix_LoadMUS(m_filepath.c_str());
			if (m_music == nullptr)
			{
				std::cout << "Error (Loading music): " << Mix_GetError() << '\n';
				return false;
			}
			return true;
		}

		std::string music_t::get_filepath()
		{
			return m_filepath;
		}

		void music_t::adjust_volume(int volume)
		{
			m_volume = volume;
			Mix_VolumeMusic(volume);
		}

		int music_t::get_volume() const
		{
			return m_volume;
		}

		bool music_t::is_on()
		{
			if (g_current_music != m_music || Mix_PlayingMusic() == 0)
			{
				return false;
			}
			else 
			{
				return true;
			}
		}

		bool music_t::is_paused()
		{
			return m_paused;
		}

		void music_t::play(int loops)
		{
			if (Mix_PlayingMusic() == 0)
			{
				Mix_PlayMusic(m_music, loops);
				g_current_music = m_music;
			}
		}

		void music_t::stop()
		{
			Mix_HaltMusic();
			g_current_music = nullptr;
		}

		void music_t::pause()
		{
			Mix_PauseMusic();
			m_paused = true;
		}

		void music_t::resume()
		{
			Mix_ResumeMusic();
			m_paused = false;
		}


		music_t::~music_t()
		{
			Mix_FreeMusic(m_music);
		}
	}
}