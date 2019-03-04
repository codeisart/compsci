#include <math.h>
#include <iostream>

template<int N>
struct Vec
{
	enum { Size=N };
	float vals[Size];

	Vec()
	{
		for(int i = 0; i < Size; ++i)
			vals[i] = 0.f;
	}	

	Vec(const float v[Size])
	{
		for(int i = 0; i < Size; ++i)
			vals[i] = v[i];
	}

	float dot(const Vec& v) const
	{
		float r = 0.0f;
		for(int i = 0; i < Size; ++i)
			r += vals[i]*v.vals[i];
		return r;
	}

	float lengthSqr() const
	{
		return dot(*this);
	}

	float length() const
	{
		return sqrt(lengthSqr());
	}

	Vec& scale(float scalar)
	{
		for(int i = 0; i < Size; ++i)
			vals[i]*= scalar;	
		return *this;
	}

	Vec scale(float scalar) const
	{
		Vec v(*this);
		v.scale(scalar);
		return v;
	}

	Vec& normalize()
	{
		scale(length());	
		return *this;
	}

	Vec normalize() const
	{
		Vec v(*this);
		v.normalize();
		return v;
	}
};

template<int N>
std::ostream&
operator<<(const Vec<N>& v, std::ostream& o)
{
	o << '[';
	for(int i = 0; i < N; ++i)
	{
		o << v.vals[i];
		if(i!=N-1)
			o << ',';
	}
	o << ']';
}

typedef Vec<2> Vec2;
typedef Vec<3> Vec3;

int main()
{
	Vec3 v3;
	Vec2 v2;
	
	std::cout << v3 << std::endl; 	

	//std::cout << "[" << v3.vals[0] << ',' << v3.vals[1] << ',' << v3.vals[2] << ']' << std::endl;


	return 0;
}
