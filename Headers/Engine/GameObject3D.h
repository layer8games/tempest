/*========================================================================


This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Vector3.h>
#include <Engine/Model.h>

namespace KM = KillerMath;

namespace KillerEngine
{
//==========================================================================================================================
//Documentation
//==========================================================================================================================
/*! The Game Object is the abstract class, (PURE VIRTUAL) that all objects that will be placed in the game will inherit from. 
	It will hold and define the cell, and will include all calls for updating and rendering. Therewill be a component map 
	which will hold anything that the object will need in the game. 

	All of the functions in this class are inlined becuase they are all trivial. The virtual functions are there so that the 
	interface can be the same for all derived classes. By doing this, the world manager	will be able to have a map of 
	GameObjects to be rendered in a specific world. 

	The GameObject itself is an interface to generic functions that each object that will be rendered will need to be drawn 
	to the screen. The GameObject holds a private Sprite member that will contain all the logic for which rendering algorithm 
	is used. 

	Accessors are created for the derived classes to access the cell, but the cell is to be accessed directly only by the 
	GameObject itself.

	GameObject3D will specficially apply to 3D game objects.  */	
	class GameObject3D
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
/*! Default constructor. Set's all members to 0, and _active to true. SetID() is called as part of the body. */
		GameObject3D(void);

/*! Copy constructor. Calls GetID(), GetActive(), GetModel(), GetPosition(), GetWidth(), GetHeight(), and GetModelView() */
		GameObject3D(const GameObject3D& obj);

		 virtual ~GameObject3D(void);

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
/*! Pure Virtual fucntion. Will be called during Level::UpdateObjects on each object, which will define what needs to happen 
	in the update section of the loop. */	
		virtual void v_Update(void)=0;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		
//==========================================================================================================================
//ID
//==========================================================================================================================
/*! Returns the id of this instance. */
		inline const U32 GetID(void) const
		{
			return _ID; 
		}

/*! Sets the id of this instance. The id is determind by _nextID. This insures that each GameObject3D will have a unique id
	although there could be a collission with GameObject2D::_ID.  */		
		inline void SetID(void)
		{
			_ID = _nextID;
			++_nextID;
		}

//==========================================================================================================================
//Active
//==========================================================================================================================
/*! Returns active state of object. */		
		bool GetActive(void) const;

/*! Sets the active state of object to true. */		
		void SetActive(void);

/*! Sets the active state of object to false. */
		void SetInactive(void);

//==========================================================================================================================
//Position
//==========================================================================================================================		
/*! Returns object Position in World Space. */		
		const KM::Vector3& GetPosition(void) const;

/*! Sets object Position in World Space.
	\param pos Vector3&. New position in world space. */
		void SetPosition(const KM::Vector3& pos);

/*! Sets the position of the object in World Space. Calls Vector3::SetX, Vector3::SetY, Vector3::SetZ and Matrix::Translate.
	This last is done to update the _modelView member. 
	\bug This is data duplication which I have not worked out a better way to handle yet.
	\param x F32. X value of new position.
	\param y F32. Y value of new position.
	\param z F32. Z value of new position. */	
		void SetPosition(F32 x, F32 y, F32 z);

/*! Scales the position of the object in World Space. Wrapper for Vector3::AddScaledVector.
	\param v Vector3&. Vector to add to position.
	\param scale F32. Scale to use when adding vector to position. */
		void AddScaledPosition(const KM::Vector3& v, F32 scale);

//==========================================================================================================================
//Dimensions
//==========================================================================================================================
/*! Returns width of the object. */
		F32 GetWidth(void) const;

/*! Sets the width of the object.
	\param w F32. New width. */
		void SetWidth(F32 w);

/*! Returns the height of the object. */		
		F32 GetHeight(void) const;

/*! Sets the hieght of the object.
	\param h F32. New height. */		
		void SetHeight(F32 h);

/*! Returns the depth of the object. */		
		F32 GetDepth(void) const;

/*! Sets depth of the object.
	\param d F32. New depth */		
		void SetDepth(F32 d);

/*! Sets width, height and depth of the object
	\bug None of these dimensions are used in anyway. Scale should be added later in some way.
	\param w F32. New width.
	\param h F32. New height.
	\param d F32. New depth. */
		void SetDimensions(F32 w, F32 h, F32 d);

//==========================================================================================================================
//Model
//==========================================================================================================================
/*! Returns object Model. */
		inline const Model& GetModel(void) const
		{
			return _model;
		}

/*! Sets object Model.  Calls Model::operator=
	\param model Model&. New Object Object. */		
		inline void SetModel(Model& model)
		{
			_model = model;
		}

/*! Wrapper. Adds new Vertex3D to object Model. Calls Model::AddVertex. */
		inline void AddVertex(Vertex3D vert)
		{
			_model.AddVertex(vert);
		}

/*! Wrapper. Adds new index to object Model. Calls Model::AddIndex */		
		inline void AddIndex(U16 index)
		{
			_model.AddIndex(index);
		}

/*! Wrapper. Adds collection of indices to object Model. Calls Model::AddIndex */		
		inline void AddIndex(std::vector<U16> indices)
		{
			_model.AddIndex(indices);
		}

/*! Wrapper. Loads object Model from file system. Calls Model::LoadModel */		
		inline void LoadModel(string filepath)
		{
			_model.LoadModel(filepath);
		}

//==========================================================================================================================
//Model View Matrix
//==========================================================================================================================
/*! Returns object Model. */
		inline const KM::Matrix& GetModelView(void) const
		{
			return _modelView;
		}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	private:
		static U32 		_nextID;		///< Global member used to track the next unique ID for GambeObject3D
		U32		   		_ID;			///< ID for this instance of GameObject3D
		bool	   		_active;		///< Tracks if the object should be updated and rendered
		Model			_model;			///< Rendering data for object. 
		KM::Vector3	   	_position;		///< Position in World Space
		F32 			_width;			///< Length of X axis in model space.
		F32 			_height;		///< Length of Y axis in model space.
		F32				_depth;			///< Lenth of Z axis in model space.
		KM::Matrix		_modelView;		///< Sent to Shader as uniform. Used to translate vertices of model from model to world space.
		KM::Matrix		_rotationX;		///< Experimental member. Trying to get rotations to work

	};//end Class
}//end Namespace