from collections import defaultdict, deque
from typing import DefaultDict


def BFS(conns: DefaultDict[str, list[str]]) -> int:
    path_counts = defaultdict()
    for k in conns.keys():
        path_counts[k] = 0

    path_counts["out"] = 0
    path_counts["you"] = 1
    queue = deque(["you"])

    while len(queue) > 0:
        curr = queue.popleft()
        count_to_curr = path_counts[curr]
        for neigh in conns[curr]:
            path_counts[neigh] += count_to_curr

            if path_counts[neigh] == count_to_curr:
                queue.append(neigh)

    return path_counts["out"]


def main():
    # filename = "test1.txt"
    filename = "input.txt"
    conns = defaultdict()
    with open(filename, "r") as file:
        for line in file:
            parts = list(map(lambda s: s.strip(), line.split(sep=":")))
            start = parts[0]
            next = list(map(lambda s: s.strip(), parts[1].split(sep=" ")))
            conns[start] = next
    conns["out"] = []

    result = BFS(conns)
    print(f"Final result: {result}")


if __name__ == "__main__":
    main()
