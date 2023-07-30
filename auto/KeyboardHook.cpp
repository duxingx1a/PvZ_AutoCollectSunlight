#include <KeyboardHook.h>
#include <KeyCapturer.h>
#include <QtDebug>
#include <Windows.h>
LRESULT CALLBACK KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam);

HMODULE WINAPI ModuleFromAddress(PVOID pv);
static HHOOK hHook;

LRESULT KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *Key_Info = (KBDLLHOOKSTRUCT*)lParam;
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
    {
        qDebug() << Key_Info->vkCode;
//        if (Key_Info->vkCode == VK_ESCAPE) {
//            shouldExit = TRUE; // 设置终止标志
//        }
        if(KeyCapturer::instance())
        {
            KeyCapturer::instance()->setkeyValue(Key_Info->vkCode);
        }
    }
    // 调用下一个钩子或默认钩子处理程序
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}
HMODULE ModuleFromAddress(PVOID pv)
{
    MEMORY_BASIC_INFORMATION mbi;
    if(VirtualQuery(pv,&mbi,sizeof(mbi))!=0)
    {
        return (HMODULE)mbi.AllocationBase;
    }
    else
        return NULL;
}

int startHook()
{
    hHook =SetWindowsHookExW(WH_KEYBOARD_LL,KeyboardHookCallback,ModuleFromAddress((PVOID)KeyboardHookCallback),0);
    int error = GetLastError();
    return error;
}

bool stopHook()
{
    return UnhookWindowsHookEx(hHook);
}

