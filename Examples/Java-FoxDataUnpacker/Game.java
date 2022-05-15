import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Random;

import javax.imageio.ImageIO;

public class Game {
	// $FF: renamed from: a Game
	public static Game field_126;
	// $FF: renamed from: a a
	public static class_0 field_127;

	public static int static_var = 0;
	public static int static_var2 = 0;
	// $FF: renamed from: a short[][]
	public static short[][] field_128;
	// $FF: renamed from: a byte[]
	public static byte[] field_129;
	// $FF: renamed from: b short[][]
	public static short[][] field_130;
	// $FF: renamed from: a short[]
	public static short[] field_131;
	// $FF: renamed from: b short[]
	public static short[] field_132;
	// $FF: renamed from: b byte[]
	public static byte[] field_133;
	// $FF: renamed from: a java.io.InputStream
	public static InputStream field_134;
	// $FF: renamed from: a boolean
	public static boolean field_135 = true;
	// $FF: renamed from: c byte[]
	public static byte[] field_136;
	// $FF: renamed from: a int
	public static int field_137;
	// $FF: renamed from: d byte[]
	public static byte[] field_138;
	// $FF: renamed from: b int
	public static int field_139;
	// $FF: renamed from: a short
	public static short field_140;
	// $FF: renamed from: b java.io.InputStream
	public static InputStream field_141;
	// $FF: renamed from: c int
	public static int field_142;
	// $FF: renamed from: d int
	public static int field_143;
	// $FF: renamed from: c short[]
	public static short[] field_144;
	// $FF: renamed from: a int[]
	public static int[] field_145;
	// $FF: renamed from: a java.lang.String
	public static String field_146 = "";
	// $FF: renamed from: e int
	public static int field_147;
	// $FF: renamed from: a java.lang.String[]
	public static String[] field_148 = new String[6];
	// $FF: renamed from: c short[][]
	public static short[][] field_149 = new short[6][];
	// $FF: renamed from: a int[][]
	public static int[][] field_150 = new int[6][];
	// $FF: renamed from: a byte[][]
	public static byte[][] field_151 = new byte[6][];
	// $FF: renamed from: d short[]
	public static short[] field_152;
	// $FF: renamed from: e byte[]
	public static byte[] field_153;
	// $FF: renamed from: a javax.microedition.lcdui.Image[][]
	public static BufferedImage[][] field_154;
	// $FF: renamed from: e short[]
	public static short[] field_155;
	// $FF: renamed from: f short[]
	public static short[] field_156;
	// $FF: renamed from: d short[][]
	public static short[][] field_157;
	// $FF: renamed from: e short[][]
	public static short[][] field_158;
	// $FF: renamed from: b int[]
	public static int[] field_159 = new int[256];
	// $FF: renamed from: f byte[]
	public static byte[] field_160;
	// $FF: renamed from: g short[]
	public static short[] field_161;
	// $FF: renamed from: f int
	public static int field_162;
	// $FF: renamed from: g int
	public static int field_163;
	// $FF: renamed from: h int
	public static int field_164;
	// $FF: renamed from: i int
	public static int field_165;
	// $FF: renamed from: j int
	public static int field_166;
	// $FF: renamed from: g byte[]
	public static byte[] field_167;
	// $FF: renamed from: b byte[][]
	public static byte[][] field_168;
	// $FF: renamed from: a long
	public static long field_169;
	// $FF: renamed from: k int
	public static int field_170;
	// $FF: renamed from: l int
	public static int field_171;
	// $FF: renamed from: c byte[][]
	public static byte[][] field_172;
	// $FF: renamed from: f short[][]
	public static short[][] field_173;
	// $FF: renamed from: m int
	public static int field_174;
	// $FF: renamed from: n int
	//   public static final int field_175;
	// $FF: renamed from: o int
	//   public static final int field_176;
	// $FF: renamed from: a javax.microedition.lcdui.Graphics
	public static Graphics field_177;
	// $FF: renamed from: p int
	public static int field_178;
	// $FF: renamed from: b long
	public static long field_179;
	// $FF: renamed from: q int
	public static int field_180;
	// $FF: renamed from: r int
	public static int field_181;
	// $FF: renamed from: c long
	public static long field_182;
	// $FF: renamed from: s int
	public static int field_183;
	// $FF: renamed from: h short[]
	public static short[] field_184;
	// $FF: renamed from: i short[]
	public static short[] field_185;
	// $FF: renamed from: h byte[]
	public static byte[] field_186;
	// $FF: renamed from: j short[]
	public static short[] field_187;
	// $FF: renamed from: t int
	public static int field_188;
	// $FF: renamed from: u int
	public static int field_189;
	// $FF: renamed from: v int
	public static int field_190;
	// $FF: renamed from: w int
	public static int field_191;
	// $FF: renamed from: x int
	public static int field_192;
	// $FF: renamed from: y int
	public static int field_193;
	// $FF: renamed from: z int
	public static int field_194;
	// $FF: renamed from: A int
	public static int field_195;
	// $FF: renamed from: B int
	public static int field_196;
	// $FF: renamed from: C int
	public static int field_197;
	// $FF: renamed from: D int
	public static int field_198;
	// $FF: renamed from: E int
	public static int field_199;
	// $FF: renamed from: b boolean
	public static boolean field_200;
	// $FF: renamed from: a javax.microedition.media.Player[]
	//   public static Player[] field_201;
	// $FF: renamed from: F int
	public static int field_202;
	// $FF: renamed from: i byte[]
	public static byte[] field_203;
	// $FF: renamed from: c int[]
	public static int[] field_204;
	// $FF: renamed from: G int
	public static int field_205;
	// $FF: renamed from: d long
	public static long field_206;
	// $FF: renamed from: c boolean
	public static boolean field_207;
	// $FF: renamed from: b java.lang.String
	public static String field_208;
	// $FF: renamed from: a javax.microedition.lcdui.Font
	public static Font field_209;
	// $FF: renamed from: H int
	public static int field_210;
	private static int var13;

	// $FF: renamed from: a (short) int
	public static int method_46(short var0) {
		int var1;
		for(var1 = 0; field_131[var1] != var0; ++var1) {
			;
		}

		return var1;
	}

	public Game() {
		try {
			field_208 = "G: 0.9.4; GP: 0.7.3";
			field_126 = this;
			field_178 = -1;
			field_127 = new class_0();
			//         Display.getDisplay(field_126).setCurrent(field_127);
			field_183 = 7;
			field_127.method_0();
		} catch (Throwable var2) {
			;
		}
	}

	public void startApp(int state) {
		if(field_135) {
			try {
				int var1;
				for(var1 = 0; var1 < 1; ++var1) {
					method_58("o" + var1, false);
				}

				for(var1 = 0; var1 < 2; ++var1) {
					// TODO: sounds?
					method_58("s" + var1, false);
				}

				for(var1 = 0; var1 < 2; ++var1) {
					method_58("g" + var1, false);
				}
				
				method_97();
				field_174 = 10;
				field_134 = method_59("o", 0);
				short var2 = method_55();
				short var3;
				field_128 = new short[var3 = method_55()][];

				short var4;
				for(var1 = 0; var1 < var3; ++var1) {
					var4 = method_55();
					field_128[var1] = new short[var4];
					method_56(field_128[var1], var4);
				}

				int var6;
				if((var6 = method_60("o0", (short) 1)) > 0) {
					field_129 = new byte[var6];
					field_134 = method_59("o", 1);
					method_57(field_129, 0, field_129.length);
				}

				field_174 = 20;
				if(method_60("o0", (short) 2) > 0) {
					field_130 = new short[var2][];
					field_134 = method_59("o", 2);

					for(var1 = 0; var1 < var2; ++var1) {
						if((var4 = method_55()) > 0) {
							field_130[var1] = new short[var4];
							method_56(field_130[var1], var4);
						}
					}
				}

				field_131 = new short[var2];
				field_132 = new short[var2];
				field_133 = new byte[method_60("o0", (short) 3) - var2 * 4];
				field_134 = method_59("o", 3);

				for(var1 = 0; var1 < var2; ++var1) {
					field_131[var1] = method_55();
					field_132[var1] = method_55();
				}

				method_57(field_133, 0, field_133.length);
				field_134 = null;
				field_174 = 30;
				class_1.field_124 = new class_1[60];

				for(var1 = 0; var1 < 60; ++var1) {
					class_1.field_124[var1] = new class_1();
				}

				System.out.println("Done!\n\nUnpack graphics:\nCall method_68() and method_67() (int another thread) for unpack graphics:");
				
				method_73();
				method_62();
				field_134 = method_59("s", 0);
				field_180 = (byte)method_55();
				field_184 = new short[method_55()];
				method_56(field_184, field_184.length);
				field_185 = new short[method_55() * 3];
				method_56(field_185, field_185.length);
				field_186 = new byte[method_55()];
				method_57(field_186, 0, field_186.length);
				method_83();

				try {
					field_200 = method_90(1, 0);
				} catch (Exception var8) {
					;
				}

				field_174 = 100;
				method_69();
				method_63(field_184, "s");
				field_134 = null;
				field_174 = 100;
				field_134 = null;
				field_135 = false;
				field_183 = state;
				return;
			} catch (Throwable var9) {
				;
			}
		}

	}

	public void pauseApp() {
	}

	public void destroyApp(boolean var1) {
		try {
			method_82();
			method_99(1);
			class_0.method_1();
			field_127 = null;
		} catch (Throwable var3) {
			;
		}

		//      this.notifyDestroyed();
		field_126 = null;
		System.gc();
	}

	// $FF: renamed from: a (byte[], int) void
	public static void method_47(byte[] var0, int var1) {
		field_136 = var0;
		if(var1 != -1) {
			field_137 = var1;
		}

	}

	// $FF: renamed from: a (int) void
	public static void method_48(int var0) {
		field_137 += var0;
	}

	// $FF: renamed from: a () int
	public static int method_49() {
		return (255 & field_136[field_137++]) << 24 | (255 & field_136[field_137++]) << 16 | (255 & field_136[field_137++]) << 8 | 255 & field_136[field_137++];
	}

	// $FF: renamed from: a () short
	public static short method_50() {
		return (short)((255 & field_136[field_137++]) << 8 | 255 & field_136[field_137++]);
	}

	// $FF: renamed from: a () byte
	public static byte method_51() {
		return field_136[field_137++];
	}

	// $FF: renamed from: b (byte[], int) void
	public static void method_52(byte[] var0, int var1) {
		field_138 = var0;
		if(var1 != -1) {
			field_139 = var1;
		}

		field_140 = 0;
	}

	// $FF: renamed from: b (int) void
	public static void method_53(int var0) {
		field_138[field_139++] = (byte)var0;
		++field_140;
	}

	// $FF: renamed from: b () int
	public static int method_54() throws Exception {
		return field_134.read() << 24 | field_134.read() << 16 | field_134.read() << 8 | field_134.read();
	}

	// $FF: renamed from: b () short
	public static short method_55() throws Exception {
		return (short)(field_134.read() << 8 | field_134.read());
	}

	// $FF: renamed from: a (short[], int) void
	public static void method_56(short[] var0, int var1) throws Exception {
		//		boolean var2 = false;

		for(int var3 = 0; var3 < var1; ++var3) {
			var0[var3] = method_55();
		}

	}

	// $FF: renamed from: a (byte[], int, int) void
	public static void method_57(byte[] var0, int var1, int var2) throws Exception {
		field_134.read(var0, var1, var2);
	}

	// $FF: renamed from: a (java.lang.String, boolean) short[]
	public static short[] method_58(String var0, boolean var1) throws Exception {
		//      field_134 = "S".getClass().getResourceAsStream(var0);
		field_134 = new FileInputStream(var0);
		int var2;
		short[] var3 = new short[var2 = method_54()];
		int[] var4 = new int[var2 << 1];

		int var5;
		for(var5 = 0; var5 < var2; ++var5) {
			var3[var5] = (short)method_54();
			var4[var5 << 1] = method_54();
			var4[1 + (var5 << 1)] = method_54();
		}

		if(var1) {
			method_57(field_151[field_147] = new byte[var4[var4.length - 1] + var4[var4.length - 2] - var4[1]], 0, field_151[field_147].length);
			var2 = 4 + var2 * 12;
			var5 = var4.length + 1;

			while(true) {
				var5 -= 2;
				if(var5 < 0) {
					break;
				}

				var4[var5] -= var2;
			}
		}

		field_148[field_147] = var0;
		field_149[field_147] = var3;
		field_150[field_147++] = var4;
		return var3;
	}

	// $FF: renamed from: a (java.lang.String, int) java.io.InputStream
	public static InputStream method_59(String var0, int var1) throws Exception {
		int var2;
		if(var0.equals(field_146)) {
			var2 = field_144.length;

			while(true) {
				--var2;
				if(var2 < 0) {
					++field_143;
					field_141.close();
					field_141 = null;
					break;
				}

				if(var1 == field_144[var2]) {
					if(field_142 != var2) {
						field_141.skip((long)(field_145[1 + (var2 << 1)] - field_145[1 + (field_142 << 1)]));
					}

					field_142 = var2 + 1;
					return field_141;
				}
			}
		} else {
			field_143 = 0;
			field_146 = var0;
		}

		var0 = var0 + field_143;
		var2 = field_147;

		do {
			--var2;
		} while(var2 >= 0 && !var0.equals(field_148[var2]));

		field_144 = field_149[var2];
		field_145 = field_150[var2];
		field_142 = 0;
		if(field_151[var2] != null) {
			field_141 = new ByteArrayInputStream(field_151[var2]);
		} else {
			(field_141 = new FileInputStream(var0)).skip((long)field_145[1]);
			//         (field_141 = "S".getClass().getResourceAsStream(var0)).skip((long)field_145[1]);
		}
		// TODO: 
		return method_59(field_146, var1);
	}

	// $FF: renamed from: a (java.lang.String, short) int
	public static int method_60(String var0, short var1) {
		//		boolean var2 = false;
		//		boolean var3 = false;
		int var4 = field_147;

		do {
			--var4;
		} while(var4 >= 0 && !var0.equals(field_148[var4]));

		int var5 = field_149[var4].length;

		do {
			--var5;
		} while(var5 >= 0 && var1 != field_149[var4][var5]);

		return field_150[var4][var5 << 1];
	}

	// $FF: renamed from: a (short) short
	public static short method_61(short var0) {
		int var1 = field_152.length;

		do {
			--var1;
		} while(var1 >= 0 && var0 != field_152[var1]);

		return (short)var1;
	}

	// $FF: renamed from: a () void
	public static void method_62() {
		field_152 = new short[50];
		field_153 = new byte[50];
		field_155 = new short[50];
		field_156 = new short[50];
		field_157 = new short[50][];
		field_154 = new BufferedImage[50][];
		field_158 = new short[50][];
		int var0 = 50;

		while(true) {
			--var0;
			if(var0 < 0) {
				return;
			}

			field_152[var0] = -1;
		}
	}

	// $FF: renamed from: a (short[], java.lang.String) void
	public static void method_63(short[] var0, String var1) throws Exception {
		field_174 += 10;
		class_0.method_2();
		short[] var3 = field_152;
		field_152 = var0;
		int var2 = var3.length;

		while(true) {
			--var2;
			if(var2 < 0) {
				field_152 = var3;
				var2 = 50;

				while(true) {
					--var2;
					if(var2 < 0) {
						System.gc();
						field_174 += 10;
						class_0.method_2();
						var2 = 0;

						while(var2 < var0.length) {
							if(method_61(var0[var2]) < 0) {
								short var4;
								method_66(field_152[var4 = method_61((short) -1)] = var0[var2++], var4, var1);
							} else {
								++var2;
							}
						}

						method_73();
						field_174 += 10;
						class_0.method_2();
						return;
					}

					if(field_152[var2] == -2) {
						method_65((short)var2);
					}
				}
			}

			if(method_61(var3[var2]) < 0 && (field_153[var2] & 2) == 0) {
				var3[var2] = -2;
			}
		}
	}

	// $FF: renamed from: a (int, int, int, int) void
	public static void method_64(int var0, int var1, int var2, int var3) {
		field_177.drawImage(field_154[var0][var1], var2 + field_157[var0][var1], var3 + field_158[var0][var1], null);
	}

	// $FF: renamed from: c (int) void
	public static void method_65(int var0) {
		field_152[var0] = -1;
		field_157[var0] = field_158[var0] = null;
		field_154[var0] = null;
	}

	// $FF: renamed from: a (short, short, java.lang.String) void
	public static void method_66(short var0, short var1, String var2) throws Exception {
		field_134 = method_59(var2, var0);
		int var6 = 0;
		field_134.read();
		int var5 = field_134.read();
		field_153[var1] = (byte)var5;
		byte[] var12 = field_168[field_134.read()];
		short var13 = field_155[var1] = method_55();
		field_156[var1] = method_55();
		int var3;
		int var4;
		short var8;
		if(field_161.length < (var4 = (var3 = var8 = method_55()) << 1)) {
			field_161 = new short[var4];
		}

		int var7;
		short[] var9;
		boolean var11;
		field_157[var1] = var9 = new short[var7 = (var11 = (var5 & 1) != 0)?var8 << 1:var8];
		short[] var10;
		field_158[var1] = var10 = new short[var7];
		field_154[var1] = new BufferedImage[var7];

		while(true) {
			--var3;
			if(var3 < 0) {
				var5 = var8 >> 3;
			if((var8 & 7) != 0) {
				++var5;
			}

			if(field_167.length < var5) {
				field_167 = new byte[var5];
			}

			method_57(field_167, 0, var5);
			if((var6 += 89 + var12.length) > field_160.length) {
				field_160 = new byte[var6];
			}

			field_162 = 0;
			method_72(-1991225785);
			method_72(218765834);
			method_72(13);
			method_72(1229472850);
			field_162 += 8;
			method_72(134414336);
			field_160[field_162++] = 0;
			field_162 = 33;
			method_72(var12.length - 4);
			method_72(1347179589);
			System.arraycopy(var12, 0, field_160, field_162, var12.length);
			field_162 += var12.length;
			method_72(1);
			method_72(1951551059);
			int var15 = field_162 - 1;
			field_160[field_162++] = 0;
			field_162 += 4;
			field_166 = field_162;
			var7 = 0;
			
			for(var4 = 0; var4 < var8; ++var4) {
				field_162 = var15 + 2;
				if((field_167[var4 >> 3] & 1 << (var4 & 7)) == 0) {
					field_160[var15] = 84;
					method_72(262622881);
				} else {
					field_160[var15] = 83;
					method_72(1088870502);
				}

				field_163 = field_161[var7++];
				field_164 = field_161[var7++];
				field_154[var1][var4] = method_67();
				if(var11) {
					var3 = var8 + var4;
					var9[var3] = (short)(var13 - var9[var4] - (field_154[var1][var3] = method_68()).getWidth());
					var10[var3] = var10[var4];
				}
			}

			return;
			}

			--var4;
			short var10001 = field_161[var4] = method_55();
			--var4;
			if(var6 < (var5 = var10001 * (1 + (field_161[var4] = method_55())))) {
				var6 = var5;
			}

			var9[var3] = method_55();
			var10[var3] = method_55();
		}
	}

	// $FF: renamed from: a () javax.microedition.lcdui.Image
	public static BufferedImage method_67() throws Exception {
		field_162 = 16;
		method_72(field_163);
		method_72(field_164);
		field_162 += 5;
		method_72(method_70(-1, field_160, 12, 17));
		field_162 = field_166;
		method_72((field_165 = (field_163 + 1) * field_164) + 11);
		method_72(1229209940);
		field_160[field_162++] = 120;
		field_160[field_162++] = -38;
		field_160[field_162++] = 1;
		field_160[field_162++] = (byte)field_165;
		field_160[field_162++] = (byte)(field_165 >> 8);
		field_160[field_162++] = (byte)(-(field_160[field_162 - 3] + 1));
		field_160[field_162++] = (byte)(-(field_160[field_162 - 3] + 1));
		int var0 = field_164;

		while(true) {
			--var0;
			if(var0 < 0) {
				method_72(method_71(field_160, field_166 + 15, field_165));
				method_72(method_70(-1, field_160, field_166 + 4, field_165 + 15));
				method_72(0);
				method_72(1229278788);
				method_72(-1371381630);
				
				String name = "res" + File.separator + "images" + File.separator + "image67_" + static_var2 + ".png";
				System.out.print("-----" + name + "...done!\n");

				BufferedImage img = ImageIO.read(new ByteArrayInputStream(field_160, 0, field_162));
				File outputfile = new File(name);
				ImageIO.write(img, "png", outputfile);
				static_var2++;

				if (static_var2 == 252) {
					System.out.println("The second pass done!\n\nAll done!\nNow, baat, you can close this window by pressing [X]!");
					// saveSongs(); // ?
					class_0.method_1();
				}
				
				if (static_var2 == 115) {
					System.out.println("\nThe first pass done!\n\n");
					// saveSongs(); // ?
					//class_0.method_1();
					field_183 = 4;
//					startApp(4);
				}

				return img;
				// TODO: 
				//return BufferedImage.createImage(field_160, 0, field_162);
			}

			field_160[field_162++] = 0;
			method_57(field_160, field_162, field_163);
			field_162 += field_163;
		}
	}

	// $FF: renamed from: b () javax.microedition.lcdui.Image
	public static BufferedImage method_68() throws IOException {
		int var0 = field_163 >> 1;
			int var1;
			int var2 = (var1 = field_163 + 1) - var0;
			int var3 = field_162 - field_165 - 19;

			for(int var6 = 0; var6 < field_164; ++var6) {
				int var4 = var3 + var1 - 2;
				int var5 = var0;

				while(true) {
					--var5;
					if(var5 < 0) {
						var3 += var2;
						break;
					}

					byte var7 = field_160[var3];
					field_160[var3++] = field_160[var4];
					field_160[var4--] = var7;
				}
			}

			field_162 -= 20;
			method_72(method_71(field_160, field_166 + 15, field_165));
			method_72(method_70(-1, field_160, field_166 + 4, field_165 + 15));
			// TODO:
			String name = "res" + File.separator + "images" + File.separator + "image68_" + static_var + ".png";
			System.out.print("-----" + name + "...done!\n");
			BufferedImage img = ImageIO.read(new ByteArrayInputStream(field_160, 0, field_162 + 12));
			File outputfile = new File(name);
			ImageIO.write(img, "png", outputfile);
			static_var++;

			return img;

			//return Image.createImage(field_160, 0, field_162 + 12);
	}

	// $FF: renamed from: b () void
	public static void method_69() throws Exception {
		field_134 = method_59("s", 1);
		int var0;
		field_168 = new byte[var0 = field_134.read()][];

		for(int var6 = 0; var6 < var0; ++var6) {
			int var1;
			int var2;
			byte[] var5;
			field_168[var6] = var5 = new byte[(var2 = (var1 = field_134.read() + 1) * 3) + 4];

			while(true) {
				--var1;
				int var4;
				if(var1 < 0) {
					var2 = var5.length - 4;
					var4 = method_70(-1269336406, var5, 0, var2);
					var5[var2++] = (byte)(var4 >>> 24 & 255);
					var5[var2++] = (byte)(var4 >>> 16 & 255);
					var5[var2++] = (byte)(var4 >>> 8 & 255);
					var5[var2] = (byte)(var4 & 255);
					break;
				}

				short var3 = method_55();
				--var2;
				var5[var2] = (byte)(((var4 = var3 & 31) << 3) + (var4 >> 2));
				--var2;
				var5[var2] = (byte)(((var4 = var3 >> 5 & 63) << 2) + (var4 >> 4));
				--var2;
				var5[var2] = (byte)(((var4 = var3 >> 11 & 31) << 3) + (var4 >> 2));
			}
		}

	}

	// $FF: renamed from: a (int, byte[], int, int) int
	public static int method_70(int var0, byte[] var1, int var2, int var3) {
		while(true) {
			--var3;
			if(var3 < 0) {
				return ~var0;
			}

			var0 = field_159[(var0 ^ var1[var2++]) & 255] ^ var0 >>> 8;
		}
	}

	// $FF: renamed from: a (byte[], int, int) int
	public static int method_71(byte[] var0, int var1, int var2) {
		int var3 = 1;
		int var4 = 0;

		while(true) {
			--var2;
			if(var2 < 0) {
				return (var4 << 16) + var3;
			}

			var4 = (var4 + (var3 = (var3 + (var0[var1++] & 255)) % '\ufff1')) % '\ufff1';
		}
	}

	// $FF: renamed from: d (int) void
	public static final void method_72(int var0) {
		field_160[field_162++] = (byte)(var0 >>> 24 & 255);
		field_160[field_162++] = (byte)(var0 >>> 16 & 255);
		field_160[field_162++] = (byte)(var0 >>> 8 & 255);
		field_160[field_162++] = (byte)(var0 & 255);
	}

	// $FF: renamed from: c () void
	public static void method_73() {
		field_160 = null;
		field_161 = null;
		field_167 = null;
		field_160 = new byte[1];
		field_167 = new byte[32];
		field_161 = new short[2];
	}

	public static int random(int var0) {
		if(var0 == 0) {
			var0 = 1;
		}

		int var1;
		int var2;
		do {
			var1 = (var2 = (int)((field_169 = field_169 * 25214903917L + 11L & 281474976710655L) >>> 16)) % var0;
		} while(var2 - var1 + (var0 - 1) < 0);

		return var1;
	}

	// $FF: renamed from: e (int) void
	public static void method_74(int var0) {
		int var1 = 176 - field_170;
		int var2 = 208 - field_171;
		int var3 = var1 + class_0.field_9;
		int var4 = var2 + class_0.field_10;
		byte[] var5 = field_172[var0];
		short[] var6;
		short var7 = (var6 = field_173[var0])[4];
		short var8 = var6[2];
		short var9 = var6[3];
		BufferedImage[] var10 = field_154[var6[6]];
		short[] var11 = field_157[var6[6]];
		short[] var12 = field_158[var6[6]];
		var1 = var1 > 0?var1 / var8:0;
		var2 = var2 > 0?var2 / var9:0;
		var3 = var3 > var6[0]?var7 - 1:(var3 - 1) / var8;
		var4 = var4 > var6[1]?var6[5] - 1:(var4 - 1) / var9;
		int var13 = var2 * var7;
		int var14 = var1 * var8 + field_170;

		for(int var15 = var2 * var9 + field_171; var2 <= var4; ++var2) {
			int var17 = var14;

			for(int var16 = var1; var16 <= var3; ++var16) {
				int var18;
				if((var18 = var5[var13 + var16] - 1) >= 0) {
					field_177.drawImage(var10[var18], var17 + var11[var18], var15 + var12[var18], null);
				}

				var17 += var8;
			}

			var13 += var7;
			var15 += var9;
		}

	}

	// $FF: renamed from: d () void
	public static void method_75() throws Exception {
		field_134 = method_59("o", (short)(class_0.field_8 + 256));
		int var0;
		field_172 = new byte[var0 = method_55()][];
		field_173 = new short[var0][9];

		label30:
			while(true) {
				--var0;
				if(var0 < 0) {
					return;
				}

				field_173[var0][6] = method_61(method_55());
				field_173[var0][4] = method_55();
				field_173[var0][5] = method_55();
				field_173[var0][7] = method_55();
				field_173[var0][8] = method_55();
				field_173[var0][2] = field_155[field_173[var0][6]];
				field_173[var0][3] = field_156[field_173[var0][6]];
				field_173[var0][0] = (short)(field_173[var0][2] * field_173[var0][4]);
				field_173[var0][1] = (short)(field_173[var0][3] * field_173[var0][5]);
				int var1 = 0;
				short var2;
				byte[] var4 = field_172[var0] = new byte[var2 = method_55()];

				while(true) {
					while(true) {
						if(var1 >= var2) {
							continue label30;
						}

						int var3;
						if((var3 = (byte)field_134.read()) >= 2) {
							while(true) {
								--var3;
								if(var3 < 0) {
									break;
								}

								var4[var1++] = 0;
							}
						} else {
							method_57(var4, var1, var3 = 2 - var3);
							var1 += var3;
						}
					}
				}
			}
	}

	// $FF: renamed from: a (boolean) void
	public static void method_76(boolean var0) {
		if(class_0.field_5 - field_179 > 3000L || var0) {
			field_179 = class_0.field_5;
			++field_178;
			if(field_178 >= field_180) {
				method_98(1);
				method_84(0);
				field_183 = 2;
				return;
			}

			field_154[0] = null;
			System.gc();

			try {
				method_66((short)(field_178 + 100), (short) 0, "s");
				class_0.method_2();
				return;
			} catch (Throwable var2) {
				;
			}
		}

	}

	// $FF: renamed from: e () void
	public static void method_77() {
		switch(field_183) {
		case 1:
			int var0 = (class_0.field_6 - field_155[0]) / 2;
			int var1 = (class_0.field_7 - field_156[0]) / 2;
			method_64(0, 0, var0, var1);
			return;
		case 2:
		case 8:
			method_92();
			method_103();
			return;
		case 4:
		case 5:
		case 6:
		case 7:
			//         field_177.setColor(0);
			field_177.fillRect(0, 0, class_0.field_6, class_0.field_7);
			//         field_177.setColor(255, 255, 255);
			//         field_177.drawString("loading", (class_0.field_6 - field_175) / 2, (class_0.field_7 - field_176) / 2, 20);
		case 3:
		default:
		}
	}

	// $FF: renamed from: f (int) void
	public static void method_78(int var0) {
		method_99(1);
		field_181 = 4;
		if(var0 != -1) {
			class_0.field_8 = (short)var0;
		}

		field_183 = 5;
	}

	// $FF: renamed from: f () void
	public static void method_79() {
		field_181 = 6;
		field_183 = 5;
	}

	// $FF: renamed from: g () void
	public static final void method_80() throws Exception {
		class_0.method_4();
		int var1;
		//      field_183 = 4;
		switch(field_183) {
		case 1:
			method_76(false);
			return;
		case 2:
		case 8:
			method_91();
			return;
		case 3:
			class_1.method_24();
			return;
		case 4:
			// TODO: 
			field_174 = 0;
			class_0.method_2();
			method_63(field_128[class_0.field_8], "g");
			field_174 = 60;
			class_0.method_2();
			method_75();
			field_174 = 90;
			class_0.method_2();
			var1 = 4;

			while(true) {
				--var1;
				if(var1 < 0) {
					class_1.field_123 = method_55();
					var1 = class_1.field_123;

					while(true) {
						--var1;
						if(var1 < 0) {
							class_1.method_23();
							field_183 = 3;
							return;
						}

						class_1.field_124[var1].method_7();
					}
				}

				class_1.field_125[var1 << 1] = method_55();
				class_1.field_125[(var1 << 1) + 1] = method_55();
			}
		case 5:
			if(field_172 != null) {
				var1 = field_172.length;

				while(true) {
					--var1;
					if(var1 < 0) {
						field_172 = (byte[][])null;
						break;
					}

					field_172[var1] = null;
				}
			}

			if(field_173 != null) {
				var1 = field_173.length;

				while(true) {
					--var1;
					if(var1 < 0) {
						field_173 = (short[][])null;
						break;
					}

					field_173[var1] = null;
				}
			}

			field_183 = field_181;
			return;
		case 6:
			method_63(field_184, "s");
			method_98(1);
			method_84(0);
			field_183 = 2;
			return;
		case 7:
			if(class_0.field_5 - field_182 > 200L) {
				field_182 = class_0.field_5;
				class_0.method_2();
				return;
			}
		}

	}

	// $FF: renamed from: a (int) short
	public static short method_81(int var0) {
		int var1;
		for(var1 = 0; field_185[var1] != var0; var1 += 3) {
			;
		}

		return field_185[var1 + 1];
	}

	// $FF: renamed from: h () void
	public static void method_82() {
		byte[] var1 = new byte[field_186.length];
		int var3 = 0;

		for(int var5 = 0; var5 < field_185.length; var5 += 3) {
			method_47(field_186, field_185[var5 + 1]);
			short var2 = field_185[var5 + 2];
			method_48(2);
			if(method_51() != 0) {
				System.arraycopy(field_186, field_185[var5 + 1], var1, var3, var2);
				var3 += var2;
			}
		}

		method_101("mn", var1, 0, var3);
	}

	// $FF: renamed from: i () void
	public static void method_83() {
		if(method_100("mn") != 0) {
			byte[] var2 = field_136;
			int var5 = 0;

			for(int var6 = 0; var6 < field_185.length; var6 += 3) {
				method_47(field_186, field_185[var6 + 1]);
				short var3 = field_185[var6 + 2];
				method_48(2);
				if(method_51() != 0) {
					System.arraycopy(var2, var5, field_186, field_185[var6 + 1], var3);
					var5 += var3;
				}
			}

		}
	}

	// $FF: renamed from: g (int) void
	public static void method_84(int var0) {
		field_188 = var0;
		field_193 = method_81(var0);
		method_47(field_186, field_193);
		method_50();
		method_51();
		field_189 = method_50();
		field_190 = method_50();
		field_191 = method_50();
		field_192 = method_50();
		short var5 = -1;
		int var7 = 0;

		for(int var8 = 0; var7 < field_191; var8 += 2) {
			short var3 = field_187[var8] = method_50();
			short var4 = field_187[1 + var8] = method_50();
			int var2 = field_137;
			field_137 = var4 + field_193;
			method_48(6);
			if(method_51() == 1) {
				var5 = var3;
			}

			field_137 = var2;
			++var7;
		}

		if(var5 != -1) {
			method_87(var5, true);
		} else {
			field_194 = -1;
			field_195 = -1;
		}
	}

	// $FF: renamed from: a (int) int
	public static int method_85(int var0) {
		int var1;
		for(var1 = 0; field_187[var1] != var0; var1 += 2) {
			;
		}

		return field_187[var1 + 1];
	}

	// $FF: renamed from: a (int, int) int
	public static int method_86(int var0, int var1) {
		method_47(field_186, var0);
		method_48(7);
		short var2 = method_50();
		method_48(2);

		for(int var6 = 0; var6 < var2; ++var6) {
			short var3 = method_50();
			short var4 = method_50();
			if(var1 == var3) {
				return var4;
			}
		}

		return -1;
	}

	// $FF: renamed from: a (int, boolean) void
	public static void method_87(int var0, boolean var1) {
		if(field_191 == 0) {
			field_194 = -1;
		} else {
			method_47(field_186, field_193);
			if(field_194 != -1 && !var1) {
				method_52(field_186, field_193 + method_85(field_194) + 6);
				method_53(0);
			}

			field_196 = method_85(var0);
			method_52(field_186, field_193 + field_196 + 6);
			method_53(1);
			method_48(field_196);
			field_195 = method_50();
			field_194 = var0;
		}
	}

	// $FF: renamed from: a (int, int, byte[], int) int
	public static int method_88(int var0, int var1, byte[] var2, int var3) {
		short var4;
		int var5 = method_86(var4 = method_81(var0), var1);
		method_47(field_186, var4 + var5 + 14);
		short var6 = method_50();
		if(var2 == null) {
			return var6;
		} else {
			System.arraycopy(field_186, field_137 - 2, var2, var3, var6 + 2);
			return var6;
		}
	}

	// $FF: renamed from: a (int, int, byte[], int) void
	public static void method_89(int var0, int var1, byte[] var2, int var3) {
		short var4;
		int var5 = method_86(var4 = method_81(var0), var1);
		System.arraycopy(var2, var3, field_186, var4 + var5 + 14, ((255 & var2[0]) << 8 | 255 & var2[1]) + 2);
	}

	// $FF: renamed from: a (int, int) boolean
	public static boolean method_90(int var0, int var1) {
		short var2;
		int var3 = method_86(var2 = method_81(var0), var1);
		method_47(field_186, var2 + var3 + 9);
		return method_51() != 0;
	}

	// $FF: renamed from: j () void
	public static void method_91() throws Exception {
		int var0 = field_194;
		switch(field_195) {
		case 3:
		case 4:
		case 5:
			if((class_0.field_17 & 16388) != 0) {
				--var0;
				if(var0 < 0) {
					var0 = field_191 - 1;
				}

				method_87(var0, false);
			}

			if((class_0.field_17 & '脀') != 0) {
				++var0;
				if(var0 >= field_191) {
					var0 = 0;
					if(field_190 != -1) {
						method_84(field_190);
					}
				}

				method_87(var0, false);
			}

			if((class_0.field_17 & 196640) != 0) {
				method_47(field_186, field_193 + field_196);
				method_48(7);
				byte var2 = method_51();
				byte var3 = method_51();
				class_0.field_17 &= -196641;
				switch(var2) {
				case 10:
				case 14:
				case 17:
					if(field_195 == 5) {
						method_47(field_186, field_193 + field_196 + 9);
						int var4 = method_51() == 0?1:0;
						method_52(field_186, field_193 + field_196 + 9);
						method_53(var4);
						if(var2 == 17) {
							if(var4 != 0) {
								field_200 = true;
								method_98(1);
							} else {
								method_99(1);
								field_200 = false;
							}
						}
					}

					if(var2 == 14) {
						field_197 = field_188;
						field_198 = field_194;
						field_199 = var3;
						class_1.method_6(1);
					}
					break;
				case 11:
					method_84(var3);
					break;
				case 12:
					method_78(var3);
					break;
				case 13:
					field_126.destroyApp(true);
					break;
				case 15:
					method_79();
					break;
				case 16:
					class_1.method_6(3);
					field_183 = 3;
				}
			}
		case 6:
		case 7:
		default:
			if((class_0.field_17 & 135184) != 0 && field_190 != -1) {
				method_84(field_190);
			}

			if((class_0.field_17 & 270400) != 0 && field_189 != -1) {
				method_84(field_189);
			}

			class_0.method_2();
		}
	}

	// $FF: renamed from: k () void
	public static void method_92() {
		method_47(field_186, field_193);
		method_48(method_50());
		int var7 = field_192;

		while(var7-- != 0) {
			short var0 = method_50();
			short var1 = method_50();
			short var2 = method_50();
			short var3;
			short var4;
			byte var8;
			switch(var0) {
			case 1:
				var3 = method_61(method_50());
				method_93(var1, var2, var3);
				break;
			case 2:
				method_64(method_61(method_50()), 0, var1, var2);
				break;
			case 3:
				var8 = method_51();
				method_48(2);
				var3 = method_61(method_50());
				var4 = method_61(method_50());
				var3 = var8 == 0?var3:var4;
				method_93(var1, var2, var3);
				break;
			case 4:
				var8 = method_51();
				method_48(2);
				if((var3 = method_50()) != -1) {
					var3 = method_61(var3);
				}

				var4 = method_61(method_50());
				if((var3 = var8 == 0?var3:var4) != -1) {
					method_64(var3, 0, var1, var2);
				}
				break;
			case 5:
				var8 = method_51();
				method_48(2);
				byte var9 = method_51();
				var3 = method_61(method_50());
				var4 = method_61(method_50());
				short var5 = method_61(method_50());
				short var6 = method_61(method_50());
				if(var9 == 0) {
					var3 = var8 == 0?var5:var6;
				} else {
					var3 = var8 == 0?var3:var4;
				}

				method_64(var3, 0, var1, var2);
				break;
			case 6:
				short var10 = method_50();
				short var11 = method_50();
				method_51();
				setVar13(method_49());
				//            field_177.setColor(var13);
				field_177.fillRect(var1, var2, var10, var11);
				setVar13(method_49());
				//            field_177.setColor(var13);
				field_177.drawRect(var1, var2, var10, var11);
				break;
			case 7:
				var8 = method_51();
				method_48(1);
				short var14 = method_50();
				var3 = method_61(method_50());
				var4 = method_61(method_50());
				var3 = var8 == 0?var3:var4;
				int var15 = method_93(var1, var2, var3);
				method_48(var14 - var15);
			}
		}

	}

	// $FF: renamed from: a (int, int, short) int
	public static int method_93(int var0, int var1, short var2) {
		short var3 = method_50();
		short var4 = field_155[var2];
		short var5 = field_156[var2];
		int var6 = var0;

		for(int var7 = 0; var7 < var3; ++var7) {
			byte var8;
			if((var8 = method_51()) == -2) {
				var0 = var6;
				var1 += var5;
			} else {
				if(var8 >= 0) {
					method_64(var2, var8, var0, var1);
				}

				var0 += var4;
			}
		}

		return var3;
	}

	// $FF: renamed from: a (int, byte[], int) int
	public static int method_94(int var0, byte[] var1, int var2) {
		int var4 = var2 + 2;

		do {
			var1[var4++] = (byte)(var0 % 10);
		} while((var0 /= 10) > 0);

		var1[var2] = 0;
		var1[var2 + 1] = (byte)(var4 - 2);
		int var3;
		int var6 = (var3 = var4 - var2) - 2 >> 1;
		var2 += 2;

		for(int var7 = 0; var7 < var6; ++var7) {
			byte var5 = var1[var7 + var2];
			var1[var7 + var2] = var1[var2 + var3 - 3 - var7];
			var1[var2 + var3 - 3 - var7] = var5;
		}

		return var3;
	}

	// $FF: renamed from: a (byte[], int) int
	public static int method_95(byte[] var0, int var1) {
		method_47(var0, var1);
		int var2 = method_50();
		int var3 = 0;
		int var4 = 1;

		while(true) {
			--var2;
			if(var2 < 0) {
				return var3;
			}

			if(var0[var2 + field_137] >= 0) {
				var3 += var0[var2 + field_137] * var4;
				var4 *= 10;
			}
		}
	}

	// $FF: renamed from: b (int) int
	public static int method_96(int var0) {
		for(int var1 = 0; var1 < field_203.length; var1 += 2) {
			if(field_203[var1] == var0) {
				return var1;
			}
		}

		return -1;
	}

	// $FF: renamed from: l () void
	public static void method_97() {
		System.out.println("Unpack sounds:");
		try {
			method_58("m0", false);
			field_134 = method_59("m", 0);
			short var1;
			field_203 = new byte[(var1 = method_55()) * 2];
			//field_201 = new Player[var1];
			String[] var5 = new String[]{"", "audio/midi", "audio/x-wav"};
			// TODO:
			for(int var7 = 0; var7 < var1; ++var7) {
				field_203[var7 << 1] = (byte)method_55();
				int var6 = field_134.read();
				field_203[1 + (var7 << 1)] = (byte)field_134.read();
				String var4 = var5[var6];
				String var3 = "" + field_203[var7 << 1] + ".snd";
				String name = "";
				if (var4.equals("audio/midi")) {
					name = "res" + File.separator + "sounds" + File.separator + "song" + var7 + ".mid";
				} else if (var4.equals("audio/x-wav")) {
					name = "res" + File.separator + "sounds" + File.separator + "song" + var7 + ".wav";
				} else {
					name = "res" + File.separator + "sounds" + File.separator + "song" + var7 + ".unk";
				}
				
				System.out.print("-----" + name + "...done!\n");

				FileInputStream fis = new FileInputStream(var3);
				FileOutputStream fos = new FileOutputStream(name);
				BufferedInputStream bis = new BufferedInputStream(fis);
				BufferedOutputStream bos = new BufferedOutputStream(fos);

				while (true) {
					int _byte = bis.read();
					if (_byte == -1) {
						break;
					}
					bos.write(_byte);
				}

				bos.flush();
				bos.close();
				fos.close();
				bis.close();
				fis.close();

				// System.out.println(var3);
				//            Player var2;
				//            (var2 = field_201[var7] = Manager.createPlayer("S".getClass().getResourceAsStream(var3), var4)).realize();
				//            var2.prefetch();
				//            var2.addPlayerListener(field_126);
			}

		} catch (Exception var8) {
			;
		}
	}

	// $FF: renamed from: h (int) void
	public static void method_98(int var0) {
		if(field_200) {
			try {
				method_99(field_202); // Stop
				if(field_202 < 0) {
					// int var1 = method_96(var0);
					//               Player var2;
					//               (var2 = field_201[var1 >> 1]).setLoopCount(field_203[var1 + 1]);
					//               var2.start();
					field_202 = var0;
				}
			} catch (Exception var3) {
				field_202 = -1;
			}
		}
	}

	// $FF: renamed from: i (int) void
	public static void method_99(int var0) {
		if(field_200) {
			try {
				if(var0 >= 0) {
					var0 = method_96(var0) >> 1;
				// field_201[var0].stop();
				}
			} catch (Exception var2) {
				;
			}

			field_202 = -1;
		}
	}

	//   public void playerUpdate(Player var1, String var2, Object var3) {
	//      try {
	//         if(var2 == "error" || field_202 > 0 && (var2 == "closed" || var2 == "stopped" || var2 == "endOfMedia" || var2 == "deviceUnavailable")) {
	//            if(field_202 == 1) {
	//               return;
	//            }
	//
	//            field_202 = -1;
	//
	//            try {
	//               var1.stop();
	//            } catch (Exception var5) {
	//               ;
	//            }
	//         }
	//
	//      } catch (Exception var6) {
	//         ;
	//      }
	//   }

	// $FF: renamed from: a (java.lang.String) int
	public static int method_100(String var0) {
		int var1 = 0;

		try {
			//RecordStore var2;
			///field_136 = (var2 = RecordStore.openRecordStore(var0, false)).enumerateRecords((RecordFilter)null, (RecordComparator)null, false).nextRecord();
			field_137 = 0;
			///var2.closeRecordStore();
			var1 = field_136.length;
		} catch (Exception var4) {
			;
		}

		return var1;
	}

	// $FF: renamed from: a (java.lang.String, byte[], int, int) void
	public static void method_101(String var0, byte[] var1, int var2, int var3) {
		try {
			// RecordStore var4 = RecordStore.openRecordStore(var0, true);

			try {
				//  var4.setRecord(var4.enumerateRecords((RecordFilter)null, (RecordComparator)null, false).nextRecordId(), var1, var2, var3);
			} catch (Exception var6) {
				//var4.addRecord(var1, var2, var3);
			}

			//var4.closeRecordStore();
		} catch (Exception var7) {
			;
		}
	}

	// $FF: renamed from: j (int) void
	public static void method_102(int var0) {
		int[] var3 = new int[]{48, 48, 49, 48};
		long var4;
		int var6;
		if((var4 = System.currentTimeMillis()) - field_206 > 3000L) {
			field_206 = var4;
			var6 = field_204.length;

			while(true) {
				--var6;
				if(var6 < 0) {
					field_205 = 0;
					break;
				}

				field_204[var6] = 655356;
			}
		}

		var6 = field_204.length;
		field_204[field_205++] = var0;
		if(field_205 == var6) {
			boolean var7 = true;

			while(true) {
				--var6;
				if(var6 < 0) {
					if(var7) {
						field_207 = !field_207;
					}

					field_205 = 0;
					break;
				}

				var7 &= var3[var6] == field_204[var6];
			}
		}

	}

	// $FF: renamed from: m () void
	public static void method_103() {
		if(field_207) {
			//         field_177.setColor(0);
			//         field_177.fillRect(0, 0, field_210, field_209.getHeight());
			//         field_177.setColor(16777215);
			//         field_177.setFont(field_209);
			//         field_177.drawString(field_208, 0, 0, 0);
		}

	}

	public static int getVar13() {
		return var13;
	}

	public static void setVar13(int var13) {
		Game.var13 = var13;
	}

	static {
		for(int var2 = 0; var2 < 256; ++var2) {
			int var0 = var2;

			for(int var1 = 0; var1 < 8; ++var1) {
				if((var0 & 1) != 0) {
					var0 = -306674912 ^ var0 >>> 1;
				} else {
					var0 >>>= 1;
				}
			}

			field_159[var2] = var0;
		}

		new Random();
		field_169 = (System.currentTimeMillis() ^ 25214903917L) & 281474976710655L;
		//      field_175 = Font.getDefaultFont().stringWidth("loading");
		//      field_176 = Font.getDefaultFont().getHeight();
		field_178 = -1;
		field_187 = new short[30];
		field_188 = 0;
		field_189 = 0;
		field_190 = 0;
		field_191 = -1;
		field_192 = -1;
		field_193 = -1;
		field_194 = -1;
		field_195 = -1;
		field_196 = -1;
		field_200 = true;
		field_202 = -1;
		field_204 = new int[]{655356, 655356, 655356, 655356};
		field_208 = "G(0.8.9), GP(0.6.8)";
		//      field_209 = Font.getDefaultFont();
		//      field_210 = field_209.stringWidth(field_208);
	}
}
