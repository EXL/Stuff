# Drawings.py
# $ sudo apt install python3-pyqt5
# $ python Drawings.py
import sys

from PyQt5.QtCore import Qt
from PyQt5.QtGui import QPainter, QColor
from PyQt5.QtWidgets import QApplication, QWidget

class MouseTracker(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.setMouseTracking(True)
        self.setAttribute(Qt.WA_OpaquePaintEvent, True)

    def initUI(self):
        self.show()
        self.posN = None
        self.posO = None

    def mouseMoveEvent(self, event):
        self.posO = self.posN
        self.posN = event.pos()
        self.update()

    def paintEvent(self, event):
        if self.posN and self.posO:
            q = QPainter(self)
            q.setPen(QColor(200, 0, 0))
            q.drawLine(self.posO.x(), self.posO.y(), self.posN.x(), self.posN.y())

app = QApplication(sys.argv)
ex = MouseTracker()
sys.exit(app.exec_())
