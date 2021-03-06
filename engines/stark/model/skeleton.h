/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef STARK_MODEL_SKELETON_H
#define STARK_MODEL_SKELETON_H

#include "common/array.h"
#include "common/str.h"

#include "math/aabb.h"
#include "math/quat.h"
#include "math/ray.h"
#include "math/vector3d.h"

namespace Stark {

class ArchiveReadStream;
class SkeletonAnim;

class BoneNode {
public:
	BoneNode() : _parent(-1), _idx(0), _u1(0) {}
	~BoneNode() { }

	/** Perform a collision test with the ray */
	bool intersectRay(const Math::Ray &ray) const;

	Common::String _name;
	float _u1;
	Common::Array<uint32> _children;
	int _parent;
	uint32 _idx;

	Math::Vector3d _animPos;
	Math::Quaternion _animRot;

	/** Bone space bounding box */
	Math::AABB _boundingBox;
};

/**
 * Skeleton manager to load and store skeletal information about an actor
 */
class Skeleton {
public:
	Skeleton();
	~Skeleton();

	/**
	 * Increment the skeleton timestamp, and apply bone animations if required
	 */
	void animate(uint32 time);

	/**
	 * Start reading animation data from the specified stream
	 */
	void setAnim(SkeletonAnim *anim);

	/**
	 * Create skeleton object from the specified stream
	 */
	void readFromStream(ArchiveReadStream *stream);

	/**
	 * Obtain the list of bones
	 */
	const Common::Array<BoneNode *> getBones();

private:
	void setNode(uint32 time, BoneNode *bone, const BoneNode *parent);

	Common::Array<BoneNode *> _bones;
	SkeletonAnim *_anim;

	uint32 _lastTime;
};

} // End of namespace Stark

#endif // STARK_MODEL_SKELETON_H
