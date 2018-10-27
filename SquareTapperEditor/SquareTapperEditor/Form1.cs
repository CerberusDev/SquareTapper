using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SquareTapperEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            comboBox1.Items.Add("test1");
            comboBox1.Items.Add("test2");
            comboBox1.Items.Add("test3");
            comboBox1.Items.Add("test4");

            comboBox1.SelectedIndex = 0;

            //comboBox1.displa
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
    }
}
