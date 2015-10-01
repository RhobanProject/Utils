/**
 * Based on Leph::ModelViewer
 */

#pragma once

#include "Color.hpp"

#include <functional>
#include <map>

#include <SFML/Window.hpp>
#include <Eigen/Dense>

namespace Rhoban {
  namespace Viewer {

    /**
     * Viewer
     *
     * Simple OpenGL viewer, handles camera movement and ground drawing
     */
    class Viewer
    {
    protected:
      /**
       * Camera control config
       */
      double camPosVel = 0.05;
      double camViewVel = 0.01;

      // Ground properties
      double groundSize = 2.0;
      double groundThickness = 1.0;
      int groundSquares = 10;

      // Wire properties
      double wireThickness = 2.0;

      /**
       * Last recorded mouse position
       */
      int _lastMousePosX;
      int _lastMousePosY;

      /**
       * SFML Windows instance
       */
      sf::Window _window;

      /**
       * Camera position and view direction
       */
      Eigen::Vector3d _camPos;
      Eigen::Vector3d _camView;

      typedef std::function<void()> Callback;
      typedef std::vector<Callback> Callbacks;
      typedef std::map<sf::Keyboard::Key, Callbacks> CallbacksMap;

      CallbacksMap onKeyPress;
      CallbacksMap onKeyRelease;

      // Return false if the event means end of the Viewer
      bool treat(const sf::Event& event);

      // Camera moves
      void rotateCamera(double pitch, double yaw);
      void depthMove(double move);
      void lateralMove(double move);
      void forwardMove();
      void backwardMove();
      void leftMove();
      void rightMove();

    public:
      /**
       * Initialize SFML and OpenGL rendering
       * with optional windows size
       */
      Viewer(unsigned int width = 800, unsigned int height = 600);

      /**
       * Poll event and update screen drawing
       * return false on exit asked
       */
      bool update();

      /**
       * Draw a box with given size at
       * given center with given orientation
       * Optional parameters are:
       * - orientation
       * - box color
       * - wireframe
       */
      void drawBox(const Eigen::Vector3d& size,
                   const Eigen::Vector3d& center, 
                   const Eigen::Matrix3d& orientation = Eigen::Matrix3d::Identity(),
                   const Color& c = Color::gray,
                   bool wireFrame = true);

      /**
       * draw identity cube -0.5 to 0.5
       */
      void drawCube(const Color& c = Color::gray,
                    bool wireFrame = true);

    private:
      /**
       * Update the opengl camera
       */
      void updateCamera();

      /**
       * Convert given rotation matrix to
       * OpenGL and multiply current matrix with
       */
      void applyRotation(const Eigen::Matrix3d& orientation);

      /**
       * Draw ground centered on origin with
       * given size
       */
      void drawGround(double size);
    };
  }
}
