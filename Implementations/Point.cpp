#include <Engine/Point.h>

using namespace KillerMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point::Point(void)
:
_2D(false),
_data{0.0f, 0.0f, 0.0f, 0.0f}
{  }

Point::Point(F32 val)
:
_2D(false),
_data{val, val, val, 0.0f}
{  }

Point::Point(F32 x, F32 y)
:
_2D(true),
_data{x, y, 0.0, 0.0f}
{  }

Point::Point(F32 x, F32 y, F32 z)
:
_2D(false),
_data{x, y, z, 0.0f}
{  }

Point::Point(const Point& v)
:
_2D(v.Is2D()),
_data{v[x], v[y], v[z], v[w]}
{  }

Point::~Point(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
//===== Point Special functions =====
F32 Point::Dot(const Point& point) const
{
	return _data[x] * point[x] +
		   _data[y] * point[y] +
		   _data[z] * point[z];
}

Point Point::CrossProduct(const Point& point) const
{
	if(_2D)
	{
		KE::ErrorManager::Instance()->SetError(KE::ErrorCode::MATH, "Attempted to perform CrossProduct on 2D Point. Point.cpp ln 60");
		return Point(0.0f);
	}

	return Point( _data[y] * point[z] - _data[z] * point[y],
				  _data[z] * point[x] - _data[x] * point[z],
				  _data[x] * point[y] - _data[y] * point[x] );
}

F32 Point::Magnitude(void)
{
	return sqrt(_data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z]);
}

F32 Point::SqrMagnitude(void)
{
	return _data[x] * _data[x] + _data[y] * _data[y] + _data[z] * _data[z];
}

void Point::Normalize(void)
{
	F32 mag = Magnitude();

	if(mag > 0 && mag != 1.0f)
	{
		(*this) *= 1 / mag;
	}
}

void Point::Reset(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	_data[z] = val;
	_data[w] = 0.0f;
}

//===== Math Helper Functions =====
void Point::AddScaledPoint(const Point& point, F32 scale)
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
Point& Point::operator=(const Point& point)
{
	_data[x] = point[x];
	_data[y] = point[y];
	_data[z] = point[z];
	_data[w] = point[w];

	return *this;
}

Point& Point::operator=(F32 val)
{
	_data[x] = val;
	_data[y] = val;
	
	if(!_2D) 
	{
		_data[z] = val;
	}

	return *this;
}

//===== Add by Point =====
Point Point::operator+(const Point& point) const
{
	if(_2D)
	{
		return Point( _data[x] + point[x],
				   	  _data[y] + point[y] );
	}

	return Point( _data[x] + point[x],
				  _data[y] + point[y],
				  _data[z] + point[z] );
}

Point& Point::operator+=(const Point& point)
{
	_data[x] += point[x];
	_data[y] += point[y];
	
	if(!_2D) 
	{
		_data[z] += point[z];
	}

	return *this;
}

Point Point::operator+(shared_ptr<Point> point) const
{
	const F32* vals = point->GetElems();

	if(_2D)
	{
		return Point( _data[x] + vals[x],
					  _data[y] + vals[y] );
	}

	return Point( _data[x] + vals[x],
				  _data[y] + vals[y],
				  _data[z] + vals[z] );
}

//===== Add by scalar =====
Point Point::operator+(F32 val) const
{
	if(_2D)
	{
		return Point( _data[x] + val,
				   	  _data[y] + val );
	}

	return Point( _data[x] + val,
				  _data[y] + val,
				  _data[z] + val );
}

Point& Point::operator+=(F32 val)
{
	_data[x] += val;
	_data[y] += val;
	
	if(!_2D) 
	{
		_data[z] += val;
	}

	return *this;
}

//===== Subtract by Point =====
Point Point::operator-(const Point& point) const
{
	if(_2D)
	{
		return Point( _data[x] - point[x],
				   	  _data[y] - point[y] );
	}

	return Point( _data[x] - point[x],
				  _data[y] - point[y],
				  _data[z] - point[z] );
}

Point& Point::operator-=(const Point& point)
{
	_data[x] -= point[x];
	_data[y] -= point[y];
	
	if(!_2D) 
	{
		_data[z] -= point[z];
	}

	return *this;
}

//===== Subtract by scalar =====
Point Point::operator-(F32 val) const
{
	if(_2D)
	{
		return Point( _data[x] - val,
				   	  _data[y] - val );
	}

	return Point( _data[x] - val,
				  _data[y] - val,
				  _data[z] - val );
}

Point& Point::operator-=(F32 val)
{
	_data[x] -= val;
	_data[y] -= val;
	
	if(!_2D) 
	{
		_data[z] -= val;
	}

	return *this;
}

//===== Component-wise multiply by Point =====
Point Point::operator*(const Point point) const
{
	if(_2D)
	{
		return Point( _data[x] * point[x],
				   	  _data[y] * point[y] );
	}

	return Point( _data[x] * point[x],
				  _data[y] * point[y],
				  _data[z] * point[z] );
}

Point& Point::operator*=(const Point point)
{
	_data[x] *= point[x];
	_data[y] *= point[y];
	
	if(!_2D) 
	{
		_data[z] *= point[z];
	}

	return *this;
}

//===== Mutliply by Scalar =====
Point Point::operator*(F32 val) const
{
	if(_2D)
	{
		return Point( _data[x] * val,
				   	  _data[y] * val );
	}

	return Point( _data[x] * val,
				  _data[y] * val,
				  _data[z] * val );
}

Point& Point::operator*=(F32 val)
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
Point Point::operator/(F32 val) const
{
	assert(val != 0.0f);

	if(_2D)
	{
		return Point( _data[x] / val,
					  _data[y] / val );
	}

	return Point( _data[x] / val,
				  _data[y] / val,
				  _data[z] / val );
}

Point& Point::operator/=(F32 val)
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
bool Point::operator>(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] > point[x] && 
		   		 _data[y] > point[y] && 
		    	 _data[w] >= point[w];
	
	if(!_2D)
	{
		state = state && _data[z] > point[z];
	}

	return state;
}

bool Point::operator<(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] < point[x] && 
		   		 _data[y] < point[y] && 
		    	 _data[w] <= point[w];
	
	if(!_2D)
	{
		state = state && _data[z] < point[z];
	}

	return state;
}

bool Point::operator>=(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] >= point[x] && 
		   		 _data[y] >= point[y] && 
		    	 _data[w] >= point[w];
	
	if(!_2D)
	{
		state = state && _data[z] >= point[z];
	}

	return state;
}

bool Point::operator<=(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] <= point[x] && 
		   		 _data[y] <= point[y] && 
		    	 _data[w] <= point[w];
	
	if(!_2D)
	{
		state = state && _data[z] <= point[z];
	}

	return state;
}

bool Point::operator==(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] == point[x] && 
		   		 _data[y] == point[y] && 
		    	 _data[w] == point[w];
	
	if(!_2D)
	{
		state = state && _data[z] == point[z];
	}

	return state;
}

bool Point::operator!=(const Point& point) const
{
	if(_2D != point.Is2D())
	{
		return false;
	}

	bool state = _data[x] != point[x] && 
		   		 _data[y] != point[y] && 
		    	 _data[w] != point[w];
	
	if(!_2D)
	{
		state = state && _data[z] != point[z];
	}

	return state;
}