mkdir build64
.\fugro-opencv-dotnet\tools\bin\cmake.exe -G "Visual Studio 15 2017 Win64" -S ./source/fugro-opencv-dotnet/ -B ./bld
.\fugro-opencv-dotnet\tools\bin\cmake.exe cmake --build ./bld --config Release

"C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe" Fugro.OpenCV.sln /t:Build /p:Configuration=Release /p:TargetFramework=v4.5

CMAKE_MAKE_PROGRAM
