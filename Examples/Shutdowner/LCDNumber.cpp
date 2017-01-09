#include "LCDNumber.h"

#include <QDebug>
#include <QApplication>

#if defined(Q_OS_UNIX)
#include <QLibrary>
#include <QtX11Extras/QX11Info>
#include <X11/Xutil.h>
#elif defined(Q_OS_WIN)
#include <windows.h>
#endif // Q_OS_MACRO

LCDNumber::LCDNumber(QWidget *parent)
    : QLCDNumber(parent)
{
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setDisplay()));
}

LCDNumber::~LCDNumber()
{
    // Empty destructor
}

void LCDNumber::setDisplay()
{
    if ((idleTime() < 1000) && !firstTick) {
        qApp->exit();
    }
    if (timeEnd == 0) {
        shutDownComputer();
        qApp->exit();
    }
    // qDebug() << timeEnd << idleTime();
    this->timeValue->setHMS(0,this->timeValue->addSecs(-1).minute(),this->timeValue->addSecs(-1).second());
    this->display(this->timeValue->toString());
    timeEnd -= 1;
    firstTick = false;
}

void LCDNumber::set_Time(int minutes, int seconds)
{
    timeValue = new QTime(0, minutes, seconds);
    this->display(timeValue->toString());
    timeEnd = minutes * 60 + seconds;
    firstTick = true;
}

void LCDNumber::start_Timer(int sec)
{
    timer->start(sec);
}

#if defined(Q_OS_UNIX)
bool LCDNumber::shutDownComputer()
{
    system("systemctl poweroff");
    return true;
}

typedef struct {
    Window  window;     /* screen saver window - may not exist */
    int     state;      /* ScreenSaverOff, ScreenSaverOn, ScreenSaverDisabled*/
    int     kind;       /* ScreenSaverBlanked, ...Internal, ...External */
    unsigned long    til_or_since;   /* time til or since screen saver */
    unsigned long    idle;      /* total time since last user input */
    unsigned long   eventMask; /* currently selected events for this client */
} XScreenSaverInfo;

typedef XScreenSaverInfo* (*XScreenSaverAllocInfo)();
typedef Status (*XScreenSaverQueryInfo)(Display* display, Drawable* drawable, XScreenSaverInfo* info);

static XScreenSaverAllocInfo _xScreenSaverAllocInfo = 0;
static XScreenSaverQueryInfo _xScreenSaverQueryInfo = 0;

uint LCDNumber::idleTime()
{
    static bool xssResolved = false;
    if (!xssResolved) {
        QLibrary xssLib(QLatin1String("Xss"), 1);
        if (xssLib.load()) {
            _xScreenSaverAllocInfo = (XScreenSaverAllocInfo) xssLib.resolve("XScreenSaverAllocInfo");
            _xScreenSaverQueryInfo = (XScreenSaverQueryInfo) xssLib.resolve("XScreenSaverQueryInfo");
            xssResolved = true;
        }
    }

    uint idle = 0;
    if (xssResolved)
    {
        XScreenSaverInfo* info = _xScreenSaverAllocInfo();
        const int screen = QX11Info::appScreen();
        Qt::HANDLE rootWindow = (void *) QX11Info::appRootWindow(screen);
        _xScreenSaverQueryInfo(QX11Info::display(), (Drawable*) rootWindow, info);
        idle = info->idle;
        if (info)
            XFree(info);
    }
    return idle;
}
#elif defined(Q_OS_WIN)
bool LCDNumber::shutDownComputer()
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    // Get a token for this process.

    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
        return( FALSE );

    // Get the LUID for the shutdown privilege.

    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
                         &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;  // one privilege to set
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    // Get the shutdown privilege for this process.

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
                          (PTOKEN_PRIVILEGES)NULL, 0);

    if (GetLastError() != ERROR_SUCCESS)
        return FALSE;

    // Shut down the system and force all applications to close.

    if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
                       SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
                       SHTDN_REASON_MINOR_UPGRADE |
                       SHTDN_REASON_FLAG_PLANNED))
        return FALSE;

    //shutdown was successful
    return TRUE;
}

uint LCDNumber::idleTime()
{
    uint idle = -1;
    LASTINPUTINFO info;
    info.cbSize = sizeof(LASTINPUTINFO);
    if (::GetLastInputInfo(&info))
        idle = ::GetTickCount() - info.dwTime;
    return idle;
}
#endif // Q_OS_MACRO
