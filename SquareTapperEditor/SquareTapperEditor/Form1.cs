using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Reflection;
using System.IO;

namespace SquareTapperEditor
{
    public partial class Form1 : Form
    {
        // Margins around owner drawn ComboBoxes.
        private const int MarginWidth = 1;
        private const int MarginHeight = 1;

        private List<ComboBox> MaskComboBoxes1;
        private List<ComboBox> MaskComboBoxes2;
        private List<Image> ButtonImages;

        public Form1()
        {
            InitializeComponent();

            Image[] maskImgases =
            {
                Properties.Resources.mask1,
                Properties.Resources.mask2,
                Properties.Resources.mask3,
                Properties.Resources.mask4,
                Properties.Resources.mask5,
            };

            MaskComboBoxes1 = new List<ComboBox>();
            MaskComboBoxes1.Add(comboBox1);
            MaskComboBoxes1.Add(comboBox3);
            MaskComboBoxes1.Add(comboBox5);
            MaskComboBoxes1.Add(comboBox7);
            MaskComboBoxes1.Add(comboBox9);
            MaskComboBoxes1.Add(comboBox11);
            MaskComboBoxes1.Add(comboBox13);
            MaskComboBoxes1.Add(comboBox15);
            MaskComboBoxes1.Add(comboBox17);
            MaskComboBoxes1.Add(comboBox19);
            MaskComboBoxes1.Add(comboBox21);
            MaskComboBoxes1.Add(comboBox23);
            MaskComboBoxes1.Add(comboBox25);
            MaskComboBoxes1.Add(comboBox27);
            MaskComboBoxes1.Add(comboBox29);

            MaskComboBoxes2 = new List<ComboBox>();
            MaskComboBoxes2.Add(comboBox2);
            MaskComboBoxes2.Add(comboBox4);
            MaskComboBoxes2.Add(comboBox6);
            MaskComboBoxes2.Add(comboBox8);
            MaskComboBoxes2.Add(comboBox10);
            MaskComboBoxes2.Add(comboBox12);
            MaskComboBoxes2.Add(comboBox14);
            MaskComboBoxes2.Add(comboBox16);
            MaskComboBoxes2.Add(comboBox18);
            MaskComboBoxes2.Add(comboBox20);
            MaskComboBoxes2.Add(comboBox22);
            MaskComboBoxes2.Add(comboBox24);
            MaskComboBoxes2.Add(comboBox26);
            MaskComboBoxes2.Add(comboBox28);
            MaskComboBoxes2.Add(comboBox30);

            foreach (Image img in maskImgases)
            {
                foreach (ComboBox cb in MaskComboBoxes1)
                    cb.Items.Add(img);

                foreach (ComboBox cb in MaskComboBoxes2)
                    cb.Items.Add(img);
            }

            foreach (ComboBox cb in MaskComboBoxes1)
            {
                cb.Visible = true;
                cb.SelectedIndex = 0;
                cb.MeasureItem += comboBox_MeasureItem;
                cb.DrawItem += comboBox_DrawItem;
                cb.SelectedValueChanged += comboBox_SelectedValueChanged;
            }

            foreach (ComboBox cb in MaskComboBoxes2)
            { 
                cb.Visible = false;
                cb.SelectedIndex = 0;
                cb.MeasureItem += comboBox_MeasureItem;
                cb.DrawItem += comboBox_DrawItem;
            }

            ButtonImages = new List<Image>();
            ButtonImages.Add(Properties.Resources.button2);
            ButtonImages.Add(Properties.Resources.button3);

            PictureBox[] picBoxes = { pictureBox1, pictureBox2, pictureBox3, pictureBox4, pictureBox5, pictureBox6, pictureBox7, pictureBox8, pictureBox9, pictureBox10, pictureBox11, pictureBox12, pictureBox13, pictureBox14, pictureBox15 };

            foreach (PictureBox pc in picBoxes)
            {
                pc.Tag = 0;
                pc.Image = ButtonImages[0];
                pc.Click += pictureBox_Click;
                pc.Paint += pictureBox_Paint;
            }

            panel1.Tag = 0;
        }
        // ======================================== constructor end ==========================================

        private void redrawChart()
        {
            float[] yValues = new float[15];

            yValues[0] = getValueFromTextbox(textBox1);
            yValues[1] = getValueFromTextbox(textBox4);
            yValues[2] = getValueFromTextbox(textBox7);
            yValues[3] = getValueFromTextbox(textBox10);
            yValues[4] = getValueFromTextbox(textBox13);
            yValues[5] = getValueFromTextbox(textBox16);
            yValues[6] = getValueFromTextbox(textBox19);
            yValues[7] = getValueFromTextbox(textBox22);
            yValues[8] = getValueFromTextbox(textBox25);
            yValues[9] = getValueFromTextbox(textBox28);
            yValues[10] = getValueFromTextbox(textBox31);
            yValues[11] = getValueFromTextbox(textBox34);
            yValues[12] = getValueFromTextbox(textBox37);
            yValues[13] = getValueFromTextbox(textBox40);
            yValues[14] = getValueFromTextbox(textBox43);

            chart1.Series[0].Points.DataBindY(yValues);
        }

        private void handleTextChanges(object sender, EventArgs e)
        {
            TextBox argTextbox = sender as TextBox;
            argTextbox.Text = argTextbox.Text.Replace(".", ",");

            if (argTextbox.Text.Length == 2 && argTextbox.Text.StartsWith(","))
            {
                argTextbox.Text = argTextbox.Text.Insert(0, "0");
                argTextbox.SelectionStart = 3;
                argTextbox.SelectionLength = 0;
            }

            redrawChart();
        }

        private void handleKeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == '.')
                e.KeyChar = ',';

            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar) && (e.KeyChar != ','))
            {
                e.Handled = true;
            }

            // only allow one decimal point
            if ((e.KeyChar == ',') && ((sender as TextBox).Text.IndexOf(',') > -1))
            {
                e.Handled = true;
            }
        }

        private float getValueFromTextbox(TextBox argTextbox)
        {
            return (argTextbox.Text.Length > 0 && argTextbox.Text != ",") ? float.Parse(argTextbox.Text) : 0.0f;
        }

        private void comboBox_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index < 0) return;

            e.DrawBackground();

            ComboBox cbo = sender as ComboBox;
            Image img = (Image)cbo.Items[e.Index];
            float hgt = e.Bounds.Height - 2 * MarginHeight;
            float scale = hgt / img.Height;
            float wid = img.Width * scale;
            RectangleF rect = new RectangleF(e.Bounds.X + MarginWidth, e.Bounds.Y + MarginHeight, wid, hgt);
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBilinear;
            e.Graphics.DrawImage(img, rect);
        }

        private void comboBox_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            if (e.Index < 0) return;

            ComboBox cbo = sender as ComboBox;
            Image img = (Image)cbo.Items[e.Index];
            e.ItemHeight = img.Height + 2 * MarginHeight;
            e.ItemWidth = img.Width + 2 * MarginWidth;
        }

        private void comboBox_SelectedValueChanged(object sender, EventArgs e)
        {
            ComboBox cbo1 = sender as ComboBox;
            ComboBox cbo2 = MaskComboBoxes2[MaskComboBoxes1.IndexOf(cbo1)];

            if (cbo1.SelectedIndex > 0)
            {
                cbo2.Visible = true;
            }
            else
            {
                if (cbo2.SelectedIndex > 0)
                {
                    cbo1.SelectedIndex = cbo2.SelectedIndex;
                    cbo2.SelectedIndex = 0;
                }
                else
                {
                    cbo2.Visible = false;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Button button = sender as Button;

            button.ImageIndex = (button.ImageIndex + 1) % button.ImageList.Images.Count;
        }

        private void pictureBox_Click(object sender, EventArgs e)
        {
            PictureBox picBox = sender as PictureBox;

            int tag = (int)picBox.Tag;
            tag = (tag + 1) % ButtonImages.Count;
            picBox.Tag = tag;

            picBox.Image = ButtonImages[tag];
        }


        private void pictureBox_Paint(object sender, PaintEventArgs e)
        {
            PictureBox pc = sender as PictureBox;

            

            Pen pen = new Pen(Color.FromArgb(255, 255, 0, 0));
            pen.Width = 3.0f;
            e.Graphics.DrawLine(pen, 20 - pc.Location.X, 10 - pc.Location.Y, 300 - pc.Location.X, 100 - pc.Location.Y);

        }
    }
}
