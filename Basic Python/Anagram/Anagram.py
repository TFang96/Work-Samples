def main():
    word1 = input("Please enter a word... ")
    word2 = input("Please enter another word... ")
    if is_anagram(word1, word2):
        print(word1 + " and " + word2 + " are anagrams.")
    else:
        print(word1 + " and " + word2 + " are not anagrams.")


def is_anagram(word1, word2):
    word_data1 = create_data_dictionary(word1)
    word_data2 = create_data_dictionary(word2)
    for k in word_data1:
        if word_data2.get(k) != word_data1[k]:
            return False
    for k in word_data2:
        if word_data1.get(k) != word_data2[k]:
            return False
    return True


def create_data_dictionary(word):
    word_data = {}
    for c in word:
        if c in word_data:
            word_data[c] = word_data[c] + 1
        else:
            word_data[c] = 1
    return word_data


main()
