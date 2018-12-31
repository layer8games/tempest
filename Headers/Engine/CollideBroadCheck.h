#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/RigidBody.h>

namespace KillerPhysics
{
	struct PotentialContact
	{
		RigidBody* body[2];
	};

	template<class BoundingVolumeClass>
	class BVHNode
	{
	public:
//==========================================================================================================================
//
//Data
//TODO:: Move to private later
//==========================================================================================================================
		BVHNode* 			  children[2];
		shared_ptr<BVHNode>   parent;
		BoundingVolumeClass   volume;
		shared_ptr<RigidBody> body;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		BVHNode(void)
		:
		children{nullptr},
		parent(nullptr),
		volume(),
		body(nullptr)
		{  }
		
		BVHNode(shared_ptr<BVHNode> parent, const BoundingVolumeClass& volume, shared_ptr<RigidBody> body=nullptr)
		:
		children{nullptr},
		parent(parent),
		volume(volume),
		body(body)
		{  }

		~BVHNode(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline bool IsLeaf(void) const
		{
			return (body != nullptr);
		}

		//Checks for Potential Contacts with this down downward. Returns number found. 
		U32 GetPotentialContacts(PotentialContact* contacts, U32 limit) const;

		void Insert(shared_ptr<RigidBody> newBody, const BoundingVolumeClass& newVolume);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================		


	protected:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
		bool _Overlaps(const BVHNode<BoundingVolumeClass>* other) const;

		U32 _GetPotentialChildContacts(const BVHNode<BoundingVolumeClass>* other, PotentialContact* contacts, U32 limit) const;

		void _RecalculateBoundingVolume(bool recursive=true);


	};//end Class

//==========================================================================================================================
//
//Template Implementations
//
//==========================================================================================================================	
	template<class BoundingVolumeClass>
	BVHNode<BoundingVolumeClass>::~BVHNode(void)
	{
		if(parent)
		{
			BVHNode<BoundingVolumeClass>* sibling;
			if(parent->children[0] == this)
			{
				sibling = parent->children[1];
			}
			else
			{
				sibling = parent->children[0];
			}

			parent->volume = sibling->volume;
			parent->body = sibling->volume;
			parent->children[0] = sibling->children[0];
			parent->children[1] = sibling->children[1];

			sibling->parent = nullptr;
			sibling->body = nullptr;
			sibling->children[0] = nullptr;
			sibling->children[1] = nullptr;
			delete sibling;

			parent->_RecalculateBoundingVolume();
		}
		
		if(children[0])
		{
			children[0]->parent = nullptr;
			delete children[0];
		}

		if(children[1])
		{
			children[1]->parent = nullptr;
			delete children[1];
		}
	}

	template<class BoundingVolumeClass>
	U32 BVHNode<BoundingVolumeClass>::GetPotentialContacts(PotentialContact* contacts, U32 limit) const
	{
		if(IsLeaf() || limit == 0)
		{
			return 0;
		}

		return children[0]->_GetPotentialChildContacts(children[1], contacts, limit);
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::Insert(shared_ptr<RigidBody> newBody, const BoundingVolumeClass& newVolume)
	{
		//If we are a leafe, spawn a two new children an dplace the new body in one.
		if(IsLeaf())
		{
			//copy of us
			children[0] = new BVHNode<BoundingVolumeClass>(this, volume, body);
			//new body
			children[1] = new BVHNode<BoundingVolumeClass>(this, newVolume, newBody);

			body = nullptr;

			_RecalculateBoundingVolume();
		}
		//Otherwise, need to work out which child keeps the inserted body. 
		//The one that would grow the least will incorporate it
		else
		{
			if(children[0]->volume.GetGrowth(newVolume) < children[1]->volume.GetGrowth(newVolume))
			{
				children[0]->Insert(newBody, newVolume);
			}
			else
			{
				children[1]->Insert(newBody, newVolume);
			}
		}
	}

	template<class BoundingVolumeClass>
	bool BVHNode<BoundingVolumeClass>::_Overlaps(const BVHNode<BoundingVolumeClass>* other) const
	{
		return volume->Overlaps(other->volume);
	}

	template<class BoundingVolumeClass>
	U32 BVHNode<BoundingVolumeClass>::_GetPotentialChildContacts(const BVHNode<BoundingVolumeClass>* other, PotentialContact* contacts, U32 limit) const
	{
		if(!_Overlaps(other) || limit == 0)
		{
			return 0;
		}

		//If both are leaf nodes, then there is a Potential Contact
		if(IsLeaf() && other->IsLeaf())
		{
			contacts->body[0] = body;
			contacts->body[1] = other->body;
			return 1;
		}

		//Determine which node to descent into.
		//If one is a Leaf, go into other.
		if(other->IsLeaf() || (!IsLeaf() && volume->GetSize() >= other->volume->GetSize()))
		{
			//Recurse into self
			U32 count = children[0]->_GetPotentialChildContacts(other, contacts, limit);

			//Make sure we still have room for other side
			if(limit > count)
			{
				//Recurse into self
				return count + children[1]->_GetPotentialChildContacts(other, contacts+count, limit-count);
			}
			else
			{
				return count;
			}
		}
		//If both are branches, use the largest
		else
		{
			//Recurse into other 
			U32 count = _GetPotentialChildContacts(other->children[0], contacts, limit);

			//Make sure we have room for the other side
			if(limit > count)
			{
				//Recurse into other
				return count + _GetPotentialChildContacts(other->children[1], contacts+count, limit-count);
			}
			else
			{
				return count;
			}
		}
	}

	template<class BoundingVolumeClass>
	void BVHNode<BoundingVolumeClass>::_RecalculateBoundingVolume(bool recursive)
	{
		if(IsLeaf())
		{
			return;
		}

		volume = BoundingVolumeClass(children[0]->volume, children[1]->volume);

		if(parent)
		{
			parent->_RecalculateBoundingVolume(true);
		}
	}
}//end Namespace
