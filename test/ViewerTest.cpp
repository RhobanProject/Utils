#include "viewer/Viewer.hpp"

using namespace Rhoban::Viewer;

int main() {
    Viewer viewer(1200, 900);
    while (viewer.update()) {
      viewer.drawCube(Color::blue);
      viewer.drawBox(Eigen::Vector3d(0.5, 0.2, 1.0),
                     Eigen::Vector3d(1.0, 0.0, 0.5),
                     Eigen::Matrix3d::Identity(),
                     Color::red,
                     false);
    }
}
