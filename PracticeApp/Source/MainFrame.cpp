#include "../JuceLibraryCode/JuceHeader.h"
#include "../Include/MainFrame.h"
#include "../Include/Application.h"
//
MainFrame::MainFrame(const String& name)
   : DocumentWindow(name, Desktop::getInstance().getDefaultLookAndFeel()
      .findColour(ResizableWindow::backgroundColourId),
      DocumentWindow::allButtons)
{
   String appName = String((std::wstring(L"Аудиоплеер")).c_str());
   //
   setName(appName);
   setUsingNativeTitleBar(true);
   setResizable(true, true);
   setResizeLimits(400, 600, 10000, 10000);
   //
   setOpaque(true);
   setContentOwned (new MainComponent(), false);
   setVisible(true);
}