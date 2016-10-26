
#!/bin/sh

tar -cvf hw3.tar globals.h printtree.cpp printtree.h scanType.h semantic.cpp semantic.h symbolTable.cpp symbolTable.h types.csv typingHelpers.cpp typingHelpers.h c-.y c-.l makefile

name=helbling
ass=3
file=hw3.tar

# adjust the next line for class and semester
curl -F student=$name -F assignment="CS445 F16 Assignment $ass" -F "submittedfile=@$file" "http://ec2-52-89-93-46.us-west-2.compute.amazonaws.com/cgi-bin/fileCapture.py"
