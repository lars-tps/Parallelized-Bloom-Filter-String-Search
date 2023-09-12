
with open('query.txt', 'r', encoding='utf-8') as f:
    with open('result.txt', 'r', encoding='utf-8') as g:
        query_words = f.read().split('\n')
        result_words = g.read().split('\n')
        set_query_words = set(query_words)
        set_result_words = set(result_words)
        false_positives = []

        for word in set_result_words:
            if word not in set_query_words:
                false_positives.append(word)

        print(((len(set_query_words)-len(false_positives))/len(set_result_words))*100)
        f.close()
        g.close()