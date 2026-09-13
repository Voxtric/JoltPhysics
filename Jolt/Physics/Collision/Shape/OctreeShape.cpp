#include <Jolt/Jolt.h>

#include <Jolt/Physics/Collision/Shape/OctreeShape.h>
#include <Jolt/Physics/Collision/Shape/ScaleHelpers.h>
#include <Jolt/Physics/Collision/Shape/GetTrianglesContext.h>
#include <Jolt/Physics/Collision/RayCast.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/CollidePointResult.h>
#include <Jolt/Physics/Collision/TransformedShape.h>
#include <Jolt/Physics/Collision/CollideSoftBodyVertexIterator.h>
#include <Jolt/Geometry/RayAABox.h>
#include <Jolt/ObjectStream/TypeDeclarations.h>
#include <Jolt/Core/StreamIn.h>
#include <Jolt/Core/StreamOut.h>
#ifdef JPH_DEBUG_RENDERER
	#include <Jolt/Renderer/DebugRenderer.h>
#endif // JPH_DEBUG_RENDERER

JPH_NAMESPACE_BEGIN

JPH_IMPLEMENT_SERIALIZABLE_VIRTUAL(OctreeShapeSettings)
{
	JPH_ADD_BASE_CLASS(OctreeShapeSettings, ShapeSettings)

	JPH_ADD_ATTRIBUTE(OctreeShapeSettings, mEndLeafSize)
}

ShapeSettings::ShapeResult OctreeShapeSettings::Create() const
{
	if (mCachedResult.IsEmpty())
		Ref<Shape> shape = new OctreeShape(*this, mCachedResult);
	return mCachedResult;
}

OctreeShape::OctreeShape(const OctreeShapeSettings &inSettings, ShapeResult &outResult) :
	Shape(EShapeType::Octree, EShapeSubType::Octree, inSettings, outResult),
	mEndLeafSize(inSettings.mEndLeafSize)
{
	if (inSettings.mEndLeafSize < 0.0f)
	{
		outResult.SetError("Invalid end leaf size");
		return;
	}
	outResult.Set(this);
}

AABox OctreeShape::GetLocalBounds() const
{
	const Vec3 halfSize = Vec3::sReplicate(mEndLeafSize * MAX_OCTREE_NODE_LEVEL_DIMENSION_SIZE * 0.5f);
	return AABox(-halfSize, halfSize);
}

JPH_NAMESPACE_END
