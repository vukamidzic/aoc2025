from typing import Dict, List, Tuple


def DFS(conns: Dict[str, List[str]]) -> int:
    memo: Dict[Tuple[str, bool, bool], int] = {}

    def visit(curr: str, visited: frozenset, dac_visited: bool, fft_visited: bool):
        if (curr, dac_visited, fft_visited) in memo:
            return memo[(curr, dac_visited, fft_visited)]

        if curr == "out":
            if dac_visited and fft_visited:
                return 1
            else:
                return 0

        count = 0
        for neigh in conns[curr]:
            if neigh not in visited:
                new_visited = visited | {neigh}
                new_dac_visited = dac_visited or (neigh == "dac")
                new_fft_visited = fft_visited or (neigh == "fft")
                count += visit(neigh, new_visited, new_dac_visited, new_fft_visited)

        memo[(curr, dac_visited, fft_visited)] = count
        return count

    return visit("svr", frozenset({"svr"}), False, False)


def main():
    # filename = "test2.txt"
    filename = "input.txt"
    conns = {}
    with open(filename, "r") as file:
        for line in file:
            parts = list(map(lambda s: s.strip(), line.split(sep=":")))
            start = parts[0]
            next = list(map(lambda s: s.strip(), parts[1].split(sep=" ")))
            conns[start] = next
    conns["out"] = []

    result = DFS(conns)
    print(f"Final result: {result}")


if __name__ == "__main__":
    main()
