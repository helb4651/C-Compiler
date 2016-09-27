
fname = "TestFiles/a2/whileif.out"

with open(fname) as f:
    correct = f.readlines()
f.close


with open("tfile") as f:
    test = f.readlines()
f.close


thefile = open("results.txt", "w")
for entry in range(len(correct)):
    try:
        if(correct[entry] != test[entry]):
            print>>thefile, correct[entry] +""+test[entry] + "\n"
    except:
        print>>thefile, "Exception comparing outputs!"
        break
