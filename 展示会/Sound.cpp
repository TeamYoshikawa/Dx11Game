#include "Sound.h"
#include <assert.h>

Sound::Sound()
{

	m_directSound = nullptr;
	m_primaryBuffer = nullptr;
	m_secondaryBuffer1 = nullptr;
}


Sound::~Sound()
{
	Finalize();
	m_directSound = nullptr;
	m_primaryBuffer = nullptr;
	m_secondaryBuffer1 = nullptr;
}


//
void Sound::Finalize(){
	FinalizeWaveFile(&m_secondaryBuffer1);
	
	FinalizeDIrectSound();

	return;
}

//
bool Sound::Load(const char* soundFile){
	bool result = false;

	result = InitializeDirectSound();
	if (!result)
	{
		return false;
	}

	result = LoadWaveFile(soundFile, &m_secondaryBuffer1);
	if (!result)
	{
		
		return false;
	}

	// Set position at the beginning of the sound buffer.
	result = m_secondaryBuffer1->SetCurrentPosition(0);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

bool Sound::InitializeDirectSound(){
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;

	result = DirectSoundCreate8(NULL, &m_directSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_directSound->SetCooperativeLevel(GetWindowHandle(), DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = m_directSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8)*waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec*waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

//
void Sound::FinalizeDIrectSound(){
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = nullptr;
	}

	if (m_directSound)
	{
		m_directSound->Release();
		m_directSound = nullptr;
	}
	return;
}

//
bool Sound::LoadWaveFile(const char* fileName, IDirectSoundBuffer8** secondaryBuffer){
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char *bufferPtr;
	unsigned long bufferSize;


	// Open the wave file in binary.
	error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the wave file header.
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Check that the chunk ID is the RIFF format.
	if ((waveFileHeader._chunkID[0] != 'R') || (waveFileHeader._chunkID[1] != 'I') ||
		(waveFileHeader._chunkID[2] != 'F') || (waveFileHeader._chunkID[3] != 'F'))
	{
		return false;
	}

	// Check that the file format is the WAVE format.
	if ((waveFileHeader._format[0] != 'W') || (waveFileHeader._format[1] != 'A') ||
		(waveFileHeader._format[2] != 'V') || (waveFileHeader._format[3] != 'E'))
	{	
		return false;
	}

	// Check that the sub chunk ID is the fmt format.
	if ((waveFileHeader._subChunkID[0] != 'f') || (waveFileHeader._subChunkID[1] != 'm') ||
		(waveFileHeader._subChunkID[2] != 't') || (waveFileHeader._subChunkID[3] != ' '))
	{	
		return false;
	}

	// Check that the audio format is WAVE_FORMAT_PCM.
	if (waveFileHeader._audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// Check that the wave file was recorded in stereo format.
	if (waveFileHeader._numChannels != 2)
	{
		return false;
	}

	// Check that the wave file was recorded at a sample rate of 44.1 KHz.
	if (waveFileHeader._sampleRate != 44100)
	{
		return false;
	}

	// Ensure that the wave file was recorded in 16 bit format.
	if (waveFileHeader._bitsPerSample != 16)
	{
		return false;
	}

	// Check for the data chunk header.
	if ((waveFileHeader._dataChunkID[0] != 'd') || (waveFileHeader._dataChunkID[1] != 'a') ||
		(waveFileHeader._dataChunkID[2] != 't') || (waveFileHeader._dataChunkID[3] != 'a'))
	{
		return false;
	}

	// Set the wave format of secondary buffer that this wave file will be loaded onto.
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// Set the buffer description of the secondary sound buffer that the wave file will be loaded onto.
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY;
	bufferDesc.dwBufferBytes = waveFileHeader._dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// Create a temporary sound buffer with the specific buffer settings.
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Test the buffer format against the direct sound 8 interface and create the secondary buffer.
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the temporary buffer.
	tempBuffer->Release();
	tempBuffer = 0;

	// Move to the beginning of the wave data which starts at the end of the data chunk header.
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// Create a temporary buffer to hold the wave file data.
	waveData = new unsigned char[waveFileHeader._dataSize];
	if (!waveData)
	{
		return false;
	}

	// Read in the wave file data into the newly created buffer.
	count = fread(waveData, 1, waveFileHeader._dataSize, filePtr);
	if (count != waveFileHeader._dataSize)
	{
		return false;
	}

	// Close the file once done reading.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Lock the secondary buffer to write wave data into it.
	result = (*secondaryBuffer)->Lock(0, waveFileHeader._dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Copy the wave data into the buffer.
	memcpy(bufferPtr, waveData, waveFileHeader._dataSize);

	// Unlock the secondary buffer after the data has been written to it.
	result = (*secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// Release the wave data since it was copied into the secondary buffer.
	delete[] waveData;
	waveData = 0;

	return true;
}

//
void Sound::FinalizeWaveFile(IDirectSoundBuffer8** secondaryBuffer){
	if (*secondaryBuffer)
	{
		(*secondaryBuffer)->Stop();
		(*secondaryBuffer)->Release();
		*secondaryBuffer = nullptr;
	}

	return;
}

//
bool Sound::PlayToOneTime(){
	bool result;
	result = PlayWaveFile(NULL);

	return result;
}

//
bool Sound::PlayToLoop(){
	bool result;
	result = PlayWaveFile(DSBPLAY_LOOPING);
	return result;
}


//
bool Sound::PlayWaveFile(DWORD isLoop){
	HRESULT result;

	// Play the contents of the secondary sound buffer.
	result = m_secondaryBuffer1->Play(0, 0, isLoop);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

//
void Sound::Stop(){
	m_secondaryBuffer1->Stop();
}

//
void Sound::SetValume(const float valume){
	m_secondaryBuffer1->SetVolume(valume);
}

//
void Sound::SetSpeed(long speed){

	m_secondaryBuffer1->SetFrequency(speed);

	return;
}