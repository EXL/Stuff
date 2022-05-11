import os
import sys
import subprocess

from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from subprocess import Popen, PIPE, STDOUT

def main():
    app = QApplication(sys.argv) 
    w = MyWindow() 
    w.show() 
    sys.exit(app.exec_())

class MyWindow(QWidget):
    def __init__(self, *args): 
        QWidget.__init__(self, *args) 
 
        # create objects
        label = QLabel(self.tr("Enter command and press Return"))
        self.le = QLineEdit()
        self.te = QTextEdit()
        self.te.setCurrentFont(QFont("Monospace"))
        self.te.setFontPointSize(9)

        # layout
        layout = QVBoxLayout(self)
        layout.addWidget(label)
        layout.addWidget(self.le)
        layout.addWidget(self.te)
        self.setLayout(layout) 

        # create connection
        self.le.returnPressed.connect(self.run_command)

    def run_command(self):
        cmd = str(self.le.text())
        p = Popen(cmd.split(), stdin=PIPE, stdout=PIPE, stderr=STDOUT)
        stdouterr, err = p.communicate(b"input data that is passed to subprocess' stdin")
        self.te.setText(stdouterr.decode("utf-8"))
  
if __name__ == "__main__": 
    main()
