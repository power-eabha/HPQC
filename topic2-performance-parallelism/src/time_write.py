import time
import sys
import os

def main():
    # Check if user provided input
    if len(sys.argv) != 2:
        print("Usage: python3 time_write.py <number_of_lines>")
        sys.exit(1)

    # Number of lines to write
    n = int(sys.argv[1])

    # Create data folder if it doesn't exist
    os.makedirs("data", exist_ok=True)

    filename = "data/sample_data.txt"

    # Start timing
    start_time = time.time()

    # Write to file
    with open(filename, "w") as f:
        for i in range(n):
            f.write(f"This is line {i}\n")

    # End timing
    end_time = time.time()

    # Calculate runtime
    run_time = end_time - start_time

    # Output results
    print(f"Wrote {n} lines to {filename}")
    print(f"Runtime: {run_time:.6f} seconds")

if __name__ == "__main__":
    main()
