import random

def generate_random_numbers_file(file_path, num_numbers, min_value, max_value):
    with open(file_path, 'w') as file:
        for _ in range(num_numbers):
            random_number = random.randint(min_value, max_value)
            file.write(f"{random_number}\n")

if __name__ == "__main__":
    file_name = "textfile"
    num_numbers = 1000
    min_value = 0
    max_value = 4999

    generate_random_numbers_file(file_name, num_numbers, min_value, max_value)
    print(f"Generated {num_numbers} random numbers in '{file_name}'")
