import csv

filename = 'batt.csv'

with open(filename, newline='') as csvfile:
    reader = csv.reader(csvfile, delimiter=',', quotechar='"')
    data = []
    next(reader)  # skip the first row
    for row in reader:
        data.append([float(x) for x in row])

    # Transpose the 2D list
    transposed_data = list(map(list, zip(*data)))

    # Print the transposed 2D vector as a string
    print("{{" + "},{".join([",".join(map(str, row)) for row in transposed_data]) + "}}")
