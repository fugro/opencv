Write-Host "Fugro.OpenCV clean script"

if((Test-Path -Path 'bld'))
{
	Remove-Item -Path 'bld' -Recurse -Force
}