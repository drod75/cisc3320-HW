import threading
import time

# threading api: https://docs.python.org/3/library/threading.html
# time api: https://docs.python.org/3/library/time.html

# Shared variables to store the result
max_divisors = 0
number_with_max_divisors = 0

# threading api: https://docs.python.org/3/library/threading.html
lock = threading.Lock()


def count_divisors(start, end):
    global max_divisors, number_with_max_divisors
    # Counts divisors for numbers in a given range.
    for num in range(start, end + 1):
        divisor_count = sum(1 for i in range(1, num + 1) if num % i == 0)

        # Update the max_divisors and corresponding number atomically
        with lock:
            if divisor_count > max_divisors:
                max_divisors = divisor_count
                number_with_max_divisors = num


# time api: https://docs.python.org/3/library/time.html
start_time = time.time()

# Define the range and number of threads
n = 10000
num_threads = 4
step = n // num_threads

threads = []

# Create and start threads
for i in range(num_threads):
    start = i * step + 1
    end = (i + 1) * step if i < num_threads - 1 else n

    # threading api: https://docs.python.org/3/library/threading.html
    thread = threading.Thread(target=count_divisors, args=(start, end))
    threads.append(thread)
    thread.start()

# Wait for all threads to finish
for thread in threads:
    thread.join()

# time api: https://docs.python.org/3/library/time.html
end_time = time.time()

# Print the results
print(f"The number with the most divisors is {
    number_with_max_divisors} with {max_divisors} divisors.")
print(f"Time taken: {end_time - start_time:.4f} seconds.")
