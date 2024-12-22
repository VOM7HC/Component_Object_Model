using System.Runtime.InteropServices;

class Application
{
    static void Main()
    {
        HenCluck();
    }

    // Need to add DLL native compiled same as folder managed
    [DllImport("COM_Essentials_One_DLL.dll")]
    static extern void HenCluck();
}