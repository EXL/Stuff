import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.image.BufferedImage;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.PrintStream;

import javax.imageio.ImageIO;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public final class AllodsDataUnpacker implements Runnable {
	// $FF: renamed from: a java.io.DataInputStream
	public DataInputStream field_265;
	// $FF: renamed from: a int[]
	public int[] field_266;
	// $FF: renamed from: a byte
	public byte field_267 = 0;
	// $FF: renamed from: a int
	public int field_268;

	// $FF: renamed from: a (java.lang.String, byte, java.lang.Class) void
	public final void method_49(String var1, byte var2) {
		this.field_267 = var2;
		this.field_268 = 0;

		try {
			this.field_265 = new DataInputStream(new FileInputStream(var1));
			this.field_266 = new int[this.field_265.readInt()];

			for(int var4 = 0; var4 < this.field_266.length; ++var4) {
				this.field_266[var4] = this.field_265.readInt();
			}

		} catch (Exception var6) {
			System.out.println("Please put the all *.pak files in catalog with this jar!\n\n");
			var6.printStackTrace();
		}
	}

	// $FF: renamed from: a () void
	public final void method_50() {
		this.field_266 = null;

		try {
			this.field_265.close();
		} catch (Exception var6) {
			var6.printStackTrace();
		}

		this.field_265 = null;
	}

	// $FF: renamed from: a () byte[]
	public final byte[] method_51() {
		byte[] var2 = new byte[this.field_266[this.field_268]];

		try {
			for(int var1 = 0; var1 < var2.length; ++var1) {
				var2[var1] = (byte)(this.field_265.readByte() ^ this.field_267);
			}
		} catch (Exception var6) {
			var6.printStackTrace();
		}

		++this.field_268;
		return var2;
	}

	// $FF: renamed from: a (int) void
	public final void method_52(int var1) {
		try {
			for(int var2 = 0; var2 < var1; ++var2) {
				this.field_265.skipBytes(this.field_266[this.field_268]);
				++this.field_268;
			}

		} catch (Exception var6) {
			var6.printStackTrace();
		}
	}

	public final void unpackFile(String file, byte b) {
		method_49(file, b);
		System.out.println("In file: " + file + " found " + field_266.length + " images.");
		try {
			String resDirName = "res";
			String resDirFileName = resDirName + File.separator + file.split("\\.")[0] + File.separator;
			File resDir = new File(resDirName);
			File resDirFile = new File(resDirFileName);
			resDir.mkdir();
			resDirFile.mkdir();
			int i = 0;
			System.out.println("Writting directory: " + resDirFileName);
			for ( ; i < field_266.length; ++i) {
				byte[] arr = method_51();
				BufferedImage img = ImageIO.read(new ByteArrayInputStream(arr));
				File outputfile = new File(resDirFileName + "image_" + i + ".png");
				System.out.print((i == 0) ? "" : " " + outputfile.getName() + "...");
				System.out.print((i % 6 == 0 && i != 0) ? "\n" : "");
				ImageIO.write(img, "png", outputfile);
			}
			i--;
			System.out.print((i % 6 == 0) ? "Done!\n\n" : "\nDone!\n\n" );
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void doneJob() {
		Thread th = new Thread(this);
		th.start();
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("Unpacker Allods sprites, special for baat, written by EXL, 2016");

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

		AllodsDataUnpacker al = new AllodsDataUnpacker();
		al.doneJob();
	}

	@Override
	public void run() {
		unpackFile("res0.pak", (byte) 83);
		unpackFile("res1.pak", (byte) 83);
		unpackFile("res2.pak", (byte) 83);
		unpackFile("res3.pak", (byte) 83);
		unpackFile("res4.pak", (byte) 83);
		System.out.println("All done!\nNow, baat, you can close this window by pressing [X]!");
		// There is no images
		// unpackFile("scenes.pak", (byte) 83);
	}
}
