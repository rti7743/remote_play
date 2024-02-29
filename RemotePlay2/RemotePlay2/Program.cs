using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices; // DLL Import

namespace RemotePlay2
{
    using System;
    using System.IO;
    using IWshRuntimeLibrary;

    class Program
    {
        static void Main(string[] args)
        {

            if (args.Length >= 1)
            {
                string filename = args[0];
                string extension = Path.GetExtension(filename);
                FileInfo fileinfo = new FileInfo(filename);

                if (extension == ".url" || fileinfo.Length <= 1024 * 1024 * 1)
                {
                    string destination = "\\\\192.168.10.10\\rti\\q\\q\\" + Path.GetFileName(filename);
                    U.WakeUpHost(destination);
                    U.CopyFile(filename, destination);
                }
                else
                {
                    string shortcut = "\\\\192.168.10.10\\rti\\q\\q\\" + Path.GetFileNameWithoutExtension(filename) + ".lnk";
                    U.WakeUpHost(shortcut);
                    U.MakeShortcut(filename, shortcut);
                }
            }

            Form1 f = new Form1();
            f.ShowDialog();
        }
    }
}