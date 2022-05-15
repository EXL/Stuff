import java.awt.BorderLayout;
import java.awt.Dimension;
import java.io.File;
import java.io.PrintStream;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class FoxDataUnpacker implements Runnable {

	static void createOutputDirs() {
		String resDirName = "res";
		String imgDirName = resDirName + File.separator + "images" + File.separator;
		String sfxDirName = resDirName + File.separator + "sounds" + File.separator;
		File resDir = new File(resDirName);
		File imgDir = new File(imgDirName);
		File sfxDir = new File(sfxDirName);
		resDir.mkdir();
		imgDir.mkdir();
		sfxDir.mkdir();
	}

	public static void main(String[] args) throws Exception {
		JFrame frame = new JFrame("Fox Data Unpacker, special for baat, written by EXL, 2016");

		JPanel pane = new JPanel();
		pane.setLayout(new BorderLayout());

		JTextArea txa = new JTextArea();
		pane.add("Center", txa);
		pane.add(new JScrollPane(txa));

		PrintStream con = new PrintStream(new TextAreaOutputStream(txa));

		System.setOut(con);
		System.setErr(con);

		frame.setContentPane(pane);
		frame.setSize(new Dimension(800, 480));
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

		FoxDataUnpacker fdu = new FoxDataUnpacker();
		fdu.doneJob();
	}

	public void doneJob() {
		Thread th = new Thread(this);
		th.start();
	}

	@Override
	public void run() {
		try {
			createOutputDirs();
			Game game = new Game();
			game.startApp(1);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
