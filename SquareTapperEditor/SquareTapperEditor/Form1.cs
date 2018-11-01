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

            int i = 0;

            foreach (PictureBox pc in picBoxes)
            {
                pc.Tag = new ButtonData(i++);
                pc.Image = ButtonImages[0];
                pc.Click += pictureBox_Click;
                pc.Paint += pictureBox_Paint;
                pc.MouseMove += pictureBox_MouseMove;
                pc.DoubleClick += pictureBox_DoubleClick;
            }

            panel1.Tag = new List<LineData>();

            redrawChart();
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

        private void pictureBox_Click(object sender, EventArgs e)
        {
            PictureBox picBox = sender as PictureBox;
            MouseEventArgs me = e as MouseEventArgs;

            if (me.Button == MouseButtons.Left)
            {
                ButtonData bt = (picBox.Tag) as ButtonData;
                bt.bDoubleTap = !bt.bDoubleTap;

                picBox.Image = bt.bDoubleTap ? ButtonImages[1] : ButtonImages[0];
            }
            else if (me.Button == MouseButtons.Right)
            {
                ButtonData bd = (picBox.Tag) as ButtonData;
                List<LineData> ldList = (panel1.Tag) as List<LineData>;

                if (ldList.Count == 0 || ldList.Last().bFinished)
                {
                    if (CanAddAnotherLineHere(ldList, bd.Index))
                    {
                        LineData ld = new LineData();

                        ld.LineStartLocation = new Point(picBox.Location.X + picBox.Width / 2, picBox.Location.Y + picBox.Height / 2);
                        ld.LineEndLocation = new Point(me.Location.X + picBox.Location.X, me.Location.Y + picBox.Location.Y);
                        ld.StartButtonIndex = ((picBox.Tag) as ButtonData).Index;
                        ldList.Add(ld);
                    }
                }
                else
                {
                    LineData ld = ldList.Last();
                    ld.LineEndLocation = new Point(picBox.Location.X + picBox.Width / 2, picBox.Location.Y + picBox.Height / 2);

                    if (bd.Index != ld.StartButtonIndex && CanAddAnotherLineHere(ldList, bd.Index) && IsLineLengthOkay(ld.LineStartLocation, ld.LineEndLocation, picBox.Width))
                    {
                        ld.bFinished = true;
                        ld.EndButtonIndex = bd.Index;
                    }
                    else
                    {
                        ldList.Remove(ld);
                    }

                    panel1.Refresh();
                }
            }
        }

        private bool CanAddAnotherLineHere(List<LineData> ldList, int buttonIdx)
        {
            int Count = 0;

            foreach (LineData ld in ldList)
            {
                if (ld.StartButtonIndex == buttonIdx || ld.EndButtonIndex == buttonIdx)
                    Count++;
            }

            return Count < 2;
        }

        private bool IsLineLengthOkay(Point Start, Point End, int buttonSize)
        {
            int X = Start.X - End.X;
            int Y = Start.Y - End.Y;
            int Z = (int)(buttonSize * 1.2f);
            return X * X + Y * Y < Z * Z;
        }

        private void pictureBox_DoubleClick(object sender, EventArgs e)
        {
            MouseEventArgs me = e as MouseEventArgs;

            if (me.Button == MouseButtons.Right)
            {
                PictureBox picBox = sender as PictureBox;
                ButtonData bd = (picBox.Tag) as ButtonData;
                List<LineData> ldList = (panel1.Tag) as List<LineData>;

                foreach (LineData ld in ldList)
                {
                    if (ld.bFinished)
                    {
                        if (ld.StartButtonIndex == bd.Index)
                        {
                            if (ldList.Last().bFinished == false)
                                ldList.Remove(ldList.Last());

                            ldList.Remove(ld);
                            ld.bFinished = false;
                            ld.LineStartLocation = ld.LineEndLocation;
                            ld.StartButtonIndex = ld.EndButtonIndex;
                            ld.EndButtonIndex = -1;
                            ldList.Add(ld);
                            break;
                        }
                        else if (ld.EndButtonIndex == bd.Index)
                        {
                            if (ldList.Last().bFinished == false)
                                ldList.Remove(ldList.Last());

                            ldList.Remove(ld);
                            ld.bFinished = false;
                            ld.EndButtonIndex = -1;
                            ldList.Add(ld);
                            break;
                        }
                    }
                }
            }
        }

        private void pictureBox_Paint(object sender, PaintEventArgs e)
        {
            if (panel1.Tag != null)
            {
                PictureBox pc = sender as PictureBox;
                List<LineData> ldList = (panel1.Tag) as List<LineData>;
                Pen pen = new Pen(Color.FromArgb(255, 255, 0, 0));
                pen.Width = 3.0f;

                foreach (LineData ld in ldList) 
                {
                    e.Graphics.DrawLine(pen, ld.LineStartLocation.X - pc.Location.X, ld.LineStartLocation.Y - pc.Location.Y, ld.LineEndLocation.X - pc.Location.X, ld.LineEndLocation.Y - pc.Location.Y);
                }
            }

        }

        private void pictureBox_MouseMove(object sender, MouseEventArgs e)
        {
            if (panel1.Tag != null)
            {
                List<LineData> ldList = (panel1.Tag) as List<LineData>;

                if (ldList.Count > 0 && !ldList.Last().bFinished)
                {
                    PictureBox pc = sender as PictureBox;
                    ldList.Last().LineEndLocation = new Point(e.Location.X + pc.Location.X, e.Location.Y + pc.Location.Y);
                    panel1.Refresh();
                }
            }
        }
    }

    class LineData
    {
        public Point LineStartLocation;
        public Point LineEndLocation;
        public int StartButtonIndex;
        public int EndButtonIndex;
        public bool bFinished;

        public LineData()
        {
            bFinished = false;
            StartButtonIndex = -1;
            EndButtonIndex = -1;
        }
    }

    class ButtonData
    {
        public bool bDoubleTap;
        public int Index;

        public ButtonData(int argIndex)
        {
            bDoubleTap = false;
            Index = argIndex;
        }
    }
}
