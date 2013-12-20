#include "LeagueMaker.h"
#include <windows.h>
// Handler function will be called on separate thread!
static BOOL WINAPI console_ctrl_handler(DWORD dwCtrlType)
{
  switch (dwCtrlType)
  {
  case CTRL_C_EVENT: // Ctrl+C
    break;
  case CTRL_BREAK_EVENT: // Ctrl+Break
    break;
  case CTRL_CLOSE_EVENT: // Closing the console window
    break;
  case CTRL_LOGOFF_EVENT: // User logs off. Passed only to services!
    break;
  case CTRL_SHUTDOWN_EVENT: // System is shutting down. Passed only to services!
    break;
  }

  // Return TRUE if handled this message, further handler functions won't be called.
  // Return FALSE to pass this message to further handlers until default handler calls ExitProcess().
  return FALSE;
}

int main(int argc, char* argv[])
{
	 SetConsoleCtrlHandler(console_ctrl_handler, TRUE);

	LeagueMaker* league = new LeagueMaker();
	league->create_basketball_league();
	league->get_basketball_league()->start( argc,  argv);

	system("PAUSE");
	return 0;
}