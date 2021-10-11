#include "../stdafx.h"
#include "SoundEngine.h"

namespace sfx
{
// Constructors and Destructor:

	SoundEngine::SoundEngine()
	{
		InitVariables();

		InitSoundSystem();
	}

	SoundEngine::~SoundEngine()
	{
		// Stopping all channels
		MasterGroup->stop();

		// Releasing sound resources
		for (uint32 i = 0; i < ChannelsMax; i++)
		{
			SoundObject[i]->release();
			MusicObject[i]->release();
		}

		// Releasing sound system resources
		SoundSystem->close();
		SoundSystem->release();
	}


// Functions:

	void SoundEngine::InitSound(const Sound name, const char* filePath)
	{
		SoundSystem->createSound(filePath, FMOD_DEFAULT, 0, &SoundObject[static_cast<uint32>(name)]);
	}

	void SoundEngine::PlaySound(const Sound name)
	{
		SoundSystem->playSound(SoundObject[static_cast<uint32>(name)], SoundGroup, false, &SoundChannel[static_cast<uint32>(name)]);
	}

	void SoundEngine::InitMusic(const Music name, const char* filePath)
	{
		MusicFile[name] = filePath;
	}
	
	void SoundEngine::PlayMusic(const Music name, const bool looped, const bool paused)
	{
		if (looped)
		{
			SoundSystem->createStream(MusicFile[name], FMOD_LOOP_NORMAL, 0, &MusicObject[static_cast<unsigned int>(name)]);
		}
		else
		{
			SoundSystem->createStream(MusicFile[name], FMOD_DEFAULT, 0, &MusicObject[static_cast<unsigned int>(name)]);
		}

		SoundSystem->playSound(MusicObject[static_cast<unsigned int>(name)], MusicGroup, paused, &MusicChannel[static_cast<unsigned int>(name)]);
	}
	
	void SoundEngine::Pause(const Music name)
	{
		MusicChannel[static_cast<uint32>(name)]->setPaused(true);
	}
	
	void SoundEngine::PauseAll()
	{
		MusicGroup->setPaused(true);
	}
	
	void SoundEngine::Unpause(const Music name)
	{
		MusicChannel[static_cast<uint32>(name)]->setPaused(false);
	}
	
	void SoundEngine::UnpauseAll()
	{
		MusicGroup->setPaused(false);
	}
	
	void SoundEngine::Stop(const Music name)
	{
		MusicChannel[static_cast<uint32>(name)]->stop();
	}
	
	void SoundEngine::StopAll()
	{
		MusicGroup->stop();
	}
	
	void SoundEngine::SetPosition(const Music name, const uint32 milliseconds)
	{
		MusicChannel[static_cast<uint32>(name)]->setPosition(milliseconds, FMOD_TIMEUNIT_MS);
	}
	
	void SoundEngine::FadeIn(const float& dt)
	{
		if (FadeRate < 1.f)
		{
			FadeRate += dt;

			if (FadeRate > 1.f)
			{
				FadeRate = 1.f;
			}
		}
		
		UpdateVolumeMusic();
	}
	
	void SoundEngine::FadeOut(const float& dt)
	{
		if (FadeRate > 0.f)
		{
			FadeRate -= dt;

			if (FadeRate < 0.f)
			{
				FadeRate = 0.f;
			}
		}

		UpdateVolumeMusic();
	}
	
	void SoundEngine::UpdateVolumeSFX()
	{
		SoundGroup->setVolume(SoundVolume);
	}
	
	void SoundEngine::UpdateVolumeMusic()
	{
		MusicGroup->setVolume(MusicVolume * FadeRate);
	}
	
	void SoundEngine::Update()
	{
		SoundSystem->update();
	}
	

// Accessors:

	const float& SoundEngine::GetVolumeSFX() const
	{
		return SoundVolume;
	}
	
	const float& SoundEngine::GetVolumeMusic() const
	{
		return MusicVolume;
	}
	
	const bool SoundEngine::IsPlaying(const Music name) const
	{
		bool playing;

		MusicChannel[static_cast<unsigned int>(name)]->isPlaying(&playing);

		return playing;
	}
	
	const bool SoundEngine::IsMusicPlaying() const
	{
		bool playing;

		MusicGroup->isPlaying(&playing);

		return playing;
	}
	
	const bool SoundEngine::IsPaused(const Music name) const
	{
		bool paused;

		MusicChannel[static_cast<unsigned int>(name)]->getPaused(&paused);

		return paused;
	}
	
	const bool SoundEngine::IsMusicPaused() const
	{
		bool paused;

		MusicGroup->getPaused(&paused);

		return paused;
	}
	
	
// Modifiers:

	void SoundEngine::IncreaseVolumeSFX(const float& dt)
	{
		SoundVolume += dt;

		if (SoundVolume > 1.f)
		{
			SoundVolume = 1.f;
		}
	}

	void SoundEngine::DecreaseVolumeSFX(const float& dt)
	{
		SoundVolume -= dt;

		if (SoundVolume < 0.f)
		{
			SoundVolume = 0.f;
		}
	}
	
	void SoundEngine::IncreaseVolumeMusic(const float& dt)
	{
		MusicVolume += dt;

		if (MusicVolume > 1.f)
		{
			MusicVolume = 1.f;
		}
	}
	
	void SoundEngine::DecreaseVolumeMusic(const float& dt)
	{
		MusicVolume -= dt;

		if (MusicVolume < 0.f)
		{
			MusicVolume = 0.f;
		}
	}
	
	
// Private Functions:

	void SoundEngine::InitVariables()
	{
		// SFX
		SoundVolume = 0.5f;

		// Music
		MusicVolume = 0.5f;
		FadeRate = 1.f;
	}
	
	void SoundEngine::InitSoundSystem()
	{
		// System initialization
		FMOD::System_Create(&SoundSystem);
		SoundSystem->init(static_cast<int32>(ChannelsMax * 2u), FMOD_INIT_NORMAL, 0);

		// Creating channel groups
		SoundSystem->createChannelGroup("SFX", &SoundGroup);
		SoundSystem->createChannelGroup("Music", &MusicGroup);
		SoundSystem->getMasterChannelGroup(&MasterGroup);

		//Set the sfxGruop and musicGroup to be children of the master group
		MasterGroup->addGroup(SoundGroup);
		MasterGroup->addGroup(MusicGroup);

		// Attaching channels to SFX group
		for (uint32 i = 0; i < ChannelsMax; i++)
		{
			SoundChannel[i]->setChannelGroup(SoundGroup);
		}

		// Attaching channels to Music group
		for (uint32 i = 0; i < ChannelsMax; i++)
		{
			MusicChannel[i]->setChannelGroup(MusicGroup);
		}

		// Setting SFX volume
		SoundGroup->setVolume(SoundVolume);

		// Setting Music volume
		MusicGroup->setVolume(MusicVolume);
	}
}