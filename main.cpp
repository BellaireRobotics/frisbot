#include "main.h"

FrisBot::FrisBot(void) {
  drive = new RobotDrive(1, 2); // (left channel, right channel)
  ljoy = new Joystick(1); // left joystick
  rjoy = new Joystick(2); // right joystick

  shooter = new Victor(4);

  tilter = new Relay(1);
  feeder = new Relay(2);
}

void FrisBot::RobotInit(void) {
  drive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
  drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

void FrisBot::DisabledInit(void) {
  // ...
}

void FrisBot::AutonomousInit(void) {
  // ...
}

void FrisBot::TeleopInit(void) {
  shooter_speed = 0.0;
}

void FrisBot::DisabledPeriodic(void) {
  // ...
}

void FrisBot::AutonomousPeriodic(void) {
  // ...
}

void FrisBot::TeleopPeriodic(void) {
  drive->TankDrive(ljoy, rjoy);

  if (rjoy->GetRawButton(8)) {
    shooter_speed = 0.0;
  } else if (rjoy->GetRawButton(4)) {
    shooter_speed = 0.7;
  } else if (rjoy->GetRawButton(3)) {
    shooter_speed = 0.8;
  } else if (rjoy->GetRawButton(5)) {
    shooter_speed = 0.9;
  } else if (rjoy->GetRawButton(2)) {
    shooter_speed = 1.0;
  }

  shooter->Set(shooter_speed);

  // Tilt
  if (ljoy->GetRawButton(3)) {
    tilter->Set(Relay::kReverse);
  } else if (ljoy->GetRawButton(2)) {
    tilter->Set(Relay::kForward);
  } else {
    tilter->Set(Relay::kOff);
  }

  // Feeder
  if (rjoy->GetTrigger()) {
    feeder->Set(Relay::kForward);
    Wait(0.17);
    feeder->Set(Relay::kOff);
    while (rjoy->GetTrigger())
      Wait(0.0001);
  } else if (ljoy->GetTrigger()) {
    feeder->Set(Relay::kReverse);
    Wait(0.1);
    feeder->Set(Relay::kOff);
    while (ljoy->GetTrigger())
      Wait(0.1);
  } else {
    feeder->Set(Relay::kOff);
  }
}

void FrisBot::DisabledContinuous(void) {
  // ...
}

void FrisBot::AutonomousContinuous(void) {
  // ...
}

void FrisBot::TeleopContinuous(void) {
  // ...
}

START_ROBOT_CLASS(FrisBot);
