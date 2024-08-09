import os
import hashlib
import time

def create_data_list(sample_size):
    data_path = os.path.join("..", "data", "100MB.txt")
    with open(data_path, "r") as f:
        data_string = f.read()
    num_samples = len(data_string) // sample_size
    data_list = [data_string[i*sample_size:(i+1)*sample_size] for i in range(num_samples)]
    return data_list

def compute_hash(data):
    hash_object = hashlib.sha256(data.encode())
    hash_value = hash_object.hexdigest()
    return hash_value

def time_hashes(data_list):
    start_time = time.time()
    _ = [compute_hash(data) for data in data_list]
    end_time = time.time()
    time_taken = end_time - start_time
    return time_taken

def benchmark(sample_size, rounds):
    data_list = create_data_list(sample_size)
    times = []
    for _ in range(rounds):
        time_taken = time_hashes(data_list)
        times.append(time_taken)
    average_time = sum(times) / len(times)
    return min(times), average_time, max(times)


sample_sizes = [100, 1024, 10240, 102400, 1024*1024, 10*1024*1024]

print ("Benchmarking...")
print()
rounds = 10
print(f"Number of rounds: {rounds}")
print()

for sample_size in sample_sizes:
    min_time, avg_time, max_time = benchmark(sample_size, 10)
    print(f"Sample size: {sample_size} bytes")
    print(f"Min time: {min_time:.6f} s")
    print(f"Average time: {avg_time:.6f} s")
    print(f"Max time: {max_time:.6f} s")
    print()
