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

        private List<TextBox> IntervalTextBoxes;
        private List<TextBox> DurationTextBoxes;

        private List<NumericUpDown> NumbericUpDowns1;
        private List<NumericUpDown> NumbericUpDowns2;
        private List<NumericUpDown> NumbericUpDowns3;

        private List<ComboBox> MaskComboBoxes1;
        private List<ComboBox> MaskComboBoxes2;
        private List<String> MaskCodes;
        private List<Image> ButtonImages;

        private List<Panel> LayoutPanels;
        private Panel lastPanelUnderCursor;

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
                Properties.Resources.mask6,
                Properties.Resources.mask7,
                Properties.Resources.mask8,
                Properties.Resources.mask9,
                Properties.Resources.mask10,
                Properties.Resources.mask11
            };

            MaskCodes = new List<String>();
            MaskCodes.Add("Horizontal-Standard");
            MaskCodes.Add("Horizontal-Killing");
            MaskCodes.Add("Vertical-Standard");
            MaskCodes.Add("Vertical-Killing");
            MaskCodes.Add("HorizontalBig-Standard");
            MaskCodes.Add("HorizontalBig-Killing");
            MaskCodes.Add("Chessboard-Standard");
            MaskCodes.Add("Chessboard-Killing");
            MaskCodes.Add("Full-Standard");
            MaskCodes.Add("Full-Killing");

            IntervalTextBoxes = new List<TextBox>();
            IntervalTextBoxes.Add(textBox1);
            IntervalTextBoxes.Add(textBox4);
            IntervalTextBoxes.Add(textBox7);
            IntervalTextBoxes.Add(textBox10);
            IntervalTextBoxes.Add(textBox13);
            IntervalTextBoxes.Add(textBox16);
            IntervalTextBoxes.Add(textBox19);
            IntervalTextBoxes.Add(textBox22);
            IntervalTextBoxes.Add(textBox25);
            IntervalTextBoxes.Add(textBox28);
            IntervalTextBoxes.Add(textBox31);
            IntervalTextBoxes.Add(textBox34);
            IntervalTextBoxes.Add(textBox37);
            IntervalTextBoxes.Add(textBox40);
            IntervalTextBoxes.Add(textBox43);

            DurationTextBoxes = new List<TextBox>();
            DurationTextBoxes.Add(textBox2);
            DurationTextBoxes.Add(textBox5);
            DurationTextBoxes.Add(textBox8);
            DurationTextBoxes.Add(textBox11);
            DurationTextBoxes.Add(textBox14);
            DurationTextBoxes.Add(textBox17);
            DurationTextBoxes.Add(textBox20);
            DurationTextBoxes.Add(textBox23);
            DurationTextBoxes.Add(textBox26);
            DurationTextBoxes.Add(textBox29);
            DurationTextBoxes.Add(textBox32);
            DurationTextBoxes.Add(textBox35);
            DurationTextBoxes.Add(textBox38);
            DurationTextBoxes.Add(textBox41);
            DurationTextBoxes.Add(textBox44);

            NumbericUpDowns1 = new List<NumericUpDown>();
            NumbericUpDowns1.Add(numericUpDown1);
            NumbericUpDowns1.Add(numericUpDown4);
            NumbericUpDowns1.Add(numericUpDown7);
            NumbericUpDowns1.Add(numericUpDown10);
            NumbericUpDowns1.Add(numericUpDown13);
            NumbericUpDowns1.Add(numericUpDown16);
            NumbericUpDowns1.Add(numericUpDown19);
            NumbericUpDowns1.Add(numericUpDown22);
            NumbericUpDowns1.Add(numericUpDown25);
            NumbericUpDowns1.Add(numericUpDown28);
            NumbericUpDowns1.Add(numericUpDown31);
            NumbericUpDowns1.Add(numericUpDown34);
            NumbericUpDowns1.Add(numericUpDown37);
            NumbericUpDowns1.Add(numericUpDown40);
            NumbericUpDowns1.Add(numericUpDown43);

            NumbericUpDowns2 = new List<NumericUpDown>();
            NumbericUpDowns2.Add(numericUpDown2);
            NumbericUpDowns2.Add(numericUpDown5);
            NumbericUpDowns2.Add(numericUpDown8);
            NumbericUpDowns2.Add(numericUpDown11);
            NumbericUpDowns2.Add(numericUpDown14);
            NumbericUpDowns2.Add(numericUpDown17);
            NumbericUpDowns2.Add(numericUpDown20);
            NumbericUpDowns2.Add(numericUpDown23);
            NumbericUpDowns2.Add(numericUpDown26);
            NumbericUpDowns2.Add(numericUpDown29);
            NumbericUpDowns2.Add(numericUpDown32);
            NumbericUpDowns2.Add(numericUpDown35);
            NumbericUpDowns2.Add(numericUpDown38);
            NumbericUpDowns2.Add(numericUpDown41);
            NumbericUpDowns2.Add(numericUpDown44);

            NumbericUpDowns3 = new List<NumericUpDown>();
            NumbericUpDowns3.Add(numericUpDown3);
            NumbericUpDowns3.Add(numericUpDown6);
            NumbericUpDowns3.Add(numericUpDown9);
            NumbericUpDowns3.Add(numericUpDown12);
            NumbericUpDowns3.Add(numericUpDown15);
            NumbericUpDowns3.Add(numericUpDown18);
            NumbericUpDowns3.Add(numericUpDown21);
            NumbericUpDowns3.Add(numericUpDown24);
            NumbericUpDowns3.Add(numericUpDown27);
            NumbericUpDowns3.Add(numericUpDown30);
            NumbericUpDowns3.Add(numericUpDown33);
            NumbericUpDowns3.Add(numericUpDown36);
            NumbericUpDowns3.Add(numericUpDown39);
            NumbericUpDowns3.Add(numericUpDown42);
            NumbericUpDowns3.Add(numericUpDown45);

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

            foreach (TextBox tb in IntervalTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
            }

            foreach (TextBox tb in DurationTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
            }

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

            LayoutPanels = new List<Panel> { panel1, panel2, panel3, panel4, panel5, panel6, panel7, panel8, panel9, panel10, panel11, panel12, panel13, panel14, panel15 };

            foreach (Panel panel in LayoutPanels)
            {
                panel.Tag = new List<LineData>();

                foreach (Control ctrl in panel.Controls)
                {
                    PictureBox pc = ctrl as PictureBox;

                    int index = int.Parse(pc.Tag as String);
                    pc.Tag = new ButtonData(index);
                    pc.Image = ButtonImages[0];
                    pc.Click += pictureBox_Click;
                    pc.Paint += pictureBox_Paint;
                    pc.MouseMove += pictureBox_MouseMove;
                    pc.DoubleClick += pictureBox_DoubleClick;
                }
            }

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
            Panel panel = (picBox.Parent) as Panel;

            if (me.Button == MouseButtons.Left)
            {
                ButtonData bt = (picBox.Tag) as ButtonData;
                SetPicBoxData(picBox, !bt.bDoubleTap);
            }
            else if (me.Button == MouseButtons.Right)
            {
                ButtonData bd = (picBox.Tag) as ButtonData;
                List<LineData> ldList = (panel.Tag) as List<LineData>;

                if (ldList.Count == 0 || ldList.Last().bFinished)
                {
                    if (CanAddAnotherLineHere(ldList, bd.Index))
                    {
                        LineData ld = new LineData();

                        ld.LineStartLocation = new Point(picBox.Location.X + picBox.Width / 2, picBox.Location.Y + picBox.Height / 2);
                        ld.LineEndLocation = new Point(me.Location.X + picBox.Location.X, me.Location.Y + picBox.Location.Y);
                        ld.StartButtonIndex = ((picBox.Tag) as ButtonData).Index;
                        ldList.Add(ld);

                        lastPanelUnderCursor = panel;
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

                    lastPanelUnderCursor = null;
                    panel.Refresh();
                }
            }
        }

        private void SetPicBoxData(PictureBox picBox, bool bDoubleTap)
        {
            ButtonData bt = (picBox.Tag) as ButtonData;
            bt.bDoubleTap = bDoubleTap;

            picBox.Image = bt.bDoubleTap ? ButtonImages[1] : ButtonImages[0];
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
                Panel panel = (picBox.Parent) as Panel;
                List<LineData> ldList = (panel.Tag) as List<LineData>;

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

                            lastPanelUnderCursor = panel;
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

                            lastPanelUnderCursor = panel;
                            break;
                        }
                    }
                }
            }
        }

        private void pictureBox_Paint(object sender, PaintEventArgs e)
        {
            PictureBox pc = sender as PictureBox;
            Panel panel = (pc.Parent) as Panel;

            if (panel.Tag != null)
            {
                List<LineData> ldList = (panel.Tag) as List<LineData>;
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
            PictureBox pc = sender as PictureBox;
            Panel panel = (pc.Parent) as Panel;

            if (lastPanelUnderCursor != null && lastPanelUnderCursor != panel)
            {
                List<LineData> ldList = (lastPanelUnderCursor.Tag) as List<LineData>;
                ldList.Remove(ldList.Last());
                lastPanelUnderCursor.Refresh();
                lastPanelUnderCursor = null;
            }

            if (panel.Tag != null)
            {
                List<LineData> ldList = (panel.Tag) as List<LineData>;

                if (ldList.Count > 0 && !ldList.Last().bFinished)
                {
                    ldList.Last().LineEndLocation = new Point(e.Location.X + pc.Location.X, e.Location.Y + pc.Location.Y);
                    panel.Refresh();
                }
            }
        }

        // ======================================== import ==========================================

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Level files|*.lvl";
            openFileDialog1.Title = "Select a Level File";
            openFileDialog1.InitialDirectory = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);

            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                System.IO.StreamReader sr = new System.IO.StreamReader(openFileDialog1.FileName);
                String line;
                int levelIdx = 0;

                while ((line = sr.ReadLine()) != null)
                {
                    if (line.Length > 1 && line[0] != '#')
                    {
                        String[] levelParamsOriginal = line.Split();
                        List<String> levelParams = new List<String>();

                        foreach (String s in levelParamsOriginal)
                            if (s.Length > 0)
                                levelParams.Add(s);

                        IntervalTextBoxes[levelIdx].Text = levelParams[0];
                        DurationTextBoxes[levelIdx].Text = levelParams[1];
                        NumbericUpDowns1[levelIdx].Value = decimal.Parse(levelParams[2]);
                        NumbericUpDowns2[levelIdx].Value = decimal.Parse(levelParams[3]);
                        NumbericUpDowns3[levelIdx].Value = decimal.Parse(levelParams[4]);

                        if (levelParams.Count > 5)
                            MaskComboBoxes1[levelIdx].SelectedIndex = MaskCodeToIdx(levelParams[5]);

                        if (levelParams.Count > 6)
                            MaskComboBoxes2[levelIdx].SelectedIndex = MaskCodeToIdx(levelParams[6]);

                        line = sr.ReadLine();

                        for (int i = 4; i >= 0; --i)
                        {
                            line = sr.ReadLine();
                            String[] lineParamsOriginal = line.Split();
                            List<String> lineParams = new List<String>();

                            foreach (String s in lineParamsOriginal)
                                if (s.Length > 0)
                                    lineParams.Add(s);

                            for (int j = 1; j <= 3; ++j)
                            {
                                int idx = i * 3 + j;

                                PictureBox pc = null;

                                foreach (Control ctrl in LayoutPanels[levelIdx].Controls)
                                {
                                    PictureBox currPC = ctrl as PictureBox;
                                    ButtonData bt = (currPC.Tag) as ButtonData;

                                    if (bt.Index == idx)
                                    {
                                        pc = currPC;
                                        break;
                                    }
                                }

                                if (lineParams[j - 1] == "DB")
                                    SetPicBoxData(pc, true);
                                else
                                    SetPicBoxData(pc, false);
                            }
                        }

                        ++levelIdx;
                    }
                }

                sr.Close();
            }
        }

        private int MaskCodeToIdx(String MaskCode)
        {
            return MaskCodes.IndexOf(MaskCode) + 1;
        }

        // ======================================== import end ==========================================
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
