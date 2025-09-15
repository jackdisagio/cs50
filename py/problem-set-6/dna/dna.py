import csv
from sys import argv


def main():

    if(len(argv) != 3):
        print("USE: dna.py [...] [...]")
        exit(0)

    # TODO: Read database file into a variable
    database = ''
    try:
        with open(argv[1]) as file:
            reader = csv.DictReader(file)
            database = list(reader)
    except:
        print("error in [databases]")

    subsequence = ''
    try:
        with open(argv[1]) as file:
            reader = file.readline()
            grup = reader.strip()
            subsequence = grup.split(',')
            del subsequence[0]

    except:
        print("error in [seguence]")

    # TODO: Read DNA sequence file into a variable
    dna = ''
    try:
        with open(argv[2]) as file:
            dna = file.read()
    except:
        print("error in [dna text]")

    # TODO: Find longest match of each STR in DNA sequence
    result = []
    for i in range(len(subsequence)):
        result.append(longest_match(dna, subsequence[i]))

    # TODO: Check database for matching profiles
    for i in range(len(database)): #passare ogni persona
        count = 0
        for j in range(len(subsequence)): #passare ogni seguenza
            temp = database[i][f'{subsequence[j]}']
            if int(temp) == result[j]:
                count = count + 1
        if count == len(subsequence):
            print(database[i]['name'])
            return
    print("No match")
    return


def longest_match(sequence, subsequence): #DNA and STR target
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
