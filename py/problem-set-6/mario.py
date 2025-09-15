




def main():
    try:
        while(True):
            height = int(input("height: "))
            if height > 0:
                build(height)
                break
            else:
                print("please use another number")
    except:
        print("error")


def build(height):
    for i in range(height):
        size = height - (i + 1)
        print(" " * size, end = "")
        print("#" * (i + 1), end = "")
        print(" ", end = "")
        print("#" * (i + 1), end = "")
        print("")


main()
