import os,sys
import subprocess
import itertools
import time

test_params={}
test_params["cutFlow"]={"-r":map(str,range(4)),
                        "-N":["1000"]}
test_params["plotObs_baseline"]={"-N":["1000"]}
test_params["plotObs_antitag"] = test_params["plotObs_baseline"]
test_params["plotObs_doubleTag"] = test_params["plotObs_baseline"]
test_params["plotObs_singleTag"] = test_params["plotObs_baseline"]
test_params["plotObs_singleEleCR_baseline"] = test_params["plotObs_baseline"]
test_params["plotObs_singleMuCR_baseline"] = test_params["plotObs_baseline"]
test_params["plotObs_photon_baseline"] = {"-N":["1000"],
                                          "-l":map(str,[0,1])}
test_params["ALPHABET"] = {"-N":["1000"],
                           "-r":map(str,range(4)),
                           "-l":map(str,[0,1])}
test_params["ALPHABET_photon"] = {"-N":["1000"],
                                  "-l":map(str,[0,1])}

def format_test( param_dict={} ):
    test_commands=[]
    for test in test_params:
        options = []
        temp=[]
        for param in test_params[test]:
            options.append(param)
            temp.append(test_params[test][param])
        permutations = list(itertools.product(*temp))
        #convert tuples to lists
        permutations=map(list,permutations)

        for p in permutations:
            args = list(itertools.chain(zip(options,p)))
            # convert tuples to lists
            args = map(list,args)
            test_commands.append([[test]]+args)
            test_commands[-1] = sum(test_commands[-1],[])
    return test_commands

alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']

def main():
    commands = format_test(test_params)
    ps=[]
    for i,command in enumerate(commands):
        with open(command[0]+"_unit_test.log","w") as out : 
            print "Running test {0}: {1}".format(alphabet[i],command[0])
            ps.append(subprocess.Popen(command,stdout=out,stderr=out))

    print " ".join(alphabet[:len(commands)])
    print "-"*2*len(commands)
    while( reduce(lambda x,y : x|y,map(lambda x : x.poll()==None,ps)) ):
        progress = map(lambda x : '\033[95mx\033[0m' if x else '\033[92mo\033[0m',map(lambda x : x.poll()==None,ps))
        sys.stdout.write("\r"+" ".join(progress))
        sys.stdout.flush()
        time.sleep(1)
                
    progress = map(lambda x : '\033[95mx\033[0m' if x else '\033[92mo\033[0m',map(lambda x : x.poll()==None,ps))              
    sys.stdout.write("\r"+" ".join(progress)+"\n") 

if __name__ == '__main__':
  main()
