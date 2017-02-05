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
        private int progress = 0;
        static String[] symbols={"\\","|","/","--","\\","/","--"};
        String symbol = "\\";
        int calc = 0;
        private void Do_it(String directory)
        {
            progress++;
            label2.Text = "Processing... " + progress + " folders" +symbol;
            label2.Update();
            this.Refresh();
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
            button1.Enabled = false;
            timer1.Enabled = true;
            timer1.Start();
            this.Refresh();
            Thread th = new Thread(new ThreadStart(forThread));  
            th.Start();
    
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

        private void timer1_Tick(object sender, EventArgs e)
        {
            calc++;
            symbol = symbols[calc%7];

        }
        private void forThread()
        {
            Do_it(textBox1.Text);
            label2.Text = "Complete, processed " + progress + " folders";
            progress = 0;
            this.Refresh();
            button1.Enabled = true;
            timer1.Stop();
        }
    }
}
