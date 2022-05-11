import javax.swing.*;
import java.awt.*;

public class Main {

    int x = 0;
    int y = 0;

    public static void main(String[] args) {
        // write your code here
        Main gui = new Main();
        gui.go();
    }


    public void go() {
        JFrame frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        MyDraw draw = new MyDraw();
        frame.getContentPane().add(draw);
        frame.setSize(600, 400);
        frame.setVisible(true);
        for (int i = 0; i < 400; i++) {
            if(i<200){
                x++;
                y++;
            }
            else {
                x++;
                y--;
            }
            draw.repaint();
            frame.getToolkit().sync();
            Toolkit.getDefaultToolkit().sync();
            try {
                Thread.sleep(10);
            } catch (Exception ex) {
            }
        }
    }

    class MyDraw extends JPanel {
        public void paintComponent(Graphics g) {
            g.setColor(Color.white);
            g.fillRect(0, 0, this.getWidth(), this.getHeight());

            g.setColor(Color.BLUE);
            g.fillRect(x, y, 40, 40);
        }
    }
}
