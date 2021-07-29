import javax.swing.*; 
import java.awt.*;
import java.awt.event.*;

/** Klasa obs³uguj¹ca rysowanie wykresów */
class Graph extends JFrame
{
    private Kernel kernel;
    private Paint graph;
    private JRadioButton insButton;
    private JRadioButton mrgButton;
    private JRadioButton hpButton;
    private JRadioButton qckButton;
    private ButtonGroup sortButtons;
    private static boolean drawAverage;
    public Graph(Kernel kernel, boolean[] switches)
    {
	setSize(720,570);
	drawAverage = switches[6];
	ActionListener al = new ActionListener()
	{
	    public void actionPerformed(ActionEvent e)
	    {
		if(e.getSource()==insButton)
		    graph.setGraph(1);
		if(e.getSource()==mrgButton)
		    graph.setGraph(2);
		if(e.getSource()==hpButton)
		    graph.setGraph(3);
		if(e.getSource()==qckButton)
		    graph.setGraph(4);
		graph.repaint();
	    }
	};
	this.kernel = kernel;
	sortButtons = new ButtonGroup();
	int buttonHeight = 50;
	setLayout(null);
	JPanel radioPanel = new JPanel(new GridLayout(0,1));
	if(switches[0])
	{
	    insButton = new JRadioButton("InsertionSort");
	    insButton.addActionListener(al);
	    sortButtons.add(insButton);
	    //insButton.setBounds(600,buttonHeight,680,buttonHeight+20);
	    radioPanel.add(insButton);
	    buttonHeight+=20;
	}
	if(switches[1])
	{
	    mrgButton = new JRadioButton("MergeSort");
	    mrgButton.addActionListener(al);
	    sortButtons.add(mrgButton);
	    //mrgButton.setBounds(600,buttonHeight,680,buttonHeight+20);
	    radioPanel.add(mrgButton);
	    buttonHeight+=20;
	}
	if(switches[2])
	{
	    hpButton = new JRadioButton("HeapSort");
	    hpButton.addActionListener(al);
	    sortButtons.add(hpButton);
	    //hpButton.setBounds(600,buttonHeight,680,buttonHeight+20);
	    radioPanel.add(hpButton);
	    buttonHeight+=20;
	}
	if(switches[3])
	{
	    qckButton = new JRadioButton("QuickSort");
	    qckButton.addActionListener(al);
	    sortButtons.add(qckButton);
	    //qckButton.setBounds(600,buttonHeight,680,buttonHeight+20);
	    radioPanel.add(qckButton);
	    buttonHeight+=20;
	}

	radioPanel.setBounds(600,50,720,150);
	add(radioPanel);
	graph = new Paint(kernel, drawAverage);
	graph.setBounds(0,0,600,520);
	add(graph);

	setResizable(false);
	setTitle("Wykresy testy: "+kernel.inversions.length+" rozmiar tablicy: "+kernel.dataName(kernel.getMinSwitch(switches)).length);
	setVisible(true);
	graph.repaint();
    }

}

class Paint extends JPanel
{
    private Kernel kernel;
    private static int whichGraph;
    private static boolean drawAverage;
    public Paint(Kernel kernel, boolean drawAverage)
    {
	this.kernel = kernel;
	this.drawAverage=drawAverage;
	//super();
    }
    public void setGraph(int which)
    {
	whichGraph = which;
    }
    public void paint(Graphics g)
    {
	double x,y;
	Color c1 = new Color(99,99,255);
	int minX = kernel.statistics.min(kernel.inversions);
	int maxX = kernel.statistics.max(kernel.inversions);
	int xStep = (maxX-minX)/10;
	//maxX+=10;
	//minX-=10;
	g.setColor(Color.WHITE);
	g.fillRect(0,0,500,700);
	g.clearRect(0,0,getSize().width,getSize().height);
	g.setColor(Color.BLACK);
	g.drawLine(50,480,550,480);
	g.drawLine(50,480,50,30);
	g.drawString(Integer.toString(minX),30,500);
/* Tutaj zajmiemy siê osi¹ pionow¹ */
	int maxY = kernel.statistics.max(kernel.resultsName(whichGraph-1));
	int minY = kernel.statistics.min(kernel.resultsName(whichGraph-1));
	int yStep = (maxY-minY)/10;
	//maxY+=10;
	//minY+=10;
	g.drawString(Integer.toString(minY),1, 475);
/** Rysuj siatkê */
	for(int j=0;j<10;j++)
	{
	    g.setColor(c1);
/** Pionowe linie */
	    g.drawLine(100+50*j,480,100+50*j,30);
	    g.drawLine(50,30+45*j,550,30+45*j);
	    g.setColor(Color.black);
	    if(maxX>10)
/** Wartoœci na osi x */
	        g.drawString(Integer.toString((j+1)*xStep + minX),30+50*(j+1),500);
/** Wartoœci na osi Y */
	    g.drawString(Integer.toString((10-j)*yStep+minY),1,30+45*j);
	}
        if(maxX<=10)
	    g.drawString(Integer.toString(maxX),540,500);
	g.setColor(Color.RED);
	double A = (550.0-50.0)/((double)maxX-(double)minX);
	double B = (30.0-480.0)/(maxY-minY);
	double C = 50.0-A*(double)minX;
	double D = 480.0 - B*(double)minY;
	double[] averageY= kernel.statistics.conditionalAverage(kernel.resultsName(whichGraph-1),kernel.inversions);  
	for(int i=0;i<kernel.inversions.length;i++)
	{
	    x=A*(double)kernel.inversions[i]+C;
	    y=B*(double)kernel.resultsName(whichGraph-1)[i]+D;	    
	    g.fillOval((int)x,(int)y,4,4);
            if(kernel.invControl>=1  && whichGraph>1 && drawAverage)
	    {
	        g.setColor(Color.BLUE);
		if(maxX-minX<400)
	            g.fillOval((int)x,(int)(B*averageY[kernel.inversions[i]]+D),8,8);
		else
	            g.fillOval((int)x,(int)(B*averageY[kernel.inversions[i]]+D),5,5);
	        g.setColor(Color.RED);
	    }
	}
    }
}