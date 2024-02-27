using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;
using System.Net;
using System.Net.Sockets;
using System.Net.NetworkInformation;
using System.Text.RegularExpressions;
using System.Runtime.InteropServices;


namespace RemotePlay2
{
    class U
    {
        public static void AddCancelButton(Form f)
        {
            if (f.CancelButton != null)
            {
                return;
            }
            Button cancelButton = new Button();
            cancelButton.Click += (Object Sender, EventArgs e) =>
            {
                f.DialogResult = DialogResult.Cancel;
                f.Close();
            };
            f.DialogResult = DialogResult.Cancel;
            f.CancelButton = cancelButton;
        }
        public static void TouchFile(string filename)
        {
            try
            {
                if (System.IO.File.Exists(filename))
                {
                    System.IO.File.Delete(filename);
                }

                System.IO.File.WriteAllText(filename, "");
            }
            catch (Exception)
            {
            }

        }
        public static void SendWakeOnLanNoError(string remoteIP)
        {
            try
            {
                SendWakeOnLan(remoteIP);
            }
            catch(Exception)
            {
            }
        }

        public static void SendWakeOnLan(string remoteIP)
        {
            // ブロードキャストアドレスとポート番号
            string remoteHost = "255.255.255.255";
            int remotePort = 9;

            // IPアドレスからMACアドレスを調べる
            string remoteMAC = GetMacAddress(remoteIP);

            // UDPクライアントを作成
            UdpClient udp = new UdpClient();

            // マジックパケットを作成
            byte[] sendBytes = new byte[102];
            for (int i = 0; i < 6; i++)
            {
                sendBytes[i] = 0xFF;
            }
            string[] macDigits = remoteMAC.Split('-');
            for (int i = 0; i < 16; i++)
            {
                for (int j = 0; j < 6; j++)
                {
                    sendBytes[i * 6 + j + 6] = Convert.ToByte(macDigits[j], 16);
                }
            }

            // マジックパケットを送信
            udp.Send(sendBytes, sendBytes.Length, remoteHost, remotePort);

            // ソケットを閉じる
            udp.Close();
        }

        // SendARP APIをインポートする
        [DllImport("iphlpapi.dll", ExactSpelling = true)]
        public static extern int SendARP(int DestIP, int SrcIP, byte[] pMacAddr, ref uint PhyAddrLen);

        // IPアドレスからMACアドレスを調べるメソッド
        private static string GetMacAddress(string ip)
        {
            // IPアドレスをint型に変換する
            int destIP = BitConverter.ToInt32(IPAddress.Parse(ip).GetAddressBytes(), 0);

            // MACアドレスを格納するバイト配列を作成する
            byte[] macAddr = new byte[6];
            uint macAddrLen = (uint)macAddr.Length;

            // SendARPメソッドを呼び出す
            int result = SendARP(destIP, 0, macAddr, ref macAddrLen);

            // 戻り値が0でなければ、例外を投げる
            if (result != 0)
            {
                throw new Exception("MACアドレスが見つかりませんでした。");
            }

            // MACアドレスを文字列に変換する
            string macAddress = BitConverter.ToString(macAddr, 0, (int)macAddrLen);

            // MACアドレスを返す
            return macAddress;
        }

    }
}
