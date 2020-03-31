#include <Engine/Point.h>

using namespace TempestMath;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Point::Point(void)
:
_2D(false),
_data{0.0f, 0.0f, 0.0f, 1.0f}
{  }

Point::Point(real val)
:
_2D(false),
_data{val, val, val, 1.0f}
{  }

Point::Point(real x, real y)
:
_2D(true),
_data{x, y, 0.0, 1.0f}
{  }

Point::Point(real x, real y, real z)
:
_2D(false),
_data{x, y, z, 1.0f}
{  }

Point::Point(real x, real y, real z, real w)
:
_2D(false),
_data{x, y, z, w}
{  }

Point::Point(const Point& v)
:
_2D(v.Is2D()),
_data{v[x], v[y], v[z], v[w]}
{  }

Point::Point(const Vector3& v)
	:
	_2D(v.Is2D()),
	_data{v[x], v[y], v[z], v[w]}
{  }

Point::Point(const Vector4& v)
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
real Point::Dot(const Point& point) const
{
	return _data[x] * point[x] +
		   _data[y] * point[y] +
		   _data[z] * point[z];
}

Point Point::CrossProduct(const Point& point) const
{
	if(_2D)
	{
		TE::ErrorManager::Instance()->SetError(TE::ErrorCode::MATH, "Attempted to perform CrossProduct on 2D Point. Point.cpp ln 60");
		return Point(0.0f);
	}

	return Point( _data[y] * point[z] - _data[z] * point[y],
				  _data[z] * point[x] - _data[x] * point[z],
				  _data[x] * point[y] - _data[y] * point[x] );
}

real Point::Magnitude(void)
{
	real totals = (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
	return sqrt(totals);
}

real Point::SqrMagnitude(void)
{
	return (_data[x] * _data[x]) + (_data[y] * _data[y]) + (_data[z] * _data[z]);
}

void Point::Normalize(void)
{
	real mag = Magnitude();

	if(mag > 0 && mag != 1.0f)
	{
		(*this) *= 1 / mag;
	}
}

void Point::Reset(real val)
{
	_data[x] = val;
	_data[y] = val;
	_data[z] = val;
	_data[w] = 1.0f;
}

real Point::Distance(const Point& p) const
{
	Point length = *this - p;
	return length.Magnitude();
}

real Point::DistanceSquared(const Point& p) const
{
	Point length = *this - p;
	return length.SqrMagnitude();
}

real Point::DistanceSquared(const Vector3& v) const
{
	Point length = *this - v;
	return length.SqrMagnitude();
}

real Point::DistanceSquared(const Vector4& v) const
{
	Point length = *this - v;
	return length.SqrMagnitude();
}

//===== Math Helper Functions =====
void Point::AddScaledPoint(const Point& point, real scale)
{
	_data[x] += point[x] * scale;
	_data[y] += point[y] * scale;

	if(!_2D)
	{
		_data[z] += point[z] * scale;
	}
}

void Point::AddScaledVector(const Vector3& vec, real scale)
{
	_data[x] += vec[x] * scale;
	_data[y] += vec[y] * scale;

	if(!_2D)
	{
		_data[z] += vec[z] * scale;
	}	
}

void Point::AddScaledVector(const Vector4& vec, real scale)
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
Point& Point::operator=(const Point& point)
{
	_data[x] = point[x];
	_data[y] = point[y];
	_data[z] = point[z];
	_data[w] = point[w];

	return *this;
}

Point& Point::operator=(real val)
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

Point Point::operator+(const Vector4& vec) const
{
	if(_2D)
	{
		return Point( _data[x] + vec[x],
				   	  _data[y] + vec[y] );
	}

	return Point( _data[x] + vec[x],
				  _data[y] + vec[y],
				  _data[z] + vec[z] );
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

Point& Point::operator+=(const Vector4& vec)
{
	_data[x] += vec[x];
	_data[y] += vec[y];
	
	if(!_2D) 
	{
		_data[z] += vec[z];
	}

	return *this;
}

Point Point::operator+(const Vector3& vec) const
{
	if (_2D)
	{
		return Point(_data[x] + vec[x],
					 _data[y] + vec[y]);
	}

	return Point(_data[x] + vec[x],
				 _data[y] + vec[y],
				 _data[z] + vec[z]);
}

Point& Point::operator+=(const Vector3& vec)
{
	_data[x] += vec[x];
	_data[y] += vec[y];

	if (!_2D)
	{
		_data[z] += vec[z];
	}

	return *this;
}

Point Point::operator+(shared_ptr<Point> point) const
{
	const real* vals = point->GetElems();

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
Point Point::operator+(real val) const
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

Point& Point::operator+=(real val)
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

Point Point::operator-(const Vector3& vec) const
{
	if(_2D)
	{
		return Point(_data[x] - vec[x],
					  _data[y] - vec[y]);
	}

	return Point(_data[x] - vec[x],
				  _data[y] - vec[y],
				  _data[z] - vec[z]);
}

Point Point::operator-(const Vector4& vec) const
{
	if(_2D)
	{
		return Point(_data[x] - vec[x],
					  _data[y] - vec[y]);
	}

	return Point(_data[x] - vec[x],
				  _data[y] - vec[y],
				  _data[z] - vec[z]);
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
Point Point::operator-(real val) const
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

Point& Point::operator-=(real val)
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
Point Point::operator*(real val) const
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

Point& Point::operator*=(real val)
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
Point Point::operator/(real val) const
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

Point& Point::operator/=(real val)
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