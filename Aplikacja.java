import javax.swing.*; 
import java.awt.*;
import java.awt.event.*;

/** Klasa g³ówna */
public class Aplikacja extends JFrame
{
    public static Kernel kernel;
    public Graph graph;
/** Tablica prze³¹czników dzia³ania j¹dra.
* Switches[0] - wykonaj InsertionSort
* Switches[1] - wykonaj MergeSort
* Switches[2] - wykonaj HeapSort
* Switches[3] - wykonaj QuickSort
* Switches[4] - wypisz dane w konsoli
* Switches[5] - zapisz dane w pliku
**/
    public boolean Switches[] = new boolean[7];;
/** Przycisk inicjuj¹cy wykonywanie sortowania. Tworzy obiekt @see kernel z zadanymi parametrami*/
    private JButton sortButton;
    private JButton fileNameButton;
/** Wykonaj sortowanie przez wstawianie. */
    private JCheckBox cb1;
/** Wykonaj sortowanie przez scalanie. */
    private JCheckBox cb2;
/** Wykonaj sortowanie przez kopcowanie. */
    private JCheckBox cb3;
/** Wykonaj sortowanie szybkie. */
    private JCheckBox cb4;
/** Zapisz rezultaty w pliku. */
    private JCheckBox toFile;
/** Wypisz dane. */
    private JCheckBox writeData;
/** Nazwa pliku, do którego zapisywane bêd¹ wyniki. */
    public static String fileName="";
/** Wybrany rodzaj danych */
    public int dataKind;
    public JComboBox cmbDataKind;
/** Pasek menu */
    private JMenuBar mainMenuBar;
    private JMenu mainMenu;
    private JMenuItem errors;
    private JMenu inversionMenu;
    private JRadioButtonMenuItem allInversions;
    private JRadioButtonMenuItem swapInversions;
    private JRadioButtonMenuItem stepInversions;
    private ButtonGroup inversionsButtonGroup;
    private static int inversionCountingKind = 1;
    private JCheckBoxMenuItem drawAverage;
/*    private ActionListener menuListener = new ActionListener()
    {
	public void actionPerformed(ActionEvent e)
	{
	    if(e.getSource()==allInversions)
		inversionCountingKind = 1;  
	    if(e.getSource()==swapInversions)
		inversionCountingKind = 2; 
	    if(e.getSource()==stepInversions)
		inversionCountingKind = 3;
	}
    };*/

    public JTextField numOfTestsTextField;
    public JTextField dataLengthTextField; 
    public Aplikacja()
    {

	ActionListener al = new ActionListener()
	{
	    public void actionPerformed(ActionEvent e)
	    {
		Switches[0] = cb1.isSelected();
		Switches[1] = cb2.isSelected();
		Switches[2] = cb3.isSelected();
		Switches[3] = cb4.isSelected();
		Switches[4] = writeData.isSelected();
		Switches[5] = toFile.isSelected();
		Switches[6] = drawAverage.isSelected();
		dataKind = cmbDataKind.getSelectedIndex();
		/*for(int i=0;i<6;i++)
		    System.out.println(Switches[i]);*/ //test dzia³ania
	    if(e.getSource()==allInversions)
		inversionCountingKind = 1;  
	    if(e.getSource()==swapInversions)
		inversionCountingKind = 2; 
	    if(e.getSource()==stepInversions)
		inversionCountingKind = 3;
		if(e.getSource() == sortButton)
		{
		    if(dataKind>0)
		    {
		        String strNumOfTest = numOfTestsTextField.getText();
		        String strDataLength = dataLengthTextField.getText();
		        int numOfTests, dataLength;
		        try
		        {
			    numOfTests = Integer.parseInt(strNumOfTest);
		        }
		        catch(NumberFormatException exc)
		        {
			    numOfTests = 1;
			    numOfTestsTextField.setText("B£¥D(1)");
		        }
		        try
		        {
			    dataLength = Integer.parseInt(strDataLength);
		        }
		        catch(NumberFormatException exc)
		        {
			    dataLength = 1;
			    dataLengthTextField.setText("B£¥D(2)");
		        }
		        if(dataLength<2)
		        {
			        //System.out.println(dataLength+"\n"+strDataLength);
			        dataLength = 1;
			        dataLengthTextField.setText("B£¥D(3)");
		        }
		        if(numOfTests<1)
		        {
			    numOfTests = 1;
			    numOfTestsTextField.setText("B£¥D(4)");
		        }
		        if(!Switches[0] && !Switches[1] && !Switches[2] && !Switches[3])
		        {
			    Switches[0] = true;
			    dataLengthTextField.setText("B£¥D(5)");			
		        }
		        if(toFile.isSelected())
		        {
			    kernel = new Kernel(Switches, fileName , numOfTests, dataLength, dataKind, inversionCountingKind);			
		        }//wywo³aj konstruktor z nazw¹ pliku
		        else
		        {
			    kernel = new Kernel(Switches, "", numOfTests, dataLength, dataKind, inversionCountingKind);
		        }//wywo³aj konstruktor bez zapisywania wyników obliczeñ do pliku
		        if(dataKind<3 && numOfTests>2)
			    graph = new Graph(kernel, Switches);
		    }
		    else
		    {
		    }//nie wybrano rodzaju danych
		}
		if(e.getSource() == fileNameButton)
		{
		    fileName = JOptionPane.showInputDialog("Podaj nazwê pliku:");
		}
	    }
	};
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setLayout(null);

/** Informacja o CheckBox'ach dotycz¹cych zaznaczenia rodzajów sortowania  */
	JLabel inf3 = new JLabel("Zaznacz rodzaj sortowania");
	inf3.setBounds(20,40, 160, 20);
	cb1 = new JCheckBox("InsertionSort");
	cb1.setBounds(40,60,120,20);
	cb2 = new JCheckBox("MergeSort");
	cb2.setBounds(40,80,120,20);
	cb3 = new JCheckBox("HeapSort");
	cb3.setBounds(40,100,120,20);
	cb4 = new JCheckBox("QuickSort");
	cb4.setBounds(40,120,120,20);
	writeData = new JCheckBox("Wypisz dane w konsoli");
	writeData.setBounds(180,60,160,20);
	toFile = new JCheckBox("Zapisz wyniki w pliku");
	toFile.setBounds(180,80,160,20);
	sortButton = new JButton("Sortuj");
	sortButton.setBounds(60,170,110,40);
	fileNameButton = new JButton("Nazwa pliku");
	fileNameButton.setBounds(190,170,110,40);

	cb1.addActionListener(al);
	cb2.addActionListener(al);
	cb3.addActionListener(al);
	cb4.addActionListener(al);
	writeData.addActionListener(al);
	toFile.addActionListener(al);
	sortButton.addActionListener(al);
	fileNameButton.addActionListener(al);

	cmbDataKind = new JComboBox();
	cmbDataKind.setBounds(180,40,200,20);
	cmbDataKind.addItem("Wybierz rodzaj danych...");
	cmbDataKind.addItem("Losowa permutacja");
	cmbDataKind.addItem("Losowe");	
	cmbDataKind.addItem("Posortowane rosn¹co");
	cmbDataKind.addItem("Posortowane malej¹co");
	cmbDataKind.addActionListener(al);

	mainMenuBar = new JMenuBar();
	mainMenu = new JMenu("Menu");
	errors = new JMenuItem("Lista b³êdów");
	errors.addActionListener(al);
	mainMenu.add(errors);
	drawAverage = new JCheckBoxMenuItem("Rysuj œredni¹",true);
	mainMenu.add(drawAverage);
	mainMenuBar.add(mainMenu);
	inversionMenu = new JMenu("Liczenie inwersji");
        inversionsButtonGroup = new ButtonGroup();
        allInversions = new JRadioButtonMenuItem("Licz wszystkie");
	allInversions.addActionListener(al);
	inversionsButtonGroup.add(allInversions);
        swapInversions = new JRadioButtonMenuItem("T(i)+1=T(i+1)");
	swapInversions.addActionListener(al);
	inversionsButtonGroup.add(swapInversions);
        stepInversions = new JRadioButtonMenuItem("T(i)=i+1");
	stepInversions.addActionListener(al);
	inversionsButtonGroup.add(stepInversions);
	inversionMenu.add(allInversions);
	inversionMenu.add(swapInversions);
	inversionMenu.add(stepInversions);
	mainMenuBar.add(inversionMenu);
	setJMenuBar(mainMenuBar);


	JLabel inf1 = new JLabel("Liczba testów");
	inf1.setBounds(180,100,80,20);
	numOfTestsTextField = new JTextField("300",5);
	numOfTestsTextField.setBounds(180,120,50,20);
	JLabel inf2 = new JLabel("Rozmiar tablicy");
	inf2.setBounds(280,100,120,20);
	dataLengthTextField = new JTextField(5);
	dataLengthTextField.setBounds(280,120,50,20);
	dataLengthTextField.setColumns(5);
	numOfTestsTextField.setColumns(5);
	numOfTestsTextField.selectAll();

	add(inf1);
	add(inf2);
	add(inf3);
	add(cb1);
	add(cb2);
	add(cb3);
	add(cb4);
	add(writeData);
	add(toFile);
	add(sortButton);
	add(fileNameButton);
	add(cmbDataKind);
	add(numOfTestsTextField);
	add(dataLengthTextField);

	setSize(400,300);
	setResizable(false);
	setTitle("Analiza algorytmów sortowania");
	setVisible(true);
    }
    public static void main(String args[])
    {
	SwingUtilities.invokeLater(new Runnable() {
	    public void run() {
		new Aplikacja();
	    }
	});
    }
}