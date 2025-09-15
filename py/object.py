

class student:
    def __init__(self, name, ID):
        self.name = name
        self.ID = ID

    def ChangeName(self, name):
        self.name = name

    def ChangeID(self, ID):
        self.ID = ID

    def print(self):
        print(self.name, self.ID)


def main():
    jane = student("jane", 5)
    jane.print()
    jane.ChangeName("JANE")
    jane.ChangeID(9)
    jane.print()



main()
