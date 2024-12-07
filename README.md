
# Conan-Qt-Cmake_MinGw-MSCV-Example
This simple project demonstrates how to use CMake, Conan, and Qt to end the struggle with libraries forever. ))))

Steps to Set Up the Project
Install Conan: Download and install Conan from conan.io/center. It is recommended to use the x64 version, not the Python version, on Windows.

Detect Conan Profile: Run the following command in your command prompt to detect the Conan profile:

`conan profile detect --force`

Move Profile Files: Move the generated profile files to C:\Users\<YourUsername>\.conan2\profiles and verify the paths if necessary.

Add Tools to System Path: Ensure that GCC, Ninja, CMake, and Nmake are added to your system's PATH environment variable.
![image](https://github.com/user-attachments/assets/68d593bf-2c90-4c97-80f3-d73fe98970b5)

Disable Unnecessary Settings: Disable any unnecessary settings as shown in the image below:
![image](https://github.com/user-attachments/assets/e128f638-57f3-4aa6-ae3e-7291263eb9f4)

Configure Kits: Check and configure your kits as shown in the image below, and enjoy your streamlined development process:
![image](https://github.com/user-attachments/assets/4725a314-e99c-4ace-8479-d27708185bad)

By following these steps, you should be able to set up and use this project without any issues. Happy coding!
