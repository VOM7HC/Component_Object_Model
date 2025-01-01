using System.Runtime.InteropServices;

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("c58b7948-3551-4692-91e8-9b6ca7a53a5b")]
interface IHen
{
    [PreserveSig] void Cluck();
    [PreserveSig] void Roost();
}

[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
[Guid("f2cb310f-18d2-4c25-8474-c3d62bfdc22e")]
interface IHen2
{
    [PreserveSig] void Cluck();
    [PreserveSig] void Roost();
    [PreserveSig] void Forage();
}

class Application
{
    static void Main()
    {
        IHen hen = CreateHen();
        hen.Cluck();
        hen.Roost();

        IHen2 hen2 = (IHen2)hen;
        hen2.Forage();
    }

    // Need to add DLL native compiled same as folder managed
    [DllImport("COM_Essentials_One_DLL.dll", PreserveSig = false)]
    static extern IHen CreateHen();
}