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

        public Form1()
        {
            InitializeComponent();

            Image[] imgs =
            {
                Properties.Resources.mask1,
                Properties.Resources.mask2,
                Properties.Resources.mask3,
                Properties.Resources.mask4,
                Properties.Resources.mask5,
            };

            ComboBox[] MaskComboBoxes1 = { comboBox1, comboBox3, comboBox5, comboBox7, comboBox9, comboBox11, comboBox13, comboBox15, comboBox17, comboBox19, comboBox21, comboBox23, comboBox25, comboBox27, comboBox29 };
            ComboBox[] MaskComboBoxes2 = { comboBox2, comboBox4, comboBox6, comboBox8, comboBox10, comboBox12, comboBox14, comboBox16, comboBox18, comboBox20, comboBox22, comboBox24, comboBox26, comboBox28, comboBox30 };

            foreach (Image img in imgs)
            {
                foreach (ComboBox cb in MaskComboBoxes1)
                    cb.Items.Add(img);

                foreach (ComboBox cb in MaskComboBoxes2)
                    cb.Items.Add(img);
            }

            foreach (ComboBox cb in MaskComboBoxes1)
            {
                cb.SelectedIndex = 0;
                cb.MeasureItem += comboBox_MeasureItem;
                cb.DrawItem += comboBox_DrawItem;
                cb.Visible = true;
            }

            foreach (ComboBox cb in MaskComboBoxes2)
            {
                cb.SelectedIndex = 0;
                cb.MeasureItem += comboBox_MeasureItem;
                cb.DrawItem += comboBox_DrawItem;
                cb.Visible = false;
            }
        }

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

        private void comboBox1_SelectedValueChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex > 0)
            {
                comboBox2.Visible = true;
            }
            else
            {
                comboBox1.SelectedIndex = Math.Max(comboBox2.SelectedIndex, 0);
                comboBox2.Visible = false;
                comboBox2.SelectedIndex = 0;
            }
        }
    }
}
