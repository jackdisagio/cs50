
def agree():
    s = input("do you agree? ")

    if s.lower() in ["y", "yes"]:
        print("agree")
        return
    elif s.lower() in ["n", "no"]:
        print("desagree")
        return
    else:
        return agree()


agree()
