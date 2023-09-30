/***********************************************************
 Name: Ziheng (Tony) Fang
 Class: CS 125-02
 Submission Date: Nov. 23 (w/ Lab 5)
 Brief Description: Creates a GUI app allowing the user to 
 customize specs for a skateboard. Includes 5 panels regarding
 the deck, assembly type, wheels, miscellaneous items, as well
 as a panel for calculating and displaying the price. There
 is a button on the price panel with an action listener that
 would calculate the price if the user clicks it or types "C".
 ***********************************************************/
import java.awt.*; // needed for border layout
import java.awt.event.*; // needed for action listener
import javax.swing.*; // needed for JFrame

public class Skateboard extends JFrame{
	private String [] decks = {"The Master Thrasher", "The Dictator",
			"The Street King"}; // list of decks
	private String [] assemblies = {"7.75 Axle", "8 axle",
			"8.5 axle"}; // list of assemblies
	private String [] wheels = {"51", "55", "58", "61"}; // types of wheels
	private String [] miscItems = {"Grip Tape", "Bearings",
			"Riser Pads", "Nuts & Bolts Kit"}; // misc. items
	private JLabel deckLabel; // label for deck
	private JComboBox deckBox; // combo box for decks
	private JLabel assemblyLabel; // label for assembly
	private JComboBox assemblyBox; // combo box for assemblies
	private JLabel wheelLabel; // label for wheels
	private JComboBox wheelBox; // combo box for wheels
	private JLabel miscLabel; // label for misc. items
	private JList miscList; // list for misc items
	private JPanel deckPanel; // hold decks
	private JPanel assemblyPanel; // hold assemblies
	private JPanel wheelPanel; // hold wheels
	private JPanel miscPanel; // hold misc. items
	private JPanel pricePanel; // panel to display price
	private JLabel priceLabel; // label for price
	private JButton calcPrice; // button for calculating price
	private JTextField priceField; // text field for price
	private double subTotal; // holds subtotal of orders
	
	/* Constructor */
	public Skateboard()
	{
		super("Configure Your New SkateBoard!"); // window title
		// specify action for close button
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// make border layout manager
		setLayout(new BorderLayout());
		
		// build the panels
		buildDeckPanel();
		buildAssemblyPanel();
		buildWheelPanel();
		buildMiscPanel();
		buildPricePanel();
		// add panels to window
		add(deckPanel, BorderLayout.NORTH);
		add(assemblyPanel, BorderLayout.WEST);
		add(wheelPanel, BorderLayout.EAST);
		add(miscPanel, BorderLayout.SOUTH);
		add(pricePanel, BorderLayout.CENTER);
		
		// pack
		pack();
		// show the window
		setVisible(true);
		
	}
	
	/* used to make the deck panel. */
	private void buildDeckPanel()
	{
		deckPanel = new JPanel(); // create the panel
		deckLabel = new JLabel("Choose the deck of your choice: "); // make label
		// make combo box for decks
		deckBox = new JComboBox(decks);
		
		// add to panel
		deckPanel.add(deckLabel);
		deckPanel.add(deckBox);
	}
	
	/* used to make the assembly panel. */
	private void buildAssemblyPanel()
	{
		assemblyPanel = new JPanel(); // create the panel
		// make combo boxes
		assemblyBox = new JComboBox(assemblies);
		//make label
		assemblyLabel = new JLabel("Choose the type of truck assembly: ");
		
		// add to panel
		assemblyPanel.add(assemblyLabel);
		assemblyPanel.add(assemblyBox);
	}
	
	/* used to make the wheel panel. */
	private void buildWheelPanel()
	{
		wheelPanel = new JPanel(); // create the panel
		// make combo box
		wheelBox = new JComboBox(wheels);
		// make label
		wheelLabel = new JLabel("Choose the wheels of your choice: ");
		// add to panel
		wheelPanel.add(wheelLabel);
		wheelPanel.add(wheelBox);
	}
	
	/* used to make the panel for miscellaneous products. */
	private void buildMiscPanel()
	{
		miscPanel = new JPanel(); // create the panel
		miscList = new JList(miscItems); // create the list.
		// make label
		miscLabel = new JLabel("Choose your miscellanous items/services: ");
		// set selection interval
		miscList.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
		miscPanel.add(miscLabel);
		miscPanel.add(miscList); // add list to panel
		
	}
	
	/* used to make panel to show the price. */
	private void buildPricePanel()
	{
		pricePanel = new JPanel(); // build the panel
		// label to indicate price
		priceLabel = new JLabel("Current price of selected items: ");
		// field for price
		priceField = new JTextField(6);
		// make the button
		calcPrice = new JButton("Calculate Price");
		calcPrice.setMnemonic(KeyEvent.VK_C); // set mnemonic
		// set tool tip for button.
		calcPrice.setToolTipText("Click to calculate price... "); 
		calcPrice.addActionListener(new ButtonListener());
		priceField.setEditable(false); // does not allow user to change price
		pricePanel.add(priceLabel); // add label to panel
		pricePanel.add(priceField); // add field to panel
		pricePanel.add(calcPrice);
		
	}
	
	/* Action Listener */ 
	private class ButtonListener implements ActionListener
	{
		public void actionPerformed (ActionEvent e)
		{
			subTotal = 0.00; // set subtotal to 0.
			double total; // holds the total
			String deckChosen; // holds the chosen deck
			String wheelChosen; // holds the wheel type chosen
			String assemblyChosen; // holds the assembly chosen
			// holds selected miscellaneous items.
			Object[] miscItemsChosen = miscList.getSelectedValues();
			deckChosen = (String) deckBox.getSelectedItem(); // get the deck chosen
			// get the chosen wheel type
			wheelChosen = (String) wheelBox.getSelectedItem(); 
			// get chosen assembly box
			assemblyChosen = (String) assemblyBox.getSelectedItem();
			/* calculate price accordingly */
			if(deckChosen == "The Master Thrasher")
				subTotal += 60;
			else if(deckChosen == "The Dictator")
				subTotal += 45;
			else if(deckChosen == "The Street King")
				subTotal += 50;
			if(assemblyChosen == "7.75 Axle")
				subTotal += 35;
			else if(assemblyChosen == "8 Axle")
				subTotal += 40;
			else if(assemblyChosen == "8.5 Axle")
				subTotal += 45;
			if(wheelChosen == "51")
				subTotal += 20;
			else if(wheelChosen =="55")
				subTotal += 22;
			else if(wheelChosen == "58")
				subTotal += 24;
			else if(wheelChosen == "61")
				subTotal += 28;
			/* check all miscellaneous items chose and calc price accordingly */
			for (int i = 0; i < miscItemsChosen.length; i++)
			{
				if(miscItemsChosen[i] == "Grip Tape")
					subTotal += 10;
				else if(miscItemsChosen[i] == "Bearings")
					subTotal += 30;
				else if(miscItemsChosen[i] == "Riser Pads")
					subTotal += 2;
				else if(miscItemsChosen[i] == "Nuts & Bolts Kit")
					subTotal += 3;
			}
			total = subTotal + subTotal *0.06; // calculate total
			priceField.setText(String.valueOf(total)); // display total on textfield
		}
	}
	
	

}
