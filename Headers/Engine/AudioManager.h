#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/AudioListener.h>
#include <Engine/AudioClip.h>
#include <Engine/AudioSource.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

//===== STL Includes =====
#include <map>

namespace Tempest
{
    class AudioListener;
    class AudioClip;
    class AudioSource;
    typedef shared_ptr<AudioSource> p_AudioSource;

    class AudioManager
    {
    public:
        TEMPEST_API ~AudioManager(void);

        TEMPEST_API static shared_ptr<AudioManager> Instance(void);

        TEMPEST_API void AddClip(U32 id, shared_ptr<AudioClip> clip);

        TEMPEST_API void LoadClip(U32 id, string filepath);

        TEMPEST_API void RemoveClip(U32 id);

        TEMPEST_API void AddSource(U32 id, shared_ptr<AudioSource> source);

        TEMPEST_API void LoadSource(U32 id);

        TEMPEST_API void RemoveSource(U32 id);

        TEMPEST_API void PlaySource(U32 id);

        TEMPEST_API void StopSource(U32 id);

        TEMPEST_API void PauseSource(U32 id);

        TEMPEST_API void RestartSource(U32 id);

        TEMPEST_API void AddClipToSource(U32 clipID, U32 sourceID);

        TEMPEST_API string GetALCerror(ALCenum error);

        inline void SetListener(void)
        {
            _listener = make_shared<AudioListener>();
        }

        inline void SetListener(shared_ptr<AudioListener> listener)
        {
            _listener = listener;
        }

        inline shared_ptr<AudioListener> GetListener(void)
        {
            return _listener;
        }

        TEMPEST_API p_AudioClip GetClip(U32 id);

        TEMPEST_API p_AudioSource GetSource(U32 id);


    protected:
        AudioManager(void);

    private:
        static shared_ptr<AudioManager> _instance; 
        ALCdevice* _device;	
        ALCcontext* _context;
        p_AudioListener _listener;
        std::map<U32, p_AudioClip> _clips;	
        std::map<U32, p_AudioSource> _sources;

    };//end Class
    typedef shared_ptr<AudioManager> p_AudioManager;
}//end Namespace
