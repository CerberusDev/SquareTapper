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

        private List<Label> LevelLabels1;
        private List<Label> LevelLabels2;

        private List<TextBox> IntervalTextBoxes;
        private List<TextBox> DurationTextBoxes;

        private List<TextBox> NumbericUpDowns1;
        private List<TextBox> NumbericUpDowns2;
        private List<TextBox> NumbericUpDowns3;

        private List<ComboBox> MaskComboBoxes1;
        private List<ComboBox> MaskComboBoxes2;
        private List<String> MaskCodes;
        private List<Image> ButtonImages;

        private List<Panel> LayoutPanels;
        private Panel lastPanelUnderCursor;

        private int openedWorldNr = -1;

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

            ButtonImages = new List<Image> { Properties.Resources.button2, Properties.Resources.button3 };

            LevelLabels1 = new List<Label> { label2 };
            LevelLabels2 = new List<Label> { label3 };
            IntervalTextBoxes = new List<TextBox> { textBox1 };
            DurationTextBoxes = new List<TextBox> { textBox2 };
            NumbericUpDowns1 = new List<TextBox> { textBox3 };
            NumbericUpDowns2 = new List<TextBox> { textBox4 };
            NumbericUpDowns3 = new List<TextBox> { textBox5 };
            MaskComboBoxes1 = new List<ComboBox> { comboBox1 };
            MaskComboBoxes2 = new List<ComboBox> { comboBox2 };
            LayoutPanels = new List<Panel> { panel1 };

            int pictureBoxSize = LayoutPanels[0].Controls[0].Size.Width;

            for (int i = 1; i < 15; ++i)
            {
                if (i < 12)
                {
                    Label lbl1 = new Label();
                    lbl1.TextAlign = LevelLabels1[0].TextAlign;
                    lbl1.Font = LevelLabels1[0].Font;
                    lbl1.Size = LevelLabels1[0].Size;
                    lbl1.Location = new Point(LevelLabels1[0].Location.X + getCurrentOffsetX(i), LevelLabels1[0].Location.Y);
                    LevelLabels1.Add(lbl1);
                    Controls.Add(lbl1);
                }

                Label lbl2 = new Label();
                lbl2.TextAlign = LevelLabels2[0].TextAlign;
                lbl2.Font = LevelLabels2[0].Font;
                lbl2.Size = LevelLabels2[0].Size;
                lbl2.Location = new Point(LevelLabels2[0].Location.X + getCurrentOffsetX(i), LevelLabels2[0].Location.Y);
                LevelLabels2.Add(lbl2);
                Controls.Add(lbl2);

                TextBox txt1 = new TextBox();
                txt1.Tag = IntervalTextBoxes[0].Tag;
                txt1.Font = IntervalTextBoxes[0].Font;
                txt1.Size = IntervalTextBoxes[0].Size;
                txt1.Location = new Point(IntervalTextBoxes[0].Location.X + getCurrentOffsetX(i), IntervalTextBoxes[0].Location.Y);
                IntervalTextBoxes.Add(txt1);
                Controls.Add(txt1);

                TextBox txt2 = new TextBox();
                txt2.Tag = DurationTextBoxes[0].Tag;
                txt2.Font = DurationTextBoxes[0].Font;
                txt2.Size = DurationTextBoxes[0].Size;
                txt2.Location = new Point(DurationTextBoxes[0].Location.X + getCurrentOffsetX(i), DurationTextBoxes[0].Location.Y);
                DurationTextBoxes.Add(txt2);
                Controls.Add(txt2);

                TextBox nb1 = new TextBox();
                nb1.Tag = NumbericUpDowns1[0].Tag;
                nb1.Font = NumbericUpDowns1[0].Font;
                nb1.Size = NumbericUpDowns1[0].Size;
                nb1.Location = new Point(NumbericUpDowns1[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns1[0].Location.Y);
                NumbericUpDowns1.Add(nb1);
                Controls.Add(nb1);

                TextBox nb2 = new TextBox();
                nb2.Tag = NumbericUpDowns2[0].Tag;
                nb2.Font = NumbericUpDowns2[0].Font;
                nb2.Size = NumbericUpDowns2[0].Size;
                nb2.Location = new Point(NumbericUpDowns2[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns2[0].Location.Y);
                NumbericUpDowns2.Add(nb2);
                Controls.Add(nb2);

                TextBox nb3 = new TextBox();
                nb3.Tag = NumbericUpDowns3[0].Tag;
                nb3.Font = NumbericUpDowns3[0].Font;
                nb3.Size = NumbericUpDowns3[0].Size;
                nb3.Location = new Point(NumbericUpDowns3[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns3[0].Location.Y);
                NumbericUpDowns3.Add(nb3);
                Controls.Add(nb3);

                ComboBox mask1 = new ComboBox();
                mask1.DropDownStyle = MaskComboBoxes1[0].DropDownStyle;
                mask1.DropDownHeight = MaskComboBoxes1[0].DropDownHeight;
                mask1.DrawMode = MaskComboBoxes1[0].DrawMode;
                mask1.ItemHeight = MaskComboBoxes1[0].ItemHeight;
                mask1.Size = MaskComboBoxes1[0].Size;
                mask1.Location = new Point(MaskComboBoxes1[0].Location.X + getCurrentOffsetX(i), MaskComboBoxes1[0].Location.Y);
                MaskComboBoxes1.Add(mask1);
                Controls.Add(mask1);

                ComboBox mask2 = new ComboBox();
                mask2.DropDownStyle = MaskComboBoxes2[0].DropDownStyle;
                mask2.DropDownHeight = MaskComboBoxes2[0].DropDownHeight;
                mask2.DrawMode = MaskComboBoxes2[0].DrawMode;
                mask2.ItemHeight = MaskComboBoxes2[0].ItemHeight;
                mask2.Size = MaskComboBoxes2[0].Size;
                mask2.Location = new Point(MaskComboBoxes2[0].Location.X + getCurrentOffsetX(i), MaskComboBoxes2[0].Location.Y);
                MaskComboBoxes2.Add(mask2);
                Controls.Add(mask2);

                Panel pan = new Panel();
                pan.Tag = new List<LineData>();
                pan.Size = LayoutPanels[0].Size;
                pan.Location = new Point(LayoutPanels[0].Location.X + getCurrentOffsetX(i), LayoutPanels[0].Location.Y);
                LayoutPanels.Add(pan);
                Controls.Add(pan);

                for (int j = 0; j < 15; ++j)
                {
                    PictureBox pc = new PictureBox();
                    pc.Size = new Size(pictureBoxSize, pictureBoxSize);
                    pc.Location = new Point(pictureBoxSize * (j % 3), pictureBoxSize * (4 - j / 3));
                    pc.Tag = (j + 1).ToString();
                    pc.SizeMode = PictureBoxSizeMode.StretchImage;
                    pan.Controls.Add(pc);
                }
            }

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

            for (int i = 0; i <= 12; ++i)
                LevelLabels2[i].Text = (i + 1).ToString();

            LevelLabels2[12].Text = "I";
            LevelLabels2[13].Text = "II";
            LevelLabels2[14].Text = "III";

            initLevelNumbers();

            foreach (TextBox tb in IntervalTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
                SpawnArrows(tb);
            }

            foreach (TextBox tb in DurationTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
                SpawnArrows(tb);
            }

            foreach (TextBox nb in NumbericUpDowns1)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                SpawnArrows(nb);
            }

            foreach (TextBox nb in NumbericUpDowns2)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                SpawnArrows(nb);
            } 

            foreach (TextBox nb in NumbericUpDowns3)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                SpawnArrows(nb);
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
                cb.SelectedValueChanged += genericValueChanged;
            }

            markAsClean();

            int alpha = 120;
            chart1.Series[0].Color = Color.FromArgb(alpha, 72, 69, 145);
            chart1.Series[1].Color = Color.FromArgb(alpha, 150, 16, 48);
            chart1.Series[2].Color = Color.FromArgb(alpha, 0, 0, 0);
            chart1.Series[3].Color = Color.FromArgb(150, 0, 25);
            chart1.Series[4].Color = Color.FromArgb(15, 15, 150);
            redrawChart();
            refreshLevelComboBox();

            if (comboBox31.Items.Count > 0)
            {
                string firstLevel = comboBox31.Items[0] as string;
                import(fileNameToWorldNr(firstLevel));
                comboBox31.SelectedItem = firstLevel;
            }
        }
        // ======================================== constructor end ==========================================

        private int getCurrentOffsetX(int i)
        {
            const int offsetX = 107;
            const int offsetX_bonus = 50;

            int baseOffset = offsetX * i;

            if (i > 11)
                baseOffset += offsetX_bonus;

            return baseOffset;
        }

        private void SpawnArrows(object ctrl)
        {
            const int arrowSize = 23;

            TextBox tx = ctrl as TextBox;

            if (tx != null)
            {
                Button bt1 = new Button();
                bt1.Image = Properties.Resources.arrow2;
                bt1.Size = new Size(arrowSize, arrowSize);
                bt1.Location = new Point(tx.Location.X - arrowSize, tx.Location.Y);
                bt1.Tag = tx;
                bt1.Click += buttonArrow1_Click;
                Controls.Add(bt1);

                Button bt2 = new Button();
                bt2.Image = Properties.Resources.arrow1;
                bt2.Size = new Size(arrowSize, arrowSize);
                bt2.Location = new Point(tx.Location.X + tx.Size.Width, tx.Location.Y);
                bt2.Tag = tx;
                bt2.Click += buttonArrow2_Click;
                Controls.Add(bt2);
            }
        }

        private void buttonArrow1_Click(object sender, EventArgs e)
        {
            Button bt = sender as Button;
            TextBox tx = bt.Tag as TextBox;
            float value = getValueFromTextbox(tx);
            float step = float.Parse(tx.Tag.ToString());
            tx.Text = (Math.Max(value - step, 0.0f)).ToString();
        }

        private void buttonArrow2_Click(object sender, EventArgs e)
        {
            Button bt = sender as Button;
            TextBox tx = bt.Tag as TextBox;
            float value = getValueFromTextbox(tx);
            float step = float.Parse(tx.Tag.ToString());
            tx.Text = (value + step).ToString();
        }

        private void refreshLevelComboBox()
        {
            ComboBox cb = comboBox31;
            cb.Items.Clear();

            string path = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string[] files = Directory.GetFiles(path, "*.lvl", SearchOption.AllDirectories);

            List<int> nrList = new List<int>();

            foreach (string fileName in files)
                nrList.Add(fileNameToWorldNr(fileName));

            nrList.Sort();

            foreach (int nr in nrList)
                cb.Items.Add(worldNrToString(nr));
        }

        private void comboBox31_SelectedValueChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            int newWorldNr = fileNameToWorldNr(cb.SelectedItem as string);

            if (newWorldNr != openedWorldNr)
            {
                if (dontQuit_ChangesMsgBox())
                {
                    comboBox31.SelectedItem = worldNrToString(openedWorldNr);
                }
                else
                {
                    import(newWorldNr);
                }
            }
        }

        private string worldNrToString(int nr)
        {
            return "World_" + nr;
        }

        private string worldNrToString(string nr)
        {
            return "World_" + nr;
        }

        private int fileNameToWorldNr(string path)
        {
            string[] tmp1 = path.Split('\\');
            string filename = tmp1[tmp1.Count() - 1];

            string[] tmp2 = filename.Split('.');
            string[] tmp3 = tmp2[0].Split('_');
            return int.Parse(tmp3[tmp3.Count() - 1]);
        }

        private string worldNrStringToPath(string worldNrString)
        {
            return Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\" + worldNrString + ".lvl";
        }

        private string worldNrToPath(int worldNr)
        {
            return Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\World_" + worldNr + ".lvl";
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Control | Keys.S))
            {
                save();
                return true;
            }
            return base.ProcessCmdKey(ref msg, keyData);
        }

        private bool dontQuit_ChangesMsgBox()
        {
            if (!isDirty())
                return false;

            DialogResult result = 
                MessageBox.Show("Would you like to return to save your changes? If you proceed those changes will not be saved in the currently opened level."
                , "Unsaved changes detected! Return?", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button1);

            return result == DialogResult.Yes;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (dontQuit_ChangesMsgBox())
            {
                e.Cancel = true;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Maximized;
        }

        private bool isDirty()
        {
            return label27.Visible;
        }

        private void markAsDirty()
        {
            label27.Visible = true;
        }

        private void markAsClean()
        {
            label27.Visible = false;
        }

        private void initLevelNumbers()
        {
            int i = 0;
            foreach (Label lb in LevelLabels1)
                lb.Text = (++i + openedWorldNr * 12).ToString();
        }

        private void redrawChart()
        {
            float[] yValues1 = new float[15];
            float[] yValues2 = new float[15];
            float[] yValues3 = new float[15];
            float[] yValues4 = new float[15];
            float[] yValues5 = new float[15];

            float max = 0.0f;

            for (int i = 0; i < 15; ++i)
            {
                yValues1[i] = getValueFromTextbox(NumbericUpDowns1[i]);
                yValues2[i] = getValueFromTextbox(NumbericUpDowns2[i]);
                yValues3[i] = getValueFromTextbox(NumbericUpDowns3[i]);
                yValues4[i] = getValueFromTextbox(IntervalTextBoxes[i]);
                yValues5[i] = getValueFromTextbox(DurationTextBoxes[i]);

                if (yValues4[i] > max)
                    max = yValues4[i];

                if (yValues5[i] > max)
                    max = yValues5[i];
            }

            float mod = 14.0f / max;

            for (int i = 0; i < 15; ++i)
            {
                yValues4[i] *= mod;
                yValues5[i] *= mod;
            }

            chart1.Series[0].Points.DataBindY(yValues1);
            chart1.Series[1].Points.DataBindY(yValues2);
            chart1.Series[2].Points.DataBindY(yValues3);
            chart1.Series[3].Points.DataBindY(yValues4);
            chart1.Series[4].Points.DataBindY(yValues5);
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
            markAsDirty();
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

        private void handleTextChanges_decimal(object sender, EventArgs e)
        {
            TextBox tx = sender as TextBox;

            if (tx.Text.Length > 0 && decimal.Parse(tx.Text) > 15)
            {
                tx.Text = (15).ToString();
                tx.SelectionStart = tx.Text.Length;
                tx.SelectionLength = 0;
            }

            redrawChart();
            markAsDirty();
        }

        private void handleKeyPress_decimal(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
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

            markAsDirty();
        }

        private void genericValueChanged(object sender, EventArgs e)
        {
            markAsDirty();
        }

        private void pictureBox_Click(object sender, EventArgs e)
        {
            PictureBox picBox = sender as PictureBox;
            MouseEventArgs me = e as MouseEventArgs;
            Panel panel = (picBox.Parent) as Panel;

            if (me.Button == MouseButtons.Left && !checkBox1.Checked)
            {
                ButtonData bt = (picBox.Tag) as ButtonData;
                SetPicBoxData(picBox, !bt.bDoubleTap);
                markAsDirty();
            }
            else if (me.Button == MouseButtons.Right || (checkBox1.Checked && me.Button == MouseButtons.Left))
            {
                ButtonData bd = (picBox.Tag) as ButtonData;
                List<LineData> ldList = (panel.Tag) as List<LineData>;

                if (ldList.Count == 0 || ldList.Last().bFinished)
                {
                    if (CanAddAnotherLineHere(ldList, bd.Index))
                    {
                        LineData ld = new LineData();

                        ld.LineStartLocation = GetControlCenter(picBox);
                        ld.LineEndLocation = new Point(me.Location.X + picBox.Location.X, me.Location.Y + picBox.Location.Y);
                        ld.StartButtonIndex = ((picBox.Tag) as ButtonData).Index;
                        ldList.Add(ld);

                        lastPanelUnderCursor = panel;
                    }
                }
                else
                {
                    LineData ld = ldList.Last();
                    ld.LineEndLocation = GetControlCenter(picBox);

                    if (bd.Index != ld.StartButtonIndex && CanAddAnotherLineHere(ldList, bd.Index) && IsLineLengthOkay(ld.LineStartLocation, ld.LineEndLocation, picBox.Width))
                    {
                        ld.bFinished = true;
                        ld.EndButtonIndex = bd.Index;
                        markAsDirty();
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

        private Point GetControlCenter(Control ctrl)
        {
            return new Point(ctrl.Location.X + ctrl.Width / 2, ctrl.Location.Y + ctrl.Height / 2);
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

            if (me.Button == MouseButtons.Right || (checkBox1.Checked && me.Button == MouseButtons.Left))
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
                            markAsDirty();
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
                            markAsDirty();
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

        private int MaskCodeToIdx(String MaskCode)
        {
            return MaskCodes.IndexOf(MaskCode) + 1;
        }

        private String IdxToMaskCode(int Idx)
        {
            if (Idx == 0)
                return null;

            return MaskCodes[Idx - 1];
        }

        // ======================================== import ==========================================

        private void import(int worldNr)
        {
            openedWorldNr = worldNr;
            initLevelNumbers();

            string worldPath = worldNrToPath(worldNr);
            StreamReader sr = new StreamReader(worldPath);
            String line;
            int levelIdx = 0;

            while ((line = sr.ReadLine()) != null)
            {
                if (line.Length > 1)
                {
                    if (line.Length > 2 && line[0] == '#' && line[1] == '!')
                    {
                        String s = line.Substring(2);
                        textBox31.Text = s;
                    }
                    else if (line[0] != '#')
                    {
                        String[] levelParamsOriginal = line.Split();
                        List<String> levelParams = new List<String>();

                        foreach (String s in levelParamsOriginal)
                            if (s.Length > 0)
                                levelParams.Add(s);

                        IntervalTextBoxes[levelIdx].Text = levelParams[0];
                        DurationTextBoxes[levelIdx].Text = levelParams[1];
                        NumbericUpDowns1[levelIdx].Text = levelParams[2];
                        NumbericUpDowns2[levelIdx].Text = levelParams[3];
                        NumbericUpDowns3[levelIdx].Text = levelParams[4];

                        if (levelParams.Count > 5)
                        {
                            MaskComboBoxes1[levelIdx].SelectedIndex = MaskCodeToIdx(levelParams[5]);
                            
                            if (levelParams.Count > 6)
                                MaskComboBoxes2[levelIdx].SelectedIndex = MaskCodeToIdx(levelParams[6]);
                            else
                                MaskComboBoxes2[levelIdx].SelectedIndex = 0;
                        }
                        else
                        {
                            MaskComboBoxes2[levelIdx].SelectedIndex = 0;
                            MaskComboBoxes1[levelIdx].SelectedIndex = 0;
                        }

                        line = sr.ReadLine();
                        List<SeqData> sequenceData = new List<SeqData>();

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
                                String currTileData = lineParams[j - 1];
                                PictureBox pc = GetPictureBoxWithIdx(LayoutPanels[levelIdx], idx);

                                if (currTileData.Contains("SQ"))
                                    sequenceData.Add(new SeqData(currTileData, idx));

                                SetPicBoxData(pc, currTileData.Contains("DB"));
                            }
                        }

                        importSequenceData(sequenceData, LayoutPanels[levelIdx]);

                        ++levelIdx;
                    }
                }
            }

            sr.Close();
            markAsClean();
        }

        private PictureBox GetPictureBoxWithIdx(Panel currPanel, int idx)
        {
            foreach (Control ctrl in currPanel.Controls)
            {
                PictureBox currPC = ctrl as PictureBox;
                ButtonData bt = (currPC.Tag) as ButtonData;

                if (bt.Index == idx)
                    return currPC;
            }

            return null;
        }

        private void importSequenceData(List<SeqData> originalSequenceData, Panel currPanel)
        {
            List<LineData> ldList = new List<LineData>();
            currPanel.Tag = ldList;

            if (originalSequenceData.Count > 0)
            {
                int maxSeqID = 0;

                foreach (SeqData sq in originalSequenceData)
                {
                    if (sq.SeqID > maxSeqID)
                        maxSeqID = sq.SeqID;
                }

                List<List<SeqData>> seqData = new List<List<SeqData>>();

                for (int i = 0; i <= maxSeqID; ++i)
                    seqData.Add(new List<SeqData>());

                foreach (SeqData sq in originalSequenceData)
                    seqData[sq.SeqID].Add(sq);

                foreach (List<SeqData> Sequence in seqData)
                {
                    Sequence.Sort((x, y) => x.TileNum > y.TileNum ? 1 : -1);

                    for (int i = 0; i < Sequence.Count - 1; ++i)
                    {
                        LineData ld = new LineData();
                        ld.bFinished = true;
                        ld.StartButtonIndex = Sequence[i].TileIndex;
                        ld.EndButtonIndex = Sequence[i + 1].TileIndex;
                        ld.LineStartLocation = GetButtonCenter(Sequence[i].TileIndex, currPanel);
                        ld.LineEndLocation = GetButtonCenter(Sequence[i + 1].TileIndex, currPanel);
                        ldList.Add(ld);
                    }
                }
            }
        }

        private Point GetButtonCenter(int Index, Panel currPanel)
        {
            foreach (Control ctrl in currPanel.Controls)
            {
                PictureBox pc = ctrl as PictureBox;
                ButtonData bt = (pc.Tag) as ButtonData;

                if (bt.Index == Index)
                    return GetControlCenter(pc);
            }

            return new Point(-1, -1);
        }

        // ======================================== import end ==========================================

        private void button2_Click(object sender, EventArgs e)
        {
            save();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (!dontQuit_ChangesMsgBox())
            {
                string lastWorldNr = comboBox31.Items[comboBox31.Items.Count - 1] as string;
                int createdWorldNr = fileNameToWorldNr(lastWorldNr) + 1;

                export(createdWorldNr);
                initLevelNumbers();
                markAsClean();
                refreshLevelComboBox();
                comboBox31.SelectedItem = comboBox31.Items[comboBox31.Items.Count - 1];
            }
        }

        private void save()
        {
            export(openedWorldNr);
            markAsClean();
        }

        // ========================================== export ============================================

        private void export(int worldNr)
        {
            StreamWriter sr = new StreamWriter(worldNrToPath(worldNr));

            sr.WriteLine();
            sr.WriteLine("#");
            sr.WriteLine("# Parameters in first line of level definition:");
            sr.WriteLine("#");
            sr.WriteLine("# 1. Interval between square's activations");
            sr.WriteLine("# 2. Total activation time of one square");
            sr.WriteLine("# 3. Number of safe squares on level");
            sr.WriteLine("# 4. Number of dangerous squares on level");
            sr.WriteLine("# 5. Number of double tap squares with dangerous second actuation part on level");
            sr.WriteLine("# 6. Mask definition (Keywords: Vertical-Killing 		Vertical-Standard");
            sr.WriteLine("#								Horizontal-Killing 		Horizontal-Standard");
            sr.WriteLine("#								HorizontalBig-Killing 	HorizontalBig-Standard");
            sr.WriteLine("#								Chessboard-Killing 		Chessboard-Standard");
            sr.WriteLine("#								Full-Killing 			Full-Standard )");
            sr.WriteLine("#");
            sr.WriteLine("# Square codes:");
            sr.WriteLine("#");
            sr.WriteLine("# ST - Standard square");
            sr.WriteLine("# DB - Double-tap square");
            sr.WriteLine("# SQ(XX).Y.Z ( e.g. SQ(ST).0.0 )- Sequence square, requires more specified definition:");
            sr.WriteLine("#	XX - Square type (ST or DB)");
            sr.WriteLine("#	Y - Sequence ID (please start counting from 0)");
            sr.WriteLine("#	Z - Square's index in sequence (0 means first)	");
            sr.WriteLine("#");
            sr.WriteLine();
            sr.WriteLine();
            sr.WriteLine("#!" + textBox31.Text);
            sr.WriteLine();

            for (int levelIdx = 0; levelIdx < 15; ++levelIdx)
            {
                if (levelIdx == 0)
                    sr.WriteLine("# ============= 1 - 3 =============");
                else if (levelIdx == 3)
                    sr.WriteLine("# ============= 4 - 6 =============");
                else if (levelIdx == 6)
                    sr.WriteLine("# ============= 7 - 9 =============");
                else if (levelIdx == 9)
                    sr.WriteLine("# ============= 10 - 12 =============");
                else if (levelIdx == 12)
                    sr.WriteLine("# ============= 13 - 15 =============");

                sr.Write(IntervalTextBoxes[levelIdx].Text.Replace(",", "."));
                sr.Write("\t\t");
                sr.Write(DurationTextBoxes[levelIdx].Text.Replace(",", "."));
                sr.Write("\t\t");
                sr.Write(NumbericUpDowns1[levelIdx].Text);
                sr.Write("\t\t");
                sr.Write(NumbericUpDowns2[levelIdx].Text);
                sr.Write("\t\t");
                sr.Write(NumbericUpDowns3[levelIdx].Text);

                String MaskCode = IdxToMaskCode(MaskComboBoxes1[levelIdx].SelectedIndex);

                if (MaskCode != null)
                {
                    sr.Write("\t\t");
                    sr.Write(MaskCode);

                    MaskCode = IdxToMaskCode(MaskComboBoxes2[levelIdx].SelectedIndex);

                    if (MaskCode != null)
                    {
                        sr.Write("\t\t");
                        sr.Write(MaskCode);
                    }
                }

                sr.WriteLine();
                sr.WriteLine();

                List<SeqData> seqData = getExportSequenceData(LayoutPanels[levelIdx]);

                for (int i = 4; i >= 0; --i)
                {
                    for (int j = 1; j <= 3; ++j)
                    {
                        int idx = i * 3 + j;
                        PictureBox pc = GetPictureBoxWithIdx(LayoutPanels[levelIdx], idx);
                        ButtonData bt = (pc.Tag) as ButtonData;

                        SeqData matchingSeqData = null;

                        foreach (SeqData sq in seqData)
                        {
                            if (sq.TileIndex == idx)
                            {
                                matchingSeqData = sq;
                                break;
                            }
                        }

                        if (matchingSeqData == null)
                        {
                            if (bt.bDoubleTap)
                                sr.Write("DB");
                            else
                                sr.Write("ST");

                            sr.Write("\t\t\t");
                        }
                        else
                        {
                            sr.Write("SQ(");

                            if (bt.bDoubleTap)
                                sr.Write("DB");
                            else
                                sr.Write("ST");

                            sr.Write(").");
                            sr.Write(matchingSeqData.SeqID);
                            sr.Write(".");
                            sr.Write(matchingSeqData.TileNum);
                            sr.Write("\t");
                        }
                    }

                    sr.WriteLine();
                }

                sr.WriteLine();
            }

            sr.Close();
        }
        
        private List<SeqData> getExportSequenceData(Panel currPanel)
        {
            List<LineData> ldList = (currPanel.Tag) as List<LineData>;
            List<SeqData> seqData = new List<SeqData>();

            if (ldList.Count > 0)
            {
                List<Point> tileIdxOccurences = new List<Point>();

                foreach (LineData ld in ldList)
                {
                    bool bStartFound = false;
                    bool bEndFound = false;

                    for (int i = 0; i < tileIdxOccurences.Count; ++i)
                    {
                        if (tileIdxOccurences[i].X == ld.StartButtonIndex)
                        {
                            Point p = new Point(tileIdxOccurences[i].X, tileIdxOccurences[i].Y + 1);
                            tileIdxOccurences[i] = p;
                            bStartFound = true;
                        }
                        else if (tileIdxOccurences[i].X == ld.EndButtonIndex)
                        {
                            Point p = new Point(tileIdxOccurences[i].X, tileIdxOccurences[i].Y + 1);
                            tileIdxOccurences[i] = p;
                            bEndFound = true;
                        }
                    }

                    if (!bStartFound)
                        tileIdxOccurences.Add(new Point(ld.StartButtonIndex, 1));

                    if (!bEndFound)
                        tileIdxOccurences.Add(new Point(ld.EndButtonIndex, 1));
                }

                List<int> seqEdgeIndices = new List<int>();

                foreach (Point p in tileIdxOccurences)
                    if (p.Y == 1)
                        seqEdgeIndices.Add(p.X);

                List<LineData> ldList_work = new List<LineData>();

                foreach (LineData ld in ldList)
                {
                    LineData ld2 = new LineData();
                    ld2.EndButtonIndex = ld.EndButtonIndex;
                    ld2.StartButtonIndex = ld.StartButtonIndex;
                    ldList_work.Add(ld2);
                }

                for (int i = 0; i < seqEdgeIndices.Count; ++i)
                {
                    recursionSeekIndex(seqEdgeIndices[i], i, 0, ldList_work, seqData);
                    seqEdgeIndices.Remove(seqData.Last().TileIndex);
                }
            }

            return seqData;
        }

        private void recursionSeekIndex(int currIndex, int seqID, int tileNum, List<LineData> ldList, List<SeqData> seqData)
        {
            seqData.Add(new SeqData(seqID, tileNum, currIndex));

            int foundIdx = -1;
            int savedI = -1;

            for (int i = 0; i < ldList.Count; ++i)
            {
                if (ldList[i].StartButtonIndex == currIndex)
                {
                    foundIdx = ldList[i].EndButtonIndex;
                    savedI = i;
                    break;
                }

                if (ldList[i].EndButtonIndex == currIndex)
                {
                    foundIdx = ldList[i].StartButtonIndex;
                    savedI = i;
                    break;
                }
            }

            if (foundIdx != -1)
            {
                ldList.RemoveAt(savedI);
                recursionSeekIndex(foundIdx, seqID, tileNum + 1, ldList, seqData);
            }
        }

        // ======================================== export end ==========================================

        private void textBox31_TextChanged(object sender, EventArgs e)
        {
            markAsDirty();
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

    class SeqData
    {
        public int SeqID;
        public int TileNum;
        public int TileIndex;

        public SeqData(String RawData, int argTileIndex)
        {
            TileIndex = argTileIndex;
            String[] tmp = RawData.Split('.');
            SeqID = int.Parse(tmp[1]);
            TileNum = int.Parse(tmp[2]);
        }

        public SeqData(int argSeqID, int argTileNum, int argTileIndex)
        {
            SeqID = argSeqID;
            TileNum = argTileNum;
            TileIndex = argTileIndex;
        }
    };
}
