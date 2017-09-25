using namespace System;
using namespace System::Diagnostics::CodeAnalysis;
using namespace System::Reflection;
using namespace System::Runtime::InteropServices;
using namespace System::Security::Permissions;
using namespace System::Resources;

#if DEBUG
[assembly: AssemblyConfiguration("Debug")];
#else
[assembly: AssemblyConfiguration("Release")];
#endif

[assembly: AssemblyProduct("Fugro.OpenCV")];
[assembly: AssemblyVersion("1.0.1")];
[assembly: AssemblyCulture("")];

[assembly: AssemblyCompany("Fugro")];
[assembly: AssemblyCopyright("© Fugro. All rights reserved.")];
[assembly: AssemblyTrademark("Fugro OpenCV")];

#if NOT_CLS_COMPLIANT
[assembly: CLSCompliant(false)];
#else
[assembly: CLSCompliant(true)];
#endif

[assembly: ComVisible(false)];

[assembly: SuppressMessage("Microsoft.Design", "CA2210:AssembliesShouldHaveValidStrongNames")];
[assembly: NeutralResourcesLanguageAttribute("en" , UltimateResourceFallbackLocation::MainAssembly)];

[assembly: AssemblyTitle("Fugro.OpenCV" )];
[assembly: AssemblyDescription("A .Net wrapper for the OpenCV (Open Source Computer Vision) library")];