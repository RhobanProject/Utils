#include <SFML/OpenGL.hpp>
#include "Viewer.hpp"

using sf::Event;
using sf::Keyboard;

namespace Rhoban {
  namespace Viewer {

    Viewer::Viewer(unsigned int width, 
                   unsigned int height) :
      _lastMousePosX(0),
      _lastMousePosY(0),
      _window(sf::VideoMode(width, height), "OpenGL", 
              sf::Style::Default, sf::ContextSettings(32)),
      _camPos(0.0, 0.0, 0.0),
      _camView(1.0, 0.0, 0.0)
    {
      _window.setVerticalSyncEnabled(true);
      _camView.normalize();
    
      //Setup projection matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(
        60.0, (double)width/(double)height, 
        0.01, 1000.0);       
      //Enable Z-buffer
      glEnable(GL_DEPTH_TEST);
      glDepthMask(GL_TRUE);
      glDepthRange(0.0f, 1.0f);
      //Set color and depth clear value
      glClearColor(0.0, 0.0, 0.0, 1.0);
      glClearDepth(1.0f);

//TODO handle wasd and zqsd navigation (french and others ;) )
      // Init camera Callbacks
      onKeyPress[Keyboard::Up   ].push_back([this](){ this->forwardMove();  });
      onKeyPress[Keyboard::Down ].push_back([this](){ this->backwardMove(); });
      onKeyPress[Keyboard::Left ].push_back([this](){ this->leftMove();     });
      onKeyPress[Keyboard::Right].push_back([this](){ this->rightMove();    });
    }

    bool Viewer::treat(const Event& event)
    {
      switch(event.type) {
      case Event::Closed:
        return false;
      case Event::KeyPressed:
        if (event.key.code == Keyboard::Escape) { return false; }
        try {
          for(const auto& callback : onKeyPress.at(event.key.code)){
            callback();
          }
        }
        // If a key is pressed which is not binded, do nothing
        catch (const std::out_of_range& exc) {}
        break;
      case Event::MouseMoved:{
        double newX = event.mouseMove.x;
        double newY = event.mouseMove.y;
        // This method allows to move the mouse without rotating point of view
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
          double mouseDeltaPosX = newX - _lastMousePosX;
          double mouseDeltaPosY = newY - _lastMousePosY;
          rotateCamera(-mouseDeltaPosY * camViewVel, mouseDeltaPosX * camViewVel);
        }
        _lastMousePosX = newX;
        _lastMousePosY = newY;
        break;
      }
      default:
        //Do nothing
        break;
      }
      return true;
    }

    void Viewer::rotateCamera(double pitch, double yaw)
    {
      Eigen::Vector3d camLat = _camView.cross(Eigen::Vector3d(0.0, 0.0, 1.0));
      Eigen::Vector3d camUp = _camView.cross(camLat);
      _camView = Eigen::AngleAxisd(pitch, camLat).toRotationMatrix()*_camView;
      _camView = Eigen::AngleAxisd(yaw, camUp).toRotationMatrix()*_camView;
      _camView.normalize();
    }

    void Viewer::depthMove(double move)
    {
      _camPos += move *_camView;
    }

    void Viewer::lateralMove(double move)
    {
      Eigen::Vector3d camLat = _camView.cross(Eigen::Vector3d(0.0, 0.0, 1.0));
      _camPos += move * camLat;
    }

    void Viewer::forwardMove()
    {
      depthMove(camPosVel);
    }

    void Viewer::backwardMove()
    {
      depthMove(-camPosVel);
    }

    void Viewer::leftMove()
    {
      lateralMove(-camPosVel);
    }

    void Viewer::rightMove()
    {
      lateralMove(camPosVel);
    }

    bool Viewer::update()
    {
      //Handle events
      Event event;
      while (_window.pollEvent(event)) {
        if (!treat(event)) { return false;};
      }

      //Camera
      updateCamera();

      //Drawing
      drawGround(groundSize);
    
      //Update drawing
      _window.display();
      //Reset drawing
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
      return true;
    }

    void Viewer::drawBox(const Eigen::Vector3d& size,
                         const Eigen::Vector3d& center, 
                         const Eigen::Matrix3d& orientation,
                         const Color& c,
                         bool wireFrame)
    {
      glPushMatrix();
      {
        glTranslated(center.x(), center.y(), center.z());
        applyRotation(orientation.transpose());
        glScaled(size.x(), size.y(), size.z());
        glLineWidth(wireThickness);
        drawCube(c, wireFrame);
      }
      glPopMatrix();
    }
        
    void Viewer::updateCamera()
    {
      Eigen::Vector3d viewPoint = _camPos + _camView;
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(
        _camPos.x(), _camPos.y(), _camPos.z(), 
        viewPoint.x(), viewPoint.y(), viewPoint.z(), 
        0.0, 0.0, 1.0);
    }
        
    void Viewer::applyRotation(const Eigen::Matrix3d& orientation)
    {
      GLfloat m[16];
      m[0] = orientation(0, 0);
      m[1] = orientation(1, 0);
      m[2] = orientation(2, 0);
      m[3] = 0.0;
      m[4] = orientation(0, 1);
      m[5] = orientation(1, 1);
      m[6] = orientation(2, 1);
      m[7] = 0.0;
      m[8] = orientation(0, 2);
      m[9] = orientation(1, 2);
      m[10] = orientation(2, 2);
      m[11] = 0.0;
      m[12] = 0.0;
      m[13] = 0.0;
      m[14] = 0.0;
      m[15] = 1.0;
      glMultMatrixf(m);
    }
        
    void Viewer::drawGround(double size)
    {
      double groundStep = size / groundSquares;
      glLineWidth(groundThickness);
      for (double x=-size;x<=size;x+=2.0*groundStep) {
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(x, -size, 0.0);
        glVertex3f(x, size, 0.0);
        glEnd();
      }
      for (double y=-size;y<=size;y+=2.0*groundStep) {
        glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(-size, y, 0.0);
        glVertex3f(size, y, 0.0);
        glEnd();
      }
    }
        
    void Viewer::drawCube(const Color& c, bool isWireFrame)
    {
      // Lazy init of point vector
      static std::vector<Eigen::Vector3d> points;
      if (points.size() == 0) {
        // drawing cube faces
        for (size_t face = 0; face < 6; face++) {
          // Choose which axis are moving for the current face
          size_t staticAxis = face % 3;
          std::vector<size_t> dynamicAxis;
          for (size_t axis = 0; axis < 3; axis++) {
            if (axis != staticAxis) {
              dynamicAxis.push_back(axis);
            }
          }
          // Add faces points to list
          double staticVal = face < 3 ? 0.5 : -0.5;
          for (size_t p = 0; p < 4; p++) {
            Eigen::Vector3d point;
            point(staticAxis) = staticVal;
            point(dynamicAxis[0]) = p < 2 ? 0.5 : -0.5;
            point(dynamicAxis[1]) = (p == 0 || p == 3) ? 0.5 : -0.5;
            points.push_back(point);
          }
        }
      }

      if (isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
      glBegin(GL_QUADS);
      // drawing cube faces
      for (size_t face = 0; face < 6; face++) {
        glColor3f(c.r, c.g, c.b);
        for (size_t pId = 0; pId < 4; pId++) {
          const auto& p = points[face * 4 + pId];
          glVertex3f(p.x(), p.y(), p.z());
        }
      }
      glEnd();
      if (isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      }
    }        
  }
}
