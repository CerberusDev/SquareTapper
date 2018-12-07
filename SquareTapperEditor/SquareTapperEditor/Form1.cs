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

        private const int iconTabOffsetX = 92;
        private const int iconTabOffsetY = 170;
        private const int iconTabLabelOffsetY = -32;
        private const int iconTabMaxWorldInRow = 20;

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

        private List<CheckBox> ResetButtons;

        private bool bClearingResetTimersInProgress;
        private CheckBox PendingResetButton;
        private System.Timers.Timer ResetButtonsTimer;

        private int openedWorldNr = -1;

        private List<IconData> AllIconImages;
        private IconData EmptyIconImage;
        private List<ComboBox> IconComboBoxes;
        private List<TextBox> IconTextBoxes;
        private List<PictureBox> LockPicBoxes;

        public Form1()
        {
            InitializeComponent();

            Image[] maskImages =
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
            ResetButtons = new List<CheckBox> { checkBox2 };

            IconComboBoxes = new List<ComboBox> { comboBox3 };
            IconTextBoxes = new List<TextBox> { textBox6 };
            LockPicBoxes = new List<PictureBox> { pictureBox16 };

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
                    tabPage1.Controls.Add(lbl1);
                }

                Label lbl2 = new Label();
                lbl2.TextAlign = LevelLabels2[0].TextAlign;
                lbl2.Font = LevelLabels2[0].Font;
                lbl2.Size = LevelLabels2[0].Size;
                lbl2.Location = new Point(LevelLabels2[0].Location.X + getCurrentOffsetX(i), LevelLabels2[0].Location.Y);
                LevelLabels2.Add(lbl2);
                tabPage1.Controls.Add(lbl2);

                TextBox txt1 = new TextBox();
                txt1.Font = IntervalTextBoxes[0].Font;
                txt1.Size = IntervalTextBoxes[0].Size;
                txt1.Location = new Point(IntervalTextBoxes[0].Location.X + getCurrentOffsetX(i), IntervalTextBoxes[0].Location.Y);
                IntervalTextBoxes.Add(txt1);
                tabPage1.Controls.Add(txt1);

                TextBox txt2 = new TextBox();
                txt2.Font = DurationTextBoxes[0].Font;
                txt2.Size = DurationTextBoxes[0].Size;
                txt2.Location = new Point(DurationTextBoxes[0].Location.X + getCurrentOffsetX(i), DurationTextBoxes[0].Location.Y);
                DurationTextBoxes.Add(txt2);
                tabPage1.Controls.Add(txt2);

                TextBox nb1 = new TextBox();
                nb1.Font = NumbericUpDowns1[0].Font;
                nb1.Size = NumbericUpDowns1[0].Size;
                nb1.Location = new Point(NumbericUpDowns1[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns1[0].Location.Y);
                NumbericUpDowns1.Add(nb1);
                tabPage1.Controls.Add(nb1);

                TextBox nb2 = new TextBox();
                nb2.Font = NumbericUpDowns2[0].Font;
                nb2.Size = NumbericUpDowns2[0].Size;
                nb2.Location = new Point(NumbericUpDowns2[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns2[0].Location.Y);
                NumbericUpDowns2.Add(nb2);
                tabPage1.Controls.Add(nb2);

                TextBox nb3 = new TextBox();
                nb3.Font = NumbericUpDowns3[0].Font;
                nb3.Size = NumbericUpDowns3[0].Size;
                nb3.Location = new Point(NumbericUpDowns3[0].Location.X + getCurrentOffsetX(i), NumbericUpDowns3[0].Location.Y);
                NumbericUpDowns3.Add(nb3);
                tabPage1.Controls.Add(nb3);

                ComboBox mask1 = new ComboBox();
                mask1.DropDownStyle = MaskComboBoxes1[0].DropDownStyle;
                mask1.DropDownHeight = MaskComboBoxes1[0].DropDownHeight;
                mask1.DrawMode = MaskComboBoxes1[0].DrawMode;
                mask1.ItemHeight = MaskComboBoxes1[0].ItemHeight;
                mask1.Size = MaskComboBoxes1[0].Size;
                mask1.Location = new Point(MaskComboBoxes1[0].Location.X + getCurrentOffsetX(i), MaskComboBoxes1[0].Location.Y);
                MaskComboBoxes1.Add(mask1);
                tabPage1.Controls.Add(mask1);

                ComboBox mask2 = new ComboBox();
                mask2.DropDownStyle = MaskComboBoxes2[0].DropDownStyle;
                mask2.DropDownHeight = MaskComboBoxes2[0].DropDownHeight;
                mask2.DrawMode = MaskComboBoxes2[0].DrawMode;
                mask2.ItemHeight = MaskComboBoxes2[0].ItemHeight;
                mask2.Size = MaskComboBoxes2[0].Size;
                mask2.Location = new Point(MaskComboBoxes2[0].Location.X + getCurrentOffsetX(i), MaskComboBoxes2[0].Location.Y);
                MaskComboBoxes2.Add(mask2);
                tabPage1.Controls.Add(mask2);

                Panel pan = new Panel();
                pan.Tag = new List<LineData>();
                pan.Size = LayoutPanels[0].Size;
                pan.Location = new Point(LayoutPanels[0].Location.X + getCurrentOffsetX(i), LayoutPanels[0].Location.Y);
                LayoutPanels.Add(pan);
                tabPage1.Controls.Add(pan);

                for (int j = 1; j < 16; ++j)
                {
                    PictureBox pc = new PictureBox();
                    pc.Size = new Size(pictureBoxSize, pictureBoxSize);
                    Point RowColumn = picBoxIdxToRowColumn(j);
                    pc.Location = new Point(pictureBoxSize * RowColumn.X, pictureBoxSize * RowColumn.Y);
                    pc.Tag = j.ToString();
                    pc.SizeMode = PictureBoxSizeMode.StretchImage;
                    pan.Controls.Add(pc);
                }

                CheckBox bt = new CheckBox();
                bt.Font = ResetButtons[0].Font;
                bt.Text = ResetButtons[0].Text;
                bt.Appearance = ResetButtons[0].Appearance;
                bt.TextAlign = ResetButtons[0].TextAlign;
                bt.Size = ResetButtons[0].Size;
                bt.Location = new Point(ResetButtons[0].Location.X + getCurrentOffsetX(i), ResetButtons[0].Location.Y);
                tabPage1.Controls.Add(bt);
                ResetButtons.Add(bt);
            }

            for (int i = 0; i < ResetButtons.Count; ++i)
            {
                ResetButtons[i].Tag = LayoutPanels[i];
                ResetButtons[i].CheckedChanged += resetCheckbox_CheckedChanged;
                ResetButtons[i].EnabledChanged += resetCheckbox_EnabledChanged;
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
                    pc.MouseUp += pictureBox_Click;
                    pc.Paint += pictureBox_Paint;
                    pc.MouseMove += pictureBox_MouseMove;
                }
            }

            for (int i = 0; i <= 12; ++i)
                LevelLabels2[i].Text = (i + 1).ToString();

            LevelLabels2[12].Text = "I";
            LevelLabels2[13].Text = "II";
            LevelLabels2[14].Text = "III";

            initLevelNumbers();
            initIconImages();

            foreach (TextBox tb in IntervalTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
                ArrowButtonsData ar = new ArrowButtonsData();
                ar.Step = 0.05f;
                tb.Tag = ar;
                SpawnArrows(tb);
            }

            foreach (TextBox tb in DurationTextBoxes)
            {
                tb.TextChanged += handleTextChanges;
                tb.KeyPress += handleKeyPress;
                ArrowButtonsData ar = new ArrowButtonsData();
                ar.Step = 0.05f;
                tb.Tag = ar;
                SpawnArrows(tb);
            }

            foreach (TextBox nb in NumbericUpDowns1)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                ArrowButtonsData ar = new ArrowButtonsData();
                ar.Step = 1;
                nb.Tag = ar;
                SpawnArrows(nb);
            }

            foreach (TextBox nb in NumbericUpDowns2)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                ArrowButtonsData ar = new ArrowButtonsData();
                ar.Step = 1;
                nb.Tag = ar;
                SpawnArrows(nb);
            }

            foreach (TextBox nb in NumbericUpDowns3)
            {
                nb.TextChanged += handleTextChanges_decimal;
                nb.KeyPress += handleKeyPress_decimal;
                ArrowButtonsData ar = new ArrowButtonsData();
                ar.Step = 1;
                nb.Tag = ar;
                SpawnArrows(nb);
            }

            foreach (Image img in maskImages)
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

            chart2.Series[0].Color = Color.FromArgb(150, 0, 25);
            chart2.Series[1].Color = Color.FromArgb(15, 15, 150);
            chart2.Series[2].Color = Color.FromArgb(alpha, 150, 150, 150);
            chart2.Series[3].Color = Color.FromArgb(alpha, 72, 69, 145);
            chart2.Series[4].Color = Color.FromArgb(alpha, 150, 16, 48);
            chart2.Series[5].Color = Color.FromArgb(alpha, 0, 0, 0);
            chart2.Series[6].Color = Color.FromArgb(180, 72, 69, 145);
            chart2.Series[7].Color = Color.FromArgb(180, 150, 16, 48);
            chart2.Series[8].Color = Color.FromArgb(alpha, 220, 160, 40);
            chart2.Series[9].Color = Color.FromArgb(150, 0, 25);
            chart2.Series[10].Color = Color.FromArgb(15, 15, 150);

            chart2.Series[9].IsVisibleInLegend = false;
            chart2.Series[10].IsVisibleInLegend = false;

            redrawChart();
            refreshLevelComboBox();

            if (comboBox31.Items.Count > 0)
            {
                string firstLevel = comboBox31.Items[0] as string;
                importToForm(fileNameToWorldNr(firstLevel));
                comboBox31.SelectedItem = firstLevel;
            }

            List<int> worldNrList = getAvailableWorldNrs();

            for (int i = 0; i < worldNrList.Count; ++i)
                addIconSet(i, worldNrList[i]);

            importInfoFile();
            updateInfoSaveButton();
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
            const int arrowSizeX = 19;
            const int arrowSizeY = 23;

            TextBox tx = ctrl as TextBox;

            if (tx != null)
            {
                Button bt1 = new Button();
                bt1.Image = Properties.Resources.arrow_left;
                bt1.Size = new Size(arrowSizeX, arrowSizeY);
                bt1.Location = new Point(tx.Location.X - arrowSizeX, tx.Location.Y);
                bt1.Tag = tx;
                bt1.Click += buttonArrow1_Click;
                tabPage1.Controls.Add(bt1);

                Button bt2 = new Button();
                bt2.Image = Properties.Resources.arrow_right;
                bt2.Size = new Size(arrowSizeX, arrowSizeY);
                bt2.Location = new Point(tx.Location.X + tx.Size.Width, tx.Location.Y);
                bt2.Tag = tx;
                bt2.Click += buttonArrow2_Click;
                tabPage1.Controls.Add(bt2);

                ArrowButtonsData arrowData = tx.Tag as ArrowButtonsData;
                arrowData.ArrowButtonLeft = bt1;
                arrowData.ArrowButtonRight = bt2;
            }
        }

        private void buttonArrow1_Click(object sender, EventArgs e)
        {
            Button bt = sender as Button;
            TextBox tx = bt.Tag as TextBox;
            float value = getValueFromTextbox(tx);

            ArrowButtonsData ar = tx.Tag as ArrowButtonsData;
            tx.Text = (Math.Max(value - ar.Step, 0.0f)).ToString();
        }

        private void buttonArrow2_Click(object sender, EventArgs e)
        {
            Button bt = sender as Button;
            TextBox tx = bt.Tag as TextBox;
            float value = getValueFromTextbox(tx);

            ArrowButtonsData ar = tx.Tag as ArrowButtonsData;
            tx.Text = (value + ar.Step).ToString();
        }

        private void refreshLevelComboBox()
        {
            ComboBox cb = comboBox31;
            cb.Items.Clear();

            List<int> worldNrList = getAvailableWorldNrs();

            foreach (int nr in worldNrList)
                cb.Items.Add(worldNrToString(nr));
        }

        private List<int> getAvailableWorldNrs()
        {
            string path = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location);
            string[] files = Directory.GetFiles(path, "*.lvl", SearchOption.AllDirectories);

            List<int> nrList = new List<int>();

            foreach (string fileName in files)
                nrList.Add(fileNameToWorldNr(fileName));

            nrList.Sort();
            return nrList;
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
                    importToForm(newWorldNr);
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

        public static Control FindFocusedControl(Control control)
        {
            var container = control as IContainerControl;
            while (container != null)
            {
                control = container.ActiveControl;
                container = control as IContainerControl;
            }
            return control;
        }

        protected override bool ProcessCmdKey(ref Message msg, Keys keyData)
        {
            if (keyData == (Keys.Control | Keys.S))
            {
                if (tabControl1.SelectedIndex == 0)
                {
                    save();
                }
                else 
                {
                    exportInfoFile();
                }

                return true;
            }
            else if (keyData == Keys.Space)
            {
                toggleEditMode();
                return true;
            }

            if (keyData == Keys.Up || keyData == Keys.Down)
            {
                Control ctrl = FindFocusedControl(this);

                if (ctrl != null)
                {
                    ArrowButtonsData arrowData = ctrl.Tag as ArrowButtonsData;

                    if (arrowData != null)
                    {
                        if (keyData == Keys.Up)
                        {
                            arrowData.ArrowButtonRight.PerformClick();
                        }
                        else
                        {
                            arrowData.ArrowButtonLeft.PerformClick();
                        }

                        return true;
                    }
                }
            }

            return base.ProcessCmdKey(ref msg, keyData);
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            if (!EditModeDoubleTaps() && !sequenceHelperActivated() && e.KeyCode == Keys.ControlKey)
                activateSequenceHelper(true);
        }

        private void Form1_KeyUp(object sender, KeyEventArgs e)
        {
            if (!EditModeDoubleTaps() && e.KeyCode == Keys.ControlKey)
            {
                activateSequenceHelper(false);
                clearUnfinishedLine();
            }
        }

        private void cantSaveInfoMsgBox()
        {
            MessageBox.Show("You cannot save world info data with empty icons!"
                , "Can't save world info data!", MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private bool dontQuit_ChangesMsgBox()
        {
            if (!isDirty())
                return false;

            DialogResult result =
                MessageBox.Show("Would you like to save your changes on the current level before proceeding?"
                , "Save changes?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button1);

            if (result == DialogResult.Yes)
            {
                if (tabControl1.SelectedIndex == 0)
                    save();
                else
                    exportInfoFile();
            }

            return result == DialogResult.Cancel;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (isAnyTabDirty())
            {
                DialogResult result = MessageBox.Show("Would you like to save all your before exiting?"
                                                        , "Save changes?", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question, MessageBoxDefaultButton.Button1);

                bool bSaveSuccessful = true;

                if (result == DialogResult.Yes)
                {
                    save();
                    bSaveSuccessful = exportInfoFile();
                }

                if (shouldPreventQuit(result, bSaveSuccessful))
                {
                    e.Cancel = true;
                }
            }
        }

        private bool shouldPreventQuit(DialogResult result, bool bSaveSuccessful)
        {
            return (result == DialogResult.Cancel || !bSaveSuccessful);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            WindowState = FormWindowState.Maximized;
        }

        private void Form1_Click(object sender, EventArgs e)
        {
            if (PendingResetButton != null)
                clearPendingResetButton();
        }

        private void Form1_MouseMove(object sender, MouseEventArgs e)
        {
            clearUnfinishedLine();
        }

        private bool isAnyTabDirty()
        {
            return tabPage1.Text.Contains('*') || tabPage3.Text.Contains('*');
        }

        private bool isDirtyTab1()
        {
            return tabPage1.Text.Contains('*');
        }

        private bool isDirty(bool bForceTabPage3 = false)
        {
            if (tabControl1.SelectedIndex == 0 && !bForceTabPage3)
            {
                return tabPage1.Text.Contains('*');
            }
            else
            {
                return tabPage3.Text.Contains('*');
            }
        }

        private void markAsDirty(bool bForceTabPage3 = false)
        {
            updateInfoSaveButton();

            if (isDirty(bForceTabPage3))
                return;

            if (tabControl1.SelectedIndex == 0 && !bForceTabPage3)
            {
                tabPage1.Text += " *";
            }
            else
            {
                tabPage3.Text += " *";
            }
        }

        private void markAsClean(bool bForceTabPage3 = false)
        {
            if (!isDirty(bForceTabPage3))
                return;

            if (tabControl1.SelectedIndex == 0 && !bForceTabPage3)
            {
                tabPage1.Text = tabPage1.Text.Substring(0, tabPage1.Text.Count() - 2);
            }
            else
            {
                tabPage3.Text = tabPage3.Text.Substring(0, tabPage3.Text.Count() - 2);
            }
        }

        private void markAsCleanTab1()
        {
            if (!isDirtyTab1())
                return;

            tabPage1.Text = tabPage1.Text.Substring(0, tabPage1.Text.Count() - 2);
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

            if (tx.Text.Length > 1 && tx.Text[0] == '0')
                tx.Text = tx.Text.Substring(1, tx.Text.Length - 1);

            redrawChart();
            markAsDirty();
        }

        private void handleTextChanges_decimalIcon(object sender, EventArgs e)
        {
            TextBox tx = sender as TextBox;

            if (tx.Text.Length > 1 && tx.Text[0] == '0')
                tx.Text = tx.Text.Substring(1, tx.Text.Length - 1);

            markAsDirty(true);
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

        private bool EditModeDoubleTaps()
        {
            return !checkBox1.Checked;
        }

        private void toggleEditMode()
        {
            checkBox1.Checked = !checkBox1.Checked;
        }

        private bool sequenceHelperActivated()
        {
            return checkBox4.Checked;
        }

        private void activateSequenceHelper(bool bNewState)
        {
            checkBox4.Checked = bNewState;
        }

        private void pictureBox_Click(object sender, EventArgs e)
        {
            if (PendingResetButton != null)
                clearPendingResetButton();

            PictureBox picBox = sender as PictureBox;
            MouseEventArgs me = e as MouseEventArgs;
            Panel panel = (picBox.Parent) as Panel;
            ButtonData bd = (picBox.Tag) as ButtonData;
            List<LineData> ldList = (panel.Tag) as List<LineData>;

            if (me.Button == MouseButtons.Right)
            {
                if (ldList.Count > 0 && !ldList.Last().bFinished)
                {
                    lastPanelUnderCursor = null;
                    ldList.Remove(ldList.Last());
                    panel.Refresh();
                }
            }
            else
            {
                if (EditModeDoubleTaps())
                {
                    SetPicBoxData(picBox, !bd.bDoubleTap);
                    markAsDirty();
                }
                else
                {
                    if (ldList.Count == 0 || ldList.Last().bFinished)
                    {
                        tryToStartNewLine(ldList, bd, picBox, me, panel);
                    }
                    else
                    {
                        lastPanelUnderCursor = null;

                        LineData ld = ldList.Last();
                        int EndIndex = bd.Index;

                        if (ld.StartButtonIndex != EndIndex && CanAddAnotherLineHere(ldList, EndIndex) && IsLineShapeOkay(ld.StartButtonIndex, EndIndex))
                        {
                            if (ConvertLongLineToShortOnesAndAddIfPossible(ldList, EndIndex, picBox, panel) && sequenceHelperActivated())
                            {
                                tryToStartNewLine(ldList, bd, picBox, me, panel);
                            }
                        }
                        else
                        {
                            ldList.Remove(ld);
                        }

                        panel.Refresh();
                    }
                }
            }

            updateResetButtonEnabledState(panel);
        }

        private void tryToStartNewLine(List<LineData> ldList, ButtonData bd, PictureBox picBox, MouseEventArgs me, Panel panel)
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

        private Point picBoxIdxToRowColumn(int index)
        {
            return new Point((index - 1) % 3, 4 - (index - 1) / 3);
        }

        private int picBoxRowColumnToIndex(Point RowColumn)
        {
            return (4 - RowColumn.Y) * 3 + RowColumn.X + 1;
        }

        private Point GetControlCenter(Control ctrl)
        {
            return new Point(ctrl.Location.X + ctrl.Width / 2, ctrl.Location.Y + ctrl.Height / 2);
        }

        private void updateResetButtonEnabledState(Panel pan)
        {
            int index = LayoutPanels.IndexOf(pan);
            bool bShouldBeEnabled = false;

            if (EditModeDoubleTaps())
            {
                foreach (Control ctrl in pan.Controls)
                {
                    PictureBox pc = ctrl as PictureBox;
                    ButtonData bt = (pc.Tag) as ButtonData;

                    if (bt.bDoubleTap)
                    {
                        bShouldBeEnabled = true;
                        break;
                    }
                }
            }
            else
            {
                List<LineData> ldList = pan.Tag as List<LineData>;
                bShouldBeEnabled = ldList.Count > 0;
            }

            ResetButtons[index].Enabled = bShouldBeEnabled;
        }

        private void updateAllResetButtonsEnabledState()
        {
            foreach (Panel pan in LayoutPanels)
                updateResetButtonEnabledState(pan);
        }

        private void SetPicBoxData(PictureBox picBox, bool bDoubleTap)
        {
            ButtonData bt = (picBox.Tag) as ButtonData;
            bt.bDoubleTap = bDoubleTap;

            picBox.Image = bt.bDoubleTap ? ButtonImages[1] : ButtonImages[0];
        }

        private bool CanAddAnotherLineHere(List<LineData> ldList, int buttonIdx, bool bRequireEmptyButtons = false)
        {
            int Count = bRequireEmptyButtons ? 1 : 0;

            foreach (LineData ld in ldList)
            {
                if (ld.StartButtonIndex == buttonIdx || ld.EndButtonIndex == buttonIdx)
                    Count++;
            }

            return Count < 2;
        }

        private bool IsLineShapeOkay(int StartButtonIndex, int EndButtonIndex)
        {
            Point startRowColumn = picBoxIdxToRowColumn(StartButtonIndex);
            Point endRowColumn = picBoxIdxToRowColumn(EndButtonIndex);

            return startRowColumn.X == endRowColumn.X || startRowColumn.Y == endRowColumn.Y || isDiagonalLine(startRowColumn, endRowColumn);
        }

        private bool ConvertLongLineToShortOnesAndAddIfPossible(List<LineData> ldList, int endButtonIdx, PictureBox endPicBox, Panel panel)
        {
            bool bLinesSuccessfullyAdded = true;

            LineData ldLast = ldList.Last();
            Point startRowColumn = picBoxIdxToRowColumn(ldLast.StartButtonIndex);
            Point endRowColumn = picBoxIdxToRowColumn(endButtonIdx);

            // Check if this is a short line already
            if (Math.Abs(startRowColumn.X - endRowColumn.X) <= 1 && Math.Abs(startRowColumn.Y - endRowColumn.Y) <= 1)
            {
                ldLast.LineEndLocation = GetControlCenter(endPicBox);
                ldLast.EndButtonIndex = endButtonIdx;
                ldLast.bFinished = true;
            }
            else if (isDiagonalLine(startRowColumn, endRowColumn))
            {
                Point middleRowColumn = new Point((startRowColumn.X + endRowColumn.X) / 2, (startRowColumn.Y + endRowColumn.Y) / 2);
                int middleIdx = picBoxRowColumnToIndex(middleRowColumn);
                PictureBox middlePicBox = GetPictureBoxWithIdx(panel, middleIdx);
                Point middleLocation = GetControlCenter(middlePicBox);

                if (CanAddAnotherLineHere(ldList, middleIdx, true))
                {
                    ldLast.LineEndLocation = middleLocation;
                    ldLast.EndButtonIndex = middleIdx;
                    ldLast.bFinished = true;

                    LineData ld = new LineData();
                    ld.StartButtonIndex = middleIdx;
                    ld.LineStartLocation = middleLocation;
                    ld.EndButtonIndex = endButtonIdx;
                    ld.LineEndLocation = GetControlCenter(endPicBox);
                    ld.bFinished = true;
                    ldList.Add(ld);
                }
                else
                {
                    bLinesSuccessfullyAdded = false;
                    ldList.Remove(ldLast);
                }
            }
            else
            {
                ldList.Remove(ldLast);

                bool bHorizontalLine = startRowColumn.Y == endRowColumn.Y;
                int startIdx = bHorizontalLine ? startRowColumn.X : startRowColumn.Y;
                int endIdx = bHorizontalLine ? endRowColumn.X : endRowColumn.Y;

                if (startIdx > endIdx)
                {
                    int tmp = endIdx;
                    endIdx = startIdx;
                    startIdx = tmp;
                }

                List<LineData> ldListTmp = new List<LineData>();

                for (int i = startIdx; i < endIdx; ++i)
                {
                    Point firstRowColumn = new Point();
                    Point secondRowColumn = new Point();

                    if (bHorizontalLine)
                    {
                        firstRowColumn.X = i;
                        firstRowColumn.Y = startRowColumn.Y;

                        secondRowColumn.X = i + 1;
                        secondRowColumn.Y = startRowColumn.Y;
                    }
                    else
                    {
                        firstRowColumn.X = startRowColumn.X;
                        firstRowColumn.Y = i;

                        secondRowColumn.X = startRowColumn.X;
                        secondRowColumn.Y = i + 1;
                    }

                    int firstIdx = picBoxRowColumnToIndex(firstRowColumn);
                    int secondIdx = picBoxRowColumnToIndex(secondRowColumn);
                    PictureBox firstPicBox = GetPictureBoxWithIdx(panel, firstIdx);
                    PictureBox secondPicBox = GetPictureBoxWithIdx(panel, secondIdx);

                    if (i == startIdx || CanAddAnotherLineHere(ldList, firstIdx, true))
                    {
                        LineData ld = new LineData();
                        ld.StartButtonIndex = firstIdx;
                        ld.LineStartLocation = GetControlCenter(firstPicBox);
                        ld.EndButtonIndex = secondIdx;
                        ld.LineEndLocation = GetControlCenter(secondPicBox);
                        ld.bFinished = true;
                        ldListTmp.Add(ld);
                    }
                    else
                    {
                        bLinesSuccessfullyAdded = false;
                        break;
                    }
                }

                if (bLinesSuccessfullyAdded)
                {
                    ldList.AddRange(ldListTmp);
                }
            }

            if (bLinesSuccessfullyAdded)
                markAsDirty();

            return bLinesSuccessfullyAdded;
        }

        private bool isDiagonalLine(Point startRowColumn, Point endRowColumn)
        {
            return Math.Abs(startRowColumn.X - endRowColumn.X) == Math.Abs(startRowColumn.Y - endRowColumn.Y);
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

            if (lastPanelUnderCursor != panel)
                clearUnfinishedLine();

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

        private void clearUnfinishedLine()
        {
            if (lastPanelUnderCursor != null)
            {
                List<LineData> ldList = (lastPanelUnderCursor.Tag) as List<LineData>;
                ldList.Remove(ldList.Last());
                lastPanelUnderCursor.Refresh();
                lastPanelUnderCursor = null;
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

        private bool isMaskKilling(int maskIdx)
        {
            string s = IdxToMaskCode(maskIdx);

            return s.Contains("Killing");
        }

        // ======================================== import ==========================================

        private WorldInfo importToWorldInfo(int worldNr)
        {
            WorldInfo wi = new WorldInfo();
            wi.nr = worldNr;

            string worldPath = worldNrToPath(worldNr);
            StreamReader sr = new StreamReader(worldPath);
            String line;
            LevelInfo li = wi.levelInfos[0];
            li.idx = -1;

            while ((line = sr.ReadLine()) != null)
            {
                if (line.Length > 1)
                {
                    if (line.Length > 2 && line[0] == '#' && line[1] == '!')
                    {
                        String s = line.Substring(2);
                        wi.comment = s;
                    }
                    else if (line[0] != '#')
                    {
                        line = line.Replace(".", ",");
                        String[] levelParamsOriginal = line.Split();
                        List<String> levelParams = new List<String>();

                        foreach (String s in levelParamsOriginal)
                            if (s.Length > 0)
                                levelParams.Add(s);

                        int levelIdx = li.idx + 1;
                        li = wi.levelInfos[levelIdx];
                        li.idx = levelIdx;

                        li.interval = float.Parse(levelParams[0]);
                        li.activation = float.Parse(levelParams[1]);
                        li.safe = int.Parse(levelParams[2]);
                        li.dangerous = int.Parse(levelParams[3]);
                        li.unfair = int.Parse(levelParams[4]);

                        if (levelParams.Count > 5)
                        {
                            li.maskIdx1 = MaskCodeToIdx(levelParams[5]);

                            if (levelParams.Count > 6)
                                li.maskIdx2 = MaskCodeToIdx(levelParams[6]);
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

                                if (currTileData.Contains("SQ"))
                                    sequenceData.Add(new SeqData(currTileData, idx));

                                li.doubleTaps[idx - 1] = currTileData.Contains("DB");
                            }
                        }

                        importSequenceData(sequenceData, li);
                    }
                }
            }

            sr.Close();

            return wi;
        }

        private void importToForm(int worldNr)
        {
            WorldInfo wi = importToWorldInfo(worldNr);
            applyWorldInfoToForm(wi);
        }

        private void applyWorldInfoToForm(WorldInfo wi)
        {
            openedWorldNr = wi.nr;
            initLevelNumbers();

            textBox31.Text = wi.comment;

            for (int i = 0; i < 15; ++i)
            {
                LevelInfo li = wi.levelInfos[i];

                IntervalTextBoxes[i].Text = li.interval.ToString();
                DurationTextBoxes[i].Text = li.activation.ToString();
                NumbericUpDowns1[i].Text = li.safe.ToString();
                NumbericUpDowns2[i].Text = li.dangerous.ToString();
                NumbericUpDowns3[i].Text = li.unfair.ToString();

                MaskComboBoxes1[i].SelectedIndex = li.maskIdx1;
                MaskComboBoxes2[i].SelectedIndex = li.maskIdx2;

                for (int j = 0; j < 15; ++j)
                {
                    PictureBox pc = GetPictureBoxWithIdx(LayoutPanels[i], j + 1);
                    SetPicBoxData(pc, li.doubleTaps[j]);

                    LayoutPanels[i].Tag = li.sequences;
                }
            }

            markAsClean();
            updateAllResetButtonsEnabledState();
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

        private void importSequenceData(List<SeqData> originalSequenceData, LevelInfo li)
        {
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
                        ld.LineStartLocation = GetButtonCenter(Sequence[i].TileIndex, LayoutPanels[li.idx]);
                        ld.LineEndLocation = GetButtonCenter(Sequence[i + 1].TileIndex, LayoutPanels[li.idx]);
                        li.sequences.Add(ld);
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

                addIconSet(IconTextBoxes.Count(), createdWorldNr);
            }
        }

        private void save()
        {
            export(openedWorldNr);
            markAsCleanTab1();
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

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = sender as CheckBox;

            if (cb.Checked)
            {
                cb.Text = "Sequences";
                checkBox4.Enabled = true;
            }
            else
            {
                cb.Text = "Double Taps";
                checkBox4.Enabled = false;
            }

            updateAllResetButtonsEnabledState();

            if (PendingResetButton != null)
                clearPendingResetButton();
        }

        private void resetCheckbox_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = sender as CheckBox;

            if (cb.Checked)
            {
                cb.Text = "You sure?";
                setNewPendingResetButton(cb);
            }
            else
            {
                cb.Text = "Reset";

                if (!bClearingResetTimersInProgress)
                {
                    clearPendingResetButton();
                    resetPanel(cb.Tag as Panel);
                }
            }
        }

        private void resetCheckbox_EnabledChanged(object sender, EventArgs e)
        {
            bool bShouldResetAllBeEnabled = false;

            foreach (CheckBox resetBt in ResetButtons)
            {
                if (resetBt.Enabled)
                {
                    bShouldResetAllBeEnabled = true;
                    break;
                }
            }

            checkBox3.Enabled = bShouldResetAllBeEnabled;
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox cb = sender as CheckBox;

            if (cb.Checked)
            {
                cb.Text = "You sure?";
                setNewPendingResetButton(cb);
            }
            else
            {
                cb.Text = "Reset All";

                if (!bClearingResetTimersInProgress)
                {
                    clearPendingResetButton();

                    foreach (Panel pan in LayoutPanels)
                        resetPanel(pan);
                }
            }
        }

        private void resetPanel(Panel pan)
        {
            if (EditModeDoubleTaps())
            {
                foreach (Control ctrl in pan.Controls)
                {
                    SetPicBoxData(ctrl as PictureBox, false);
                }
            }
            else
            {
                pan.Tag = new List<LineData>();
                pan.Refresh();
            }

            markAsDirty();
            updateResetButtonEnabledState(pan);
        }

        private void setNewPendingResetButton(CheckBox cb)
        {
            if (PendingResetButton != null)
                clearPendingResetButton();

            PendingResetButton = cb;

            ResetButtonsTimer = new System.Timers.Timer(1000);
            ResetButtonsTimer.SynchronizingObject = this;
            ResetButtonsTimer.Elapsed += resetTimerElapsed;
            ResetButtonsTimer.Enabled = true;
        }

        private void resetTimerElapsed(Object source, System.Timers.ElapsedEventArgs e)
        {
            clearPendingResetButton();
        }

        private void clearPendingResetButton()
        {
            ResetButtonsTimer.Close();
            ResetButtonsTimer = null;

            bClearingResetTimersInProgress = true;
            PendingResetButton.Checked = false;
            bClearingResetTimersInProgress = false;

            PendingResetButton = null;
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {
            int newIdx = (sender as TabControl).SelectedIndex;
            TabPage gameOverviewPage = (sender as TabControl).TabPages[1];

            if (newIdx == 1)
            {
                const int startOffsetX = 10;
                const int startOffsetY = 5;
                const int offsetX = 65;
                const int offsetY = 30;

                chart2.Series[0].Points.Clear();
                chart2.Series[1].Points.Clear();
                chart2.Series[2].Points.Clear();
                chart2.Series[3].Points.Clear();
                chart2.Series[4].Points.Clear();
                chart2.Series[5].Points.Clear();
                chart2.Series[6].Points.Clear();
                chart2.Series[7].Points.Clear();
                chart2.Series[8].Points.Clear();
                chart2.Series[9].Points.Clear();
                chart2.Series[10].Points.Clear();

                List <int> worldNrList = getAvailableWorldNrs();
                float max = 0;
                int maxMechUsed = 0;

                for (int i = 0; i < worldNrList.Count; ++i)
                {
                    WorldInfo wi = importToWorldInfo(worldNrList[i]);
                    SummaryWorldInfo summary = generateSummaryWorldInfo(wi);

                    generateGameOverviewLabel(summary.nr.ToString(), new Point(startOffsetX + i * offsetX, startOffsetY), true);
                    generateGameOverviewLabel(Math.Round(summary.avgInterval, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY));
                    generateGameOverviewLabel(Math.Round(summary.avgActivation, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 2));
                    generateGameOverviewLabel(Math.Round(summary.avgDoubleTaps, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 3));
                    generateGameOverviewLabel(Math.Round(summary.avgSafe, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 4));
                    generateGameOverviewLabel(Math.Round(summary.avgDangerous, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 5));
                    generateGameOverviewLabel(Math.Round(summary.avgUnfair, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 6));
                    generateGameOverviewLabel(Math.Round(summary.avgSaveMasks, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 7));
                    generateGameOverviewLabel(Math.Round(summary.avgKillingMasks, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 8));
                    generateGameOverviewLabel(Math.Round(summary.avgSequenceLength, 2).ToString(), new Point(startOffsetX + i * offsetX, startOffsetY + offsetY * 9));

                    chart2.Series[9].Points.AddXY(wi.nr, summary.avgInterval);
                    chart2.Series[10].Points.AddXY(wi.nr, summary.avgActivation);

                    int[] mechUsed = new int[7];
                    int mechUsedSum = 0;

                    mechUsed[0] = summary.avgDoubleTaps > 0 ? 1 : 0;
                    mechUsed[1] = summary.avgSafe > 0 ? 1 : 0;
                    mechUsed[2] = summary.avgDangerous > 0 ? 1 : 0;
                    mechUsed[3] = summary.avgUnfair > 0 ? 1 : 0;
                    mechUsed[4] = summary.avgSaveMasks > 0 ? 1 : 0;
                    mechUsed[5] = summary.avgKillingMasks > 0 ? 1 : 0;
                    mechUsed[6] = summary.avgSequenceLength > 0 ? 1 : 0;

                    for (int j = 0; j < mechUsed.Count(); ++j)
                    {
                        chart2.Series[j + 2].Points.AddXY(wi.nr, mechUsed[j]);
                        mechUsedSum += mechUsed[j];
                    }

                    if (summary.avgInterval > max)
                        max = summary.avgInterval;

                    if (summary.avgActivation > max)
                        max = summary.avgActivation;

                    if (mechUsedSum > maxMechUsed)
                        maxMechUsed = mechUsedSum;
                }

                double finalMaxY = Math.Ceiling(max * 2.0) / 2.0;
                chart2.ChartAreas[0].Axes[1].Maximum = finalMaxY;
                chart2.ChartAreas[0].Axes[1].Interval = 0.5f;

                chart2.ChartAreas[0].Axes[0].Interval = 1.0f;
                chart2.ChartAreas[0].Axes[0].IntervalOffset = 0.5f;
                chart2.ChartAreas[0].Axes[0].Minimum = -0.5f;
                chart2.ChartAreas[0].Axes[0].Maximum = worldNrList.Count - 0.5f;

                for (int i = 0; i < worldNrList.Count; ++i)
                    for (int j = 2; j < 9; ++j)
                        chart2.Series[j].Points[i].YValues[0] *= finalMaxY / maxMechUsed;
            }
            else
            {
                panel2.Controls.Clear();
            }
        }

        private void updateInfoSaveButton()
        {
            button1.Enabled = isSavingInfoPossible();
        }

        private bool isSavingInfoPossible()
        {
            foreach (ComboBox cb in IconComboBoxes)
            {
                IconData ic = cb.SelectedItem as IconData;

                if (ic == EmptyIconImage)
                    return false;
            }

            return true;
        }

        private void addIconSet(int i, int worldNr)
        {
            Point labelLocation = new Point(IconComboBoxes[0].Location.X + (i % iconTabMaxWorldInRow) * iconTabOffsetX,
                                IconComboBoxes[0].Location.Y + iconTabLabelOffsetY + iconTabOffsetY * (int)(i / iconTabMaxWorldInRow));

            generateIconOverviewLabel(worldNr.ToString(), labelLocation, true);

            if (i > 0)
            {
                addIconCombobox(false);
                addIconTextbox(false);
                addIconPicturebox();
            }
            else
            {
                addIconCombobox(true);
                addIconTextbox(true);
            }
        }

        private void addIconPicturebox()
        {
            int i = LockPicBoxes.Count();
            PictureBox pc = new PictureBox();
            pc.SizeMode = LockPicBoxes[0].SizeMode;
            pc.Image = LockPicBoxes[0].Image;
            pc.Location = new Point(LockPicBoxes[0].Location.X + (i % iconTabMaxWorldInRow) * iconTabOffsetX, LockPicBoxes[0].Location.Y + iconTabOffsetY * (int)(i / iconTabMaxWorldInRow));
            pc.Size = LockPicBoxes[0].Size;
            LockPicBoxes.Add(pc);
            panel3.Controls.Add(pc);
        }

        private void addIconTextbox(bool bAlreadyCreated)
        {
            int i = IconTextBoxes.Count();
            TextBox tx;

            if (bAlreadyCreated)
            {
                tx = IconTextBoxes[0];
            }
            else
            {
                tx = new TextBox();
                tx.Font = IconTextBoxes[0].Font;
                tx.Size = IconTextBoxes[0].Size;
                tx.Text = "0";
                tx.Location = new Point(IconTextBoxes[0].Location.X + iconTabOffsetX * (i % iconTabMaxWorldInRow), IconTextBoxes[0].Location.Y + iconTabOffsetY * (int)(i / iconTabMaxWorldInRow));
                IconTextBoxes.Add(tx);
                panel3.Controls.Add(tx);
            }

            tx.TextChanged += handleTextChanges_decimalIcon;
            tx.KeyPress += handleKeyPress_decimal;
        }

        private void addIconCombobox(bool bAlreadyCreated)
        {
            const int dropDownHeightBase = 920;
            int i = IconComboBoxes.Count();
            ComboBox cb;

            if (bAlreadyCreated)
            {
                cb = IconComboBoxes[0];
            }
            else
            {
                cb = new ComboBox();
                cb.DropDownStyle = IconComboBoxes[0].DropDownStyle;
                cb.DropDownHeight = IconComboBoxes[0].DropDownHeight;
                cb.DrawMode = IconComboBoxes[0].DrawMode;
                cb.ItemHeight = IconComboBoxes[0].ItemHeight;
                cb.Size = IconComboBoxes[0].Size;
                cb.Location = new Point(IconComboBoxes[0].Location.X + iconTabOffsetX * (i % iconTabMaxWorldInRow), IconComboBoxes[0].Location.Y + iconTabOffsetY * (int)(i / iconTabMaxWorldInRow));
                IconComboBoxes.Add(cb);
                panel3.Controls.Add(cb);
            }

            cb.DropDownHeight = dropDownHeightBase - cb.Location.Y;
            cb.MeasureItem += comboBoxIcon_MeasureItem;
            cb.DrawItem += comboBoxIcon_DrawItem;
            cb.SelectedValueChanged += comboBoxIcon_SelectedValueChanged;
            cb.DropDown += comboBoxIcon_DropDown;

            cb.Items.Add(EmptyIconImage);
            cb.SelectedIndex = 0;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            exportInfoFile();
        }

        private bool exportInfoFile()
        {
            if (!isSavingInfoPossible())
            {
                cantSaveInfoMsgBox();
                return false;
            }

            string path = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\_Info.txt";
            StreamWriter sr = new StreamWriter(path);

            foreach (ComboBox cb in IconComboBoxes)
            {
                IconData ic = cb.SelectedItem as IconData;

                if (ic.path.Count() > 0)
                {
                    string[] tmp = ic.path.Split('\\');
                    sr.WriteLine(tmp.Last());
                }
                else
                {
                    sr.WriteLine();
                }
            }

            sr.WriteLine();
            sr.WriteLine("# unlock levels");

            foreach (TextBox tx in IconTextBoxes)
            {
                sr.WriteLine(tx.Text);
            }

            sr.Close();
            markAsClean();

            return true;
        }

        private void importInfoFile()
        {
            string path = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location) + "\\_Info.txt";
            StreamReader sr = new StreamReader(path);
            String line;
            bool bReadingIcons = true;
            int index = 0;

            while ((line = sr.ReadLine()) != null)
            {
                if (bReadingIcons)
                {
                    if (line.Length > 1)
                    {
                        if (line[0] == '#')
                        {
                            bReadingIcons = false;
                            index = 0;
                        }
                        else if (index < IconComboBoxes.Count())
                        {
                            foreach (IconData ic in AllIconImages)
                            {
                                if (ic.path.Contains(line))
                                {
                                    IconComboBoxes[index].Items.Clear();
                                    IconComboBoxes[index].Items.Add(ic);
                                    IconComboBoxes[index].SelectedIndex = 0;
                                    ++index;
                                    break;
                                }
                            }
                        }
                    }
                    else if (index < IconComboBoxes.Count())
                    {
                        IconComboBoxes[index].SelectedItem = EmptyIconImage;
                        ++index;
                    }
                }
                else if (index < IconTextBoxes.Count())
                {
                    if (line.Length > 1)
                    {
                        IconTextBoxes[index].Text = line;
                        ++index;
                    }
                    else
                    {
                        IconTextBoxes[index].Text = "0";
                        ++index;
                    }
                }
            }

            sr.Close();
            markAsClean(true);
        }

        private void initIconImages()
        {
            string[] basePath = Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location).Split('\\');
            string finalBasePath = "";

            for (int i = 0; i < basePath.Count() - 1; ++i)
                finalBasePath += basePath[i] + "\\";

            finalBasePath += "gui\\signs";

            string[] iconImages = Directory.GetFiles(finalBasePath, "*.png", SearchOption.AllDirectories);


            EmptyIconImage = new IconData();
            EmptyIconImage.path = "";
            EmptyIconImage.img = Properties.Resources.empty_icon;

            AllIconImages = new List<IconData>();

            foreach (string iconPath in iconImages)
            {
                if (iconPath.Contains("inactive"))
                {
                    IconData ic = new IconData();
                    ic.path = iconPath;
                    ic.img = new Bitmap(iconPath);
                    AllIconImages.Add(ic);
                }
            }
        }

        private void comboBoxIcon_DropDown(object sender, EventArgs e)
        {
            ComboBox senderCb = sender as ComboBox;
            List<IconData> availableIcons = new List<IconData>(AllIconImages);

            foreach (ComboBox cb in IconComboBoxes)
                if (senderCb != cb)
                    availableIcons.Remove(cb.SelectedItem as IconData);

            object ic = senderCb.SelectedItem;
            senderCb.Items.Clear();
            senderCb.Items.Add(EmptyIconImage);
            senderCb.Items.AddRange(availableIcons.ToArray());
            senderCb.SelectedItem = ic;
        }

        private void comboBoxIcon_SelectedValueChanged(object sender, EventArgs e)
        {
            markAsDirty(true);

            bool tmp = button1.Enabled;
            button1.Enabled = true;
            button1.Focus();
            button1.Enabled = tmp;
        }

        private void comboBoxIcon_DrawItem(object sender, DrawItemEventArgs e)
        {
            if (e.Index < 0) return;

            e.DrawBackground();

            ComboBox cbo = sender as ComboBox;
            IconData ic = cbo.Items[e.Index] as IconData;
            Image img = ic.img;
            float hgt = e.Bounds.Height - 2 * MarginHeight;
            float scale = hgt / img.Height;
            float wid = img.Width * scale;
            RectangleF rect = new RectangleF(e.Bounds.X + MarginWidth, e.Bounds.Y + MarginHeight, wid, hgt);
            e.Graphics.InterpolationMode = System.Drawing.Drawing2D.InterpolationMode.HighQualityBilinear;
            e.Graphics.DrawImage(img, rect);
        }

        private void comboBoxIcon_MeasureItem(object sender, MeasureItemEventArgs e)
        {
            const int desiredSize = 40;

            if (e.Index < 0) return;

            e.ItemHeight = desiredSize + 2 * MarginHeight;
            e.ItemWidth = desiredSize + 2 * MarginWidth;
        }

        private void generateGameOverviewLabel(string text, Point location, bool bBold = false)
        {
            Label lbl = new Label();
            lbl.TextAlign = LevelLabels1[0].TextAlign;
            lbl.Font = new Font(LevelLabels1[0].Font, bBold ? FontStyle.Bold : FontStyle.Regular);
            lbl.Size = new Size(60, 23);
            lbl.AutoSize = false;
            lbl.TextAlign = ContentAlignment.MiddleCenter;
            lbl.Location = location;
            lbl.Text = text;
            panel2.Controls.Add(lbl);
        }

        private void generateIconOverviewLabel(string text, Point location, bool bBold = false)
        {
            Label lbl = new Label();
            lbl.TextAlign = LevelLabels1[0].TextAlign;
            lbl.Font = new Font(LevelLabels1[0].Font, bBold ? FontStyle.Bold : FontStyle.Regular);
            lbl.Size = new Size(60, 23);
            lbl.AutoSize = false;
            lbl.TextAlign = ContentAlignment.MiddleCenter;
            lbl.Location = location;
            lbl.Text = text;
            panel3.Controls.Add(lbl);
        }

        private SummaryWorldInfo generateSummaryWorldInfo(WorldInfo wi)
        {
            SummaryWorldInfo summary = new SummaryWorldInfo();
            summary.nr = wi.nr;

            for (int i = 0; i < 12; ++i)
            {
                LevelInfo li = wi.levelInfos[i];

                summary.avgInterval += li.interval;
                summary.avgActivation += li.activation;
                summary.avgSafe += li.safe;
                summary.avgDangerous += li.dangerous;
                summary.avgUnfair += li.unfair;

                if (li.maskIdx1 != 0)
                {
                    if (isMaskKilling(li.maskIdx1))
                        ++summary.avgKillingMasks;
                    else
                        ++summary.avgSaveMasks;
                }

                if (li.maskIdx2 != 0)
                {
                    if (isMaskKilling(li.maskIdx2))
                        ++summary.avgKillingMasks;
                    else
                        ++summary.avgSaveMasks;
                }

                for (int j = 0; j < 15; ++j)
                    if (li.doubleTaps[j] == true)
                        ++summary.avgDoubleTaps;

                summary.avgSequenceLength += li.sequences.Count;
            }

            summary.avgInterval /= 12.0f;
            summary.avgActivation /= 12.0f;
            summary.avgDoubleTaps /= 12.0f;
            summary.avgSafe /= 12.0f;
            summary.avgDangerous /= 12.0f;
            summary.avgUnfair /= 12.0f;
            summary.avgSaveMasks /= 12.0f;
            summary.avgKillingMasks /= 12.0f;
            summary.avgSequenceLength /= 12.0f;

            return summary;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            var myForm = new Form2();
            myForm.Show();
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

    class ArrowButtonsData
    {
        public Button ArrowButtonLeft;
        public Button ArrowButtonRight;
        public float Step;
    }

    class WorldInfo
    {
        public int nr;
        public string comment;
        public LevelInfo[] levelInfos;

        public WorldInfo()
        {
            levelInfos = new LevelInfo[15];
            for (int i = 0; i < 15; ++i)
                levelInfos[i] = new LevelInfo();
        }
    }

    class LevelInfo
    {
        public int idx;

        public float interval;
        public float activation;
        public int safe;
        public int dangerous;
        public int unfair;

        public int maskIdx1;
        public int maskIdx2;

        public bool[] doubleTaps;
        public List<LineData> sequences;

        public LevelInfo()
        {
            doubleTaps = new bool[15];
            sequences = new List<LineData>();
        }
    }

    class SummaryWorldInfo
    {
        public int nr;
        public float avgInterval;
        public float avgActivation;
        public float avgSafe;
        public float avgDangerous;
        public float avgUnfair;
        public float avgSaveMasks;
        public float avgDoubleTaps;
        public float avgKillingMasks;
        public float avgSequenceLength;
    }

    class IconData
    {
        public string path;
        public Image img;

        public override bool Equals(object obj)
        {
            var item = obj as IconData;

            if (item == null)
            {
                return false;
            }

            return path == item.path;
        }

        public override int GetHashCode()
        {
            return path.GetHashCode();
        }
    }
}
