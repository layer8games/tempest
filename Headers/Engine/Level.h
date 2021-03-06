#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Driver.h"
#include "Engine/ErrorManager.h"
#include "Engine/GameObject2D.h"
#include "Engine/GameObject3D.h"
#include "Engine/StaticGameObject2D.h"
#include "Engine/TextureManager.h"
#include "Engine/Vector4.h"
#include "Engine/Color.h"
#include "Engine/Text.h"
#include "Engine/ForceRegistry.h"
#include "Engine/Text.h"
#include "Engine/RigidBody2D.h"
#include "Engine/Vector2.h"
#include "Engine/CameraController.h"
#include "Engine/Camera.h"
#include "Engine/Factory.h"

namespace TM = TempestMath;
namespace TP = TempestPhysics;

#include "rapidxml.hpp"

#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

namespace Tempest 
{
    class Engine;
    
    class Level
    {
    public:
        typedef rapidxml::xml_node<>* xmlNode;
        typedef rapidxml::xml_document<> xmlDoc;

        TEMPEST_API Level(void);

        TEMPEST_API virtual ~Level(void);

        TEMPEST_API virtual void v_Init(string path);

        TEMPEST_API virtual void v_Init(void);
    
        TEMPEST_API virtual void v_Update(void);
        
        TEMPEST_API virtual void v_Enter(void);

        TEMPEST_API virtual void v_Exit(void);
        
        TEMPEST_API void RegisterRigidBody2DForce(TP::p_RigidBody2D body, TP::p_ForceGenerator generator);
    
        TEMPEST_API void SetBackgroundColor(const Color& c);

        TEMPEST_API void ActivateBackgroundColor(void);

        TEMPEST_API S32 GetWidth(void) const;

        TEMPEST_API S32 GetHeight(void) const;

        TEMPEST_API void SetWidth(S32 w);

        TEMPEST_API void SetHeight(S32 h);

        TEMPEST_API void SetDimensions(S32 w, S32 h);
 
        TEMPEST_API S32 GetTopBorder(void) const;

        TEMPEST_API S32 GetBottomBorder(void) const;
        
        TEMPEST_API S32 GetLeftBorder(void) const;

        TEMPEST_API S32 GetRightBorder(void) const;
 
        TEMPEST_API void SetDepth(S32 d);

        TEMPEST_API S32 GetDepth(void);

        TEMPEST_API void SetNearBorder(S32 n);
 
        TEMPEST_API void SetFarBorder(S32 f);

        TEMPEST_API S32 GetNearBorder(void);

        TEMPEST_API S32 GetFarBorder(void);

        TEMPEST_API void SetID(U32 id);

        TEMPEST_API U32 GetID(void) const;

        TEMPEST_API void SetFactory(p_Factory factory);

    protected:
        struct TileData
        {
            U32 id;
            U32 imageWidth;
            U32 imageHeight;
            string type;
            string imageFilePath;
            TM::Point2 pos;
        };

        struct GridPos
        {
            S32 x;
            S32 y;
        };
        
        TEMPEST_API void _DefaultInit(string filepath);

        TEMPEST_API void _DefaultInit(void);
        
        TEMPEST_API void _DefaultUpdate(void);
        
        TEMPEST_API void _DefaultExit(void);
        
        TEMPEST_API void _DefaultEnter(void);

        TEMPEST_API std::vector<TileData> _ImportTMXMapData(string filepath);
        
        TEMPEST_API GridPos _ConvertIndexToTileData(U32 index, U32 width, U32 height);

        TEMPEST_API void _LoadLevel(string filepath);
       
        p_Factory _factory;
        
    private:
        string _OpenFile(string filePath);
        
        std::vector<U32> _SplitU32(string text, char delim) const;		
        
        S32 _width;
        S32 _height;
        S32 _topBorder;
        S32 _bottomBorder;
        S32 _rightBorder;
        S32 _leftBorder;
        S32 _depth;
        S32	_nearBorder;
        S32 _farBorder;
        Color _bgColor;
        U32 _ID;
        TP::ForceRegistry _forceRegistry;
    };
    typedef shared_ptr<Level> p_Level;
}//End namespace

