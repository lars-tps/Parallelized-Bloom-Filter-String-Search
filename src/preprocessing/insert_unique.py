uniques_filename = 'unique_wordlist.txt'
another_filename = 'ITALIAN.txt'

definitely_not_there_ls = []

with open(uniques_filename, 'r', encoding='utf-8') as f:
    with open(another_filename, 'r', encoding='utf-8') as g:
        words = f.read().split('\n')
        other_words = g.read().split('\n')

        unique_words = set(words)
        other_unique_words = set(other_words)

        for word in other_unique_words:
            if word not in unique_words:
                definitely_not_there_ls.append(word)
        
        f.close()
        g.close()

for word in definitely_not_there_ls:
    output = open('definitely_not_there.txt', 'a', encoding='utf-8')
    output.write(word + ' 0' + '\n')
    output.close()
