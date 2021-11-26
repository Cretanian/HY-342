JFLAGS = -g
JC = javac
JVM = java
ASSERTION = -ea

FILE = input2.txt
ITERATIONS = 10000

.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \ TreeNode.java  \ Body.java \ Main.java

default: classes

run1:
	$(JVM) $(ASSERTION) Main $(FILE) $(ITERATIONS) 1

run2:
	$(JVM) $(ASSERTION) Main $(FILE) $(ITERATIONS) 4

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
