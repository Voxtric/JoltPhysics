#pragma once

#include <intrin.h>

#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/PhysicsSettings.h>

static constexpr size_t MAX_OCTREE_NODE_LEVEL = 3; // 16x16x16
static constexpr size_t MAX_OCTREE_NODE_LEVEL_DIMENSION_ELEMENTS = (2 << MAX_OCTREE_NODE_LEVEL);
static constexpr float MAX_OCTREE_NODE_LEVEL_DIMENSION_SIZE = static_cast<float>(MAX_OCTREE_NODE_LEVEL_DIMENSION_ELEMENTS);

JPH_NAMESPACE_BEGIN

class JPH_EXPORT OctreeShapeSettings final : public ShapeSettings
{
	JPH_DECLARE_SERIALIZABLE_VIRTUAL(JPH_EXPORT, OctreeShapeSettings)

	/// Default constructor for deserialization
							OctreeShapeSettings() = default;
	explicit				OctreeShapeSettings(float inEndLeafSize) : mEndLeafSize(inEndLeafSize) { }

	// See: ShapeSettings
	virtual ShapeResult		Create() const override;

	float					mEndLeafSize = 0.0f;
};

class JPH_EXPORT OctreeShape final : public Shape
{
public:
	JPH_OVERRIDE_NEW_DELETE

	/// Constructor
							OctreeShape() : Shape(EShapeType::Octree, EShapeSubType::Octree) { }
							OctreeShape(const OctreeShapeSettings &inSettings, ShapeResult &outResult);

	// See Shape::GetLocalBounds
	virtual AABox			GetLocalBounds() const override;

	// See Shape::GetInnerRadius
	virtual float			GetInnerRadius() const override					{ return mEndLeafSize * 0.5f; }

	// See Shape::GetSubShapeIDBitsRecursive
	virtual uint			GetSubShapeIDBitsRecursive() const override		{ static_cast<uint>(__popcntd(MAX_OCTREE_NODE_LEVEL_DIMENSION_ELEMENTS * MAX_OCTREE_NODE_LEVEL_DIMENSION_ELEMENTS * MAX_OCTREE_NODE_LEVEL_DIMENSION_ELEMENTS) - 1); }

private:
	float					mEndLeafSize = 0.0f;
};

JPH_NAMESPACE_END
