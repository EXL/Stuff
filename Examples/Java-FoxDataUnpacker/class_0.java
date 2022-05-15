import java.awt.Graphics;

// $FF: renamed from: a
public final class class_0 implements Runnable {
	// $FF: renamed from: a long
	public static long field_0;
	// $FF: renamed from: b long
	public static long field_1;
	// $FF: renamed from: a boolean
	public static boolean field_2;
	// $FF: renamed from: a java.lang.Thread
	public static Thread field_3;
	// $FF: renamed from: b boolean
	public static boolean field_4;
	// $FF: renamed from: c long
	public static long field_5;
	// $FF: renamed from: a int
	public static int field_6;
	// $FF: renamed from: b int
	public static int field_7;
	// $FF: renamed from: a short
	public static short field_8;
	// $FF: renamed from: c int
	public static int field_9;
	// $FF: renamed from: d int
	public static int field_10;
	// $FF: renamed from: e int
	public static int field_11;
	// $FF: renamed from: f int
	public static int field_12;
	// $FF: renamed from: g int
	public static int field_13;
	// $FF: renamed from: h int
	public static int field_14;
	// $FF: renamed from: d long
	public static long field_15;
	// $FF: renamed from: i int
	public static int field_16;
	// $FF: renamed from: j int
	public static int field_17;

	public class_0() throws Exception {
		//      super(false);
		//      this.setFullScreenMode(true);
		field_6 = 176;
		field_7 = 208;
	}

	// $FF: renamed from: a () void
	public final void method_0() {
		field_3 = new Thread(this);
		field_4 = true;
		field_3.start();
	}

	// $FF: renamed from: b () void
	public static void method_1() {
		field_4 = false;
		field_3 = null;
	}

	public final void run() {
		while(field_4) {
			try {
				field_0 = System.currentTimeMillis();
				if(Game.field_183 != 8) {
					field_5 += field_0 - field_1;
				}

				field_1 = field_0;
				Game.method_80();
			} catch (Throwable var2) {
				;
			}
		}

	}

	// $FF: renamed from: c () void
	public static void method_2() {
		try {
			//         Game.field_177 = Game.field_127.getGraphics();
			class_1.method_41();
			//         Game.field_127.flushGraphics();
		} catch (Throwable var1) {
			;
		}
	}

	public final void paint(Graphics var1) {
		if(!field_2) {
			field_2 = true;
			field_2 = false;
		}
	}

	public final void keyPressed(int var1) {
		Game.method_102(var1);
		if(Game.field_183 == 1) {
			Game.method_76(false);
		} else if(Game.field_183 == 3 && var1 == -6) {
			field_14 = 0;

			try {
				class_1.method_6(2);
			} catch (Throwable var4) {
				;
			}

			Game.method_84(100);
			Game.field_183 = 8;
		} else {
			switch(var1) {
			case -8:
				field_14 |= 524288;
				field_13 |= 524288;
				break;
			case -7:
				field_14 |= 262144;
				field_13 |= 262144;
				break;
			case -6:
				field_14 |= 131072;
				field_13 |= 131072;
				break;
			case 35:
				field_14 |= 2048;
				field_13 |= 2048;
				break;
			case 42:
				field_14 |= 1024;
				field_13 |= 1024;
				break;
			case 48:
			case 49:
			case 50:
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
				field_14 |= 1 << var1 - 48;
				field_13 |= 1 << var1 - 48;
				break;
			default:
				if(var1 < 0) {
					//               switch(this.getGameAction(var1)) {
					//               case 1:
					//                  field_14 |= 16384;
					//                  field_13 |= 16384;
					//                  break;
					//               case 2:
					//                  field_14 |= 4096;
					//                  field_13 |= 4096;
					//               case 3:
					//               case 4:
					//               case 7:
					//               default:
					//                  break;
					//               case 5:
					//                  field_14 |= 8192;
					//                  field_13 |= 8192;
					//                  break;
					//               case 6:
					//                  field_14 |= '耀';
					//                  field_13 |= '耀';
					//                  break;
					//               case 8:
					//                  field_14 |= 65536;
					//                  field_13 |= 65536;
					//               }
				}
			}

			field_15 = field_5;
			field_16 = var1;

			try {
				Game.field_197 = var1;
				class_1.method_6(4);
			} catch (Throwable var5) {
				;
			}
		}
	}

	public final void keyReleased(int var1) {
		switch(var1) {
		case -8:
			field_14 &= -524289;
			break;
		case -7:
			field_14 &= -262145;
			break;
		case -6:
			field_14 &= -131073;
			break;
		case 35:
			field_14 &= -2049;
			break;
		case 42:
			field_14 &= -1025;
			break;
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			field_14 &= ~(1 << var1 - 48);
			break;
		default:
			if(var1 < 0) {
				//            switch(this.getGameAction(var1)) {
				//            case 1:
				//               field_14 &= -16385;
				//               break;
				//            case 2:
				//               field_14 &= -4097;
				//            case 3:
				//            case 4:
				//            case 7:
				//            default:
				//               break;
				//            case 5:
				//               field_14 &= -8193;
				//               break;
				//            case 6:
				//               field_14 &= -32769;
				//               break;
				//            case 8:
				//               field_14 &= -65537;
				//            }
			}
		}

		try {
			Game.field_197 = var1;
			class_1.method_6(5);
		} catch (Throwable var3) {
			;
		}
	}

	// $FF: renamed from: a (int) int
	public static int method_3(int var0) {
		return 0;
		//      return Game.field_127.getGameAction(var0);
	}

	// $FF: renamed from: d () void
	public static void method_4() {
		int var0 = field_13 | field_14;
		field_13 = 0;
		field_12 = field_11 ^ var0;
		field_11 = var0;
		field_17 = field_11 & field_12;
	}
}
