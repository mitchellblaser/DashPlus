# DashPlus

###### An alternative to the WPILib SmartDashboard.

#### Installation Instructions:

For client-side installation (on your driver station), just go to the releases page, and download the latest Win64 binary.

To install the ``DashPlusServer`` class in your FRC Project, follow the instructions below.

1. Copy ``DashPlusServer.cpp`` to the cpp folder of your FRC project.

2. Copy ``DashPlusServer.h`` to the include folder of your FRC project.

3. In ``RobotContainer.h``, ``include <DashPlusServer.h>``,  and make a public instance of a DashPlusServer.

   ```c++
   //RobotContainer.h
   #include <DashPlusServer.h>
   class RobotContainer {
       public:
       	RobotContainer();
       	DashPlusServer dashPlusServer;
   ```

4. In the ``RobotContainer`` Constructor inside ``RobotContainer.cpp``, add the following:

   ```c++
   //RobotContainer.cpp
   RobotContainer::RobotContainer() :
   dashPlusServer{}    
   {
       //constructor code here, send a value with:
       dashPlusServer.sendInteger("Key", 5);
   }
   ```

5. You can create the ``dashPlusServer`` in any command you like and push values.

