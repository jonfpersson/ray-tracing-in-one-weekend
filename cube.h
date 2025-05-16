#ifndef CUBE_H
#define CUBE_H

#include "hittable.h"
#include "vec3.h"

class cube : public hittable {
    public:
        cube() {}

        cube(const point3& cen, float r, shared_ptr<material> m)
            : center_point(cen), side_length(r), mat_ptr(m) {};

        virtual bool hit(
            const ray& r, float t_min, float t_max, hit_record& rec) const override;

    public:
        point3 center_point;
        int side_length;
        shared_ptr<material> mat_ptr;

};

bool cube::hit(const ray& r, float t_min, float t_max, hit_record& rec) const noexcept{
    vec3 half_extents = vec3(side_length / 2.0, side_length / 2.0, side_length / 2.0); // half of the cube's side length in each axis
    vec3 center = center_point; // Center of the cube

    // Calculate the minimum and maximum points of the cube along each axis
    float x_min = center.x() - half_extents.x();
    float x_max = center.x() + half_extents.x();
    float y_min = center.y() - half_extents.y();
    float y_max = center.y() + half_extents.y();
    float z_min = center.z() - half_extents.z();
    float z_max = center.z() + half_extents.z();

    // Slab method for each axis
    float t_x_min = (x_min - r.origin().x()) / r.direction().x();
    float t_x_max = (x_max - r.origin().x()) / r.direction().x();
    float t_y_min = (y_min - r.origin().y()) / r.direction().y();
    float t_y_max = (y_max - r.origin().y()) / r.direction().y();
    float t_z_min = (z_min - r.origin().z()) / r.direction().z();
    float t_z_max = (z_max - r.origin().z()) / r.direction().z();

    // Find the largest t_min among t_x_min, t_y_min, and t_z_min. Let's call this value t_enter.
    float t_enter = fmax(fmax(fmin(t_x_min, t_x_max), fmin(t_y_min, t_y_max)), fmin(t_z_min, t_z_max));
    // Find the smallest t_max among t_x_max, t_y_max, and t_z_max. Let's call this value t_exit.
    float t_exit = fmin(fmin(fmax(t_x_min, t_x_max), fmax(t_y_min, t_y_max)), fmax(t_z_min, t_z_max));

    // Check if the ray misses the cube
    if (t_enter > t_exit || t_exit < t_min || t_enter > t_max) {
        return false;
    }

    // The ray intersects the cube, set the hit record information
    rec.t = t_enter;
    rec.start_point = r.at(rec.t);

    // Calculate outward normal based on which face was hit
    struct FaceNormal {
        float t;
        vec3 normal;
    };

    FaceNormal normals[] = {
        { t_x_min, vec3(-1, 0, 0) },
        { t_x_max, vec3(1, 0, 0) },
        { t_y_min, vec3(0, -1, 0) },
        { t_y_max, vec3(0, 1, 0) },
        { t_z_min, vec3(0, 0, -1) },
        { t_z_max, vec3(0, 0, 1) }
    };

    vec3 outward_normal;
    for (const auto& face : normals) {
        if (t_enter == face.t) {
            outward_normal = face.normal;
            break;
        }
    }

    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}


#endif
