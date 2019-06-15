#include <Engine/Vector3.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Vector3::Vector3(void)
:
_2D(false),
_data{0.0f, 0.0f, 0.0f}
{  }

Vector3::Vector3(F32 val)
:
_2D(false),
_data{val, val, val}
{  }

Vector3::Vector3(F32 x, F32 y)
:
_2D(true),
_data{x, y, 0.0}
{  }

Vector3::Vector3(F32 x, F32 y, F32 z)
:
_2D(false),
_data{x, y, z}
{  }

Vector3::Vector3(const Vector3& v)
:
_2D(v.Is2D()),
_data{v[x], v[y], v[z]}
{  }

Vector3::Vector3(const Vector4& v)
:
_data{v[x], v[y], v[z]}
{  }

Vector3::~Vector3(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Vector3 Special functions =====
F32 Vector3::Dot(const Vector3& vec) const
{
	return _data[x] * vec[x] +
		   _data[y] * vec[y] +
		   _data[z] * vec[z];
}

Vector3 Vector3::CrossProduct(const Vector3& vec) const
{
	return Vector3( _data[y] * vec[z] - _data[z] * vec[y],
				    _data[z] * vec[x] - _data[x] * vec[z],
				    _data[x] * vec[y] - _data[y] * vec[x] );
}

F32 Vector3::Magnitude(void)
{
	return sqrt(_data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

F32 Vector3::SqrMagnitude(void)
{
	return _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z];
}

void Vector3::Normalize(void)
{
	F32 mag = Magnitude();

	if(mag > 0 && mag != 1.0f)
	{
		(*this) *= 1 / mag;
	}
}

void Vector3::Reset(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	_data[z] = val;
}

//===== Math Helper Functions =====
void Vector3::AddScaledVector(const Vector3& vec, F32 scale)
{
	_data[x] += vec[x] * scale;
	_data[y] += vec[y] * scale;

	if(!_2D)
	{
		_data[z] += vec[z] * scale;
	}
}

void Vector3::AddScaledVector(const Vector4& vec, F32 scale)
{
	_data[x] += vec[x] * scale;
	_data[y] += vec[y] * scale;

	if(!_2D)
	{
		_data[z] += vec[z] * scale;
	}
}

void Vector3::AddScaledVector(const Point& point, F32 scale)
{
	_data[x] += point[x] * scale;
	_data[y] += point[y] * scale;

	if(!_2D)
	{
		_data[z] += point[z] * scale;
	}
}
//==========================================================================================================================
//
//Operator overloads
//
//==========================================================================================================================
//===== Copy Assignment =====		
Vector3& Vector3::operator=(const Vector3& vec)
{
	_data[x] = vec[x];
	_data[y] = vec[y];
	_data[z] = vec[z];

	return *this;
}

Vector3& Vector3::operator=(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	
	if(!_2D) 
	{
		_data[z] = val;
	}

	return *this;
}

//===== Add by Vector3 =====
Vector3 Vector3::operator+(const Vector3& vec) const
{
	if(_2D)
	{
		return Vector3( _data[x] + vec[x],
				   	    _data[y] + vec[y] );
	}

	return Vector3( _data[x] + vec[x],
				    _data[y] + vec[y],
				    _data[z] + vec[z] );
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
	_data[x] += vec[x];
	_data[y] += vec[y];
	
	if(!_2D) 
	{
		_data[z] += vec[z];
	}

	return *this;
}

Vector3 Vector3::operator+(shared_ptr<Vector3> vec) const
{
	const F32* vals = vec->GetElems();

	if(_2D)
	{
		return Vector3( _data[x] + vals[x],
					    _data[y] + vals[y] );
	}

	return Vector3( _data[x] + vals[x],
				    _data[y] + vals[y],
				    _data[z] + vals[z] );
}

//===== Add by scalar =====
Vector3 Vector3::operator+(F32 val) const
{
	if(_2D)
	{
		return Vector3( _data[x] + val,
				   	    _data[y] + val );
	}

	return Vector3( _data[x] + val,
				    _data[y] + val,
				    _data[z] + val );
}

Vector3& Vector3::operator+=(F32 val)
{
	_data[x] += val;
	_data[y] += val;
	
	if(!_2D) 
	{
		_data[z] += val;
	}

	return *this;
}

//===== Subtract by Vector3 =====
Vector3 Vector3::operator-(const Vector3& vec) const
{
	if(_2D)
	{
		return Vector3( _data[x] - vec[x],
				   	    _data[y] - vec[y] );
	}

	return Vector3( _data[x] - vec[x],
				    _data[y] - vec[y],
				    _data[z] - vec[z] );
}

Vector3& Vector3::operator-=(const Vector3& vec)
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
Vector3 Vector3::operator-(F32 val) const
{
	if(_2D)
	{
		return Vector3( _data[x] - val,
				   	    _data[y] - val );
	}

	return Vector3( _data[x] - val,
				    _data[y] - val,
				    _data[z] - val );
}

Vector3& Vector3::operator-=(F32 val)
{
	_data[x] -= val;
	_data[y] -= val;
	
	if(!_2D) 
	{
		_data[z] -= val;
	}

	return *this;
}

//===== Component-wise multiply by Vector3 =====
Vector3 Vector3::operator*(const Vector3 vec) const
{
	if(_2D)
	{
		return Vector3( _data[x] * vec[x],
				   	    _data[y] * vec[y] );
	}

	return Vector3( _data[x] * vec[x],
				    _data[y] * vec[y],
				    _data[z] * vec[z] );
}

Vector3& Vector3::operator*=(const Vector3 vec)
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
Vector3 Vector3::operator*(F32 val) const
{
	if(_2D)
	{
		return Vector3( _data[x] * val,
				   	    _data[y] * val );
	}

	return Vector3( _data[x] * val,
				    _data[y] * val,
				    _data[z] * val );
}

Vector3& Vector3::operator*=(F32 val)
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
Vector3 Vector3::operator/(F32 val) const
{
	assert(val != 0.0f);

	if(_2D)
	{
		return Vector3( _data[x] / val,
					    _data[y] / val );
	}

	return Vector3( _data[x] / val,
				    _data[y] / val,
				    _data[z] / val );
}

Vector3& Vector3::operator/=(F32 val)
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
bool Vector3::operator>(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] > vec[x] && 
		   		 _data[y] > vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] > vec[z];
	}

	return state;
}

bool Vector3::operator<(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] < vec[x] && 
		   		 _data[y] < vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] < vec[z];
	}

	return state;
}

bool Vector3::operator>=(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] >= vec[x] && 
		   		 _data[y] >= vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] >= vec[z];
	}

	return state;
}

bool Vector3::operator<=(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] <= vec[x] && 
		   		 _data[y] <= vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] <= vec[z];
	}

	return state;
}

bool Vector3::operator==(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] == vec[x] && 
		   		 _data[y] == vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] == vec[z];
	}

	return state;
}

bool Vector3::operator!=(const Vector3& vec) const
{
	if(_2D != vec.Is2D())
	{
		return false;
	}

	bool state = _data[x] != vec[x] && 
		   		 _data[y] != vec[y];
	
	if(!_2D)
	{
		state = state && _data[z] != vec[z];
	}

	return state;
}