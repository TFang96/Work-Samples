/**************************************************************
Name: Ziheng (Tony) Fang
Class: CS 125-02
Submission Date: November 23 (w/ Lab 05)
Description: This class creates a window called MPG Calculator
which is a GUI program that allows user to input the total number
of miles a car can drive and the max gallons of fuel it can hold
and then calculates the MPG of the car and displays it in a textbox.
 **************************************************************/

import java.awt.event.*; // needed for action listener
import javax.swing.*; // needed for window.

public class MPGCalculator extends JFrame{
	
	private JPanel panel; // references a panel
	private JLabel milesMessageLabel; // label for miles
	private JLabel gallonsMessageLabel; // label for gallons
	private JLabel MPGMessageLabel;
	private JButton calcMPGButton; // button to calculate mpg
	private JTextField milesTextField; // text field to hold miles input
	private JTextField gallonsTextField; // text field to hold gallons input
	private JTextField MPGTextField; // text to hold mpg
	private float miles; // holds miles user inputs
	private float gallons; // holds gallons user inputs
	private float MPG; // holds the mpg
	
	/* constructor */
	public MPGCalculator()
	{
		// sets the title of the winder by superclass
		super("MPG Calculator");
		
		// set window size
		setSize(500, 250);
		
		// what to do if close button is clicked
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// generate the panel
		makePanel();
		
		// put panel on window
		add(panel);
		
		// make the window shown on screen
		setVisible(true);
		
		
	}
	
	/* used to make the panel */
	private void makePanel()
	{
		// create label for user to enter number of miles
		milesMessageLabel = new JLabel("Enter the max # of miles car can be driven "
				+ "on a full tank: ");
		
		// create label for user to enter number of max gallons take holds
		gallonsMessageLabel = new JLabel("Enter the max gallons of fuel car can hold: ");
		// create label for mpg
		MPGMessageLabel = new JLabel("MPG of car: ");
		
		milesTextField = new JTextField(4); // creates text field for miles input
		gallonsTextField = new JTextField(4); // creates text field for gallon input (4 chars)
		MPGTextField = new JTextField(6); // text field for mpg - 6 characters
		
		calcMPGButton = new JButton("Calculate MPG"); // create the button
		calcMPGButton.addActionListener(new ButtonListener()); // implement action listener
		
		// create the panel
		panel = new JPanel();
		
		panel.add(milesMessageLabel); // miles message label
		panel.add(milesTextField); // add miles text field
		panel.add(gallonsMessageLabel); // add gallons message label
		panel.add(gallonsTextField); // add gallons text field
		panel.add(calcMPGButton); // add calc mpg button
		panel.add(MPGMessageLabel); // add mpg message label
		panel.add(MPGTextField); // add mpg text field
	}
	
	/* create action listener */
	private class ButtonListener implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			String inptMiles; // holds temp miles from user input
			String inptGallons; // holds temp gallons from user input
			inptMiles = milesTextField.getText(); // get miles from field
			inptGallons = gallonsTextField.getText(); // get gallons from field
			
			miles = Float.parseFloat(inptMiles); // convert string to float
			gallons = Float.parseFloat(inptGallons); // convert string to float
			
			MPG = miles/gallons; // calculate the MPG
			MPGTextField.setText(String.valueOf(MPG)); // display mpg in mpg text field.
		}
	}

}
