#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <time.h>
#include <openssl/evp.h>  // Include the EVP header

// Function to read the file and create a list of data strings
char** create_data_list(size_t sample_size, int* num_samples) {
    FILE* file = fopen("../data/100MB.txt", "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Get the length of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file into a buffer
    char* data_string = (char*)malloc(file_size + 1);
    if (!data_string) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
    fread(data_string, 1, file_size, file);
    data_string[file_size] = '\0';
    fclose(file);

    // Calculate the number of samples and allocate the list
    *num_samples = file_size / sample_size;
    char** data_list = (char**)malloc(*num_samples * sizeof(char*));
    if (!data_list) {
        perror("Failed to allocate memory for data list");
        free(data_string);
        exit(EXIT_FAILURE);
    }

    // Populate the data list with substrings
    for (int i = 0; i < *num_samples; i++) {
        data_list[i] = strndup(data_string + i * sample_size, sample_size);
        if (!data_list[i]) {
            perror("Failed to allocate memory for sample");
            free(data_string);
            for (int j = 0; j < i; j++) {
                free(data_list[j]);
            }
            free(data_list);
            exit(EXIT_FAILURE);
        }
    }

    free(data_string);
    return data_list;
}

// FASTER HASHING ALGORITHM
//
// Function to compute the SHA-256 hash of a string
// void compute_hash(const char* data, unsigned char output[SHA256_DIGEST_LENGTH]) {
//    SHA256_CTX sha256;
//    SHA256_Init(&sha256);
//    SHA256_Update(&sha256, data, strlen(data));
//    SHA256_Final(output, &sha256);
//}

void compute_hash(const char* data, unsigned char output[SHA256_DIGEST_LENGTH]) {
    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    unsigned int md_len;

    // Create and initialize the context
    mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        perror("Failed to create context");
        exit(EXIT_FAILURE);
    }

    // Select the digest algorithm (SHA-256)
    md = EVP_sha256();
    if (md == NULL) {
        perror("Failed to get SHA-256 digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Initialize the digest operation
    if (EVP_DigestInit_ex(mdctx, md, NULL) != 1) {
        perror("Failed to initialize digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Provide the message to be hashed
    if (EVP_DigestUpdate(mdctx, data, strlen(data)) != 1) {
        perror("Failed to update digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Finalize the digest and obtain the output
    if (EVP_DigestFinal_ex(mdctx, output, &md_len) != 1) {
        perror("Failed to finalize digest");
        EVP_MD_CTX_free(mdctx);
        exit(EXIT_FAILURE);
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);
}

// Function to time the hash computation for a list of data strings
double time_hashes(char** data_list, int num_samples) {
    clock_t start_time = clock();

    for (int i = 0; i < num_samples; i++) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        compute_hash(data_list[i], hash);
    }

    clock_t end_time = clock();
    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}

// Function to benchmark the hashing with a given sample size and number of rounds
void benchmark(size_t sample_size, int rounds) {
    int num_samples;
    char** data_list = create_data_list(sample_size, &num_samples);

    double times[rounds];
    for (int i = 0; i < rounds; i++) {
        times[i] = time_hashes(data_list, num_samples);
    }

    double min_time = times[0], max_time = times[0], sum_time = 0;
    for (int i = 0; i < rounds; i++) {
        if (times[i] < min_time) min_time = times[i];
        if (times[i] > max_time) max_time = times[i];
        sum_time += times[i];
    }
    double avg_time = sum_time / rounds;

    printf("Sample size: %zu bytes\n", sample_size);
    printf("Min time: %.6f s\n", min_time);
    printf("Average time: %.6f s\n", avg_time);
    printf("Max time: %.6f s\n", max_time);
    printf("\n");

    for (int i = 0; i < num_samples; i++) {
        free(data_list[i]);
    }
    free(data_list);
}

int main() {
    size_t sample_sizes[] = {100, 1024, 10240, 102400, 1024*1024, 10*1024*1024};
    int rounds = 10;

    printf("Benchmarking...\n\n");
    printf("Number of rounds: %d\n\n", rounds);

    for (int i = 0; i < sizeof(sample_sizes)/sizeof(sample_sizes[0]); i++) {
        benchmark(sample_sizes[i], rounds);
    }

    return 0;
}
