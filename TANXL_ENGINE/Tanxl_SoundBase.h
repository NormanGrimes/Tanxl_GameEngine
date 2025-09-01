//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-26 22:23
// ����ö�����ذ汾����Ƶ���Ź���
// ������������
// ����������ͼ�¼�����Ƶ
// �����ָ�����ֵ�����������Ƶ
// ����ϵͳ������Ƶ
// ���Ӱ汾��Ϣ����
// ����ֹͣ������Ƶ����
// ��Ϊ�̳������������
// �����ɾͽ�����Ƶ
// ���Ӽ������غ��ĵ���Ƶ
// ���Ӽ��ָ����Ƶ�Ƿ��ڲ��ŵĽӿ�
// ���Ӽ�⵱ǰ������Ƶ��ŵĽӿ�
// ���ӱ���������������ӽӿ�
// ��������ö������Ϊ�ļ�·���ĺ����汾
// �����������ֲ��Žӿ�
// ��������ö�ٵļ��
// ���ӻ�ȡ���������Ƿ񲥷ŵĽӿ�

#pragma once

#ifndef _TANXL_SOUNDBASE_
#define _TANXL_SOUNDBASE_

#include <string>
#include <vector>
#include <irrKlang/irrKlang.h>

#include "Tanxl_EngineBase.h"

enum ESound_WAV
{
    SOUND_GAME_START        = 0,
    SOUND_GAME_OVER         = 1,
    SOUND_EVENT_START       = 2,
    SOUND_RESTORE_HEALTH    = 3,
    SOUND_MOUSE_CLICK       = 4,
    SOUND_SYSTEM_CALL       = 5,
    SOUND_ACHIEVEMENT       = 6,
    SOUND_SECRET_CORE       = 7,
    SOUND_BACKGROUND_01     = 8,
    SOUND_BACKGROUND_02     = 9,
    SOUND_BACKGROUND_03     = 10,
    SOUND_BACKGROUND_04     = 11,
    SOUND_BACKGROUND_05     = 12,

    SOUND_NO_SOUND          = 0xFF
};

class SoundBase : public Tanxl_ClassBase
{
public:
    static SoundBase& GetSoundBase();

    void Play_Sound(std::string Wav_File_Location);

    void Play_Sound(ESound_WAV Sound_Name);

    void Append_BackGround_Music(std::string Wav_File_Location);

    void Append_BackGround_Music(ESound_WAV Sound_Name);

    void Stop_AllSound();
    // �����Ա������ֵ�˳�򲥷Ź��� ˳�򲥷Ź�����Ҫ��������
    void Play_BackGround_Music(int Begin_Id);

    bool Sound_Playing(std::string Wav_File_Location);

    bool Sound_Playing(ESound_WAV Sound_Name);

    bool BackGround_Playing();

    ESound_WAV Sound_Playing_Id();

    const std::string Get_Version();

private:
    irrklang::ISoundEngine* _SoundEngine;

    std::string _Sound_Names[13]
    { 
        "music/Game_Start.wav", 
        "music/Game_Over.wav",
        "music/Game_Event_Start.wav",
        "music/Game_Event_Restore_Health.wav" ,
        "music/Game_Mouse_Click.wav",
        "music/Game_System_Call.wav",
        "music/Achievement_Unlock.wav",
        "music/Game_Event_Secret_Core.wav",
        "music/Game_BackGround_01.mp3",
        "music/Game_BackGround_02.mp3",
        "music/Game_BackGround_03.mp3",
        "music/Game_BackGround_04.mp3",
        "music/Game_BackGround_05.mp3"
    };

    std::vector<std::string> _BackGround_Music_List;

    int _Current_BackGround_Id;
    bool _BackGround_Music_Playing;

    SoundBase();
    ~SoundBase();
    SoundBase(const SoundBase&);
    SoundBase& operator=(const SoundBase&);
};

#endif
