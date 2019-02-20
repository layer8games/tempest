#include <Engine/Vector.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector::Vector(void)
:
_2D(false),
_data{0.0f, 0.0f, 0.0f, 0.0f}
{  }

Vector::Vector(F32 val)
:
_2D(false),
_data{val, val, val, 0.0f}
{  }

Vector::Vector(F32 x, F32 y)
:
_2D(true),
_data{x, y, 0.0, 0.0f}
{  }

Vector::Vector(F32 x, F32 y, F32 z)
:
_2D(false),
_data{x, y, z, 0.0f}
{  }

Vector::Vector(F32 x, F32 y, F32 z, F32 w)
:
_2D(false),
_data{x, y, z, w}
{  }

Vector::Vector(const Vector& v)
:
_2D(v.Is2D()),
_data{v[x], v[y], v[z], v[w]}
{  }

Vector::~Vector(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector Special functions =====
F32 Vector::Dot(const Vector& vec) const
{
	return _data[x] * vec[x] +
		   _data[y] * vec[y] +
		   _data[z] * vec[z];
}

Vector Vector::CrossProduct(const Vector& vec) const
{
	return Vector( _data[y] * vec[z] - _data[z] * vec[y],
				   _data[z] * vec[x] - _data[x] * vec[z],
				   _data[x] * vec[y] - _data[y] * vec[x] );
}

F32 Vector::Magnitude(void)
{
	return sqrt(_data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

F32 Vector::SqrMagnitude(void)
{
	return _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z];
}

void Vector::Normalize(void)
{
	F32 mag = Magnitude();

	if(mag > 0 && mag != 1.0f)
	{
		(*this) *= 1 / mag;
	}
}

void Vector::Reset(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	_data[z] = val;
	_data[w] = 0.0f;
}

//===== Math Helper Functions =====
void Vector::AddScaledVector(const Vector& vec, F32 scale)
{
	_data[x] += vec[x] * scale;
	_data[y] += vec[y] * scale;

	if(!_2D)
	{
		_data[z] += vec[z] * scale;
	}
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector& Vector::operator=(const Vector& vec)
{
	_data[x] = vec[x];
	_data[y] = vec[y];
	_data[z] = vec[z];
	_data[w] = vec[w];

	return *this;
}

Vector& Vector::operator=(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	
	if(!_2D) 
	{
		_data[z] = val;
	}

	return *this;
}

//===== Add by Vector =====
Vector Vector::operator+(const Vector& vec) const
{
	if(_2D)
	{
		return Vector( _data[x] + vec[x],
				   	   _data[y] + vec[y] );
	}

	return Vector( _data[x] + vec[x],
				   _data[y] + vec[y],
				   _data[z] + vec[z] );
}

Vector& Vector::operator+=(const Vector& vec)
{
	_data[x] += vec[x];
	_data[y] += vec[y];
	
	if(!_2D) 
	{
		_data[z] += vec[z];
	}

	return *this;
}

Vector Vector::operator+(shared_ptr<Vector> vec) const
{
	const F32* vals = vec->GetElems();

	if(_2D)
	{
		return Vector( _data[x] + vals[x],
					   _data[y] + vals[y] );
	}

	return Vector( _data[x] + vals[x],
				   _data[y] + vals[y],
				   _data[z] + vals[z] );
}

//===== Add by scalar =====
Vector Vector::operator+(F32 val) const
{
	if(_2D)
	{
		return Vector( _data[x] + val,
				   	   _data[y] + val );
	}

	return Vector( _data[x] + val,
				   _data[y] + val,
				   _data[z] + val );
}

Vector& Vector::operator+=(F32 val)
{
	_data[x] += val;
	_data[y] += val;
	
	if(!_2D) 
	{
		_data[z] += val;
	}

	return *this;
}

//===== Subtract by Vector =====
Vector Vector::operator-(const Vector& vec) const
{
	if(_2D)
	{
		return Vector( _data[x] - vec[x],
				   	   _data[y] - vec[y] );
	}

	return Vector( _data[x] - vec[x],
				   _data[y] - vec[y],
				   _data[z] - vec[z] );
}

Vector& Vector::operator-=(const Vector& vec)
{
	_data[x] -= vec[x];
	_data[y] -= vec[y];
	
	if(!_2D) 
	{
		_data[z] -= vec[z];
	}

	return *this;
}

//===== Subtract by scalar =====
Vector Vector::operator-(F32 val) const
{
	if(_2D)
	{
		return Vector( _data[x] - val,
				   	   _data[y] - val );
	}

	return Vector( _data[x] - val,
				   _data[y] - val,
				   _data[z] - val );
}

Vector& Vector::operator-=(F32 val)
{
	_data[x] -= val;
	_data[y] -= val;
	
	if(!_2D) 
	{
		_data[z] -= val;
	}

	return *this;
}

//===== Component-wise multiply by vector =====
Vector Vector::operator*(const Vector vec) const
{
	if(_2D)
	{
		return Vector( _data[x] * vec[x],
				   	   _data[y] * vec[y] );
	}

	return Vector( _data[x] * vec[x],
				   _data[y] * vec[y],
				   _data[z] * vec[z] );
}

Vector& Vector::operator*=(const Vector vec)
{
	_data[x] *= vec[x];
	_data[y] *= vec[y];
	
	if(!_2D) 
	{
		_data[z] *= vec[z];
	}

	return *this;
}

//===== Mutliply by Scalar =====
Vector Vector::operator*(F32 val) const
{
	if(_2D)
	{
		return Vector( _data[x] * val,
				   	   _data[y] * val );
	}

	return Vector( _data[x] * val,
				   _data[y] * val,
				   _data[z] * val );
}

Vector& Vector::operator*=(F32 val)
{
	_data[x] *= val;
	_data[y] *= val;

	if(!_2D)
	{
		_data[z] *= val;
	}

	return *this;
}

//===== Divide by scalar =====
Vector Vector::operator/(F32 val) const
{
	assert(val != 0.0f);

	if(_2D)
	{
		return Vector( _data[x] / val,
					   _data[y] / val );
	}

	return Vector( _data[x] / val,
				   _data[y] / val,
				   _data[z] / val );
}

Vector& Vector::operator/=(F32 val)
{
	assert(val != 0.0f);

	_data[x] /= val;
	_data[y] /= val;

	if(!_2D)
	{
		_data[z] /= val;
	}

	return *this;
}

//===== Comparison =====
bool Vector::operator>(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] > vec[x] && 
		   		 _data[y] > vec[y] && 
		    	 _data[w] >= vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] > vec[z];
	}

	return state;
}

bool Vector::operator<(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] < vec[x] && 
		   		 _data[y] < vec[y] && 
		    	 _data[w] <= vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] < vec[z];
	}

	return state;
}

bool Vector::operator>=(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] >= vec[x] && 
		   		 _data[y] >= vec[y] && 
		    	 _data[w] >= vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] >= vec[z];
	}

	return state;
}

bool Vector::operator<=(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] <= vec[x] && 
		   		 _data[y] <= vec[y] && 
		    	 _data[w] <= vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] <= vec[z];
	}

	return state;
}

bool Vector::operator==(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] == vec[x] && 
		   		 _data[y] == vec[y] && 
		    	 _data[w] == vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] == vec[z];
	}

	return state;
}

bool Vector::operator!=(const Vector& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] != vec[x] && 
		   		 _data[y] != vec[y] && 
		    	 _data[w] != vec[w];
	
	if(!_2D)
	{
		state = state && _data[z] != vec[z];
	}

	return state;
}