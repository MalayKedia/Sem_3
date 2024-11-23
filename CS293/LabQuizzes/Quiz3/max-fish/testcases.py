import random
import os


def generate_random_grid(rows, cols, max_fish=10):
    values = list(range(11))
    weights = [50] + [5] * 10
    return [
        [random.choices(values, weights=weights)[0] for _ in range(cols)]
        for _ in range(rows)
    ]


def generate_test_cases(seed):
    random.seed(seed)
    test_cases = []

    for i in range(1, 11):
        rows = random.randint(1, 10)
        cols = random.randint(1, 10)

        grid = generate_random_grid(rows, cols)
        test_cases.append((rows, cols, grid))

    return test_cases


def main():
    seed = 6
    test_cases = generate_test_cases(seed)

    os.makedirs("testcases/inputs", exist_ok=True)
    os.makedirs("testcases/outputs", exist_ok=True)

    for i, (rows, cols, grid) in enumerate(test_cases, start=1):
        input_file = f"testcases/inputs/{i}.txt"
        output_file = f"testcases/outputs/{i}.txt"

        with open(input_file, "w") as f:
            f.write(f"{rows}\n{cols}\n")
            for row in grid:
                f.write(" ".join(map(str, row)) + "\n")


if __name__ == "__main__":
    main()
