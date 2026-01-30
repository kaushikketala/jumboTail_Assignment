# jumboTail_Assignment
Search bar Architechture


final 1 :
this include a search bar idea how to search a given string with in the given set of strings or the large amount of data

Why Trie for a Search Bar?

Compared to arrays or maps:

Operation	  Array	HashMap	Trie
Insert word	O(n)	O(n)	O(L)
Prefix search	O(n·L)	-	O(L)
Autocomplete	Hard	-	Easy

Where L = length of word
Trie is optimal for prefix-based searching

Inserting a Word into Trie
Algorithm

Start at root

For each character:

If child exists → move

Else → create new node

Mark last node as isEnd = true


Prefix Search (Core of Search Bar)
Goal

Given prefix "ip", find all words starting with "ip"

Steps

Traverse trie using prefix characters

If path breaks → no result

From last node, DFS to collect words

Here in this way we collect the respective serachbar options to get the results

Final 2:

this actually builds a better way of detectecting the words or strings even if there is a bias in the spelling 

for this we use a fuzzy logic

the fuzzy logic is as given:

For strings, closeness is usually measured by:

Number of character edits needed to transform one string into another

This is called approximate string matching.

Edit Distance

Fuzzy matching is based on Edit Distance, usually Levenshtein Distance.

Definition

The minimum number of edits required to convert one string into another.

Allowed edits:

Insert a character

Delete a character

Replace a character


How Fuzzy Matching Works Conceptually


System:

Computes edit distance between "ifone" and each word

Filters words with distance ≤ threshold (e.g., 1 or 2)

Returns those words

We Use a Threshold (K)

We define:

K = maximum allowed edits


Typical values:

K = 1 → small typos

K = 2 → larger mistakes

K > 2 → expensive and noisy

Most search bars use K = 1 or 2


for final3:

this gives me a recommendation based on the frequency of occuring
do this helps to get a better understanding how frequent the product is bought

we just increment the frequency whenever the product is bought.

The similar thing can be extended to more data because its of time O(N) this actually helps a lot and also with the data retrival fastly.
