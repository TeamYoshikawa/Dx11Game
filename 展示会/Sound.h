#ifndef _SOUND_H
#define _SOUND_H

#ifndef _SOUNDLINK_
#define _SOUNDLINK_
#pragma comment (lib,"dsound.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib,"winmm.lib")
#endif

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>
#include "DirectXEntity.h"
	enum eSoundSpeed{
		eHighSpeed = 44100,
		eSecondSpeed = 32050,
		eThirdSpeed = 11025,
		eFourthSpeed = 5512,
		eFifthSpeed = 2756,
		eSixthSpeed = 1378,
		eSeventhSpeed = 689,
		eEighthSpeed = 344,
		eLowSpeed = 172,
		eNull = 0
	};

	class Sound:
		aetherClass::DirectXEntity
	{

	private:
		struct WaveHeaderType{
			char _chunkID[4];
			unsigned long _chunkSize;
			char _format[4];
			char _subChunkID[4];
			unsigned long _subChunkSize;
			unsigned short _audioFormat;
			unsigned short _numChannels;
			unsigned long _sampleRate;
			unsigned long _bytesPerSecound;
			unsigned short _blockAign;
			unsigned short _bitsPerSample;
			char _dataChunkID[4];
			unsigned long _dataSize;
		};

	public:
		Sound();
		~Sound();
		
		
		bool Load(const char*);
		void SetValume(const float);
		void SetSpeed(long);
		bool PlayToOneTime();
		bool PlayToLoop();
		void Stop();
	private:
	
		void Finalize();
		
		bool InitializeDirectSound();
		void FinalizeDIrectSound();

		bool LoadWaveFile(const char*, IDirectSoundBuffer8**);
		void FinalizeWaveFile(IDirectSoundBuffer8**);

		bool PlayWaveFile(DWORD);


	private:
		IDirectSound8* m_directSound;
		IDirectSoundBuffer* m_primaryBuffer;

		IDirectSoundBuffer8* m_secondaryBuffer1;
	};
#endif