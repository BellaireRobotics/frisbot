#include "main.h"

FrisBot::FrisBot(void) {
  drive = new RobotDrive(1, 2); // (left channel, right channel)
  ljoy = new Joystick(1); // left joystick
  rjoy = new Joystick(2); // right joystick

  shooter = new Victor(4);
  feeder = new Jaguar(5);
  tilter = new Jaguar(6);

  ledring = new Relay(4, Relay::kForwardOnly);
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
  done = 0;
}

void FrisBot::TeleopInit(void) {
  drivemode = LEFT_HAND_DRIVE;
  shooter_speed = 0.0;
  ledring_state = ON;
}

void FrisBot::DisabledPeriodic(void) {
  // ...
}

void FrisBot::AutonomousPeriodic(void) {
  int i = 0;

  if (!done) {
    ledring->Set(Relay::kOn);

    shooter->Set(1.0);
    tilter->Set(-1.0);
    Wait(7.0);
    tilter->Set(0.0);

    for (i = 0; i < 2; i++) {
      feed();
      Wait(2.0);
    }

    shooter->Set(0.0);

    tilter->Set(1.0);
    Wait(4.0);
    tilter->Set(0.0);

    ledring->Set(Relay::kOff);

    done = 1;
  }
}

void FrisBot::TeleopPeriodic(void) {
  // DriveMode Setter
  if (ljoy->GetRawButton(11)) {
    drivemode = RIGHT_HAND_DRIVE;
  } else if (ljoy->GetRawButton(10)) {
    drivemode = LEFT_HAND_DRIVE;
  }

  // Drive
  //drive->TankDrive(ljoy, rjoy, true); // Old tank drive
  if (drivemode == RIGHT_HAND_DRIVE) {
    drive->ArcadeDrive(ljoy, Joystick::kDefaultYAxis, rjoy, Joystick::kDefaultXAxis);
  } else if (drivemode == LEFT_HAND_DRIVE) {
    drive->ArcadeDrive(rjoy, Joystick::kDefaultYAxis, ljoy, Joystick::kDefaultXAxis);
  } else {
    drive->ArcadeDrive(ljoy, Joystick::kDefaultYAxis, rjoy, Joystick::kDefaultXAxis);
  }

  // Shooter
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
  if (ljoy->GetRawButton(2)) {
    tilter->Set(1.0);
  } else if (ljoy->GetRawButton(3)) {
    tilter->Set(-1.0);
  } else {
    tilter->Set(0.0);
  }

  // Feeder
  if (ljoy->GetTrigger() || rjoy->GetTrigger()) {
    feed();
  } else if (ljoy->GetRawButton(6)) {
    feeder->Set(1.0);
  } else if (ljoy->GetRawButton(7)) {
    feeder->Set(-1.0);
  } else {
    feeder->Set(0.0);
  }

  // LED Ring
  if (ljoy->GetRawButton(8)) {
    ledring_state = 1;
  } else if (ljoy->GetRawButton(9)) {
    ledring_state = 0;
  }

  if (ledring_state) {
    ledring->Set(Relay::kOn);
  } else {
    ledring->Set(Relay::kOff);
  }
}

void FrisBot::DisabledContinuous(void) {
  if (ledring->Get() == Relay::kOn) {
    ledring->Set(Relay::kOff);
  } else {
    ledring->Set(Relay::kOn);
  }

  Wait(0.3);
}

void FrisBot::AutonomousContinuous(void) {
  // ...
}

void FrisBot::TeleopContinuous(void) {
}

void FrisBot::feed(void) {
  feeder->Set(1.0);
  Wait(0.3);
  feeder->Set(-1.0);
  Wait(0.3);
  feeder->Set(0.0);
}

START_ROBOT_CLASS(FrisBot);
