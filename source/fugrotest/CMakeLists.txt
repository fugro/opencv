set(project_name Fugro.OpenCV.Test)

project(${project_name} VERSION 2.0.0 LANGUAGES CSharp)

include(CSharpUtilities)

add_library(${project_name} SHARED
	ContourTests.cs
	DoubleArrayTests.cs
	ImageArrayTests.cs
	KernelTests.cs
	Properties/AssemblyInfo.cs
)

csharp_set_designer_cs_properties(Properties/AssemblyInfo.cs)

set_property(TARGET ${project_name} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
set_property(TARGET ${project_name} PROPERTY WIN32_EXECUTABLE TRUE)

target_link_libraries(${project_name} 
			PUBLIC Fugro.OpenCV 
)
set_property(TARGET ${project_name} PROPERTY VS_PACKAGE_REFERENCES 
	"NUnit_3.10.1"
	"NUnit3TestAdapter_3.8.0")

set_target_properties(${project_name} PROPERTIES
  VS_DOTNET_REFERENCES_COPY_LOCAL OFF
)


set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR}/Release )
set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug )
set_target_properties(${project_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release )


set_property(TARGET ${project_name} PROPERTY VS_DOTNET_REFERENCES
	"PresentationCore"
	"System"
	"System.Core"
	"System.Data"
	"System.Data.DataSetExtensions"
	"System.Drawing"
	"System.Xml"
	"System.Xml.Linq"
	"WindowsBase")

set(NUGET "${CMAKE_SOURCE_DIR}/../Tools/nuget.exe")

add_custom_command(TARGET ${project_name}
    PRE_BUILD
    COMMAND ${NUGET} restore ${CMAKE_BINARY_DIR}/Fugro.OpenCV.sln
)