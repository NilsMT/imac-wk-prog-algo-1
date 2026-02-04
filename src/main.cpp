#include <sil/sil.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <cmath>

using vec2 = glm::vec2;

vec2 rotated(vec2 point, vec2 center_of_rotation, float angle)
{
    return vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

int main() {
    //config
    float maxAngle = (4*M_PI); //the max angle a pixel can be rotate too (radians)

    sil::Image image{"images/logo.png"};
    auto vortex = image;

    vec2 center = vec2{
        image.width()/2,
        image.height()/2
    };

    const float maxDistance = 
        glm::distance(vec2{0,0}, center);

    for (int x = 0; x < image.width(); ++x) {
        for (int y = 0; y < image.height(); ++y) {
            vec2 pos{float(x), float(y)};
            float d = glm::distance(pos, center);
            float r = d / maxDistance; //= the further the higher [0;1]
            float angle = maxAngle * r;

            //rotation
            vec2 rot = rotated(pos, center, angle);

            //clamp image bounds
            rot.x = glm::clamp(rot.x, 0.f, float(image.width() - 1));
            rot.y = glm::clamp(rot.y, 0.f, float(image.height() - 1));

            //assign the current one to the rotated pixel
            vortex.pixel(x, y) = image.pixel(int(rot.x), int(rot.y));
        }
    }
    
    vortex.save("output/vortex.png");
}