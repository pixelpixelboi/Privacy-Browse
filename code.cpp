#include "include/cef_app.h"
#include "include/cef_browser.h"
#include "include/cef_client.h"

class SimpleClient : public CefClient {
public:
    SimpleClient() {}
    IMPLEMENT_REFCOUNTING(SimpleClient);
};

int main(int argc, char* argv[]) {
    // Chromium initialization
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefApp> app;

    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) return exit_code;

    CefSettings settings;
    settings.no_sandbox = true;
    CefInitialize(main_args, settings, app, nullptr);

    // Create browser window
    CefBrowserSettings browser_settings;
    CefWindowInfo window_info;

#if defined(OS_WIN)
    window_info.SetAsPopup(NULL, "Privacy & Browse");
#else
    window_info.SetAsPopup(0, "Privacy & Browse");
#endif

    CefRefPtr<SimpleClient> client(new SimpleClient());
    CefBrowserHost::CreateBrowser(window_info, client, "https://startpage.com", browser_settings, nullptr, nullptr);

    // Run event loop
    CefRunMessageLoop();
    CefShutdown();
    return 0;
}
