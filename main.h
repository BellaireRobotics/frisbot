#ifndef _MAIN_H
#define _MAIN_H

#include "WPILib.h"
//#include "vision_const.h"

/*
#include "IterativeRobot.h"
#include "Jaguar.h"
#include "Joystick.h"
#include "Relay.h"
#include "RobotDrive.h"
#include "SmartDashboard/SmartDashboard.h"
#include "Victor.h"
#include "Vision/AxisCamera.h"
*/

#define NORMALIZE(v) (-v + 1) / 2

class FrisBot : public IterativeRobot {
  RobotDrive *drive;
  Joystick *ljoy;
  Joystick *rjoy;

  Victor *shooter;
  Jaguar *feeder;
  Jaguar *tilter;

  SmartDashboard *dash;

  float shooter_speed;

public:
  FrisBot(void);

  void RobotInit(void);
  void DisabledInit(void);
  void AutonomousInit(void);
  void TeleopInit(void);
  void DisabledPeriodic(void);
  void AutonomousPeriodic(void);
  void TeleopPeriodic(void);
  void DisabledContinuous(void);
  void AutonomousContinuous(void);
  void TeleopContinuous(void);
};

#endif
