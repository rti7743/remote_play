using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Secretbro2
{
    using System.Diagnostics;

    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length <= 0)
            {
                Process.Start("chrome.exe", "--incognito --disable-session-crashed-bubble --disable-infobars");
                return;
            }
            string filePath = string.Join(" ",args);
            string url = GetURL(filePath);
            if (IsSteamURL(url))
            {
                Process.Start("explorer.exe", url);
                return;
            }
            if (url != "")
            {
                Process.Start("chrome.exe", "--incognito --disable-session-crashed-bubble --disable-infobars " + url);
                return;
            }
            Process.Start("chrome.exe", "--incognito --disable-session-crashed-bubble --disable-infobars \"" + filePath + "\"");
        }

        static bool IsSteamURL(string url)
        {
            if (url.IndexOf("steam://") >= 0)
            {
                return true;
            }
            return false;
        }

        static string GetURL(string filePath)
        {
            string fileExtension = Path.GetExtension(filePath);

            if (fileExtension != ".url")
            {
                return "";
            }

            string[] lines = File.ReadAllLines(filePath);

            foreach (string line in lines)
            {
                if (line.StartsWith("URL="))
                {
                    string url = line.Substring(4);
                    return url;
                }
            }
            return "";
        }   
    }
}
