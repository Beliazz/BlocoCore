#ifndef Geometry_h__
#define Geometry_h__

#include "BlocoCore.h"

//////////////////////////////////////////////////////////////////////////
// Matrix 4x4
//////////////////////////////////////////////////////////////////////////
class BLOCOCORE_API Mat
{
private:
	XMFLOAT4X4 m_storage;

public:
	Mat()					{XMStoreFloat4x4(&m_storage, XMMatrixIdentity());}
	Mat(CXMMATRIX val)		{XMStoreFloat4x4(&m_storage, val);}
	Mat(float* pArray)		{m_storage = XMFLOAT4X4(pArray);}
	Mat(XMFLOAT4X4& val)	{m_storage = val;}
	Mat(const char* str)	
	{
		stringstream stream(str);
		float m[4][4];

		stream >> m[0][0];
		stream >> m[0][1];
		stream >> m[0][2];
		stream >> m[0][3];

		stream >> m[1][0];
		stream >> m[1][1];
		stream >> m[1][2];
		stream >> m[1][3];

		stream >> m[2][0];
		stream >> m[2][1];
		stream >> m[2][2];
		stream >> m[2][3];

		stream >> m[3][0];
		stream >> m[3][1];
		stream >> m[3][2];
		stream >> m[3][3];

		m_storage = XMFLOAT4X4((float*)m);
	}
	Mat(std::istream & in)	
	{
		float m[16];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				in >> m[4 * j + i];

		m_storage = XMFLOAT4X4(m);
	}

	inline void* operator new(size_t size)
	{
		return malloc(sizeof(Mat));
	}
	inline void operator delete(void* ptr)
	{
		free(ptr);
	}

	inline XMMATRIX Get()				{return XMLoadFloat4x4(&m_storage);}
	inline XMFLOAT4X4 GetStorage()		{return m_storage;}
	inline float*	GetArray()			{return (float*)&m_storage;}
	inline void		GetArray(float* pArray)	
	{
		for (int i=0; i<4; i++)
			for (int j=0; j<4; j++)
				pArray[4*j+i] = m_storage.m[i][j];
	}
	inline operator float*()			{return GetArray();}
	inline void Serialize(std::ostream& stream) const 
	{
		for (int i=0; i<4; ++i)
			for (int j=0; j<4; ++j)
				stream << m_storage.m[i][j] << " ";
	}
	inline string str()
	{
		stringstream stm;

		for (int i=0; i<4; ++i)
			for (int j=0; j<4; ++j)
				stm << m_storage.m[i][j] << " ";

		return stm.str();
	}
	inline void operator *= (Mat& rhs)
	{
		XMMATRIX temp = XMLoadFloat4x4(&m_storage);
		temp = XMMatrixMultiply(temp, rhs.Get());
		XMStoreFloat4x4(&m_storage, temp);
	}
	inline void operator *= (CXMMATRIX rhs)
	{
		XMMATRIX temp = XMLoadFloat4x4(&m_storage);
		temp = XMMatrixMultiply(rhs, temp);
		XMStoreFloat4x4(&m_storage, temp);
	}
	inline void operator *= (XMFLOAT4X4& rhs)
	{
		XMMATRIX temp1 = XMLoadFloat4x4(&m_storage);
		XMMATRIX temp2 = XMLoadFloat4x4(&rhs);
		temp1 = XMMatrixMultiply(temp1, temp2);
		XMStoreFloat4x4(&m_storage, temp1);
	}
};

//////////////////////////////////////////////////////////////////////////
// Vector 4 dimensional
// 
// use overloaded operators only for vectors, not for planes 
// or quaternions. For this classes use the appropriate functions
//
// multiply operators are overloaded for transformations with matrices
// and quaternions
//////////////////////////////////////////////////////////////////////////
class BLOCOCORE_API Vec
{
private:
	XMFLOAT4 m_storage;

public:
	Vec(float x, float y, float z, float w) {m_storage = XMFLOAT4(x, y, z, w);}
	Vec(float x, float y, float z)			{m_storage = XMFLOAT4(x, y, z, 0.0f);}
	Vec(float x, float y)					{m_storage = XMFLOAT4(x, y, 0.0f, 0.0f);}
	Vec(std::istream& stream)				{stream >> m_storage.x >> m_storage.y >> m_storage.z;}

	Vec(double x, double y, double z, double w) {m_storage = XMFLOAT4((float)x, (float)y, (float)z, (float)w);}
	Vec(double x, double y, double z)			{m_storage = XMFLOAT4((float)x, (float)y, (float)z, 0.0f);}
	Vec(double x, double y)						{m_storage = XMFLOAT4((float)x, (float)y, 0.0f, 0.0f);}

	Vec(int x, int y, int z, int w)			{m_storage = XMFLOAT4((float)x, (float)y, (float)z, (float)w);}
	Vec(int x, int y, int z)				{m_storage = XMFLOAT4((float)x, (float)y, (float)z, 0.0f);}
	Vec(int x, int y)						{m_storage = XMFLOAT4((float)x, (float)y, 0.0f, 0.0f);}
	Vec(FXMVECTOR vec)						{XMStoreFloat4(&m_storage, vec);}
	Vec(XMFLOAT4& val)						{m_storage = val;}
	Vec(FLOAT* pArray)						{m_storage = XMFLOAT4(pArray);}
	Vec()									{m_storage = XMFLOAT4();}

	inline FLOAT		GetX()			{return m_storage.x;}
	inline FLOAT		GetY()			{return m_storage.y;}
	inline FLOAT		GetZ()			{return m_storage.z;}
	inline FLOAT		GetW()			{return m_storage.w;}
	inline XMVECTOR		Get()			{return XMLoadFloat4(&m_storage);}
	inline XMFLOAT4&	GetStorage()	{return m_storage;}
 	inline float*		GetArray()
 	{	
 		return (float*)&m_storage;
 	}
	inline void			GetArray(float* pArray)
	{	
		pArray[0] = GetX();
		pArray[1] = GetY();
		pArray[2] = GetZ();
		pArray[3] = GetW();
	}
	inline operator float*()			{return GetArray();}

	inline void Serialize(std::ostream& stream) const {stream << m_storage.x  << " " << m_storage.y << " " << m_storage.z << " ";}
	inline void SetX(FLOAT val)	{m_storage.x = val;}
	inline void SetY(FLOAT val)	{m_storage.y = val;}
	inline void SetZ(FLOAT val)	{m_storage.z = val;}
	inline void SetW(FLOAT val)	{m_storage.w = val;}

	inline operator const XMVECTOR()	{return Get();}
	inline operator XMFLOAT4()			{return m_storage;}
	inline operator XMFLOAT4*()			{return &m_storage;}

	inline BOOL operator ==(Vec& rhs)
	{
		return XMVector4Equal(Get(), rhs.Get());
	}
	inline BOOL operator ==(FXMVECTOR rhs)
	{
		return XMVector4Equal(Get(), rhs);
	}
	inline BOOL operator ==(XMFLOAT4& rhs)
	{
		return XMVector4Equal(Get(), XMLoadFloat4(&rhs));
	}

	inline BOOL operator != (Vec& rhs)
	{
		return !((*this) == rhs);
	}
	inline BOOL operator != (FXMVECTOR rhs)
	{
		return !((*this) == rhs);
	}
	inline BOOL operator != (XMFLOAT4& rhs)
	{
		return !((*this) == rhs);
	}
	
	inline BOOL operator <(Vec& rhs)
	{
		return XMVector4Less(Get(), rhs.Get());
	}
	inline BOOL operator <(FXMVECTOR rhs)
	{
		return XMVector4Less(Get(), rhs);
	}
	inline BOOL operator <(XMFLOAT4& rhs)
	{
		return XMVector4Less(Get(), XMLoadFloat4(&rhs));
	}

	inline BOOL operator >(Vec& rhs)
	{
		return XMVector4Greater(Get(), rhs.Get());
	}
	inline BOOL operator >(FXMVECTOR rhs)
	{
		return XMVector4Greater(Get(), rhs);
	}
	inline BOOL operator >(XMFLOAT4& rhs)
	{
		return XMVector4Greater(Get(), XMLoadFloat4(&rhs));
	}

	inline BOOL operator <=(Vec& rhs)
	{
		return XMVector4LessOrEqual(Get(), rhs.Get());
	}
	inline BOOL operator <=(FXMVECTOR rhs)
	{
		return XMVector4LessOrEqual(Get(), rhs);
	}
	inline BOOL operator <=(XMFLOAT4& rhs)
	{
		return XMVector4LessOrEqual(Get(), XMLoadFloat4(&rhs));
	}

	inline BOOL operator >=(Vec& rhs)
	{
		return XMVector4GreaterOrEqual(Get(), rhs.Get());
	}
	inline BOOL operator >=(FXMVECTOR rhs)
	{
		return XMVector4GreaterOrEqual(Get(), rhs);
	}
	inline BOOL operator >=(XMFLOAT4& rhs)
	{
		return XMVector4GreaterOrEqual(Get(), XMLoadFloat4(&rhs));
	}
	
	inline void operator +=(Vec& rhs)
	{ 
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorAdd(temp, rhs.Get());
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator +=(XMFLOAT4& rhs)	
	{ 
		XMVECTOR temp1 = XMLoadFloat4(&m_storage);
		XMVECTOR temp2 = XMLoadFloat4(&rhs);
		temp1 = XMVectorAdd(temp1, temp2);
		XMStoreFloat4(&m_storage, temp1);
	}
	inline void operator +=(FXMVECTOR rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorAdd(temp, rhs);
		XMStoreFloat4(&m_storage, temp);
	}

	inline void operator -=(Vec& rhs)
	{ 
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorSubtract(temp, rhs.Get());
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator -=(XMFLOAT4& rhs)	
	{ 
		XMVECTOR temp1 = XMLoadFloat4(&m_storage);
		XMVECTOR temp2 = XMLoadFloat4(&rhs);
		temp1 = XMVectorSubtract(temp1, temp2);
		XMStoreFloat4(&m_storage, temp1);
	}
	inline void operator -=(FXMVECTOR rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorSubtract(temp, rhs);
		XMStoreFloat4(&m_storage, temp);
	}

	inline void operator *=(Vec& rhs)
	{ 
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorMultiply(temp, rhs.Get());
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(XMFLOAT4& rhs)	
	{ 
		XMVECTOR temp1 = XMLoadFloat4(&m_storage);
		XMVECTOR temp2 = XMLoadFloat4(&rhs);
		temp1 = XMVectorMultiply(temp1, temp2);
		XMStoreFloat4(&m_storage, temp1);
	}
	inline void operator *=(FXMVECTOR rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorMultiply(temp, rhs);
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(Mat& rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVector4Transform(temp, rhs.Get());
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(CXMMATRIX rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVector4Transform(temp, rhs);
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(XMFLOAT4X4& rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVector4Transform(temp, XMLoadFloat4x4(&rhs));
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(float rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorScale(Get(), rhs);
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator *=(int rhs)
	{
		float rhs_f = (float)rhs;
		(*this) *= rhs_f;
	}
	inline void operator *=(double rhs)
	{
		float rhs_f = (float)rhs;
		(*this) *= rhs_f;
	}
	inline void operator *=(short rhs)
	{
		float rhs_f = (float)rhs;
		(*this) *= rhs_f;
	}
	inline void operator *=(long rhs)
	{
		float rhs_f = (float)rhs;
		(*this) *= rhs_f;
	}

	inline void operator /=(Vec& rhs)
	{ 
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorDivide(temp, rhs.Get());
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator /=(XMFLOAT4& rhs)	
	{ 
		XMVECTOR temp1 = XMLoadFloat4(&m_storage);
		XMVECTOR temp2 = XMLoadFloat4(&rhs);
		temp1 = XMVectorDivide(temp1, temp2);
		XMStoreFloat4(&m_storage, temp1);
	}
	inline void operator /=(FXMVECTOR rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorDivide(temp, rhs);
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator /=(float rhs)
	{
		XMVECTOR temp = XMLoadFloat4(&m_storage);
		temp = XMVectorScale(Get(), 1.0f / rhs);
		XMStoreFloat4(&m_storage, temp);
	}
	inline void operator /=(int rhs)
	{
		float rhs_f = (float)rhs;
		(*this) /= rhs_f;
	}
	inline void operator /=(double rhs)
	{
		float rhs_f = (float)rhs;
		(*this) /= rhs_f;
	}
	inline void operator /=(short rhs)
	{
		float rhs_f = (float)rhs;
		(*this) /= rhs_f;
	}
	inline void operator /=(long rhs)
	{
		float rhs_f = (float)rhs;
		(*this) /= rhs_f;
	}
};

//////////////////////////////////////////////////////////////////////////
// Quaternion
// 
// used to express rotations avoiding "glimbal lock"
//
// a 4D-vector is used to represent quaternions, where the X, Y, and Z components
// are the vector part and the W component is the scalar part.
//
// use overloaded operators only for vectors, not for planes, 
// quaternions or colors. For this classes use the appropriate functions
///////////////////////////////////////////////////////////////////////
typedef Vec BLOCOCORE_API Quat;

//////////////////////////////////////////////////////////////////////////
// Plane
// 
// a 4D-vector is used to represent the coefficients of the plane equation, 
// Ax+By+Cz+D = 0, where the X-component is A, the Y-component is B, 
// the Z-component is C, and the W-component is D.
//
// use overloaded operators only for vectors, not for planes, 
// quaternions or colors. For this classes use the appropriate functions
//////////////////////////////////////////////////////////////////////////
typedef Vec BLOCOCORE_API Plane;

//////////////////////////////////////////////////////////////////////////
// Color
// 
// a 4D-vector is used to represent the color, where the
// W-component is always Alpha (Translucency T).
//
// if not specified the values are between 0.0f and 1.0f
//
// RGB:
// the X-component is Red (R), the Y-component is Green (G), 
// the Z-component is Blue (B).
//
// Other types that will be implemented in future releases:
//
// HSV
// the X-component is Hue (H), the Y-component is Saturation (S), 
// the Z-component is Value (V).
//
// HSL
// the X-component is Hue (H), the Y-component is Saturation (S), 
// the Z-component is Luminance (L).
//
// XYZ
// the trisimulus values, X-component is Red (Y), the Y-component is Green (U), 
// the Z-component is Blue (V).
//
// YUV (YCrCb)
// the X-component contains Luma (Y, 0.0f to 1.0f), the Y-component contains blue-difference
// chroma (U, -0.5f to 0.5f), the Z element contains the Red-difference chroma (V, -0.5f to 0.5f)
//
// use overloaded operators only for vectors, not for planes, 
// quaternions or colors. For this classes use the appropriate functions
//////////////////////////////////////////////////////////////////////////
typedef Vec BLOCOCORE_API Col;

//////////////////////////////////////////////////////////////////////////
// operators
//////////////////////////////////////////////////////////////////////////
inline Vec BLOCOCORE_API operator + (Vec& lhs, Vec& rhs)
{
	return Vec(XMVectorAdd(lhs.Get(), rhs.Get()));
}
inline Vec BLOCOCORE_API operator + (Vec& lhs, XMFLOAT4& rhs)
{
	return Vec(XMVectorAdd(lhs.Get(), XMLoadFloat4(&rhs)));
}
inline Vec BLOCOCORE_API operator + (XMFLOAT4& lhs, Vec& rhs)
{
	return Vec(XMVectorAdd(rhs.Get(), XMLoadFloat4(&lhs)));
}
inline Vec BLOCOCORE_API operator + (Vec& lhs, FXMVECTOR rhs)
{
	return Vec(XMVectorAdd(lhs.Get(), rhs));
}
inline Vec BLOCOCORE_API operator + (FXMVECTOR rhs, Vec& lhs)
{
	return Vec(XMVectorAdd(lhs.Get(), rhs));
}

inline Vec BLOCOCORE_API operator - (Vec& lhs, Vec& rhs)
{
	return Vec(XMVectorSubtract(lhs.Get(), rhs.Get()));
}
inline Vec BLOCOCORE_API operator - (Vec& lhs, XMFLOAT4& rhs)
{
	return Vec(XMVectorSubtract(lhs.Get(), XMLoadFloat4(&rhs)));
}
inline Vec BLOCOCORE_API operator - (XMFLOAT4& lhs, Vec& rhs)
{
	return Vec(XMVectorSubtract(rhs.Get(), XMLoadFloat4(&lhs)));
}
inline Vec BLOCOCORE_API operator - (Vec& lhs, FXMVECTOR rhs)
{
	return Vec(XMVectorSubtract(lhs.Get(), rhs));
}
inline Vec BLOCOCORE_API operator - (FXMVECTOR lhs , Vec& rhs)
{
	return Vec(XMVectorSubtract(lhs, rhs.Get()));
}

inline Vec BLOCOCORE_API operator * (Vec& lhs, Vec& rhs)
{
	return Vec(XMVectorMultiply(lhs.Get(), rhs.Get()));
}
inline Vec BLOCOCORE_API operator * (Vec& lhs, XMFLOAT4& rhs)
{
	return Vec(XMVectorMultiply(lhs.Get(), XMLoadFloat4(&rhs)));
}
inline Vec BLOCOCORE_API operator * (XMFLOAT4& lhs, Vec& rhs)
{
	return Vec(XMVectorMultiply(rhs.Get(), XMLoadFloat4(&lhs)));
}
inline Vec BLOCOCORE_API operator * (Vec& lhs, Mat& rhs)
{
	return Vec(XMVector3Transform(lhs.Get(), rhs.Get()));
}
inline Vec BLOCOCORE_API operator * (Vec& lhs, XMFLOAT4X4& rhs)
{
	return Vec(XMVector4Transform(lhs, XMLoadFloat4x4(&rhs)));
}
inline Vec BLOCOCORE_API operator * (Mat& lhs, Vec& rhs)
{
	return Vec(XMVector4Transform(rhs.Get(), lhs.Get()));
}
inline Vec BLOCOCORE_API operator * (XMFLOAT4X4& lhs, Vec& rhs )
{
	return Vec(XMVector4Transform(rhs, XMLoadFloat4x4(&lhs)));
}
inline Vec BLOCOCORE_API operator * (FXMVECTOR lhs, Vec& rhs)
{
	return Vec(XMVectorMultiply(rhs.Get(), lhs));
}
inline Vec BLOCOCORE_API operator * (Vec& lhs, FXMVECTOR rhs)
{
	return Vec(XMVectorMultiply(lhs.Get(), rhs));
}
inline Vec BLOCOCORE_API operator * (Vec& lhs, CXMMATRIX rhs)
{
	return Vec(XMVector4Transform(lhs.Get(), rhs));
}
inline Vec BLOCOCORE_API operator * (CXMMATRIX lhs, Vec& rhs)
{
	return Vec(XMVector4Transform(rhs.Get(), lhs));
}

inline Vec BLOCOCORE_API operator / (Vec& lhs, Vec& rhs)
{
	return Vec(XMVectorDivide(lhs.Get(), rhs.Get()));
}
inline Vec BLOCOCORE_API operator / (Vec& lhs, XMFLOAT4& rhs)
{
	return Vec(XMVectorDivide(lhs.Get(), XMLoadFloat4(&rhs)));
}
inline Vec BLOCOCORE_API operator / (XMFLOAT4& lhs, Vec& rhs)
{
	return Vec(XMVectorDivide(rhs.Get(), XMLoadFloat4(&lhs)));
}
inline Vec BLOCOCORE_API operator / (Vec& lhs, FXMVECTOR rhs)
{
	return Vec(XMVectorDivide(lhs.Get(), rhs));
}
inline Vec BLOCOCORE_API operator / (FXMVECTOR lhs, Vec& rhs)
{
	return Vec(XMVectorDivide(rhs.Get(), lhs));
}

inline Mat BLOCOCORE_API operator * (Mat& lhs, Mat& rhs)
{
	return Mat(XMMatrixMultiply(lhs.Get(), rhs.Get()));
}
inline Mat BLOCOCORE_API operator * (Mat& lhs, XMFLOAT4X4& rhs)
{
	return Mat(XMMatrixMultiply(lhs.Get(), XMLoadFloat4x4(&rhs)));
}
inline Mat BLOCOCORE_API operator * (XMFLOAT4X4& lhs, Mat& rhs)
{
	return Mat(XMMatrixMultiply(rhs.Get(), XMLoadFloat4x4(&lhs)));
}
inline Mat BLOCOCORE_API operator * (CXMMATRIX lhs, Mat& rhs)
{
	return Mat(XMMatrixMultiply(rhs.Get(), lhs));
}
inline Mat BLOCOCORE_API operator * (Mat& lhs, CXMMATRIX rhs)
{
	return Mat(XMMatrixMultiply(lhs.Get(), rhs));
}

//////////////////////////////////////////////////////////////////////////
// Math Functions
//////////////////////////////////////////////////////////////////////////
// Vector
inline Vec BLOCOCORE_API VecAddAngle(Vec& vec1, Vec& vec2)									{return Vec(XMVectorAddAngles(vec1.Get(), vec2.Get()));}
inline Vec BLOCOCORE_API VecSlerp(Vec& vec1, Vec& vec2, float t)								{return Vec(XMVectorLerp(vec1, vec2, t));}

inline Vec BLOCOCORE_API Vec2Cross(Vec& vec1, Vec& vec2)										{return Vec(XMVector2Cross(vec1.Get(), vec2.Get()));}
inline Vec BLOCOCORE_API Vec2Normalize(Vec& vec)												{return Vec(XMVector2Normalize(vec.Get()));}
inline Vec BLOCOCORE_API Vec2NormalizeEst(Vec& vec)											{return Vec(XMVector2NormalizeEst(vec.Get()));}
inline Vec BLOCOCORE_API Vec2Length(Vec& vec)													{return Vec(XMVector2Length(vec.Get()));}
inline Vec BLOCOCORE_API Vec2LengthEst(Vec& vec)												{return Vec(XMVector2LengthEst(vec.Get()));}
inline Vec BLOCOCORE_API Vec2LengthSq(Vec& vec)												{return Vec(XMVector2LengthSq(vec.Get()));}
inline Vec BLOCOCORE_API Vec2Dot(Vec& vec1, Vec& vec2)										{return Vec(XMVector2Dot(vec1, vec2));}
inline Vec BLOCOCORE_API Vec2Transform(Vec& vec, Mat& mat)									{return Vec(XMVector2Transform(vec.Get(), mat.Get()));}
inline Vec BLOCOCORE_API Vec2Transform(Vec& vec, Quat& quat)									{return Vec(XMVector2Transform(vec.Get(), XMMatrixRotationQuaternion(quat.Get())));}

inline Vec BLOCOCORE_API VecCross(Vec& vec1, Vec& vec2)										{return Vec(XMVector3Cross(vec1.Get(), vec2.Get()));}
inline Vec BLOCOCORE_API VecNormalize(Vec& vec)												{return Vec(XMVector3Normalize(vec.Get()));}
inline Vec BLOCOCORE_API VecNormalizeEst(Vec& vec)											{return Vec(XMVector3NormalizeEst(vec.Get()));}
inline Vec BLOCOCORE_API VecLength(Vec& vec)													{return Vec(XMVector3Length(vec.Get()));}
inline Vec BLOCOCORE_API VecLengthEst(Vec& vec)												{return Vec(XMVector3LengthEst(vec.Get()));}
inline Vec BLOCOCORE_API VecLengthSq(Vec& vec)												{return Vec(XMVector3LengthSq(vec.Get()));}
inline Vec BLOCOCORE_API VecDot(Vec& vec1, Vec& vec2)										{return Vec(XMVector3Dot(vec1, vec2));}
inline Vec BLOCOCORE_API VecTransform(Vec& vec, Mat& mat)									{return Vec(XMVector3Transform(vec.Get(), mat.Get()));}
inline Vec BLOCOCORE_API VecTransform(Vec& vec, Quat& quat)									{return Vec(XMVector3Transform(vec.Get(), XMMatrixRotationQuaternion(quat.Get())));}

inline Vec BLOCOCORE_API Vec4Normalize(Vec& vec)												{return Vec(XMVector4Normalize(vec.Get()));}
inline Vec BLOCOCORE_API Vec4NormalizeEst(Vec& vec)											{return Vec(XMVector4NormalizeEst(vec.Get()));}
inline Vec BLOCOCORE_API Vec4Length(Vec& vec)													{return Vec(XMVector4Length(vec.Get()));}
inline Vec BLOCOCORE_API Vec4LengthEst(Vec& vec)												{return Vec(XMVector4LengthEst(vec.Get()));}
inline Vec BLOCOCORE_API Vec4LengthSq(Vec& vec)												{return Vec(XMVector4LengthSq(vec.Get()));}
inline Vec BLOCOCORE_API Vec4Dot(Vec& vec1, Vec& vec2)										{return Vec(XMVector4Dot(vec1, vec2));}
inline Vec BLOCOCORE_API Vec4Transform(Vec& vec, Mat& mat)									{return Vec(XMVector4Transform(vec.Get(), mat.Get()));}
inline Vec BLOCOCORE_API Vec4Transform(Vec& vec, Quat& quat)									{return Vec(XMVector4Transform(vec.Get(), XMMatrixRotationQuaternion(quat.Get())));}

// Matrix
inline Mat BLOCOCORE_API MatTranslation(float x, float y, float z)							{return Mat(XMMatrixTranslation(x, y, z));}
inline Mat BLOCOCORE_API MatTranslation(Vec& offset)											{return Mat(XMMatrixTranslationFromVector(offset.Get()));}
inline Mat BLOCOCORE_API MatRotation(float x, float y, float z)								{return Mat(XMMatrixRotationRollPitchYaw(x, y, z));}
inline Mat BLOCOCORE_API MatRotation(Vec& offset)												{return Mat(XMMatrixRotationRollPitchYawFromVector(offset.Get()));}
inline Mat BLOCOCORE_API MatRotationQuat(Quat& offset)										{return Mat(XMMatrixRotationQuaternion(offset.Get()));}
inline Mat BLOCOCORE_API MatRotationAxis(Vec& rotAxis, float angle)							{return Mat(XMMatrixRotationAxis(rotAxis.Get(), angle));}
inline Mat BLOCOCORE_API MatRotationNormalAxis(Vec& normalAxis, float angle)					{return Mat(XMMatrixRotationNormal(normalAxis, angle));}
inline Mat BLOCOCORE_API MatRotationYawPitchRoll(float yaw, float pitch, float roll)			{return Mat(XMMatrixRotationRollPitchYaw(pitch, yaw, roll));}
inline Mat BLOCOCORE_API MatRotationYawPitchRoll(Vec& v)										{return Mat(XMMatrixRotationRollPitchYawFromVector(v));}
inline Mat BLOCOCORE_API MatScaling(Vec& offset)												{return Mat(XMMatrixScalingFromVector(offset.Get()));}
inline Mat BLOCOCORE_API MatCamera(Vec& pos, Vec& lookAt, Vec& up)							{return Mat(XMMatrixLookAtLH(pos.Get(), lookAt.Get(), up.Get()));}
inline Mat BLOCOCORE_API MatProjection(float fov, float fAspect, float fNear, float fFar)		{return Mat(XMMatrixPerspectiveFovLH(fov, fAspect, fNear, fFar));}
inline Mat BLOCOCORE_API MatIdentity()														{return Mat(XMMatrixIdentity());}
inline Mat BLOCOCORE_API MatTranspose(Mat& mat)												{return Mat(XMMatrixTranspose(mat.Get()));}
inline Vec BLOCOCORE_API MatDeterminant(Mat& mat)												{return Vec(XMMatrixDeterminant(mat.Get()));}
inline BOOL BLOCOCORE_API MatIsIdentity(Mat& mat)												{return XMMatrixIsIdentity(mat.Get());}
inline Vec  BLOCOCORE_API MatXForm(Mat& mat)													{Vec vec; return Vec4Transform(vec, mat);}	
inline bool BLOCOCORE_API MatDecompose(Vec* pScale, Quat* pRot, Vec* pTrans, Mat& mat)
{
	XMVECTOR scale(pTrans->Get());
	XMVECTOR rot(pRot->Get());
	XMVECTOR trans(pRot->Get());

	if(XMMatrixDecompose(&scale, &rot, &trans, mat.Get()))
	{
		pScale = DEBUG_CLIENTBLOCK Vec(scale);
		pRot = DEBUG_CLIENTBLOCK Vec(rot);
		pTrans = DEBUG_CLIENTBLOCK Vec(trans);

		return true;
	}

	return false;
}
inline Mat BLOCOCORE_API MatInverse(Mat& mat, Vec* determinant)
{ 
	XMVECTOR det(determinant->Get()); 
	Mat out(XMMatrixInverse(&det, mat.Get()));
	*determinant = Vec(det);
	return out;
}
inline Mat BLOCOCORE_API MatSetPosition(Mat& mat, Vec& pos)										
{ 
	FLOAT* arr = mat.GetArray(); 
	arr[12] = pos.GetX();
	arr[13] = pos.GetY();
	arr[14] = pos.GetZ();
	arr[15] = 1.0f;
		
	return Mat(arr);
}
inline Vec BLOCOCORE_API MatGetPosition(Mat& mat)
{
	return Vec(mat.GetArray()[ 12],
			   mat.GetArray()[ 13],
			   mat.GetArray()[ 14],
			   1.0f);
}

// Quaternion
inline Quat BLOCOCORE_API QuatRotation(float x, float y, float z)								{return Quat(XMQuaternionRotationRollPitchYaw(x, y, z));}
inline Quat BLOCOCORE_API QuatRotation(Vec& offset)											{return Quat(XMQuaternionRotationRollPitchYawFromVector(offset));}
inline Quat BLOCOCORE_API QuatRotationAxis(Vec& rotAxis, float angle)							{return Quat(XMQuaternionRotationAxis(rotAxis.Get(), angle));}
inline Quat BLOCOCORE_API QuatRotationNormalAxis(Vec& normalAxis, float angle)				{return Quat(XMQuaternionRotationNormal(normalAxis, angle));}
inline Quat BLOCOCORE_API QuatRotationMatrix(Mat& mat)										{return Quat(XMQuaternionRotationMatrix(mat.Get()));}
inline Quat BLOCOCORE_API QuatNormalize(Quat& quat)											{return Quat(XMQuaternionNormalize(quat.Get()));}
inline Quat BLOCOCORE_API QuatNormalizeEst(Quat& quat)										{return Quat(XMQuaternionNormalizeEst(quat.Get()));}
inline Quat BLOCOCORE_API QuatSlerp(Quat& quat1, Quat& quat2, float t)						{return Quat(XMQuaternionSlerp(quat1, quat2, t));}
inline Quat BLOCOCORE_API QuatLength(Quat& quat)												{return Quat(XMQuaternionLength(quat.Get()));}
inline Quat BLOCOCORE_API QuatLengthSq(Quat& quat)											{return Quat(XMQuaternionLengthSq(quat.Get()));}
inline Quat BLOCOCORE_API QuatInverse(Quat& quat)												{return Quat(XMQuaternionInverse(quat.Get()));}
inline Quat BLOCOCORE_API QuatMultiply(Quat& quat1, Quat& quat2 )								{return Quat(XMQuaternionMultiply(quat1.Get(), quat2.Get()));}

// Plane
inline Plane BLOCOCORE_API PlaneFromPoints(Vec& p1, Vec& p2, Vec& p3)								{return Plane(XMPlaneFromPoints(p1.Get(), p2.Get(), p3.Get()));}
inline Plane BLOCOCORE_API PlaneFromPointNormal(Vec& point, Vec& normal)							{return Plane(XMPlaneFromPointNormal(point.Get(), normal.Get()));}
inline Vec BLOCOCORE_API	 PlaneDot(Plane& plane, Vec& vec)										{return Vec(XMPlaneDot(plane.Get(), vec.Get()));}
inline Vec BLOCOCORE_API	 PlaneDotCoord(Plane& plane, Vec& vec)									{return Vec(XMPlaneDotCoord(plane.Get(), vec.Get()));}
inline Vec BLOCOCORE_API	 PlaneDotNormal(Plane& plane, Vec& vec)									{return Vec(XMPlaneDotNormal(plane.Get(), vec.Get()));}
inline Vec BLOCOCORE_API	 PlaneIntersectLine(Plane& plane, Vec& p1, Vec& p2)						{return Vec(XMPlaneIntersectLine(plane.Get(), p1.Get(), p2.Get()));}
inline bool BLOCOCORE_API	 PlaneInside(Plane& plane, Vec& point)									{return ( PlaneDotCoord(plane, point).GetX() >= 0.0f ); }
inline bool BLOCOCORE_API	 PlaneInside(Plane& plane, Vec& point, float radius)					{return ( PlaneDotCoord(plane, point).GetX() >= -radius );}
inline void BLOCOCORE_API  PlaneIntersectPlane(Plane& plane1, Plane& plane2, Vec* pP1, Vec* pP2)
{
	XMVECTOR temp1;
	XMVECTOR temp2;

	XMPlaneIntersectPlane(&temp1, &temp2, plane1.Get(), plane2.Get());

	(*pP1) = Vec(temp1);
	(*pP2) = Vec(temp2);
}


// Color
inline Col BLOCOCORE_API ColAdjustContrast(Col& col, float contrast)							{return Col(XMColorAdjustContrast(col.Get(), contrast));};
inline Col BLOCOCORE_API ColAdjustSaturation(Col& col, float saturation)						{return Col(XMColorAdjustSaturation(col.Get(), saturation));}
inline Col BLOCOCORE_API ColModulate(Col& col1, Col& col2)									{return Col(XMColorModulate(col1.Get(), col2.Get()));}
inline Col BLOCOCORE_API ColNegativ(Col& col)													{return Col(XMColorNegative(col.Get()));}

inline UINT32 BLOCOCORE_API ColToHex(Col& col)
{
	UINT color = 0;
	float arr[4];
	col.GetArray(arr);

	for(UCHAR i = 0; i < 4; i++)
	{
		color |= (0xff & (UINT)(arr[i] * 255)) << (i * 8);
	}

	return color;
}
inline Col BLOCOCORE_API	HexToCol(UINT32 col)
{
	float color[4];

	for(UCHAR i = 0; i < 4; i++)
	{
		color[i] = (0xff & (col >> (i * 8))) / 255.0f;
	}

	return Col(color);
}

inline bool BLOCOCORE_API operator ==(const POINT& lhs, const POINT& rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}
inline bool BLOCOCORE_API operator !=(const POINT& lhs, const POINT& rhs)
{
	return !(lhs == rhs);
}


#endif // Geometry_h__