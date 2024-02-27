namespace RemotePlay2
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.VolUpButton = new System.Windows.Forms.Button();
            this.VolDownButton = new System.Windows.Forms.Button();
            this.RewindButton = new System.Windows.Forms.Button();
            this.FastForwardButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // VolUpButton
            // 
            this.VolUpButton.Location = new System.Drawing.Point(32, 40);
            this.VolUpButton.Name = "VolUpButton";
            this.VolUpButton.Size = new System.Drawing.Size(138, 37);
            this.VolUpButton.TabIndex = 0;
            this.VolUpButton.Text = "音量アップ";
            this.VolUpButton.UseVisualStyleBackColor = true;
            this.VolUpButton.Click += new System.EventHandler(this.VolUpButton_Click);
            // 
            // VolDownButton
            // 
            this.VolDownButton.Location = new System.Drawing.Point(32, 101);
            this.VolDownButton.Name = "VolDownButton";
            this.VolDownButton.Size = new System.Drawing.Size(138, 37);
            this.VolDownButton.TabIndex = 1;
            this.VolDownButton.Text = "音量ダウン";
            this.VolDownButton.UseVisualStyleBackColor = true;
            this.VolDownButton.Click += new System.EventHandler(this.VolDownButton_Click);
            // 
            // RewindButton
            // 
            this.RewindButton.Location = new System.Drawing.Point(243, 40);
            this.RewindButton.Name = "RewindButton";
            this.RewindButton.Size = new System.Drawing.Size(77, 98);
            this.RewindButton.TabIndex = 2;
            this.RewindButton.Text = "<=";
            this.RewindButton.UseVisualStyleBackColor = true;
            this.RewindButton.Click += new System.EventHandler(this.RewindButton_Click);
            // 
            // FastForwardButton
            // 
            this.FastForwardButton.Location = new System.Drawing.Point(349, 40);
            this.FastForwardButton.Name = "FastForwardButton";
            this.FastForwardButton.Size = new System.Drawing.Size(77, 98);
            this.FastForwardButton.TabIndex = 3;
            this.FastForwardButton.Text = "=>";
            this.FastForwardButton.UseVisualStyleBackColor = true;
            this.FastForwardButton.Click += new System.EventHandler(this.FastForwardButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(505, 403);
            this.Controls.Add(this.FastForwardButton);
            this.Controls.Add(this.RewindButton);
            this.Controls.Add(this.VolDownButton);
            this.Controls.Add(this.VolUpButton);
            this.KeyPreview = true;
            this.Name = "Form1";
            this.Text = "Form1";
            this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Form1_KeyDown);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button VolUpButton;
        private System.Windows.Forms.Button VolDownButton;
        private System.Windows.Forms.Button RewindButton;
        private System.Windows.Forms.Button FastForwardButton;
    }
}