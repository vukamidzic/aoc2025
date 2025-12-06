from math import prod


def main():
    # filename = "test.txt"
    filename = "input.txt"
    lines = []
    ops = []
    with open(filename, "r") as file:
        lines = [line[:-1] for line in file.readlines()]
        ops = list(filter(lambda c: c != " ", lines[-1]))
        lines = lines[:-1]

    numbers = []
    block = []
    for col in range(len(lines[0])):
        num = "".join([lines[row][col] for row in range(len(lines))])
        tmp = map(lambda c: False if c != " " else True, num)
        if not all(tmp):
            block.append(int(num))
        else:
            numbers.append(block)
            block = []
    numbers.append(block)

    result = 0
    combined = list(zip(ops, numbers))
    for pair in combined:
        result += sum(pair[1]) if pair[0] == "+" else prod(pair[1])

    print(f"Final result: {result}")


if __name__ == "__main__":
    main()
