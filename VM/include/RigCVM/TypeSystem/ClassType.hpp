#pragma once

#include RIGCVM_PCH

#include <RigCVM/TypeSystem/Shared/DataMember.hpp>
#include <RigCVM/TypeSystem/IType.hpp>
#include <RigCVM/TypeSystem/StructuralType.hpp>
#include <RigCVM/Scope.hpp>

namespace rigc::vm
{

class ClassType

	:
	public StructuralType
{
public:
	auto constructors() const -> FunctionOverloads const*;
	auto defaultConstructor() const -> Function*;
};

}
