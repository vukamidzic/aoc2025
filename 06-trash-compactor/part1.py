import re


def main():
    # filename = "test.txt"
    filename = "input.txt"
    numbers = []
    ops = []
    with open(filename, "r") as file:
        for line in file:
            if "*" in line or "+" in line:
                ops = re.findall(r"\*|\+", line)
            else:
                numberMatches = list(map(lambda x: int(x), re.findall(r"\d+", line)))
                numbers.append(numberMatches)

    result = 0
    col = 0

    for op in ops:
        curr = 0 if op == "+" else 1
        for row in range(len(numbers)):
            curr = curr + numbers[row][col] if op == "+" else curr * numbers[row][col]

        result += curr
        col += 1
    print(f"Final result: {result}")


if __name__ == "__main__":
    main()
