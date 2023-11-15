# ankify
CLI Tool for managing  and processing notes - includes modes for learning/review, self-testing(including an 'overkill' mode') and functionality to format the notes ready for import into Anki. This tool can utilise the gpt-3.5 API also to format regular prose notes into flashcard format suitable for Ankify.

# .txt file format

Ankify is intended for use with .txt files consisting of question and answer pairs to construct flashcards. These text files should be formatted as follows, with each side of the card contained on a single line. Blank lines can separate each of the cards and these will be ignored by ankify.

<pre>
Front of first card
Back of first card

Front of second card
Back of second card

Front of third card
Back of third card
</pre>

A 'real' example follows:

<pre>
What does it mean to say that arrays are stored 'contiguously' in memory? 
This means that the blocks of data are all adjacent to each other in memory. If an element of 4 bytes is stored at location '1000', then the next element starts at location 1004

To what two files in Linux do programs send their outputs?
stdout and stderr

What does an HTTP status code of 401 indicate?
HTTP status code 401 indicates "Unauthorized." - valid credentials have not been included in the 'Authorization' header
</pre>

# N.B. ankify uses TABS or '\t' to format notes for import into anki, it is recommended NOT to have tabs in your notes if you intend to use this formatting feature

# usage

ankify \[option] \[filename.txt]

