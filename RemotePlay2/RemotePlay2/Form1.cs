using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace RemotePlay2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            U.AddCancelButton(this);
        }

        private void VolUpButton_Click(object sender, EventArgs e)
        {
            string destination = "\\\\192.168.10.10\\rti\\q\\q\\_VolUp.txt";
            U.TouchFile(destination);
        }

        private void VolDownButton_Click(object sender, EventArgs e)
        {
            string destination = "\\\\192.168.10.10\\rti\\q\\q\\_VolDown.txt";
            U.TouchFile(destination);
        }
        private void RewindButton_Click(object sender, EventArgs e)
        {
            string destination = "\\\\192.168.10.10\\rti\\q\\q\\_RewindKey.txt";
            U.TouchFile(destination);

        }

        private void FastForwardButton_Click(object sender, EventArgs e)
        {
            string destination = "\\\\192.168.10.10\\rti\\q\\q\\_FastForwardKey.txt";
            U.TouchFile(destination);

        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.W && e.Control)
            {
                e.Handled = true;
                this.Close();
            }
        }


    }
}
