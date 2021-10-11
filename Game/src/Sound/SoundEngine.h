#pragma once

namespace sfx
{
	enum class Sound : uint32
	{
		Positive = 0, Covered, Negative
	};

	enum class Music : uint32
	{
		MainMenu = 0
	};

	class SoundEngine
	{
	public:

	// Constructors and Destructors:

		SoundEngine();

		~SoundEngine();

	// Functions:

		// Loads sound file into memory.
		// @param	const sfx::Sound name		Name to associate with sound file.
		// @param	const char* file_path		Actual file path, 256 symbols maximum.
		void InitSound(const Sound name, const char* filePath);

		void PlaySound(const Sound name);

		// Associates music file with audio stream.
		// @param	const sfx::Music name		Name to associate with music file.
		// @param	const char* file_path		Actual file path, 256 symbols maximum.
		void InitMusic(const Music name, const char* filePath);

		void PlayMusic(const Music name, const bool looped, const bool paused);

		void Pause(const Music name);

		void PauseAll();

		void Unpause(const Music name);

		void UnpauseAll();
		
		void Stop(const Music name);

		void StopAll();

		void SetPosition(const Music name, const uint32 milliseconds);

		void FadeIn(const float& dt);

		void FadeOut(const float& dt);

		void UpdateVolumeSFX();

		void UpdateVolumeMusic();

		void Update();

	// Accessors:

		const float& GetVolumeSFX() const;

		const float& GetVolumeMusic() const;

		const bool IsPlaying(const Music name) const;

		const bool IsMusicPlaying() const;

		const bool IsPaused(const Music name) const;

		const bool IsMusicPaused() const;

	// Modifiers:

		void IncreaseVolumeSFX(const float& dt);

		void DecreaseVolumeSFX(const float& dt);

		void IncreaseVolumeMusic(const float& dt);

		void DecreaseVolumeMusic(const float& dt);

	private:

	// Private Functions:

		void InitVariables();

		void InitSoundSystem();

	// System:

		FMOD::System* SoundSystem;

		static const uint32 ChannelsMax = 32;

	// Sounds:

		// SFX
		FMOD::Sound* SoundObject[ChannelsMax];

		// Music
		FMOD::Sound* MusicObject[ChannelsMax];

	// Channels:

		// SFX
		FMOD::Channel* SoundChannel[ChannelsMax];
		FMOD::ChannelGroup* SoundGroup;

		// Music
		FMOD::Channel* MusicChannel[ChannelsMax];
		FMOD::ChannelGroup* MusicGroup;

		// Master channel group
		FMOD::ChannelGroup* MasterGroup;

	// Variables:

		// SFX
		float SoundVolume;

		// Music
		float MusicVolume;
		float FadeRate;
		std::map<const Music, const char*> MusicFile;
	};
}