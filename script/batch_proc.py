import os
import argparse
import subprocess

# The script takes three flagged input arguments:
#   -e, --executable    The name of the executable
#   -i, --inputfolder   The name of the input folder
#   -o, --outputfolder  The name of the output folder
#   -p, --processing    1 for encryption, 0 for decryption
if __name__ == "__main__":
    # Parse input arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-e", "--executable", type=str,
                        help="The name of the executable")
    parser.add_argument("-i", "--inputfolder", type=str,
                        help="The name of the input folder")
    parser.add_argument("-o", "--outputfolder", type=str,
                        help="The name of the output folder")
    parser.add_argument("-p", "--processing", type=int,
                        help="1 for encryption, 0 for decryption")
    args = parser.parse_args()
    
    # Get the list of names of the files in the input folder
    file_list = os.listdir(args.inputfolder)

    # Interpret the processing flag
    if args.processing == 1:
        p = "-e"
    elif args.processing == 0:
        p = "-d"
    else:
        raise Exception("Invalid input value for the flag '-p'. Please see the help")

    # Recursively run the executable on each file in the 
    # input folder
    for file in file_list:
        result = subprocess.run(
            [args.executable, "-k", "newkey.txt", "-f", p, "-i", f"{args.inputfolder}\\{file}", "-o", f"{args.outputfolder}\\{file}"],
            shell=True, text=True,
        )
        print(result.stdout)
