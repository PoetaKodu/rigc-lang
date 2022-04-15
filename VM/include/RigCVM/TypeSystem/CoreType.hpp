#pragma once

#include RIGCVM_PCH

#include <RigCVM/TypeSystem/IType.hpp>

namespace rigc::vm
{

class CoreType
	: public IType
{
public:
	enum Kind : uint8_t
	{
		Int16,		Int32,		Int64,
		Uint16,		Uint32,		Uint64,
		Float32,	Float64,
		Char,		Char16,		Char32,
		Bool,
		MAX
	};

private:

	static constexpr auto Num = static_cast<size_t>(Kind::MAX);

	static constexpr auto Sizes = std::to_array({
			sizeof(int16_t),	sizeof(int32_t),	sizeof(int64_t),
			sizeof(uint16_t),	sizeof(uint32_t),	sizeof(uint64_t),
			sizeof(float),		sizeof(double),
			sizeof(char),		sizeof(char16_t),	sizeof(char32_t),
			sizeof(bool)
		});

	static constexpr auto Names = std::to_array<std::string_view>({
			"Int16",	"Int32",	"Int64",
			"Uint16",	"Uint32",	"Uint64",
			"Float32",	"Float64",
			"Char",		"Char16",	"Char32",
			"Bool"
		});
public:



	template <typename T>
	static Kind fromCppType()
	{
		#define HANDLE_TYPE(CppName, EnumValue) if constexpr (std::is_same_v<T, CppName>) return EnumValue;
		#define ELSE_HANDLE_TYPE(CppName, EnumValue) else if constexpr (std::is_same_v<T, CppName>) return EnumValue;

		HANDLE_TYPE		(int16_t,	Int16)
		ELSE_HANDLE_TYPE(int32_t,	Int32)
		ELSE_HANDLE_TYPE(int64_t,	Int64)
		ELSE_HANDLE_TYPE(uint16_t,	Uint16)
		ELSE_HANDLE_TYPE(uint32_t,	Uint32)
		ELSE_HANDLE_TYPE(uint64_t,	Uint64)
		ELSE_HANDLE_TYPE(float,		Float32)
		ELSE_HANDLE_TYPE(double,	Float64)
		ELSE_HANDLE_TYPE(char,		Char)
		ELSE_HANDLE_TYPE(char16_t,	Char16)
		ELSE_HANDLE_TYPE(char32_t,	Char32)
		ELSE_HANDLE_TYPE(bool,		Bool)
		else
			static_assert(std::is_same_v<T, bool>, "Unsupported type");
		#undef HANDLE_TYPE
		#undef ELSE_HANDLE_TYPE
	}

	std::string_view toString() const
	{
		return Names[static_cast<int>(kind)];
	}

	std::size_t size() const override
	{
		return Sizes[static_cast<int>(kind)];
	}

	std::string name() const override
	{
		return std::string(this->toString());
	}

	InnerType decay() const override
	{
		return const_cast<CoreType*>(this)->shared_from_this();
	}

	CoreType(Kind kind_)
		: kind(kind_)
	{}

	Kind kind;
};


}
