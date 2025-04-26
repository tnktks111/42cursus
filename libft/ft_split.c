#include "libft.h"

static char ft_count(char const *s, char c)
{
    size_t cnt;

    cnt = 0;
    while (*s)
    {
        if (*s != c)
        {
            cnt++;
            while(*s && *s != c)
                s++;
        }
        else
            s++;
    }
    return (cnt);
}

static char *word_splitter(char const *s, char c)
{
    size_t i;
    char *word;

    i = 0;
    while (s[i] && s[i] != c)
        i++;
    word = malloc(i + 1);
    if (!word)
        return (NULL);
    word[i] = '\0';
    i = 0;
    while (s[i] && s[i] != c)
    {
        word[i] = s[i];
        i++;
    }
    return (word);
}

static void free_words(char **words, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
    {
        free(words[i++]);
    }
    free(words);
}

char **ft_split(char const *s, char c) 
{
    size_t i;
    size_t j;
    size_t len;
    char **words;

    if (!s || !s[0] || ft_count(s, c) == 0)
    {
        words = (char **)malloc(sizeof(char *));
        if (!words)
            return (NULL);
        words[0] = (NULL);
        return (words);
    }
    len = ft_count(s, c);
    words = (char **)malloc(sizeof(char *) * (len + 1));
    if (!words)
        return (NULL);
    words[len] = NULL;
    i = 0;
    j = 0;
    while (i < len)
    {
        while (s[j] && s[j] == c)
            j++;
        words[i] = word_splitter(&s[j], c);
        if (!words[i++])
        {
            free_words(words, i);
            return (NULL);
        }
        while (s[j] && s[j] != c)
            j++;
    }
    return (words);
}

// #include <stdio.h>
// int main()
// {
//     char **words = ft_split("aaaaaaa", 'a');
//     printf("%s", words[0]);
// }