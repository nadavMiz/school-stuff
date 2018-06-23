import sys
import tarfile
import getopt


class Arguments:
    mode = ""  # extract or compress
    tar_name = ""  # tar file name
    directory = "."  # target directory (current directory by default)
    file_names = []  # names of files to extract/compress


def usage(name):
    print(name + " [c compress] [x extract] [t tar file name], [d directory to extract to]")
    sys.exit(1)


def files_to_extract_generator(members, files_to_extract):
    for member in members:
        if member.name in files_to_extract:
            yield member


def tar_extract(tar_file, files_to_extract, dest_dir):
    tar = tarfile.open(tar_file, "r:gz")
    tar.extractall(path=dest_dir, members=files_to_extract_generator(tar, files_to_extract))
    tar.close()


def tar_compress(tar_name, files_to_compress):
    tar = tarfile.open(tar_name, "w:gz")
    for file in files_to_compress:
        tar.add(file, recursive=False)

    tar.close()


def parse_args(argv, data):
    name = argv[0]
    try:
        opts, data.file_names = getopt.getopt(argv[1:], "hcxt:d:")
    except getopt.GetoptError:
        usage(name)
        sys.exit()

    for opt, arg in opts:
        # help flag
        if opt == "-h":
            usage(name)
            sys.exit(0)

        # set mode (extract or compress)
        if opt == "-c" or opt == "-x":
            # mode already defined
            if data.mode != "":
                print("You may not specify more than one -cx")
                sys.exit(1)
            # opt character represent the mode
            else:
                data.mode = opt[1];

        elif opt == "-t":
            data.tar_name = arg

        elif opt == "-d":
            data.directory = arg

    # no tar file to compress extract from
    if data.tar_name == "":
        usage(name)
        sys.exit(1)

    return


def main(argv):
    data = Arguments

    parse_args(argv, data)

    if data.mode == "c":
        tar_compress(data.tar_name, data.file_names)

    elif data.mode == "x":
        tar_extract(data.tar_name, data.file_names, data.directory)

    # if no function was called until now the arguments are invalid
    else:
        usage(argv[0])


if __name__ == "__main__":
    main(sys.argv)
