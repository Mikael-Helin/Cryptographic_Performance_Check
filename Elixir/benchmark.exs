defmodule Benchmark do
  @data_path "../data/100MB.txt"

  def run do
    sample_sizes = [100, 1024, 10240, 102400, 1024 * 1024, 10 * 1024 * 1024]
    rounds = 10

    IO.puts("Benchmarking...")
    IO.puts("")
    IO.puts("Number of rounds: #{rounds}")
    IO.puts("")

    for sample_size <- sample_sizes do
      {min_time, avg_time, max_time} = benchmark(sample_size, rounds)
      IO.puts("Sample size: #{sample_size} bytes")
      IO.puts("Min time: #{min_time} s")
      IO.puts("Average time: #{avg_time} s")
      IO.puts("Max time: #{max_time} s")
      IO.puts("")
    end
  end

  defp benchmark(sample_size, rounds) do
    data_list = create_data_list(sample_size)

    times = for _ <- 1..rounds do
      time_hashes(data_list)
    end

    min_time = Enum.min(times)
    avg_time = Enum.sum(times) / length(times)
    max_time = Enum.max(times)
    
    {min_time, avg_time, max_time}
  end

  defp create_data_list(sample_size) do
    # Read data as a binary, process it as binary slices
    data = File.read!(@data_path)
    num_samples = div(byte_size(data), sample_size)

    for i <- 0..(num_samples - 1) do
      binary_part(data, i * sample_size, sample_size)
    end
  end

  defp time_hashes(data_list) do
    start_time = :os.system_time(:microsecond)

    _ = Enum.map(data_list, &compute_hash/1)

    end_time = :os.system_time(:microsecond)
    time_taken = (end_time - start_time) / 1_000_000
    time_taken
  end

  defp compute_hash(data) do
    :crypto.hash(:sha256, data)
  end
end

Benchmark.run()