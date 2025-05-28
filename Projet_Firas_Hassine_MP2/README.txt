To get everything up and running on your machine, please follow these steps:

my project is in "patients" the others are external libraries
there are two sql files to create the database table for each part of the project

1. **Update the executable path in the launcher**  
   - Open `mainwindow.cpp` in the `man_sys` (launcher) project.  
   - Find the line with:

     QProcess::startDetached("C:/Users/.../Patients.exe");

   - Replace the path inside the quotes with the actual location of `Patients.exe` on your computer.  

2. **Build and run in Release mode first**  

3. ** Test in Debug mode**  

4. **Database configuration**  
   - Verify there is a User/System DSN named **Source_ProjetA2** using the same driver and connection details used in development.  

5. **Dependencies are already included**  
   - All required Qt DLLs and plugins have been bundled via `windeployqt`.  
   - OpenCV DLLs and `libZXing.dll` are present next to the executables.


Feel free to reach out if you run into any issues. Happy testing!
