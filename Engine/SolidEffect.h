#pragma once

#include "Pipeline.h"
#include "DefaultGeometryShader.h"
#include "BaseVertexShader.h"
//solid color attribute not interpolated

class SolidEffect {
public:
	//the vertex type that will be input into the pipeline
	class Vertex {
	public:
		Vertex() = default;
		Vertex(const Vec3 & pos)
			:
			pos(pos)
		{}
		Vertex(const Vec3 & pos, const Vertex & src)
			:
			color(src.color),
			pos(pos)
		{}
		Vertex(const Vec3 & pos, const Color & color)
			:
			color(color),
			pos(pos)
		{}
		Vertex& operator+=(const Vertex & rhs)
		{
			pos += rhs.pos;
			return *this;
		}
		Vertex operator+(const Vertex & rhs) const
		{
			return Vertex(*this) += rhs;
		}
		Vertex& operator-=(const Vertex & rhs)
		{
			pos -= rhs.pos;
			return *this;
		}
		Vertex operator-(const Vertex & rhs) const
		{
			return Vertex(*this) -= rhs;
		}
		Vertex& operator*=(float rhs)
		{
			pos *= rhs;
			return *this;
		}
		Vertex operator*(float rhs) const
		{
			return Vertex(*this) *= rhs;
		}
		Vertex& operator/=(float rhs)
		{
			pos /= rhs;
			return *this;
		}
		Vertex operator/(float rhs) const
		{
			return Vertex(*this) /= rhs;
		}
	public:
		Vec3 pos;
		Color color;
	};
	// default vs rotates and translates vertices
	// does not touch attributes
	class VSOutput
	{
	public:
		VSOutput() = default;
		VSOutput(const Vec4& pos)
			:
			pos(pos)
		{}
		VSOutput(const Vec4& pos, const Vertex& src)
			:
			color(src.color),
			pos(pos)
		{}
		VSOutput(const Vec4& pos, const Color& color)
			:
			color(color),
			pos(pos)
		{}
		VSOutput& operator+=(const VSOutput& rhs)
		{
			pos += rhs.pos;
			return *this;
		}
		VSOutput operator+(const VSOutput& rhs) const
		{
			return VSOutput(*this) += rhs;
		}
		VSOutput& operator-=(const VSOutput& rhs)
		{
			pos -= rhs.pos;
			return *this;
		}
		VSOutput operator-(const VSOutput& rhs) const
		{
			return VSOutput(*this) -= rhs;
		}
		VSOutput& operator*=(float rhs)
		{
			pos *= rhs;
			return *this;
		}
		VSOutput operator*(float rhs) const
		{
			return VSOutput(*this) *= rhs;
		}
		VSOutput& operator/=(float rhs)
		{
			pos /= rhs;
			return *this;
		}
		VSOutput operator/(float rhs) const
		{
			return VSOutput(*this) /= rhs;
		}
	public:
		Vec4 pos;
		Color color;
	};

	class VertexShader : public BaseVertexShader<VSOutput>
	{
	public:

		VSOutput operator()(const Vertex& v) const
		{
			return{ Vec4(v.pos) * worldViewProj, v.color };
		}

	};

	//default gs passed vertices through and output triangle
	typedef	DefaultGeometryShader<VertexShader::Output> GeometryShader;

	// invoked for each pixel of a triangle
	// takes an input of attributes that are the
	// result of interpolating vertex attributes
	// and outputs a color
	class PixelShader
	{
	public:
		template<class I>
		Color operator()(const I& in) const
		{
			return in.color;
		}
	};
public:
	VertexShader vs;
	PixelShader ps;
	GeometryShader gs;
};