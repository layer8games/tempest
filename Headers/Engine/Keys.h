#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>

namespace Tempest
{
    /// Keycodes to access specific Key state. Each value is used to represent keys that are pressed by the user.
/// These codes represent all possible key inputs. In order to add support for a new key, this enum must be 
/// updated 
    enum TEMPEST_API Keys
    {
        NO_KEY, 			///<Used as a fall through to indicated an error 
        A,					///< Alphabetic A key
        B,					///< Alphabetic B key
        C,					///< Alphabetic C key
        D,					///< Alphabetic D key
        E,					///< Alphabetic E key		
        F,					///< Alphabetic F key
        G,					///< Alphabetic G key
        H,					///< Alphabetic H key
        I,					///< Alphabetic I key
        J,					///< Alphabetic J key
        K,					///< Alphabetic K key
        L,					///< Alphabetic L key
        M,					///< Alphabetic M key
        N,					///< Alphabetic N key
        O,					///< Alphabetic O key
        P,					///< Alphabetic P key
        Q,					///< Alphabetic Q key
        R,					///< Alphabetic R key
        S,					///< Alphabetic S key
        T,					///< Alphabetic T key
        U,					///< Alphabetic U key
        V,					///< Alphabetic V key
        W,					///< Alphabetic W key
        X,					///< Alphabetic X key
        Y,					///< Alphabetic Y key
        Z,					///< Alphabetic Z key
        UP_ARROW,			///< Up Arrow key
        DOWN_ARROW,			///< Down Arrow key
        LEFT_ARROW,			///< Left Arrow key
        RIGHT_ARROW,		///< Right Arrow key
        ZERO,				///< 0 key
        ONE,				///< 1 key
        TWO,				///< 2 key
        THREE,				///< 3 key
        FOUR,				///< 4 key
        FIVE,				///< 5 key
        SIX,				///< 6 key
        SEVEN,				///< 7 key
        EIGHT,				///< 8 key
        NINE,				///< 9 key
        MINUS,				///< Minus key
        EQUAL,				///< Plus key
        SPACE,				///< Spacebar
        ESCAPE,				///< Escape key
        TAB,				///< Tab key
        LSHIFT,				///< Left Shift key
        RSHIFT,				///< Right Shift key
        ENTER,				///< Enter key
        RIGHT_MOUSE,		///< Right Mouse click
        LEFT_MOUSE,			///< Left Mouse click
        MIDDLE_MOUSE,		///< Middle Mouse click
        F1,					///< F1 key
        F2,					///< F2 key
        F3,					///< F3 key
        F4,					///< F4 key
        F5,					///< F5 key
        F6,					///< F6 key
        F7,					///< F7 Key
        F8,					///< F8 key
        F9,					///< F9 key
        F10,				///< F10 key
        F11,				///< F11 key
        TOTAL_KEYS			///< Total keys available. 
    };
}