package Code.diagnostic;
// Needs a package declaration to move to another folder

import java.awt.Color;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.JFrame;

import edu.cmu.ri.createlab.terk.robot.finch.Finch;

/**
 * Created by:
 * Date:
 * A starter file to use the Finch
 */

public class Tester
{
	JFrame frame = new JFrame();
	
	Finch myFinch;
	public Tester()
	{
		KeyListener listener = new MyKeyListener();
		frame.addKeyListener(listener);
		myFinch = new Finch();
		frame.setVisible(true);
		frame.setFocusable(true);
		int health = 100;
	}
	public static void main(final String[] args)
	{
		// Instantiating the Finch object
		//myFinch = new Finch();

		// Write some code here!
		Tester t = new Tester();
		t.myFinch.setLED(Color.blue, 1000);
		t.myFinch.setLED(Color.red, 1000);
		t.myFinch.setLED(Color.green, 1000);
		t.myFinch.saySomething("finch bots engaged",2000);
		t.myFinch.buzz(200, 2000);
		t.myFinch.sleep(2000);
		t.myFinch.buzz(280, 2000);
		//t.myFinch.sleep(2000);
		//t.myFinch.setWheelVelocities(255, 0, 3000);
		while(true)
		{
			
		}
		// Always end your program with finch.quit()
		//t.myFinch.quit();
		//System.exit(0);
	}
	/**
	 *Inner class for keyboard listening
	 */
	private class MyKeyListener implements KeyListener
	{
		public void keyTyped(KeyEvent e) 
		{}

		/**
		 * Listens for keys to be pressed while the program
		 * is running. Only keys that correspond to program
		 * function have actions.
		 */
		public void keyPressed(KeyEvent e)
		{
			//Activates if the R key is pressed
			if (e.getKeyCode() == KeyEvent.VK_W) 
			{
				myFinch.setWheelVelocities(255, 255);
			}
			if (e.getKeyCode() == KeyEvent.VK_A) 
			{
				myFinch.setWheelVelocities(-255, 255);
			}
			if (e.getKeyCode() == KeyEvent.VK_S) 
			{
				myFinch.setWheelVelocities(-255, -255);
			}
			if (e.getKeyCode() == KeyEvent.VK_D) 
			{
				myFinch.setWheelVelocities(255, -255);
			}
			if (e.getKeyCode() == KeyEvent.VK_F) 
			{
				myFinch.setLED(Color.red, 1000);
			}
			if (e.getKeyCode() == KeyEvent.VK_E) 
			{
				myFinch.buzz(262, 500);
			}
			if (e.getKeyCode() == KeyEvent.VK_SPACE) 
			{
				myFinch.quit();
				System.exit(0);
			}
		}
		public void keyReleased(KeyEvent e) 
		{
			if (e.getKeyCode() == KeyEvent.VK_W) 
			{
				myFinch.stopWheels();
			}
			if (e.getKeyCode() == KeyEvent.VK_A) 
			{
				myFinch.stopWheels();
			}
			if (e.getKeyCode() == KeyEvent.VK_S) 
			{
				myFinch.stopWheels();
			}
			if (e.getKeyCode() == KeyEvent.VK_D) 
			{
				myFinch.stopWheels();
			}
		}
	}
}

