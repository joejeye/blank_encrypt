import os
import send2trash
import argparse

def move_files_to_recycle_bin(folder_path, file_to_keep):
    # Check if the specified folder exists
    if not os.path.exists(folder_path):
        print(f"The folder {folder_path} does not exist.")
        return

    # Iterate over all the files in the folder
    for filename in os.listdir(folder_path):
        file_path = os.path.join(folder_path, filename)

        # Check if it is a file and not the file to keep
        if os.path.isfile(file_path) and filename != file_to_keep:
            # Move the file to the recycle bin
            send2trash.send2trash(file_path)
            print(f"Moved {file_path} to the recycle bin.")

# Example usage
# folder = 'path_to_your_folder'  # Replace with your folder path
# file_to_keep = 'file_to_keep.ext'  # Replace with the file name you want to keep
# move_files_to_recycle_bin(folder, file_to_keep)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--directory", help="The directory where files are to be removed")
    parser.add_argument("-k", "--keep", help="The name of the file to keep")

    args = parser.parse_args()

    if not args.directory:
        print("Please specify the directory")
    
    if not args.keep:
        keepfile = ""
    else:
        keepfile = args.keep

    move_files_to_recycle_bin(args.directory, keepfile)