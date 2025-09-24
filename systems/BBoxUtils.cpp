#include <BBoxUtils.h>

namespace TAKO {

    Vector3f BBoxUtils::rotatePoint(Vector3f p1, Vector3f p2, float angle){

        Vector2f xAxis;
        Vector2f yAxis;
        float rotation = BBoxUtils::get_degrees(angle);

        float s = sin(rotation);
        float c = cos(rotation);

        // translate point back to origin:
        p1.X -= p2.X;
        p1.Z -= p2.Z;

        // rotate point
        float xnew = p1.X * c - p1.Z * s;
        float ynew = p1.X * s + p1.Z * c;

        // translate point back:
        p1.X = xnew + p2.X;
        p1.Z = ynew + p2.Z;
        return p1;

    }

    float BBoxUtils::get_degrees(float num)
    {
        return 2 * M_PI * (num /360); 
    }

    void BBoxUtils::calculateBBox(OBB2D& body, const Vector3f& pos, const float rot, const int defaultBoxSize) {
        const TAKO::Vector2f center = Vector2f(pos.X, pos.Z);

        float w = body.node.getScale().X * defaultBoxSize;
        float h = body.node.getScale().Z * defaultBoxSize;

        rotate(body, center, w, h, rot);

    }


    Vector2f rotatePoint2D(Vector2f p1, Vector2f p2, float angle){

        Vector2f xAxis;
        Vector2f yAxis;
        float rotation = BBoxUtils::get_degrees(angle);

        float s = sin(rotation);
        float c = cos(rotation);

        // translate point back to origin:
        p1.X -= p2.X;
        p1.Y -= p2.Y;

        // rotate point
        float xnew = p1.X * c - p1.Y * s;
        float ynew = p1.X * s + p1.Y * c;

        // translate point back:
        p1.X = xnew + p2.X;
        p1.Y = ynew + p2.Y;
        // std::cout<<xnew<<" xnew VS "<<p1.X<<" xold"<<std::endl;
        // std::cout<<ynew<<" Znew VS "<<p1.Z<<" Zold"<<std::endl; 


        return p1;

    }

    void BBoxUtils::rotate(OBB2D& bbox, const Vector2f center, const float w, const float h, float angle){

        Vector2f X( 1, 0);
        Vector2f Y( 0, 1);
        X *= (w / 2);
        Y *= (h / 2);   

        bbox.corner[0] = center - X - Y;
        bbox.corner[0] = rotatePoint2D(bbox.corner[0], center, angle);
        bbox.corner[1] = center + X - Y;
        bbox.corner[1] = rotatePoint2D(bbox.corner[1], center, angle);
        bbox.corner[2] = center + X + Y;
        bbox.corner[2] = rotatePoint2D(bbox.corner[2], center, angle);
        bbox.corner[3] = center - X + Y;
        bbox.corner[3] = rotatePoint2D(bbox.corner[3], center, angle);


        computeAxes(bbox);
    }

    void BBoxUtils::computeAxes(OBB2D& bbox) {
        bbox.axis[0] = bbox.corner[1] - bbox.corner[0]; 
        bbox.axis[1] = bbox.corner[3] - bbox.corner[0]; 

        // Make the length of each axis 1/edge length so we know any
        // dot product must be less than 1 to fall within the edge.

        for (int a = 0; a < 2; ++a) {
            bbox.axis[a] /= bbox.axis[a].getLengthSQ();
            bbox.origin[a] = bbox.corner[0].dotProduct(bbox.axis[a]);
            //std::cout<<bbox->axis[a].X<<"/"<<bbox->axis[a].Y<<std::endl;
        }
    }
}