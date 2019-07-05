Write-Host "Fugro.OpenCV build script"

if(!(Test-Path -Path 'bld'))
{
	New-Item -Path 'bld' -ItemType Directory
}

$command = '.\tools\bin\cmake.exe -G "Visual Studio 15 2017 Win64" -S ./source -B ./bld'
iex $command

