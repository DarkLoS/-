using System;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
namespace WindowsFormsApplication2{
    public partial class Form1 : Form{
        public Form1(){
            InitializeComponent();
            string[] args = Environment.GetCommandLineArgs();
            if (args.Length > 1) textBox1.Text = args[1];
        }
        private int count = 0;
        private int progress = 0;
        private void Do_it(String directory){
            progress++;
            progressBar1.Value = progress * 100 / count;
            progressBar1.Update();
            Thread.Sleep(1);
            string[] files = Directory.GetFiles(directory);
            foreach (string s in Directory.GetDirectories(directory)){
                Do_it(s);
            }
            List<DateTime> dateCollection = new List<DateTime>();
            foreach (string file in files){
                FileInfo f_i = new FileInfo(file);
                DateTime dt = Convert.ToDateTime(f_i.LastWriteTime);
                dateCollection.Add(dt);
            }
            foreach (string s in Directory.GetDirectories(directory)){
                DirectoryInfo inf = new DirectoryInfo(s);
                DateTime dt = Convert.ToDateTime(inf.LastWriteTime);
                dateCollection.Add(dt);
            }
            if (dateCollection.Count > 0)
            {
                try
                {
                    DirectoryInfo inf = new DirectoryInfo(directory);
                    Directory.SetLastWriteTime(directory, dateCollection.Max());
                }
                catch (Exception e)
                {
                    MessageBox.Show("System.IO.IOException: Процесс не может получить доступ к файлу "+directory, "Alert", MessageBoxButtons.OK);       
                }
                
                
            }
        }
        private void button1_Click(object sender, EventArgs e){
            DirectoryInfo di = new DirectoryInfo(textBox1.Text);
            count = di.GetDirectories("*", SearchOption.AllDirectories).Length+1; 
            progressBar1.Visible = true;
            button1.Enabled = false;
            progressBar1.Value = 0;
            button1.Location = new System.Drawing.Point(12, button1.Location.Y + 30);
            button2.Location = new System.Drawing.Point(174, button2.Location.Y + 30);
            this.Refresh();
            Do_it(textBox1.Text);
            count = 0;
            progress = 0;
            button1.Location = new System.Drawing.Point(12, button1.Location.Y - 30);
            button2.Location = new System.Drawing.Point(174, button2.Location.Y - 30);
            this.Refresh();
            progressBar1.Visible = false;
            button1.Enabled=true;
        }
        private void button2_Click(object sender, EventArgs e){
            Application.Exit();
        }

        private void textBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter)
            {
                button1.PerformClick();
            }
        }
    }
}
