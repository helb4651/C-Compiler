

fname = "scannerTest.out"

with open(fname) as f:
    correct = f.readlines()
f.close


with open("tfile") as f:
    test = f.readlines()
f.close

for entry in range(len(correct)):
    if(correct[entry] != test[entry]):
        print correct[entry] +""+test[entry] + "\n\n"
