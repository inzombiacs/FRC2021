// Header for the main robot file
#include <frc/Compressor.h>
#include <frc/I2C.h>
#include <frc/Timer.h>
#include <iostream>
#include <cstdlib>
#include <frc/DriverStation.h>
#include <frc/Joystick.h>
#include <frc/PWMVictorSPX.h>
#include <frc/TimedRobot.h>
#include <frc/drive/MecanumDrive.h>
#include "Pixy2.c"
#include "ADIS16448_IMU.h"
#include <frc/Solenoid.h>
#include <frc/Encoder.h>

class Robot : public frc::TimedRobot {
public:
    void RobotInit() override;
    void RobotPeriodic() override;
    void DisabledInit() override;
    void DisabledPeriodic() override;
    void AutonomousInit() override;
    void AutonomousPeriodic() override;
    void TeleopInit() override;
    void TeleopPeriodic() override;
    void TestPeriodic() override;
    void TrackBall();
 
private:
    frc::DriverStation& ds = frc::DriverStation::GetInstance();
    frc::ADIS16448_IMU imu{};
    
    //Preset belt speed
    const double belt_speed = 0.75;
    // Ball tracking
    Pixy2 pixy2;
    bool trackState = true;
    // Predetermined number of pixels allowable for ball pickup
    static constexpr int ballOffset = 20;
    // Middle of the Pixy2 frame
    static constexpr int pixyMid = 168;
    static constexpr int noBall = -168;


    // Joysticks
    static constexpr int kJoystickChannel = 0;
    static constexpr int kAltJoystickChannel = 1;
    frc::Joystick m_stick{kJoystickChannel};
    frc::Joystick m_alt{kAltJoystickChannel};

    //Prime Joystick Buttons
    static constexpr int kJoystickButtonX = 1;
    static constexpr int kJoystickButtonA = 2;
    static constexpr int kJoystickButtonB = 3;
    static constexpr int kJoystickButtonY = 4;
    static constexpr int kJoystickButtonLB = 5;
    static constexpr int kJoystickButtonRB = 6;
    static constexpr int kJoystickButtonLT = 7;
    static constexpr int kJoystickButtonRT = 8;
    static constexpr int kJoystickButtonBack = 9;
    static constexpr int kJoystickButtonStart = 10;
    static constexpr int kJoystickButtonLStick = 11;    
    static constexpr int kJoystickButtonRStick = 12;

    int m_XButton = 0;
    int m_AButton = 0;
    int m_BButton = 0;
    int m_YButton = 0;
    int m_LBButton = 0;
    int m_RBButton = 0;
    int m_LTButton = 0;
    int m_RTButton = 0;
    int m_BackButton = 0;
    int m_StartButton = 0;
    int m_LStickButton = 0;
    int m_RStickButton = 0;

    int m_BackButton_old = 0;
    int m_StartButton_old = 0;

    //Alternate Stick Buttons
    static constexpr int kAltJoystickEnableA = 1;
    static constexpr int kAltJoystickEnableB = 2;
    static constexpr int kAltJoystick6 = 6;
    static constexpr int kAltJoystick7 = 7;
    static constexpr int kAltJoystick8 = 8;
    static constexpr int kAltJoystick9 = 9;
    static constexpr int kAltJoystick10 = 10;
    static constexpr int kAltJoystick11 = 11;

    int m_altButton6 = 0;
    int m_altButton7 = 0;
    int m_altButton8 = 0;
    int m_altButton9 = 0;
    int m_altButton10 = 0;
    int m_altButton11 = 0;

    int m_altEnableA = 1;
    int m_altEnableB = 2;

/*
------------------------
    PWM DECLARATIONS
------------------------
*/
    // Drive Motors
    static constexpr int kFrontLeftChannel = 0;
    static constexpr int kRearLeftChannel = 1;
    static constexpr int kFrontRightChannel = 2;
    static constexpr int kRearRightChannel = 3;
    
    //Aux Motors
    static constexpr int kBeltChanel = 4;
     //i see both sides of the belt
    static constexpr int kWinchChannel = 5;
    static constexpr int kControlArmChannel = 6;

    //Motor Declarations
    frc::PWMVictorSPX m_frontLeft{kFrontLeftChannel};
    frc::PWMVictorSPX m_rearLeft{kRearLeftChannel};
    frc::PWMVictorSPX m_frontRight{kFrontRightChannel};
    frc::PWMVictorSPX m_rearRight{kRearRightChannel};
    frc::PWMVictorSPX m_belt{kBeltChanel};
    frc::PWMVictorSPX m_winch{kWinchChannel};
    frc::PWMVictorSPX m_controlArmSpinner{kControlArmChannel};

    //Solenoids
    frc::Solenoid m_mainArmsUp{1};
    frc::Solenoid m_mainArmsDown{6};
    frc::Solenoid m_backDoorDown{0};
    frc::Solenoid m_backDoorUp{7};   
    frc::Solenoid m_controlArmUp{2};
    frc::Solenoid m_controlArmDown{5};


    //Compressor & encoder
    frc::Compressor m_compressor{0};
    frc::Encoder encoderSpin{1,2};


    //13 colonies (the initial states of each subsystem being used)
    // driveState = False for no robot-oriented (default)
    // driveState = True for no field-oriented
    bool backState = 0;
    bool armState = 0;
    bool winchState = 0;
    bool controlState = 0;
    bool spinnerState = 0;
    int enableState = 0;

    bool cReading = 0;
    bool cState = 0;
    bool cPrevious = 0;
    bool driveState = false;
    frc::MecanumDrive m_robotDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};
    
};