#include "stdafx.h"
#include "Engine/Level.h"
using namespace Tempest;

Level::Level(void) 
: 
_width(0),
_height(0),
_topBorder(0),
_bottomBorder(0),
_rightBorder(0),
_leftBorder(0),
_depth(0),
_nearBorder(0),
_farBorder(0),
_bgColor(),
_ID(0),
_forceRegistry(),
_factory(nullptr)
{  }

Level::~Level(void)
{  }

void Level::v_Init(string path)
{
    _DefaultInit(path);
}

void Level::v_Init(void)
{
    _DefaultInit();
}

void Level::_DefaultInit(void)
{
    CameraController::Instance()->SetOrthographicCamera();
}

void Level::_DefaultInit(string filepath)
{
    CameraController::Instance()->SetOrthographicCamera();
    _LoadLevel(filepath);
}

void Level::v_Update(void)
{
    _DefaultUpdate();
}

void Level::_DefaultUpdate(void)
{
    _forceRegistry.UpdateForces();
}

void Level::v_Enter(void)
{
    _DefaultEnter();
}

void Level::_DefaultEnter(void)
{
    ActivateBackgroundColor();
}

void Level::v_Exit(void)
{
    _DefaultExit();
}

void Level::_DefaultExit(void)
{

}

void Level::RegisterRigidBody2DForce(TP::p_RigidBody2D body, TP::p_ForceGenerator generator)
{
    _forceRegistry.Add(body, generator);
}

void Level::SetBackgroundColor(const Color& c) 
{ 
    _bgColor = c;
    ActivateBackgroundColor();
}

void Level::ActivateBackgroundColor(void)
{
    Driver::Instance()->SetScreenColor(_bgColor);
}

Level::GridPos Level::_ConvertIndexToTileData(U32 index, U32 width, U32 height)
{
    GridPos pos;
    pos.x = index % width;
    pos.y = height - (index / height);

    return pos;
}

std::vector<Level::TileData> Level::_ImportTMXMapData(string filepath)
{
    std::map<U32, TileData> tiles;
    std::vector<TileData> objects;
    if(filepath.find(".tmx") != std::string::npos)
    {
        string content = _OpenFile(filepath);

        xmlDoc doc;
        doc.parse<0>(const_cast<char*>(content.c_str()));

        xmlNode map_node = doc.first_node("map");
        xmlNode tileset_node = map_node->first_node("tileset");

        U32 mapWidth = std::stoul(map_node->first_attribute("width")->value());
        U32 mapHeight = std::stoul(map_node->first_attribute("height")->value());
        U32 tileWidth = std::stoul(map_node->first_attribute("tilewidth")->value());
        U32 tileHeight = std::stoul(map_node->first_attribute("tileheight")->value());
        F32 halfMapWidthInPixels = static_cast<F32>(mapWidth * tileWidth)  / 2.0f;
        F32 halfMapHeightInPixels = static_cast<F32>(mapHeight * tileHeight) / 2.0f;

        string tileSetFilePath = tileset_node->first_attribute("source")->value();

        typedef std::vector<U32> U32Array;
        std::vector<U32Array> data_array;

        for(xmlNode l=map_node->first_node("layer"); l; l=l->next_sibling("layer"))
        {
            data_array.push_back(_SplitU32(l->first_node("data")->value(), ','));
        }

        if(tileSetFilePath.find(".tsx") != std::string::npos)
        {
            string tile_buffer = _OpenFile(tileSetFilePath);

            xmlDoc tile_doc;
            tile_doc.parse<0>(const_cast<char*>(tile_buffer.c_str()));

            // t == tile node
            for(xmlNode t=tile_doc.first_node("tileset")->first_node("tile"); t; t=t->next_sibling("tile"))
            {
                TileData data;
                data.id = std::stoul(t->first_attribute("id")->value());
                //// add 1, for 0 indexing
                data.id += 1;

                // child nodes of the tile
                xmlNode child = t->first_node("properties");
                if(child)
                {
                    for(child=child->first_node("property"); child; child=child->next_sibling("property"))
                    {
                        string name = child->first_attribute("name")->value();
                        if(name == "type")
                        {
                            data.type = child->first_attribute("value")->value();
                        }
                    }
                }

                child = t->first_node("image");
                data.imageWidth = std::stoul(child->first_attribute("width")->value());
                data.imageHeight = std::stoul(child->first_attribute("height")->value());
                data.imageFilePath = child->first_attribute("source")->value();

                tiles.insert({data.id, data});
            }
        }
        else
        {
            ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMapData no valid tileset found in tmx file");
        }
        
        // This counts down. The layers in tiled are in reverse order for rendering
        for(U32 j = data_array.size(); j-- != 0;)
        {
            for(U32 i = 0; i < data_array[j].size(); ++i)
            {
                if(data_array[j][i] > 0)
                {
                    Level::GridPos pos = _ConvertIndexToTileData(i, mapWidth, mapHeight);
                    TM::Point2 cartPos{ };
                    cartPos.SetX((pos.x * static_cast<F32>(tileWidth)) - halfMapWidthInPixels);
                    cartPos.SetY((pos.y * static_cast<F32>(tileHeight)) - halfMapHeightInPixels);

                    TileData object = tiles[data_array[j][i]];
                    object.pos = cartPos;
                    object.type = tiles[data_array[j][i]].type;

                    objects.push_back(object);
                }
            }
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "Level::ImportTMXMaqData: Invalid file type!");
    }

    return objects;
}

std::vector<U32> Level::_SplitU32(string text, char delim) const
{
    std::vector<U32> data;
    std::stringstream stream(text);
    string item;

    while(std::getline(stream, item, delim))
    {
        data.push_back(std::stoul(item.c_str()));
    }

    return data;
}

S32 Level::GetWidth(void) const 
{ 
    return _width; 
}

S32 Level::GetHeight(void) const 
{ 
    return _height; 
}

void Level::SetWidth(S32 w)  
{ 
    _width = w;
    _rightBorder = w / 2;
    _leftBorder = -w / 2;
}

void Level::SetHeight(S32 h) 
{ 
    _height = h;
    _topBorder = h / 2; 
    _bottomBorder = -h / 2;
}

void Level::SetDimensions(S32 w, S32 h) 
{ 
    SetWidth(w);
    SetHeight(h);
}

S32 Level::GetTopBorder(void) const 
{ 
    return _topBorder; 
}

S32 Level::GetBottomBorder(void) const 
{ 
    return _bottomBorder; 
}

S32 Level::GetLeftBorder(void) const 
{ 
    return _leftBorder; 
}

S32 Level::GetRightBorder(void) const 
{
    return _rightBorder; 
}

void Level::SetDepth(S32 d)
{
    _depth = d;
}

S32 Level::GetDepth(void)
{
    return _depth;
}

void Level::SetNearBorder(S32 n)
{
    _nearBorder = n;
}

void Level::SetFarBorder(S32 f)
{
    _farBorder = f;
}

S32 Level::GetNearBorder(void)
{
    return _nearBorder;
}
S32 Level::GetFarBorder(void)
{
    return _farBorder;
}

void Level::SetID(U32 id) 
{ 
    _ID = id; 
}

U32 Level::GetID(void) const
{
    return _ID;
}

void Level::SetFactory(p_Factory factory)
{
    _factory = factory;
}

// TODO: XML doc creates an error about being out of memory.
void Level::_LoadLevel(string filepath)
{
    if(_factory == nullptr)
    {
        ErrorManager::Instance()->SetError(ENGINE, "Level::_LoadLevel Level::_factory has not been set yet. Set it first, then call v_Init");
        return;
    }
    
    string content = _OpenFile(filepath);
    
    xmlDoc doc;
    doc.parse<0>(const_cast<char*>(content.c_str()));

    xmlNode level = doc.first_node("level");

    SetWidth(std::stoi(level->first_attribute("width")->value()));
    SetHeight(std::stoi(level->first_attribute("height")->value()));

    F32 red = std::stof(level->first_attribute("red")->value());
    F32 green = std::stof(level->first_attribute("green")->value());
    F32 blue = std::stof(level->first_attribute("blue")->value());
    
    SetBackgroundColor(Color(red, green, blue));

    F32 pixelSize = std::stof(level->first_attribute("pixelsize")->value());
    
    xmlNode objects = doc.first_node("level")->first_node("objects")->first_node("dynamic");

    for(xmlNode i = objects->first_node("obj"); i; i = i->next_sibling("obj"))
    {
        string type = i->first_attribute("type")->value();

        string name = i->first_attribute("name")->value();
        
        TM::Point2 pos{std::stof(i->first_attribute("xpos")->value()),
                        std::stof(i->first_attribute("ypos")->value())};

        F32 scale = std::stof(i->first_attribute("scale")->value());
        
        U32 textureID = std::stoi(i->first_attribute("textureID")->value());
        
        p_GameObject2D obj = _factory->v_Create2D(type, pos, scale, pixelSize, textureID);
        obj->SetName(name);
        obj->SetLevel(this);
        ErrorManager::Instance()->DisplayErrors();
        GameObjectManager::Instance()->AddDynamicObject2D(obj);
    }

    objects = doc.first_node("level")->first_node("objects")->first_node("static");

     for(xmlNode i = objects->first_node("obj"); i; i = i->next_sibling("obj"))
    {
        string name = i->first_attribute("name")->value();
        
        TM::Point2 pos{std::stof(i->first_attribute("xpos")->value()),
                        std::stof(i->first_attribute("ypos")->value())};

        F32 scale = std::stof(i->first_attribute("scale")->value());
        
        U32 textureID = std::stoi(i->first_attribute("textureID")->value());
        
        p_StaticGameObject2D obj = _factory->CreateStaticObject2D(pos, scale, pixelSize, textureID);
        obj->SetName(name);
        obj->SetLevel(this);
        ErrorManager::Instance()->DisplayErrors();
        GameObjectManager::Instance()->AddStaticObject2D(obj);
    }

    doc.clear();
}

string Level::_OpenFile(string filepath)
{
    std::ifstream file(filepath);

    if(!file)
    {
        ErrorManager::Instance()->SetError(ENGINE, "Level::_CreateXMLDoc Unable to open file at " + filepath);
        return "";
    }

    string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    //xml file must be 0 terminating
    content.push_back('\0');

    file.close();

    return content;
}