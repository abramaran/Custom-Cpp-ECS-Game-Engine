#include <CollisionUtils.h>
#include <PlayerConstants.h>

namespace TAKO{
bool CollisionUtils::overlaps1Way(const OBB2D& one,const OBB2D& two) {
  for (int a = 0; a < 2; ++a) {
        float t = two.corner[0].dotProduct(one.axis[a]);
        // Find the extent of box 2 on axis a
        float tMin = t;
        float tMax = t;

         for (auto c = 1; c < 4; ++c) {
            t = two.corner[c].dotProduct(one.axis[a]);
            //std::cout<<t<<"(t) vs "<<tMin<<"(tMin) vs "<<tMax<<"(tMax)"<<std::endl;
            if (t < tMin) {
                tMin = t;
            } else if (t > tMax) {
                tMax = t;
            }
        }
        // We have to subtract off the origin

        // See if [tMin, tMax] intersects [0, 1]
        if ((tMin > 1 + one.origin[a]) || (tMax < one.origin[a])) {
            // There was no intersection along this dimension;
            // the boxes cannot possibly overlap.
            return false;
        }
    }

    // There was no dimension along which there is no intersection.
    // Therefore the boxes overlap.
    return true;
}

bool CollisionUtils::overlaps(const OBB2D& one,const OBB2D& two) {
   return overlaps1Way(one, two) && overlaps1Way(two, one);
}

bool CollisionUtils::collides(const OBB2D& bbox1, const OBB2D& bbox2){
    float minY1, maxY1, minY2, maxY2;
    
    minY1 = bbox1.node.getPosition().Y - defaultBoxSizeHalf * bbox1.node.getScale().Y;
    maxY1 = bbox1.node.getPosition().Y + defaultBoxSizeHalf * bbox1.node.getScale().Y;
    minY2 = bbox2.node.getPosition().Y - defaultBoxSizeHalf * bbox2.node.getScale().Y;
    maxY2 = bbox2.node.getPosition().Y + defaultBoxSizeHalf * bbox2.node.getScale().Y;

    return  (overlaps(bbox1, bbox2) && (maxY1 < minY2 || maxY2 > minY1));

}

// Perdoname alberto por esto pero se cargaba la IA de jose
bool CollisionUtils::collidesBueno(const OBB2D& bbox1, const OBB2D& bbox2){
    float minY1, maxY1, minY2, maxY2;
    
    minY1 = bbox1.node.getPosition().Y - defaultBoxSizeHalf * bbox1.node.getScale().Y;
    maxY1 = bbox1.node.getPosition().Y + defaultBoxSizeHalf * bbox1.node.getScale().Y;
    minY2 = bbox2.node.getPosition().Y - defaultBoxSizeHalf * bbox2.node.getScale().Y;
    maxY2 = bbox2.node.getPosition().Y + defaultBoxSizeHalf * bbox2.node.getScale().Y;


    return  (overlaps(bbox1, bbox2) && !(minY1 > maxY2 || minY2 > maxY1));
}

Vector2f CollisionUtils::getYComponentsBBox(const OBB2D& bbox) {
    float minY, maxY;
    
    minY = bbox.node.getPosition().Y - defaultBoxSizeHalf * bbox.node.getScale().Y;
    maxY = bbox.node.getPosition().Y + defaultBoxSizeHalf * bbox.node.getScale().Y;

    return Vector2f(minY, maxY);
}


Vector2f CollisionUtils::getXComponentsBBox(const OBB2D& bbox){
    float minX, maxX;
    
    minX = bbox.node.getPosition().X - defaultBoxSizeHalf * bbox.node.getScale().X;
    maxX = bbox.node.getPosition().X + defaultBoxSizeHalf * bbox.node.getScale().X;

    return Vector2f(minX, maxX);
}

Vector2f CollisionUtils::getZComponentsBBox(const OBB2D& bbox){
    float minZ, maxZ;
    
    minZ = bbox.node.getPosition().Z - defaultBoxSizeHalf * bbox.node.getScale().Z;
    maxZ = bbox.node.getPosition().Z + defaultBoxSizeHalf * bbox.node.getScale().Z;

    return Vector2f(minZ, maxZ);
}

float CollisionUtils::getPlayerHeight(const OBB2D& bbox) {
    float minY, maxY;
    
    minY = bbox.node.getPosition().Y - defaultBoxSizeHalf * bbox.node.getScale().Y;
    maxY = bbox.node.getPosition().Y + defaultBoxSizeHalf * bbox.node.getScale().Y;

    return abs(maxY - minY);
}
}