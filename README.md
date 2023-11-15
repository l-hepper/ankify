# ankify
CLI Tool for managing  and processing notes - includes modes for learning/review, self-testing(including an 'overkill' mode') and functionality to format the notes ready for import into Anki. This tool can utilise the gpt-3.5 API also to format regular prose notes into flashcard format suitable for Ankify.

# .txt file format

Ankify is intended for use with .txt files consisting of question and answer pairs to construct flashcards. These text files should be formatted as follows, with each side of the card 

<pre>
Front of first card
Back of first card

Front of second card
Back of second card

Front of third card
Back of third card
</pre>

# usage

Ankify has three main modes, review, prompt, and overkill.

To use