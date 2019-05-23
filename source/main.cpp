#pragma comment(lib, "WindowsApp")

#include <windows.h>

#ifdef GetCurrentTime
#undef GetCurrentTime
#endif

#include <winrt/Windows.Foundation.h>
// #include <winrt/Windows.Foundation.Collections.h>
// #include <winrt/Windows.System.h>
// #include <winrt/Windows.UI.Xaml.h>
// #include <winrt/Windows.UI.Xaml.Controls.h>
// #include <winrt/Windows.UI.Xaml.Hosting.h>
// #include <winrt/Windows.UI.Xaml.Media.h>
// #include <Windows.UI.Xaml.Hosting.DesktopWindowXamlSource.h>

using namespace winrt;
using namespace Windows::Foundation;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, LPWSTR, int)
{
    init_apartment(apartment_type::single_threaded);
    Uri uri(L"http://aka.ms/cppwinrt");
    ::MessageBoxW(::GetDesktopWindow(), uri.AbsoluteUri().c_str(), L"C++/WinRT Desktop Application", MB_OK);
}
