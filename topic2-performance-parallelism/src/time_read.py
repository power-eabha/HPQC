import time

def main():
    filename = "data/sample_data.txt"

    start_time = time.time()

    with open(filename, "r") as f:
        contents = f.read()

    end_time = time.time()
    run_time = end_time - start_time

    print(f"Read {len(contents)} characters from {filename}")
    print(f"Runtime: {run_time:.6f} seconds")

if __name__ == "__main__":
    main()

