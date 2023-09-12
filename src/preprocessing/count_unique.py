
filenames = [f'250000_WORDS_{i}.txt' for i in range(0, 5)]
for filename in filenames:
    with open(filename, 'r', encoding='utf-8') as f:
        words = f.read().split('\n')

        unique_words = set(words)
        print(len(unique_words))