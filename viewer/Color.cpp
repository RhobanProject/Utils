#include "Color.hpp"

namespace Rhoban {
  namespace Viewer {

    const Color Color::red(1,0,0);
    const Color Color::green(0,1,0);
    const Color Color::blue(0,0,1);
    const Color Color::gray(0.3,0.6,0.6);

    Color::Color(double r_, double g_, double b_)
      : r(r_), g(g_), b(b_)
    {
    }

  }
}
