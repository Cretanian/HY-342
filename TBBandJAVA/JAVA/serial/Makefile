JFLAGS = -g
JC = javac
JVM = java
ASSERTION = -ea

FILE = input1.txt
ITERATIONS = 2

.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \ TreeNode.java  \ Body.java \ Main.java

default: classes

run:
	$(JVM) $(ASSERTION) Main $(FILE) $(ITERATIONS)

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
