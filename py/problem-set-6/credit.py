


def main():
    number = input("Number: ")
    if(len(number) > 13 or len(number) < 16):
        detect(len(number), number)
    else:
        print("INVALID")

def detect(x, number):
    if (number[0] == '4' and (x == 13 or x == 16)):
        print("VISA")
    elif ((number[0:2] in ['51', '52', '53', '54', '55']) and x == 16):
        print("MASTERCARD")
    elif ((number[0:2] in ['34', '37']) and x == 15):
        print("AMEX")
    else:
        print("INVALID")


main()
