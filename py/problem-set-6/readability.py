def main():
    text = input('Text:')
    words = text.split()
    n_word = min(len(words), 100)

    temp = l_s(n_word, words)

    if n_word < 100:
        L = (temp[0] / n_word) * 100
        S = (temp[1] / n_word) * 100
    else:
        L = temp[0] / 100
        S = temp[1] / 100

    grade = round(0.0588 * L - 0.296 * S - 15.8)
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def l_s(n_word, words):
    s = 0
    l = 0
    for i in range(n_word):
        for j in range(len(words[i])):
            if words[i][j].isalpha():
                l += 1
            elif words[i][j] == '.':
                s += 1
    return l, s


main()
